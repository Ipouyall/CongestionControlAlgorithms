#include <cmath>
#include <iostream>

#ifndef UTILSS_H
#define UTILSS_H

struct Packet {
    int data;
    bool is_sent;
    bool is_ack;
    bool is_sack;
    int index;
};

struct SlidingWindow {
    int last_ack;
    int last_written;
    int last_sent;

};

bool loose_packet(int num, int lower_bound, int upper_bound);

#endif //UTILSS_H