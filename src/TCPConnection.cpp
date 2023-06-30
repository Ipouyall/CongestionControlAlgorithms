#include "TCPConnection.h"

using namespace std;


TCPConnection::TCPConnection() {
    cwnd = 1;
    ssthresh = INT_MAX;
    rtt = 2;
    curr_time = 0;
    wait_time = 0;
    time_out = 2 * rtt;
    fast_recovery = true;
    fast_retransmit = true;
    window.last_ack = -1;
    window.last_sent = -1;
    window.last_written = -1;
}

TCPConnection::TCPConnection(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_) {
    cwnd = cwnd_;
    ssthresh = INT_MAX;
    rtt = rtt_;
    curr_time = 0;
    wait_time = 0;
    time_out = time_out_;
    fast_recovery = fast_recovery_;
    fast_retransmit = fast_retransmit_;
    window.last_ack = -1;
    window.last_sent = -1;
    window.last_written = -1;
}

void TCPConnection::createPackets(int count) {
    for (int i = 0; i < count; i++) {
        sent_data.push_back(Packet{ rand(), false, false, false, i });
        window.last_written++;
    }
}

vector<Packet> TCPConnection::SendData(pair<int, bool> lost_packet_verified) {
    vector<Packet> data;
    int count = 0;
    if (lost_packet_verified.first != -1)
        return data;
    for (int i = window.last_ack + 1; i <= window.last_written; i++) {
        if (count == cwnd)
            return data;
        if (sent_data[i].is_ack == false) {
            sent_data[i].is_sent = true;
            data.push_back(sent_data[i]);
            count++;
            window.last_sent = i;
        }
    }
    return data;
}
bool TCPConnection::timeOut() {
    return wait_time * rtt >= time_out;
}
void TCPConnection::onRTTUpdate(pair<int, bool>& lost_packet_verified) {
    save_state("tcp_reno.csv", curr_time, cwnd);
    cout << "cwnd = " << cwnd << "::" << "time = " << curr_time << "::" << "wait time = " << wait_time << endl;
    if (lost_packet_verified.first != -1 && lost_packet_verified.second) {
        curr_time += 0.3 * rtt;
        ssthresh = cwnd / 2;
        if (fast_recovery)
            cwnd = ssthresh;
        else
            cwnd = 1;
        lost_packet_verified.first = -1;
        lost_packet_verified.second = false;
        return;
    }
    else if (lost_packet_verified.first != -1  || wait_time > 0) {
        if (timeOut()) {
            cout << "Time out occured!" << endl;
            wait_time = 0;
            ssthresh = cwnd / 2;
            cwnd = 1;
            lost_packet_verified.first = -1;
            lost_packet_verified.second = false;
        }
        else {
            wait_time++;
        }
    }
    else {
        if (cwnd >= ssthresh)
            cwnd++;
        else
            cwnd *= 2;
    }
    curr_time += rtt;
}
pair<int, bool> TCPConnection::onPacketLost(std::vector<Packet>& packets, pair<int, bool> last_lost_packet_verified) {
    int lost_count = 0;
    int dup_ack = 0;
    pair<int, bool> lost_packet_verified = {-1, false};
    if (last_lost_packet_verified.first != -1)
        return last_lost_packet_verified;
    for (int i = 0; i < (int) packets.size(); i++) {
        if (loose_packet(cwnd, 1, 1000)) {
            if (lost_packet_verified.first == -1) {
                lost_packet_verified.first = packets[i].index;
                packets[i].is_ack = false;
                lost_count++;
            }
        }
        else {
            if (lost_packet_verified.first != -1) {
                if (dup_ack == 2 && fast_retransmit) {
                    lost_packet_verified.second = true;
                    return lost_packet_verified;
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
    return lost_packet_verified;
}
void TCPConnection::showPacketsSent(const std::vector<Packet>& packets) {
    cout << "Packets sent:" << endl;
    for (int i = 0; i < (int) packets.size(); i++) {
        if (i == (int) packets.size() - 1)
            cout << packets[i].index;
        else
            cout << packets[i].index << ", ";
    }
    cout << endl;
}
void TCPConnection::showLostPacket(const pair<int, bool>& lost_packet_verified) {
    if (lost_packet_verified.first != -1) {
        cout << "Packet " << lost_packet_verified.first << " lost." << endl;
        if (lost_packet_verified.second)
            cout << "3 duplicate Ack received!" << endl;
    }
}
void TCPConnection::showSlidingWindow() {
    cout << "Sliding window: " << endl;
    cout << "lastAck = " << window.last_ack << "::" << "last sent = " <<
        window.last_sent << "::" << "last written = " << window.last_written << endl;
}

void TCPConnection::simulate() {
    int losts = 0;
    pair<int, bool> lost_packet_verified = { -1, false };
    createPackets(100000);
    while (window.last_ack != window.last_written) {
        vector<Packet> packets = SendData(lost_packet_verified);
        showSlidingWindow();
        lost_packet_verified = onPacketLost(packets, lost_packet_verified);
        showLostPacket(lost_packet_verified);
        onRTTUpdate(lost_packet_verified);
    }
}


int TCPConnection::getCwnd() {
    return cwnd;
}

int TCPConnection::getSsthresh() {
    return ssthresh;
}

int TCPConnection::getRTT() {
    return rtt;
}

void TCPConnection::setCwnd(int cwnd) {
    this->cwnd = cwnd;
}

void TCPConnection::setSsthresh(int ssthresh) {
    this->ssthresh = ssthresh;
}

void TCPConnection::setRTT(int rtt) {
    this->rtt = rtt;
}