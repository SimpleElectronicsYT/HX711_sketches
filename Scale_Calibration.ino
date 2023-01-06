/*
 * This is a quick little program to help you calibrate your HX711 and load cell.
 * This software is written in 2023 by Simple Electronics (https://www.youtube.com/simpleelectronics)
 * and that should serve as a permission to do what you want with it but also as a warning that it might
 * not exactly work the way you think it might.
 * The author of the library did a great job making the library but I found it hard to follow the examples,
 * so I made my own. Enjoy!
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
 * SCK you till define later on in the code - no worries, I commented my code
 * 
 * How to calibrate your loadcell:
 * 
 * The goal here is to come up with a value to put into the "set_scale()" function's parameter (the space between the backets),
 * here is how we do that:
 *    NOTE:Make sure you open your serial monitor, that is where the information will be displayed.
 * 
 * 1: We will call the set_scale function with no parameter (with the brackets empty).
 * 
 * 2: We will call the tare() function with no parameter either, to zero out the reading.
 * 
 * 3: You must set a weight that you know the exact weight of on the load cell (load cells are directional but it's hard to explain in text -
 *    try a google image search for HX711 and loadcell for how to mechanically set it up)
 *    NOTE: you will have 5 seconds to do this once the serial monitor prompts you
 *    NOTE: the UNIT of the weight (grams, oz, lbs etc...) doesn't matter BUT this will be the default unit of your code.
 *    so I recommend using grams. And yes, this does mean you need a scale in order to calibrate your scale, sorry.
 *    
 * 4: Take the number that will print in your serial monitor and divide it by your known weight. The result is your set_scale() value
 *    EXAMPLE: your known weight is 189 grams. The result on the serial monitor is 90548.9
 *    simply do 90548.9 / 189 = 479.09 and therefore you can use 479 in your code to set the scale
 *    So your function will look like this: XXXX.set_scale(479);
 *    
 * 5: You can now change the scale.set_scale(); to be scale.set_scale(479); (don't forget to use YOUR result in place of the 479) in this sketch
 *    and once it tells you to put on a weight, you can put on your known weight and the result should be darn close to your known weigth.
 *    
 *    This set_scale() value you can use in your future sketches, this only needs to be done every time a different load sensor is installed.
 *    
 *    I hope this is clear enough, for more information check out the line-by-line comments.
 *    
 *    Good luck, You got this!
 * 
 */
 
//You need to include the HX711 library, I searched in the Arduino library manager and took the one called "HX711 Arduino Library" by Bogdan Necula
#include "HX711.h"

//Use these two variables to set the arduino pins (DOUT is labelled DT on the HX711 circuit board)
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

//Give your object a name to be used in the code, "scale" is used in this case, but it can be whatever you would like
HX711 scale;

void setup() {

  //These lines will start up the serial monitoring, make sure to open the serial monitor window to see the data we will be printing to it
  //Make sure the baud rate at the bottom of the window is set to 115200 - or you may see some gibberish
  Serial.begin(115200);
  
  //Printing an into line to make sure the serial data is coming across, this is just fluff.
  Serial.println("let's calibrate this thing!");

  //Printing a line to tell the user what is going on, again, just fluff, not really needed
  Serial.println("Initializing the scale...");
  
  //This line will just initialize our loadcell which we named "scale", we are using the two pins we defined earlier.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  //This is the function to set the scaling factor, the first time around it needs to be blank (blank brackets) but once you have you result
  //You can input your result between the brackets and it should give you a weight very close to your known weight 
  scale.set_scale();

  //Setting a small delay to allow things to settle, this is my personal choice, probably not required.
  delay(10);

  //Setting the scale to remove the offset, which is likely just it's own weight - we don't want this while calibrating
  //If you have a platter or a board to put objects on, this should remove the offset it creates.
  scale.tare();

  //Setting a small delay to allow things to settle, this is my personal choice, probably not required.
  delay(10);

  //Letting the user know it is time to place their known weight on their load cell and that the yhave 5 seconds to do so.
  Serial.println("Place something on the scale and wait for confirmation");
  //Doing the actual delay - giving the user time to set the weight on the load cell
  delay(5000);

  //This will post the raw value of the load cell reading and this is the number you will have to divide by your known weight
  Serial.println(scale.get_units(10));

  
}

void loop() {

 //Nothing in here - doesn't seem to be needed. Subscribe to Simple Electronics (https://www.youtube.com/SimpleElectronics)

 //if this code saved your bacon - maybe consider Patreon? (https://www.patreon.com/SimpleElectronics)
 
}
