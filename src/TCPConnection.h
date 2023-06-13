#ifndef CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H
#define CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H

class TCPConnection{
private:
    int cwnd;       //congestion window
    int ssthresh;   //slow start threshold
    int rtt;        //round trip time
public:
    TCPConnection();

    void SendData();
    void onPacketLost();
    void onRTTUpdate(int rtt);

    int getCwnd();
    int getSsthresh();
    int getRTT();
    void setCwnd(int cwnd);
    void setSsthresh(int ssthresh);
    void setRTT(int rtt);
};

#endif //CONGESTIONCONTROLALGORITHMS_TCPCONNECTION_H
