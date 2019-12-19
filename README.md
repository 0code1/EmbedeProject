# <center>Embede Project</center>


For this project I have choose to use an LCD, Keypad, hue ,  thermometer and a fan.
 The objective of my project is to be able to measure a house temperature, and be able to display it on an LCD (change temperature) , at wish the fan will be regulate depending on the temperature on the house, the keypad will be use to change the temperature in the house.

***
# The program is on the Feature branch since the project is unfinish.
***
---
# Main Flowshart

![Minion](Introflow.png)
---
___

in our main C file, where we start the program there will be 2 interrupt and 2 timer interrupt.
the Init represent all the funtion that will be Initialise under the start,
and of course our super loop

___

---
# Here are the overview of the flowshart

![Minion](flowsharts.png)
---
___

# The ADC flowshart

![Minion](flowsharts.png)

___
The ADC interrupt will be runnning  everytime that the ADCSRA bit is flip to 
