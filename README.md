# Wind Tunnel User Interface Program
This Github contains the code for LCD/Keypad interface for the Wind Tunnel.
The idea is that the user should be able to control the operation of the tunnel without
the need for a computer connection to the Teknic ClearPath MCPV motor. 
To see how to wire the motor using the molex cable, as well as all other necessary setup/connections
refer to the motor's manual found below:
https://www.teknic.com/files/downloads/ac_clearpath-mc-sd_manual.pdf


# As We Left It
In the current configuration, I am leaving you with the LCD programed to produce an output from the keypad.
There are however bugs that remain with the keypad. For instance, each number press is not guaranteed. 
Most of the time (>80%) the number pressed is produced once. However, there are times it is not produced at all
or produced twice or more. This I beleive is due to button bounce which I tried to counter. Then there is the issue
with pressing "0" on the keypad. The code to produce a "0" is...fubar'ed. "0" is used as a condition else where in the code
and when pressed it will print 8 times, stop, print 8 times, stop, repeat. But, good news. By pressing "A" you can clear the display.
But only for the first line :) As you can see there is a lot of clean up to do. This is mainly due to time contraints expereinced and COVID-19.
And possibly because we weren't the best coders :) (that is more likely the case).

Additionally, for PWM operation, PB1 or PB2 or both needs to be open but it is currently occupied by the LCD. This is a simple 
code change I might do in the next day. If not, change this pin location to PC4/5 or whatever else is open that you are 
sure you don't need to use for something else. As ususal, refer to the microcontrollers datasheet for info as well as your ECE 263 notes:
http://ww1.microchip.com/downloads/en/DeviceDoc/40001906A.pdf

# Useful Links and Images:
Please check out our user manual for general operation of the wind tunnel using a computer connection. You must know how to do this. Use the QR code to access the manual:
![UserManualCover](https://user-images.githubusercontent.com/46977434/116702238-d9407200-a996-11eb-95f6-5137b7dac163.PNG)
![image](https://user-images.githubusercontent.com/46977434/116702362-fd03b800-a996-11eb-91af-5c83eb606173.png)

The last revision of the schematic can be found here:
![Schematic](https://user-images.githubusercontent.com/46977434/116702538-3805eb80-a997-11eb-8f58-c7fd30297ea6.png)
Notice I changed the connection LCD D5 from PB1 to PC4. 
