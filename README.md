# IADCPingPong


This project demonstrates using the IADC peripheral in conjunction with the LDMA
to continuously sample a single-ended input channel. The LDMA will be operating in Ping Pong mode and
Sample results are stored in an internal array. When the transfer is complete, WSTK LED0 is set.

How To Test:
1. Update the kit's firmware from the Simplicity Launcher (if necessary)
2. Build the project and download to the Starter Kit
3. Open the Simplicity Debugger and add "pingBuffer" and "pongBuffer" to the Expressions Window
4. Monitor EXP11, LED0 on the Wireless Starter Kit, it will toggle everytime one of the buffers get updated.

Board:  Silicon Labs EFR32xG21 Radio Board (BRD4181A) +
        Wireless Starter Kit Mainboard
Device: EFR32MG21A010F1024IM32
PB00 - GPIO Push/Pull output, Expansion Header Pin 11, WSTK Pin 8, LED0
PC04 - IADC input, single-ended, J102 of BRD4001, Pin 25
