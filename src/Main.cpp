#include <iostream>
// #include "TCPConnection.h"
#include "NewReno.h"

using namespace std;

void run() {
    TCPNewRenoConnection con;
    int losts = 0;
    for (int i = 0; i < 2000; i++) {
        vector<Packet> packets = con.SendData(losts);
        losts = con.onPacketLost(packets);
        con.onRTTUpdate(losts);
        //Sleep(con.getCwnd()/ 100);
    }
}
int main() {
    srand(time(NULL));
    cout << "hello world!" << endl;
    run();
    return 0;
}