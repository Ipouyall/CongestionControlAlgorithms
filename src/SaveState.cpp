#include "SaveState.h"

using namespace std;

void save_state(std::string file_name, double time, int cwnd) {
	std::ofstream outfile;

	outfile.open(file_name, std::ios_base::app);
	outfile << time << ", " << cwnd << endl;
	outfile.close();
}