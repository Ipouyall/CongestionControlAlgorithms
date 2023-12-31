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

![plot](./results/tcp_reno.png)

## New Reno

TCP New Reno is an enhancement of the TCP Reno congestion control algorithm. 
It is designed to provide better throughput and responsiveness in scenarios where there are both 
packet losses and random packet reordering. By enhancing the fast recovery mechanism, introducing limited transmit, 
and improving recovery after timeouts, TCP New Reno aims to improve the overall performance and efficiency of TCP congestion control.

**Enhancement:**
1. Fast Recovery Enhancements: TCP New Reno improves the fast recovery mechanism used in TCP Reno. In traditional Reno, 
upon receiving three duplicate acknowledgments (dupACKs), the sender reduces the congestion window by half and enters the fast recovery phase. 
However, in TCP New Reno, the sender keeps transmitting new packets during fast recovery, 
instead of waiting for additional duplicate ACKs. This allows for a more efficient use of available bandwidth.
2. Limited Transmit: TCP New Reno introduces a feature called limited transmit. 
When the sender has fewer than cwnd outstanding packets (where cwnd is the congestion window size), 
and there is a small number of unacknowledged packets, it can transmit additional packets beyond the congestion window. 
This helps to utilize available capacity and reduce unnecessary delay caused by waiting for congestion window updates.
3. Recovery After Timeouts: TCP New Reno improves the recovery process after a timeout event. 
In traditional Reno, after a timeout, the sender resets the congestion window to a conservative value and re-enters the slow start phase. 
In TCP New Reno, the sender uses a more aggressive approach. 
It sets the congestion window to approximately half of the previous congestion window and starts the congestion avoidance phase directly. 
This allows for a faster recovery and avoids an overly cautious restart.

![plot](./results/tcp_new_reno.png)

## BBR
The BBR (Bottleneck Bandwidth and Round-trip propagation time) algorithm's goal is to maximize network utilization 
while minimizing latency and achieving a high throughput. It does this by continuously estimating the available bandwidth, 
regulating the sending rate using pacing and probing, and responding to congestion signals.

**How it works:**
1. Bandwidth and RTT Estimation: 
BBR actively estimates the available bandwidth and round-trip time (RTT) to the network bottleneck. 
It measures the sending rate and observed RTT to determine the capacity of the network.
2. Pacing and Probing: 
BBR uses a combination of pacing and probing to regulate the sending rate. 
Pacing ensures that packets are sent at a rate that matches the estimated bottleneck capacity. 
Probing allows BBR to explore the available bandwidth without causing excessive queueing delay or packet loss.
3. Mode Selection: 
BBR operates in different modes based on network conditions. 
The two main modes are the `startup` mode and the `steady-state` mode:
   - Startup Mode: In the startup mode, BBR rapidly increases the sending rate to probe the available bandwidth. 
   It aims to reach the bottleneck capacity quickly while avoiding excessive queueing delay.
   - Steady-State Mode: Once BBR reaches the steady-state, 
   it maintains the sending rate close to the estimated bottleneck capacity. 
   It continuously monitors the network and adjusts the sending rate based on observed RTT and available bandwidth.
4. Latency Optimization: BBR focuses on minimizing queuing delay and reducing network latency. 
It does this by pacing the sending rate to match the available capacity and avoiding sending more data 
than the network can handle without introducing excessive queueing delay.
5. Response to Congestion: BBR is designed to be responsive to congestion signals. 
When it detects signs of congestion such as increased queuing delay or packet loss, 
it reacts by reducing the sending rate to alleviate congestion and avoid further deterioration of network performance.

![plot](./results/tcp_bbr.png)

# Questions

## 1. Difference between congestion control and flow control
congestion control and flow control are both important mechanisms for ensuring that data is transmitted efficiently and reliably over computer networks. Congestion control prevents too much data from being injected into the network, while flow control prevents senders from overrunning the capacity of receivers.

