# CongestionControlAlgorithms
Implementing some of Congestion Control algorithms, 4th CA of The Computer Networks course @ University of Tehran, spring 2023

# Introduction
In this assignment, we would implement 3 Congestion Control algorithms: `Reno`, `New Reno` and `BBR`.

# Algorithms

## Reno
RCP Reno's goal is to ensure fair and efficient sharing of network bandwidth among different TCP connections.

By dynamically adjusting the congestion window based on network conditions and utilizing mechanisms like 
slow start, congestion avoidance, fast recovery, and fast retransmit, TCP Reno attempts to provide 
reliable and efficient data transmission while reacting to network congestion.

**How it works:**
1. low Start: When a TCP connection is established or retransmitted due to packet loss, 
TCP Reno starts in the slow start phase. In this phase, the sender increases the congestion window (cwnd) exponentially, 
doubling it with each successful transmission, until a congestion event occurs.
2. Congestion Avoidance: After the slow start phase, TCP Reno enters the congestion avoidance phase. 
In this phase, the sender increases the cwnd linearly, adding one segment for each successful round-trip time (RTT). 
This gradual increase helps to prevent congestion from occurring too quickly.
3. Congestion Detection: TCP Reno uses a combination of packet loss and acknowledgment information 
to detect network congestion. If a packet loss is detected (e.g., due to a timeout or three duplicate ACKs), 
it indicates congestion in the network.
4. Fast Recovery: When packet loss is detected, TCP Reno performs fast recovery to avoid excessive congestion. 
The sender reduces its cwnd by half and enters the fast recovery phase. It retransmits the lost packet(s) 
without waiting for a timeout and continues to transmit new packets while waiting for acknowledgments.
5. Fast Retransmit: TCP Reno uses a mechanism called fast retransmit to recover from packet loss without waiting for a timeout. 
When the sender receives three duplicate ACKs (indicating that the receiver has received out-of-order packets), 
it assumes that the next expected packet is lost and performs a fast retransmit by resending that packet.
6. Timeout: If a packet loss is not detected through fast retransmit, TCP Reno eventually triggers a timeout event. 
When a timeout occurs, the sender assumes that all unacknowledged packets are lost and retransmits them, 
restarting the slow start phase.

## New Reno

## BBR

# Questions

## 1. Difference between congestion control and flow control
congestion control and flow control are both important mechanisms for ensuring that data is transmitted efficiently and reliably over computer networks. Congestion control prevents too much data from being injected into the network, while flow control prevents senders from overrunning the capacity of receivers.

- congestion control: it is the process of preventing too much data from being injected into the network, which can cause switches or links to become overloaded and lead to network congestion. Congestion can occur when there is more traffic on the network than it can handle, which can result in slower data transfer rates, dropped packets, and other issues. Congestion control mechanisms are designed to prevent this from happening by regulating the amount of data that is sent into the network.
- flow control: it is the process of preventing senders from overrunning the capacity of receivers. This is important because if a sender sends data too quickly, the receiver may not be able to process it all, which can result in dropped packets and other issues. Flow control mechanisms are designed to prevent this from happening by regulating the rate at which data is sent from the sender to the receiver.

## 2. New Reno algorithm explanation


## 3. BBR algorithm explanation

## 4. Difference between Reno, New Reno and BBR

## 5.

## 6.

