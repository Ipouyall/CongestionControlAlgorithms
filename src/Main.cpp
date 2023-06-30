#include <iostream>
#include "Reno.h"
#include "NewReno.h"
#include "BBR.h"
using namespace std;


int main() {
    srand(time(NULL));
    cout << "hello world!" << endl;
    Reno con;
    con.simulate();
    cout << "____________________________________________________________________________" << endl << endl;
    NewReno con2;
    con2.simulate();
    cout << "____________________________________________________________________________" << endl << endl;
    BBR con3;
    con3.simulate();

    return 0;
}