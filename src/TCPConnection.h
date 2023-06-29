#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "SaveState.h"

#ifndef CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H
#define CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H

//This is Reno

struct Packet {
    int data;
    bool is_sent;
    bool is_ack;
};
class TCPConnection {
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
    TCPConnection();

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

#endif //CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H