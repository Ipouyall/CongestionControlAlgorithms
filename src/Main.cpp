#include <iostream>
#include "TCPConnection.h"

using namespace std;


int main() {
    srand(time(NULL));
    cout << "hello world!" << endl;
    TCPConnection con;
    con.simulate();
    return 0;
}