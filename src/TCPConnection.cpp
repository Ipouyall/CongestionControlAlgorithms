#include "TCPConnection.h"

using namespace std;

TCPConnection::TCPConnection(){
    cwnd = 1;
    ssthresh = 65535;
    rtt = 0;
    last_sent = 0
}

int TCPConnection::SendData(int size) {
    last_sent++;
    sent_data.push_back(last_sent);
    return last_sent
}

void TCPConnection::onAck(int ack) {
    auto it = find(sent_data.begin(), sent_data.end(), ack);
    if (it != sent_data.end())
        sent_data.erase(it);
    else
        return;
    cwnd += 1;
}

void TCPConnection::onRTTUpdate(int rtt) {
    this->rtt = rtt;
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