- **congestion control**: it is the process of preventing too much data from being injected into the network, 
which can cause switches or links to become overloaded and lead to network congestion. 
Congestion can occur when there is more traffic on the network than it can handle, which can result in slower data transfer rates, 
dropped packets, and other issues. Congestion control mechanisms are designed to prevent this from happening by regulating 
the amount of data that is sent into the network.
- **flow control**: it is the process of preventing senders from overrunning the capacity of receivers. 
This is important because if a sender sends data too quickly, the receiver may not be able to process it all, 
which can result in dropped packets and other issues. 
Flow control mechanisms are designed to prevent this from happening by regulating the rate at which data is sent from the sender to the receiver.

## 2. New Reno algorithm explanation
1. Slow Start: TCP new Reno begins by setting the congestion window (cwnd) to a small value, typically one or a few segments. 
It sends packets into the network, monitoring for acknowledgments (ACKs) from the receiver. 
For every ACK received, it increases the cwnd exponentially, effectively doubling it.
2. Congestion Avoidance: Once a certain threshold, known as the congestion threshold (ssthresh), 
is reached or when a congestion event occurs (e.g., packet loss), TCP new Reno enters the congestion avoidance phase. 
In this phase, it increases the cwnd linearly by adding one segment for each successful round-trip time (RTT).
3. Congestion Detection: TCP Reno detects congestion through two primary indicators:
   - Triple Duplicate ACKs: If the sender receives three duplicate ACKs, indicating that the receiver has received 
   out-of-order packets, it assumes that a packet has been lost. This triggers the fast retransmit and recovery mechanism.
   - Timeout: If the sender does not receive an ACK for a transmitted packet within a certain time period (timeout), 
   it assumes that the packet is lost and triggers a retransmission.
4. Fast Recovery: Upon detecting a packet loss through triple duplicate ACKs, 
TCP new Reno enters the fast recovery phase instead of going back to the slow start phase. 
In fast recovery, it reduces the cwnd by a smaller amount, usually by half or less, and retransmits the missing packets(regarding SACK) 
without waiting for a timeout. Additionally, it continues to transmit new packets, 
assuming they were lost due to network congestion. This helps maintain a certain level of sending rate during the recovery process.
5. Fast Retransmit: TCP new Reno performs fast retransmit when it receives three duplicate ACKs. 
It considers this as an indication that the next expected packet is lost and retransmits it immediately without waiting for a timeout.
6. Timeout: If a packet loss is not detected through fast retransmit, TCP new Reno eventually triggers a timeout event. 
When a timeout occurs, the sender assumes that all unacknowledged packets are lost and retransmits them, 
resetting the cwnd to a small value and reentering the slow start phase.

## 3. BBR algorithm explanation
The BBR algorithm aims to maximize network utilization, minimize latency, and achieve high throughput. 
By actively estimating the available bandwidth, regulating the sending rate through pacing and probing, 
and responding promptly to congestion signals, BBR optimizes network performance in various scenarios.

1. Bandwidth and RTT Estimation: 
BBR continuously measures the sending rate and the round-trip time (RTT) of packets. 
It uses this information to estimate the available bandwidth and the RTT to the network bottleneck—the point 
in the network where congestion occurs.
2. Pacing and Probing: 
BBR regulates the sending rate using a combination of pacing and probing. Pacing ensures that packets are sent at a rate 
that matches the estimated bottleneck capacity. Probing allows BBR to explore the available bandwidth 
without causing excessive queueing delay or packet loss.
3. Mode Selection: BBR operates in different modes depending on network conditions:
    - Startup Mode: In the startup mode, BBR rapidly increases the sending rate to probe the available bandwidth. 
   It aims to reach the bottleneck capacity quickly while avoiding excessive queueing delay.
    - Drain Mode: Once BBR detects that the network is fully utilized and congestion is likely, it enters the drain mode. 
   In this mode, BBR gradually reduces the sending rate to alleviate congestion and prevent excessive queueing delay.
    - Probe Bandwidth and Probe RTT Modes: BBR dynamically switches between these modes to estimate the available bandwidth 
   and the RTT to the bottleneck. It periodically probes the network to ensure accurate measurements.
