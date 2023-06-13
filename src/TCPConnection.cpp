#include "TCPConnection.h"

using namespace std;

TCPConnection::TCPConnection(){
    cwnd = 1;
    ssthresh = 65535;
    rtt = 0;
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
