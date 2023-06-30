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

void TCPConnection::showState(){
        cout << "cwnd = " << cwnd << "::" << "time = " << curr_time << "::" << "wait time = " << wait_time <<
         "::" << "ssthresh = " << ssthresh << endl;
}

void TCPConnection::simulate() {
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
bool TCPConnection::timeOut() {
    return wait_time * rtt >= time_out;
}