4. Latency Optimization: BBR focuses on minimizing queuing delay and reducing network latency. 
It does this by carefully pacing the sending rate to match the available capacity and avoiding sending more data 
than the network can handle without introducing excessive queueing delay.
5. Congestion Responsiveness: BBR is designed to respond quickly to signs of congestion. 
It continuously monitors the network and looks for indicators such as increased queuing delay or packet loss. 
When congestion is detected, BBR reacts by reducing the sending rate to alleviate congestion and maintain stability.
6. Coupled Sender and Receiver: BBR requires both the sender and receiver to implement the algorithm to achieve 
optimal performance. The receiver provides feedback to the sender about the available receive bandwidth, 
enabling more accurate rate control.

## 4. Difference between Reno, New Reno and BBR

### TCP Reno vs. TCP New Reno
TCP New Reno builds upon the TCP Reno algorithm and enhances the fast recovery mechanism by introducing limited transmit 
and improving the handling of new ACKs during the recovery phase. 
These enhancements aim to improve the efficiency and responsiveness of TCP in scenarios involving packet loss and subsequent ACKs.

The primary difference between TCP Reno and TCP New Reno lies in their handling of fast recovery after detecting packet loss.

- Fast Recovery Mechanism: In TCP Reno, when the sender receives three duplicate ACKs (indicating packet loss), 
it assumes that the next expected packet is lost and performs a fast retransmit, retransmitting that packet immediately. 
TCP Reno then reduces the congestion window (cwnd) by half and enters the congestion avoidance phase.
  - Handling of New ACKs: In TCP Reno, after performing the fast retransmit and reducing the cwnd, 
  the sender waits for a new ACK for the retransmitted packet to exit the fast recovery phase and resume normal congestion control. 
  This means that if new ACKs for subsequent packets arrive during this period, they are treated as duplicate ACKs and do not affect the cwnd.
+ Enhanced Fast Recovery in TCP New Reno: TCP New Reno introduces an improvement to the fast recovery mechanism. 
When TCP New Reno receives three duplicate ACKs, it performs a fast retransmit of the missing packet, similar to TCP Reno. 
However, TCP New Reno differs in how it handles new ACKs during the fast recovery phase. 
  - Limited Transmit: TCP New Reno employs a feature called limited transmit. 
  It allows the sender to transmit new packets beyond the congestion window (cwnd) during fast recovery, 
  as long as the number of outstanding packets is below a certain threshold. This enables better utilization of available bandwidth.
  - Handling New ACKs: In TCP New Reno, if new ACKs arrive during fast recovery, 
  indicating that subsequent packets have been successfully received by the receiver, it exits the fast recovery phase. 
  Unlike TCP Reno, TCP New Reno does not require waiting for a specific ACK for the retransmitted packet. 
  This helps to avoid unnecessary delay and allows for a more efficient recovery process.


### TCP (new) Reno vs. TCP BBR
1. Approach to Congestion Control:
    - TCP Reno: TCP Reno relies on packet loss as a signal of network congestion. 
   It uses a combination of slow start, congestion avoidance, fast recovery, and fast retransmit mechanisms 
   to regulate the sending rate and react to congestion events.
    - TCP BBR: TCP BBR takes a different approach to congestion control. 
   It focuses on estimating the available network bandwidth and the round-trip time (RTT) to the bottleneck of the network. 
   It aims to maximize network utilization and achieve low latency by continuously probing and adapting the sending rate 
   based on available capacity and RTT measurements.
2. Congestion Detection:
   - TCP Reno: TCP Reno detects congestion primarily through the occurrence of packet loss. 
   It interprets the receipt of duplicate ACKs or a timeout as indications of congestion in the network.
   - TCP BBR: TCP BBR infers network congestion by monitoring the rate at which acknowledgments (ACKs) are received 
   and the observed RTT. It aims to maintain a high sending rate while avoiding increased queueing delay or loss at the bottleneck.
