#include "BBR.h"

using namespace std;

float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
BBR::BBR()
    :TCPConnection()
{
    phase = BBRPhase::Startup;
    reduce_percent = 20;
    bw_phase_wait = 25;
    bw_incresing_percent = 25;
    rtt_phase_wait = 5;
    bandwidth = 100;
}

BBR::BBR(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_)
    : TCPConnection(cwnd_, rtt_, time_out_, fast_retransmit_, fast_recovery_)
{
    phase = BBRPhase::Startup;
    reduce_percent = 20;
    bw_phase_wait = 25;
    bw_incresing_percent = 25;
    rtt_phase_wait = 5;
    bandwidth = 100;
}



vector<Packet> BBR::SendData() {
    vector<Packet> data;
    int count = 0;
    if (wait_time != 0)
        return data;
    for (int i = 0; i < cwnd; i++) {
        data.push_back(Packet{ rand(), true, false, false, i });
    }
    return data;
}

void BBR::onRTTUpdate(pair<int, bool>& lost_packet_verified) {
    curr_time += rtt;
    if (phase == BBRPhase::ProbeRTT || phase == BBRPhase::ProbeBW)
        return;
    //if (phase ==  BBRPhase::ProbeBW) {
    //    cwnd += (cwnd * 0.2);
    //}

    if (lost_packet_verified.first == -1) {
        if (cwnd >= ssthresh)
            cwnd++;
        else
            cwnd *= 2;
    }
    
}
double BBR::estRTT() {
    return RandomFloat(30, 100);
}
pair<int, bool> BBR::onPacketLost(std::vector<Packet>& packets, pair<int, bool> last_lost_packet_verified) {
    int lost_count = 0;
    int dup_ack = 0;
    pair<int, bool> lost_packet_verified = { -1, false };
    for (int i = 0; i < cwnd; i++) {
        if (loose_packet(cwnd, 1, 1000)) {
            if (lost_packet_verified.first == -1) {
                lost_count++;
                lost_packet_verified.first = i;
                break;
            }
        }
    }
    if (phase == BBRPhase::ProbeBW) {
        if (bw_phase_wait == 0) {
            phase = BBRPhase::ProbeRTT;
            bw_phase_wait = 20;
            last_cwnd = cwnd;
            return last_lost_packet_verified;
        }
        float est = bandwidth * estRTT();
        if (est != bandwidth * min_rtt)
            ok = !ok;

        if (ok)
            cwnd *= 1.25;
        else
            cwnd *= 0.8;
        bw_phase_wait--;
    }
    if (phase == BBRPhase::ProbeRTT) {
        if (rtt_phase_wait == 0) {
            phase = BBRPhase::ProbeBW;
            rtt_phase_wait = 5;
            cwnd = last_cwnd;
            return last_lost_packet_verified;
        }
        cwnd = 10;
        min_rtt = min(min_rtt, estRTT());
        rtt_phase_wait--;
        return last_lost_packet_verified;
    }
    if (lost_packet_verified.first != -1) {
        if (phase == BBRPhase::Startup) {
            phase = BBRPhase::Drain;
            return lost_packet_verified;
        }
        if (phase == BBRPhase::Drain) {
            cwnd -= floor(cwnd * (reduce_percent / 100.0));
            reduce_percent--;
        }
    }
    else {
        if (phase == BBRPhase::Drain)
            phase = BBRPhase::ProbeBW;
        if (phase == BBRPhase::Startup) {
            cwnd *= 2;
        }
    }
    

    return lost_packet_verified;
}
void BBR::showPacketsSent(const std::vector<Packet>& packets) {
    cout << "Packets sent:" << endl;
    for (int i = 0; i < (int)packets.size(); i++) {
        if (i == (int)packets.size() - 1)
            cout << packets[i].index;
        else
            cout << packets[i].index << ", ";
    }
    cout << endl;
}
void BBR::showLostPacket(const pair<int, bool>& lost_packet_verified) {
    if (lost_packet_verified.first != -1) {
        cout << "Packet " << lost_packet_verified.first << " lost." << endl;
        if (lost_packet_verified.second)
            cout << "3 duplicate Ack received!" << endl;
    }
}
void BBR::showSlidingWindow() {
    cout << "Sliding window: " << endl;
    cout << "lastAck = " << window.last_ack << "::" << "last sent = " <<
        window.last_sent << "::" << "last written = " << window.last_written << endl;
}

void BBR::simulate() {
    pair<int, bool> lost_packet_verified = { -1, false };
    TCPConnection::createPackets(1000);
    int x = 0;
    while (window.last_ack != window.last_written && x < 1000) {
        save_state(BBR_FILE, curr_time, cwnd);
        TCPConnection::showState();
        vector<Packet> packets = SendData();
        //showSlidingWindow();
        lost_packet_verified = onPacketLost(packets, lost_packet_verified);
        //showLostPacket(lost_packet_verified);
        onRTTUpdate(lost_packet_verified);
        cout << x << endl;
        x++;
    }
}

