#include <iostream>
#include "Reno.h"
#include "NewReno.h"

using namespace std;


int main() {
    srand(time(NULL));
    cout << "hello world!" << endl;
    Reno con;
    con.simulate();
    cout << "____________________________________________________________________________" << endl << endl;
    NewReno con2;
    con2.simulate();
    return 0;
}