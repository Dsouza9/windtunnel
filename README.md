# Wind Tunnel User Interface Program
This Github contains the code for LCD/Keypad interface for the Wind Tunnel.
The idea is that the user should be able to control the operation of the tunnel without
the need for a computer connection to the Teknic ClearPath MCPV motor. 
To see how to wire the motor using the molex cable, as well as all other necessary setup/connections
refer to the motor's manual found below:
https://www.teknic.com/files/downloads/ac_clearpath-mc-sd_manual.pdf

In the current configuration, I am leaving you with the LCD programed to produce an output from the keypad.
There are however bugs that remain with the keypad. For instance, each number press is not guaranteed. 
Most of the time (>80%) the number pressed is produced once. However, there are times it is not produced at all
or produced twice or more. This I beleive is due to button bounce which I tried to counter. Then there is the issue
with pressing "0" on the keypad. The code to produce a "0" is...fubar'ed. "0" is used as a condition else where in the code
and when pressed it will print 8 times, stop, print 8 times, stop, repeat. But, good news. By pressing "A" you can clear the display.
But only for the first line :) As you can see there is a lot of clean up to do. Additionally, for PWM operation, PB1 or PB2 or both needs to be open 
but it is currently occupied by the LCD, this is a simple code change I might do in the next day. If not, change this pin location to C4/5 or 
whatever else is open that you are sure you don't need to use for something else.
