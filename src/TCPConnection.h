#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <climits>
#include <utility>
#include "Utils.h"
#include "SaveState.h"

#ifndef CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H
#define CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H

//This is Reno

class TCPConnection {
protected:
    bool fast_retransmit;
    int cwnd;                    //congestion window
    int ssthresh;                //slow start threshold
    int rtt;                     //round trip time
    std::vector<Packet> sent_data;  //sent data
    double curr_time;
    double wait_time;
    int time_out;
    bool fast_recovery;
    SlidingWindow window;
public:
    TCPConnection();
    TCPConnection(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_);
    virtual void createPackets(int count);
    virtual std::vector<Packet> SendData(std::pair<int, bool> lost_packet_verified) = 0;
    virtual std::pair<int, bool> onPacketLost(std::vector<Packet>& packets, std::pair<int, bool> last_lost_packet_verified) = 0;
    virtual void onRTTUpdate(std::pair<int, bool>& lost_packet_verified) = 0;
    bool timeOut();

    int getCwnd();
    int getSsthresh();
    int getRTT();
    void setCwnd(int cwnd);
    void setSsthresh(int ssthresh);
    void setRTT(int rtt);
    virtual void simulate();
};

#endif //CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H