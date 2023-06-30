#include "SaveState.h"
#include <sys/stat.h>

using namespace std;

bool directoryExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
        return false;
    return (info.st_mode & S_IFDIR) != 0;
}

bool createDirectory(const std::string& path) {
    return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}

void check_path(std::string path) {
    if (!directoryExists(path))
        createDirectory(path);
}

void save_state(std::string file_name, double time, int cwnd) {
    check_path("results");
    file_name = "results/" + file_name;
	std::ofstream outfile;
	if (time == 0.0)
		outfile.open(file_name);
	else
		outfile.open(file_name, std::ios_base::app);
	outfile << time << ", " << cwnd << std::endl;
	outfile.close();
}