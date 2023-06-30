#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <climits>
#include <utility>
#include "Utils.h"
#include "Reno.h"
#include "SaveState.h"

#ifndef NEW_RENO_H
#define NEW_RENO_H

//This is New Reno

const std::string NEW_RENO_FILE = "tcp_new_reno.csv";

class NewReno :public Reno{
private:
public:
    NewReno();
    NewReno(int cwnd_, int rtt_, int time_out_, bool fast_retransmit_, bool fast_recovery_);
    virtual std::vector<Packet> SendData();
    virtual std::pair<int, bool> onPacketLost(std::vector<Packet>& packets, std::pair<int, bool> last_lost_packet_verified);
    void showSackPackets(const std::vector<Packet>& sack_packet, std::pair<int, bool> last_lost_packet_verified);
    virtual void simulate();
};

#endif //NEW_RENO_H