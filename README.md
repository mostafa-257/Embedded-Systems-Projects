# Embedded-Systems-Projects
Token Ring Network &amp; ADAS Simulator for Automotive Embedded Systems

MCUs used for Debugging : TIVA C Launchpad TM4C123GH6PM Cortex M4 Processor. 

The Token Ring Network is a network where all processors, in our case ECUs, are connected in a LAN, in our case using a CAN Bus. Its most distinctive feature is that each ECU takes its turn in broadcasting to the network. In this project the token is represented as a WHITE LED light and the broadcasted message is a press on one of two switches.  
Another application in this project is an ADAS (Advanced Driver Assistance Systems) Simulator in which only an ultrasonic sensor operation is implemented. 
The system is implemented as 2 subsystems: Master ECU (Gives token) and ADAS ECUs (Take token and are used to implement the ADAS System).  
For the upcoming components to be implemented a header file, COMMON.h must be included. 

  