3. Bandwidth Estimation:
   - TCP Reno: TCP Reno does not explicitly estimate the available bandwidth in the network.
   - TCP BBR: TCP BBR actively estimates the available bandwidth by continuously probing the network using 
   a combination of pacing and probing mechanisms. It aims to maintain a sending rate close to the estimated bottleneck bandwidth.
4. Latency Optimization:
   - TCP Reno: TCP Reno does not explicitly optimize for low latency.
   - TCP BBR: TCP BBR aims to minimize queuing delay and achieve low latency by continuously probing the network 
   and adjusting the sending rate based on RTT measurements.
5. Performance:
   - TCP Reno: TCP Reno is a widely adopted and well-established congestion control algorithm. 
   It performs well in a wide range of network scenarios, but its performance can be affected by high latency or packet loss.
   - TCP BBR: TCP BBR is a relatively newer congestion control algorithm designed to optimize both bandwidth and latency. 
   It has shown significant improvements in throughput and latency in many network conditions, 
   particularly in networks with high bandwidth and long RTTs.

## 5. How you choose between these algorithms?
Choosing between different congestion control approaches, such as TCP Reno, TCP New Reno, and TCP BBR, 
depends on several factors and considerations:

- Network Characteristics: Consider the specific characteristics of your network, including the available bandwidth, 
round-trip time (RTT), and potential for congestion. TCP BBR is known to perform well in networks with high bandwidth 
and long RTTs, while TCP Reno and TCP New Reno are more widely used and suitable for a variety of network conditions.
- Latency vs. Throughput: Determine your priorities regarding latency and throughput. 
If minimizing latency is crucial, TCP BBR may be a favorable choice due to its focus on reducing queuing delay. 
If achieving high throughput is a primary concern, TCP BBR's bandwidth estimation and pacing mechanisms can optimize network utilization.
- Application Requirements: Consider the specific requirements of your applications. Some applications, 
such as real-time video streaming or interactive communication, may prioritize low latency and responsiveness. 
Others, like bulk data transfer or file sharing, may prioritize maximizing throughput.
- Deployment Compatibility: Evaluate the compatibility of the congestion control algorithms with your network infrastructure and endpoints. 
TCP Reno and TCP New Reno are widely supported and available in most TCP implementations. TCP BBR may require 
specific kernel patches or support from network devices and endpoints.
- Experimental Evaluation: Consider conducting experiments or simulations in your specific network environment to evaluate 
the performance of different congestion control algorithms. This can provide insights into their behavior, efficiency, 
and suitability for your specific use case.
- Expert Advice and Research: Consult with network experts, researchers, or industry best practices to gather insights 
and recommendations regarding the selection of congestion control algorithms. 
Stay informed about the latest developments and research in this field, as new algorithms and enhancements may emerge over time.

## 6. Available  congestion control algorithms
- TCP Reno: This is the standard and widely deployed congestion control algorithm. It uses a combination of slow start, 
congestion avoidance, fast recovery, and fast retransmit mechanisms.
- TCP New Reno: An enhancement to TCP Reno, it improves the handling of fast recovery by introducing limited transmit 
and allowing for faster exit from the recovery phase.
- TCP BBR (Bottleneck Bandwidth and Round-trip propagation time): A modern congestion control algorithm that aims 
to maximize network throughput and reduce latency by estimating available bandwidth and round-trip time.
- TCP Cubic: An algorithm designed to provide a scalable congestion control mechanism for high-speed networks. 
It uses a cubic function to regulate the sending rate based on network conditions.
- TCP Vegas: This algorithm focuses on minimizing delay instead of packet loss. 
It adjusts the sending rate based on observed RTT variations to achieve low latency.
- TCP CUBIC Plus: An enhancement to TCP Cubic that combines the benefits of both TCP Cubic 
and TCP BBR to improve performance in different network scenarios.
- Compound TCP (CTCP): This algorithm aims to provide fairness and congestion control in networks 
with high bandwidth-delay products.
- TCP Westwood: A TCP variant designed for wireless networks, particularly for dealing 
with the characteristics of lossy and time-varying wireless links.

