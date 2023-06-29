#include "TCPConnection.h"

using namespace std;

TCPConnection::TCPConnection() {
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

vector<Packet> TCPConnection::SendData(int packet_losts) {
    vector<Packet> data;
    if (packet_losts > 0)
        return data;
    for (int i = 0; i < cwnd; i++) {
        data.push_back(Packet{ rand(), true, false });
    }
    return data;
}
bool TCPConnection::timeOut() {
    return wait_time * rtt >= time_out;
}
void TCPConnection::onRTTUpdate(int& packet_losts) {
    save_state("tcp_new_reno.csv", curr_time, cwnd);
    if (wait_time > 0)
        cout << "hi";
    if (packet_losts > 0 && packet_losts < cwnd - 3 && fast_recovery) {
        curr_time += 0.3 * rtt;
        //save_state("tcp_new_reno.csv", curr_time, cwnd);
        ssthresh = ceil((1.0 * cwnd) / (1LL << packet_losts));
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
int TCPConnection::onPacketLost(std::vector<Packet>& packets) {
    int lost_count = 0;
    int sent_packet = cwnd;
    for (int i = 0; i < packets.size(); i++) {
        //using namespace std::this_thread; // sleep_for, sleep_until
        //using namespace std::chrono; // nanoseconds, system_clock, seconds

        //sleep_for(nanoseconds(10));
        //sleep_until(system_clock::now() + seconds(1));
        double rand_num = (double)rand() / RAND_MAX;
        double frac = (sent_packet / 1000.0);
        if ((pow(frac, 10) > rand_num)) {
            packets[i].is_ack = false;
            lost_count++;
            sent_packet--;
        }
    }
    return lost_count;
    //double rand_num = (double)rand() / RAND_MAX;
    //double frac = (cwnd / 1000.0);
    //if (pow(frac, 10)> rand_num)
    //    return 1;
    //else
    //    return 0;
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