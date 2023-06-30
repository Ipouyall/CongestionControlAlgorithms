#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <climits>
#include <utility>
#include "Utils.h"
#include "TCPConnection.h"
#include "SaveState.h"

#ifndef RENO_H
#define RENO_H

//This is Reno

class Reno : public TCPConnection{
private:
    // bool fast_retransmit;
    // int cwnd;                    //congestion window
    // int ssthresh;                //slow start threshold
    // int rtt;                     //round trip time
    // std::vector<Packet> sent_data;  //sent data
    // double curr_time;
    // double wait_time;
    // int time_out;
    // bool fast_recovery;
    // SlidingWindow window;
public:
    Reno();
    Reno(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_);
    virtual std::vector<Packet> SendData(std::pair<int, bool> lost_packet_verified);
    virtual std::pair<int, bool> onPacketLost(std::vector<Packet>& packets, std::pair<int, bool> last_lost_packet_verified);
    virtual void onRTTUpdate(std::pair<int, bool>& lost_packet_verified);
    void showPacketsSent(const std::vector<Packet>& packets);
    void showLostPacket(const std::pair<int, bool>& lost_packet_verified);
    void showSlidingWindow();
    virtual void simulate();
};

#endif //RENO_H