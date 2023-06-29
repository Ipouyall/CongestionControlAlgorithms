#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <climits>
#include "SaveState.h"

#ifndef CONGESTIONCONTROLALGORITHMS_TCPNEWRENO_CONNECTION_H
#define CONGESTIONCONTROLALGORITHMS_TCPNEWRENO_CONNECTION_H

//this is New Reno

struct Packet {
    int data;
    bool is_sent;
    bool is_ack;
};
class TCPNewRenoConnection {
private:
    int cwnd;                    //congestion window
    int ssthresh;                //slow start threshold
    int rtt;                     //round trip time
    std::vector<Packet> sent_data;  //sent data
    int last_sent;               //last sent packet
    double lost_rate;
    double curr_time;
    double wait_time;
    int time_out;
    bool fast_recovery;
public:
    TCPNewRenoConnection();

    std::vector<Packet> SendData(int packet_lost);
    int onPacketLost(std::vector<Packet>& packets);
    void onRTTUpdate(int& packet_losts);
    bool timeOut();

    int getCwnd();
    int getSsthresh();
    int getRTT();
    void setCwnd(int cwnd);
    void setSsthresh(int ssthresh);
    void setRTT(int rtt);
};

#endif //CONGESTIONCONTROLALGORITHMS_TCPNEWRENO_CONNECTION_H