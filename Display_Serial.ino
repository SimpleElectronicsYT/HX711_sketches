/*
 * Here is a simple sketch to get a reading of the weight of an object placed on a loadcell connected to a HX711 pcb displayed onto the Serial monitor
 * 
 * This software is written in 2023 by Simple Electronics (https://www.youtube.com/simpleelectronics)
 * and that should serve as a permission to do what you want with it but also as a warning that it might
 * not exactly work the way you think it might.
 * The author of the library did a great job making the library but I found it hard to follow the examples,
 * so I made my own. Enjoy!
 * 
 * This code cannot really be used without first calibrating the loadcell/HX711 combination, please calibrate it first
 * and then input the number into the calibration section (const int cal = ??;
 * 
 * You NEED the HX711 library. I used the one in the Arduino library manager, "HX711 Arduino Library" by Bogdan Necula
 */

//this is to include the HX711 library into your program - make sure to download it first!
#include "HX711.h"

//we need to define the pins for the SCK and the DOUT (marked DT on the HX711 circuit board)
//I personally used pins 2 and 3, therefore they are defaulted to that - feel free to change them.
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

//Put your calibration value in the place of the "1" below. You can find the sketch to find the calibration value here:
//https://github.com/SimpleElectronicsYT/HX711_sketches/blob/main/Scale_Calibration.ino
const int cal = 1;

//Give a name to your object, "Scale" in this case, it can be whatever you want though!
HX711 scale;

void setup() {

  //These lines start up the serial monitor, they aren't needed if you plan on using a display, but if you remove them, make sure to remove all the serial commands in the code.
  //Make sure to set the baud rate dropdown at the bottom of the serial monitor to 115200 or you may get gibberish in the serial monitor window.
  Serial.begin(115200);

  //This line prints a message to the serial monitor to confirm that the monitor is working. Again, this isn't needed for the core functionality of the code.
  Serial.println("Serial communications are operational!");

  //This line will let us know that the loadcell is initializing by sending a message to the serial monitor.
  Serial.println("Initializing the loadcell...");
  //Here is the actual initialization of the loadcell now. The two variables in the brackets are the ones setting which pins are being used for DOUT and SCK.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  //Here is where we will use the calibration number you set higher up to actually calibrate the scale, it goes in the brackets of the set_scale() function
  scale.set_scale(cal);

  //We also need to "tare" the scale - that is to say we need to offset any initial weight from the measurement. Useful if we want to fill a container to a set weight without the weight of the container.
  //We can simply place the empty container on the scale before powering it on.
  scale.tare();
}

void loop() {

  //This is how we get the actual weight on the scale. The number in brackets corresponds to how many measurements it will take and average out to give us the final answer.
  Serial.println(scale.get_units(10));

  //Setting a delay to limit how often the code retrieves weight data
  delay(500);

}
