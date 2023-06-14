#include <vector>

#ifndef CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H
#define CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H

class TCPConnection{
private:
    int cwnd;                    //congestion window
    int ssthresh;                //slow start threshold
    int rtt;                     //round trip time
    std::vector<int> sent_data;  //sent data -ack
    int last_sent;               //last sent packet
public:
    TCPConnection();

    int SendData(int size=1); // TODO: need work: 1. handle segment, 2. handle window size
    void onPacketLost();
    void onRTTUpdate(int rtt);
    void onAck(int ack);

    int getCwnd();
    int getSsthresh();
    int getRTT();
    void setCwnd(int cwnd);
    void setSsthresh(int ssthresh);
    void setRTT(int rtt);
};

#endif //CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H
