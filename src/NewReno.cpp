#include "NewReno.h"

using namespace std;


NewReno::NewReno() :Reno() {

}

NewReno::NewReno(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_)
            :Reno(cwnd_, rtt_, time_out_, fast_retransmit_, fast_recovery_)  {
}


vector<Packet> NewReno::SendData() {
    vector<Packet> data;
    int count = 0;
    if (wait_time != 0)
        return data;
    for (int i = window.last_ack + 1; i <= window.last_written; i++) {
        if (count == cwnd)
            return data;
        if (sent_data[i].is_sack && sent_data[i].is_ack == false) {
            sent_data[i].is_sent = true;
            data.push_back(sent_data[i]);
        }
        else if (sent_data[i].is_ack == false && !sent_data[i].is_sack) {
            sent_data[i].is_sent = true;
            data.push_back(sent_data[i]);
            count++;
            window.last_sent = i;
        }
    }
    return data;
}


pair<int, bool> NewReno::onPacketLost(std::vector<Packet>& packets, pair<int, bool> last_lost_packet_verified) {
    int lost_count = 0;
    int dup_ack = 0;
    vector<Packet> sack_packets;
    pair<int, bool> lost_packet_verified = {-1, false};
    for (int i = 0; i < (int) packets.size(); i++) {
        if (packets[i].is_sack && !packets[i].is_ack && lost_packet_verified.first != -1) {
            window.last_ack++;
            packets[i].is_ack = true;
            sent_data[packets[i].index].is_ack = true;
            continue;
        }
        if (loose_packet(cwnd, 1, 1000)) {
            if (lost_packet_verified.first == -1) {
                lost_packet_verified.first = packets[i].index;
                packets[i].is_ack = false;
                lost_count++;
            }
        }
        else {
            if (lost_packet_verified.first != -1) {
                packets[i].is_sack = true;
                sent_data[packets[i].index].is_sack = true;
                sack_packets.push_back(sent_data[packets[i].index]);
                if (dup_ack == 2 && fast_retransmit) {
                    lost_packet_verified.second = true;
                }
                else {
                    dup_ack++;
                }
            }
            else {
                window.last_ack++;
                packets[i].is_ack = true;
                sent_data[packets[i].index].is_ack = true;
            }
        }
    }

    if (lost_packet_verified.first != -1 && lost_packet_verified.second) {
        curr_time += 0.3 * rtt;
        ssthresh = cwnd / 2;
        if (fast_recovery)
            cwnd = ssthresh;
        else
            cwnd = 1;
    }
    else if (lost_packet_verified.first != -1  || wait_time > 0) {
        if (wait_time > 0)
            lost_packet_verified = last_lost_packet_verified;
        if (TCPConnection::timeOut()) {
            cout << "Time out occured!" << endl;
            wait_time = 0;
            ssthresh = cwnd / 2;
            cwnd = 1;
        }
        else {
            wait_time++;
        }
    }

    showSackPackets(sack_packets, lost_packet_verified);
    return lost_packet_verified;
}

void NewReno::showSackPackets(const std::vector<Packet>& sack_packet,
    std::pair<int, bool> last_lost_packet_verified) {
    if ((int)sack_packet.size() == 0)
        return;
    cout << "Packet " << last_lost_packet_verified.first << "'s ack not received." << endl;
    cout << "Sack received for packets: ";
    for (int i = 0; i < (int)sack_packet.size(); i++) {
        if (i == (int)sack_packet.size())
            cout << sack_packet[i].index;
        else
            cout << sack_packet[i].index << ", ";
    }
    cout << endl;

}
void NewReno::simulate() {
    pair<int, bool> lost_packet_verified = { -1, false };
    Reno::createPackets(100000);
    while (window.last_ack != window.last_written || sent_data[sent_data.size() - 1].is_sack) {
        save_state(NEW_RENO_FILE, curr_time, cwnd);
        Reno::showState();
        vector<Packet> packets = SendData();
        Reno::showSlidingWindow();
        //Reno::showPacketsSent(packets);
        lost_packet_verified = onPacketLost(packets, lost_packet_verified);
        Reno::showLostPacket(lost_packet_verified);
        Reno::onRTTUpdate(lost_packet_verified);
    }
}


