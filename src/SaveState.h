#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>

#ifndef SAVE_STATE_H
#define SAVE_STATE_H

void save_state(std::string file_name, double time, int cwnd);


#endif //SAVE_STATE_H