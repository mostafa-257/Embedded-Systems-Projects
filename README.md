# Embedded-Systems-Projects
Token Ring Network &amp; ADAS Simulator for Automotive Embedded Systems

MCUs used for Debugging : TIVA C Launchpad TM4C123GH6PM Cortex M4 Processor. 

The Token Ring Network is a network where all processors, in our case ECUs, are connected in a LAN, in our case using a CAN Bus. Its most distinctive feature is that each ECU takes its turn in broadcasting to the network. In this project the token is represented as a WHITE LED light and the broadcasted message is a press on one of two switches.  
Another application in this project is an ADAS (Advanced Driver Assistance Systems) Simulator in which only an ultrasonic sensor operation is implemented. 
The system is implemented as 2 subsystems: Master ECU (Gives token) and ADAS ECUs (Take token and are used to implement the ADAS System).  
For the upcoming components to be implemented a header file, COMMON.h must be included. 

The logical ring uses token ring message. This message is transmitted from low address (low ID) to high address (high ID) and finally from the highest address back to the lowest address, which forms a ring. In below Figure, the ring message is transmitted from 1 to 2, then from 2 to 3, and so on. The ring message is finally transmitted from 7 to 1 to form a ring, and then the ring transmission starts over again.

Create CAN network from 3 ECU (Node ID 1, 2 and 3). Each ECU Has the following functional requirements:
  1- Token Ring.
  2- ADAS simulation.
  
1- Token Ring
  • A ring token should be rotated along the network nodes.
  • Each token should hold the token 1 second before transmitting to the next ECU.
  • The ECU which has the token should turn on the white LED as long as it holds the token.
  • At initial state each ECU is associated with a specific color to be turned on as the following:
        Node 1 -> RED , Node 2 -> GREEN and Node 3 -> BLUE
  • The token LED will overwrite the ECU specific color.
  • If SW1 of the token owner ECU is pressed. Then the color sequence will be changed and started from this ECU. For instance, after the initial state declared above, if SW1 of      the node 3 is pressed while it is holding the token (white LED is on), the color sequence will be
        Node 3 -> RED, Node 1 -> GREEN and Node 2 -> BLUE
  • If SW2 of the token owner ECU is pressed, then the color sequence will be changed and started from this ECU with reversed order. For instance, after the initial state            declared above if SW2 of the node 2 is pressed while it is holding the token (white LED is on), the color sequence will be
        Node 2-> BLUE, Node 3 -> RED and Node 1 -> GREEN
        
2- ADAS Simulator
  • System has Node2 and Node3 which acting as car ADAS simulator (controlling car based on car and obstacle distance). Node2 role is:
    - Act as Sensor ECU.
    - Responsible for receiving the distance sensor read though UART on Duty cycle.
    - Send Distance over CAN every 100 ms. (The latest received).
    - Convert the Duty cycle to Distance based on the following:
        Duty Cycle       |      Distance
        -------------------------------------
        0%  to 10%       |      Sensor Error
        11% to 20%       |      1 meter
        21% to 40%       |      2 meters
        41% to 60%       |      3 meters
        61% to 100%      |      No Obstcale
  
