#include <cmath>
#include <iostream>
#include "TCPConnection.h"
#ifndef BBR_H
#define BBR_H


//This is Reno

const std::string BBR_FILE = "tcp_bbr.csv";

float RandomFloat(float a, float b);

enum class BBRPhase {
    Startup,
    Drain,
    ProbeBW,
    ProbeRTT
};

class BBR : public TCPConnection {
private:
    BBRPhase phase;
    double reduce_percent;
    int bw_phase_wait;
    int rtt_phase_wait;
    int bw_incresing_percent;
    int last_cwnd;
    double min_rtt;
    double bandwidth;
    bool ok;
public:
    BBR();
    BBR(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_);
    virtual std::vector<Packet> SendData();
    virtual std::pair<int, bool> onPacketLost(std::vector<Packet>& packets, std::pair<int, bool> last_lost_packet_verified);
    virtual void onRTTUpdate(std::pair<int, bool>& lost_packet_verified);
    void showPacketsSent(const std::vector<Packet>& packets);
    void showLostPacket(const std::pair<int, bool>& lost_packet_verified);
    void showSlidingWindow();
    virtual void simulate();
    double estRTT();
};

#endif //BBR_H