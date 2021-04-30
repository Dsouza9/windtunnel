# Wind Tunnel User Interface Program
This Github contains the code for LCD/Keypad interface for the Wind Tunnel.
The idea is that the user should be able to control the operation of the tunnel without
the need for a computer connection to the Teknic ClearPath MCPV motor. 
To see how to wire the motor using the molex cable, as well as all other necessary setup/connections
refer to the motor's manual found below:
https://www.teknic.com/files/downloads/ac_clearpath-mc-sd_manual.pdf

# Recommended Team Qualifications
* B+ or better in ECE 263
* Used an LCD/Keypad extensively before
* Used and completed a project using an LCD/Keypad as well as PWM operations in ECE 388/previously
(not just for a lab in ECE 263 unless you still remember it thoroughly)
* One ECE major and CPE major or One ECE major and a dual ECE-CPE major

# How We Designed It
We wanted the user to be able to control the operation of the tunnel without the need for a computer connection to the motor. Thus, we chose an LCD for the user display and a keypad for user input. The user is to enter a specific frequency, that through iterative testing with an anemometer, and a sheet compiled of airspeeds and the value needed for the user to enter, thus allows the user to set a specific speed that they desire. We did this using the computer connection and the motors included software in .1m/s increments starting from 1 m/s - 6 m/s. The end goal was 20 m/s in the test section. The Commanded Velocity (RPM) is what was recorded for the user to enter in the motor's software. This RPM input, changes the frequency automatically in the program. In the stand-alone configuration every 70RPM is approx 1 m/s. In the Wind/Water configuration, every 80RPM is approx 1 m/s. The Wind Tunnel Speed sheet we created for the user to reference when operating the tunnel can be found in our Wind Tunnel User Manual. Additionally, we planned to use the motor's High Level Feedback (HLFB) to cotinuously output the motor's RPM to the LCD display. The user should be able to clear their input, have to press enter to apply their input, toggle the enable for the motor, start and stop the motor, change the direction of the mtor spin (last thing you should focus on as the motor should only spin CCW in its current coniguration), and anything else you thing the user should be able to control. You could be like, "Hey, I don't like this idea. I want to change it." Go right ahead. This was just our concept. Refine and improve upon this. Maybe have the user input their desired speed, and do some algorithm in the background to make that happen. This was our original idea we had but couldn't figure it out. You got this. Make this project your own. Start from scratch or use what we have provided. I was you the best of luck. You got this. Any questions you have, you can ask me directly at: dylansou2399@yahoo.com

# As We Left It
In the current configuration, primary control is designed with a computer connection to the motor and user input using the motor's in-house software. 
I am leaving you with the LCD programmed to display output from the keypad. There are however bugs that remain with the keypad. For instance, each number press is not guaranteed. Most of the time (>80%) the number pressed is produced once. However, there are times it is not produced at all
or produced twice or more. This I beleive is due to button bounce which I tried to counter. Then there is the issue
with pressing "0" on the keypad. The code to produce a "0" is...fubar'ed. "0" is used as a condition else where in the code
and when pressed it will print 8 times, stop, print 8 times, stop, repeat. But, good news. By pressing "A" you can clear the display.
But only for the first line :) As you can see there is a lot of clean up to do. This is mainly due to time contraints expereinced and COVID-19.
And possibly because we weren't the best coders :) (that is more likely the case).

Additionally, for PWM operation, PB1 or PB2 or both needs to be open. As ususal, refer to the microcontrollers datasheet/Teknic motor manual for info 
as well as your ECE 263 notes:
http://ww1.microchip.com/downloads/en/DeviceDoc/40001906A.pdf

# Useful Links and Images
Please check out our user manual for general operation of the wind tunnel using a computer connection. You must know how to do this. Use the QR code to access the manual:
![UserManualCover](https://user-images.githubusercontent.com/46977434/116702238-d9407200-a996-11eb-95f6-5137b7dac163.PNG)
![image](https://user-images.githubusercontent.com/46977434/116702362-fd03b800-a996-11eb-91af-5c83eb606173.png)

The last revision of the schematic can be found here:
![Schematic](https://user-images.githubusercontent.com/46977434/116702538-3805eb80-a997-11eb-8f58-c7fd30297ea6.png)
Notice I changed the connection LCD D5 from PB1 to PC4. 

You also might be curious as to why there is a 5V-12V step-up buck converter. This is to ensure the signal from the ATMega328 is strong enough for the input to the motor to read. The minimum input voltage to the motor is 5V so to account for any error, we wanted to bring it up to 12V. The max input voltage is 24V.