**TCP Reno**:
- Pros:
  1. Well-Established: TCP Reno is a widely adopted and well-established congestion control algorithm, supported by most TCP implementations.
  2. Compatibility: It is compatible with a wide range of network infrastructure and endpoints.
  3. Robustness: TCP Reno performs well in various network scenarios and is resilient to different network conditions.
  4. Fairness: It provides fair bandwidth sharing among multiple flows.
- Cons:
  1. Susceptible to Congestion Collapse: TCP Reno can experience congestion collapse in certain situations where multiple flows rapidly increase their sending rates simultaneously, leading to degraded network performance.
  2. Latency: It may introduce higher latency due to its reliance on packet loss as a congestion signal.

**TCP BBR**:
- Pros:
  1. Throughput Optimization: TCP BBR is designed to maximize network throughput by actively estimating available bandwidth and regulating the sending rate accordingly.
  2. Low Latency: It aims to minimize queuing delay and reduce network latency, making it suitable for latency-sensitive applications.
  3. Performance in High-Bandwidth Networks: TCP BBR performs well in networks with high bandwidth and long round-trip times.
  4. Congestion Responsiveness: It responds quickly to congestion signals, adjusting the sending rate to alleviate congestion and maintain stability.
- Cons:
  1. Compatibility: TCP BBR may require specific kernel patches or support from network devices and endpoints, which could limit its compatibility in some environments.
  2. Fairness: It has been observed that TCP BBR may prioritize its own flow over competing flows, potentially leading to unfairness in bandwidth allocation.
  3. Sensitivity to RTT Estimation: Accurate estimation of round-trip time (RTT) is crucial for TCP BBR's performance, and inaccurate RTT measurements can impact its effectiveness.

**TCP Westwood**:
- Pros:
  1. Wireless Network Optimization: TCP Westwood is specifically designed for wireless networks and performs well in lossy and time-varying wireless environments.
  2. Enhanced Congestion Control: It uses a different approach to congestion control by considering the variation in available bandwidth, resulting in improved performance in wireless scenarios.
  3. Fairness: TCP Westwood aims to provide fair bandwidth sharing among multiple flows.
- Cons:
  1. Limited Deployment: TCP Westwood is not as widely deployed or supported as TCP Reno or TCP BBR, and its compatibility may be limited.
  2. Complexity: The algorithms and mechanisms used in TCP Westwood are more complex compared to traditional congestion control algorithms, making it more challenging to implement and understand.


**TCP CUBIC**:
- Pros:
  1. Scalable Congestion Control: TCP CUBIC is designed to provide scalable performance in high-speed networks with large bandwidth-delay products.
  2. Fairness: It aims to provide fair bandwidth sharing among multiple flows.
  3. Stability: TCP CUBIC has been shown to provide stability and robustness in various network scenarios.
- Cons:
  1. Increased Latency: In certain situations, TCP CUBIC can introduce higher latency due to its congestion control mechanisms, especially when competing with other algorithms that prioritize low latency.
  2. Sensitivity to Congestion Collapse: Similar to TCP Reno, TCP CUBIC may be susceptible to congestion collapse when multiple flows rapidly increase their sending rates simultaneously.

**TCP Vegas**:
- Pros:
  1. Low Latency: TCP Vegas focuses on minimizing delay instead of relying on packet loss as a congestion signal, making it suitable for latency-sensitive applications.
  2. Stability: It aims to provide stability in network congestion situations and performs well in scenarios with high bandwidth-delay products.
- Cons:
  1. Limited Deployment: TCP Vegas is not as widely deployed or supported as TCP Reno or TCP BBR, which may limit its compatibility.
  2. Fairness: There have been concerns about TCP Vegas potentially prioritizing its own flow over competing flows, leading to fairness issues in bandwidth allocation.


