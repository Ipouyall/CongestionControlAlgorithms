#include "Utils.h"

using namespace std;

bool loose_packet(int num, int lower_bound, int upper_bound) {
    double ex = (pow(10 * upper_bound, static_cast<float>(num - lower_bound) /
        (upper_bound - lower_bound)) - 1) / (10 * upper_bound - 1);
    int p = static_cast<int>(1000 * ex);
    int random = (rand() % (1000 - 1)) + 1;;
    return random <= p;
}