/*
 * Here is a simple sketch to get a reading of the weight of an object placed on a loadcell connected to a HX711 pcb displayed onto the Serial monitor
 * This sketch adds the functionality of a "tare" or "zeroing" button to zero the scale measurements.
 * 
 * This software is written in 2023 by Simple Electronics (https://www.youtube.com/simpleelectronics)
 * and that should serve as a permission to do what you want with it but also as a warning that it might
 * not exactly work the way you think it might.
 * The author of the library did a great job making the library but I found it hard to follow the examples,
 * so I made my own. Enjoy!
 * 
 * This code cannot really be used without first calibrating the loadcell/HX711 combination, please calibrate it first
 * and then input the number into the calibration section (const int cal = ??;)
 * 
 * You can find my sketch for calibrating the loadcell here: https://github.com/SimpleElectronicsYT/HX711_sketches
 * 
 * First you need to hook up the HX711 module to your load sensor;
 * 
 * RED to E+
 * BLACK to E-
 * WHITE to A-
 * GREEN to A+
 *  
 * And then you need to hook the module up to your microcontroller:
 *
 * VCC to any 5v source (I used the 5v pin on my Arduino)
 * GND to any ground source (I used the GND pin on my Arduino)
 * 
 * --PLEASE MAKE SURE THAT IF YOUR ARDUINO IS POWERED SEPARATELY TO YOUR HX711 BOARD THAT
 * YOU CONNECT THE GROUNDS OF BOTH OF THEM TOGETHER--
 * 
 * DT you will define later on in the code - no worries, I commented my code
 * SCK you will define later on in the code - no worries, I commented my code
 * 
 * 
 * You NEED the HX711 library. I used the one in the Arduino library manager, "HX711 Arduino Library" by Bogdan Necula
 */

//this is to include the HX711 library into your program - make sure to download it first!
#include "HX711.h"

//we need to define the pins for the SCK and the DOUT (marked DT on the HX711 circuit board)
//I personally used pins 2 and 3, therefore they are defaulted to that - feel free to change them.
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

//We need to define a pin to use a button to trigger the "xxxx.tare()" function which zeros the weight on the scale - I picked pin 4 here, arbirarily.
//Any pin that can be used as an input can be chosen here.
const int tareBtn = 4;


//Put your calibration value in the place of the "1" below. You can find the sketch to find the calibration value here:
//https://github.com/SimpleElectronicsYT/HX711_sketches/blob/main/Scale_Calibration.ino
const int cal = 1;

//Give a name to your scale, "scale" in this case, it can be whatever you want though - just remember you have to call it by name in the code.
HX711 scale;

//The "Setup" function only runs once on every time the device is powered on.
void setup() {

  //Setting out "tare" button pin to be an input and to use the interal pullup resistors so that no external resistor is needed and the
  //microcontroller will always see it as a "HIGH" unless a button is pressed. It is good practice to always force an input pin into a known state.
  pinMode(tareBtn, INPUT_PULLUP);
  
  //These lines start up the serial monitor, they aren't needed if you plan on using a display, but if you remove them, make sure to remove all the serial commands in the code.
  //Make sure to set the baud rate dropdown at the bottom of the serial monitor to 115200 or you may get gibberish in the serial monitor window.
  //more information on using the serial monitor can be found here: https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor
  Serial.begin(115200);

  //This line prints a message to the serial monitor to confirm that the monitor is working. Again, this isn't needed for the core functionality of the code.
  //But it is a nice step to confirm the code ahas made it this far and the baud rate is correct.
  Serial.println("Serial communications are operational!");

  //This line will let us know that the loadcell is initializing by sending a message to the serial monitor.
  //This is also not required, but agin, is nice to know where the code is at
  Serial.println("Initializing the loadcell...");
  
  //Here is the actual initialization of the loadcell now. The two variables in the brackets are the ones telling the library which pins are being used for DOUT and SCK.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  //Here is where we will use the calibration number you set higher up to actually calibrate the scale, it goes in the brackets of the set_scale() function
  scale.set_scale(cal);

  //We also need to "tare" the scale - that is to say we need to offset any initial weight from the measurement. Useful if we want to fill a container to a set weight without the weight of the container.
  //We can simply place the empty container on the scale before powering it on.
  scale.tare();
}

//The "loop" function runs over and over ad infinitum once the "setup" function is complete.
void loop() {

  //This is where the checking takes place to tell if the "tare" button is pressed or not. - it is normally "HIGH" because of the INPUT_PULLUP we set earlier
  //and if the user presses the button, it will read "LOW"
  if(digitalRead(tareBtn) == LOW){
    
    //IF the "tare" button's pin is pulled to ground (a.k.a. LOW) then we call the "xxxx.tare()" function which zeroes the scale.
    scale.tare();
    
    //Adding a short delay to give the user time to remove their finger from the "tare" button and then back to business as usual.
    delay(250);
  }
  
  //This is how we get the actual weight on the scale. The number in brackets corresponds to how many measurements it will take and average out to give us the final answer.
  //10 is a good starting point, but feel free to experiment with different values here.
  Serial.println(scale.get_units(10));

  //Setting a delay to limit how often the code retrieves weight data - feel free to have your code do other things aswell or instead of this.
  //I find 500mS is a decent delay
  delay(500);

}
