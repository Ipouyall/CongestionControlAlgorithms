#include "NewReno.h"

using namespace std;

TCPNewRenoConnection::TCPNewRenoConnection() {
    cwnd = 1;
    ssthresh = INT_MAX;
    rtt = 2;
    last_sent = 0;

    lost_rate = 0.0001;
    curr_time = 0;
    wait_time = 0;
    time_out = 2 * rtt;
    fast_recovery = true;
}

vector<Packet> TCPNewRenoConnection::SendData(int packet_losts) {
    vector<Packet> data;
    if (packet_losts > 0)
        return data;
    for (int i = 0; i < cwnd; i++) {
        data.push_back(Packet{ rand(), true, false });
    }
    return data;
}
bool TCPNewRenoConnection::timeOut() {
    return wait_time * rtt >= time_out;
}
void TCPNewRenoConnection::onRTTUpdate(int& packet_losts) {
    save_state("tcp_reno.csv", curr_time, cwnd);
    if (wait_time > 0)
        cout << "hi";
    if (packet_losts > 0 && packet_losts < cwnd - 3 && fast_recovery) {
        curr_time += 0.3 * rtt;
        save_state("tcp_reno.txt", curr_time, cwnd);
        ssthresh = cwnd / 2;
        cwnd = ssthresh;
        packet_losts = 0;
        return;
    }
    else if (packet_losts > 0 || wait_time > 0) {
        if (timeOut()) {
            wait_time = 0;
            ssthresh = cwnd / 2;
            cwnd = 1;
            packet_losts = 0;
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
int TCPNewRenoConnection::onPacketLost(std::vector<Packet>& packets) {
        int lost_count = 0;
    int sent_packet = cwnd;
    for (int i = 0; i < packets.size(); i++) {
        //using namespace std::this_thread; // sleep_for, sleep_until
        //using namespace std::chrono; // nanoseconds, system_clock, seconds

        //sleep_for(nanoseconds(10));
        //sleep_until(system_clock::now() + seconds(1));
        double rand_num = (double)rand() / RAND_MAX;
        double frac = (sent_packet / 1000.0);
        // cout << "hi\n";
        if ((pow(frac, 10) > rand_num)) {
            packets[i].is_ack = false;
            lost_count++;
            sent_packet--;
        }
    }
    return lost_count;
}
int TCPNewRenoConnection::getCwnd() {
    return cwnd;
}

int TCPNewRenoConnection::getSsthresh() {
    return ssthresh;
}

int TCPNewRenoConnection::getRTT() {
    return rtt;
}

void TCPNewRenoConnection::setCwnd(int cwnd) {
    this->cwnd = cwnd;
}

void TCPNewRenoConnection::setSsthresh(int ssthresh) {
    this->ssthresh = ssthresh;
}

void TCPNewRenoConnection::setRTT(int rtt) {
    this->rtt = rtt;
}