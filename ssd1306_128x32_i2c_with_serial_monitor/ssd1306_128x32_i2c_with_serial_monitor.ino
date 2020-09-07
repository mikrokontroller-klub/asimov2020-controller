#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3C for 128x32
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  //testdrawstyles();    // Draw 'stylized' characters

  /*// Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);*/  
}

void loop() 
{
    char charlie = 0; 
    if (Serial.available() > 0) {    // is a character available?
      charlie = Serial.read();       // get the character
      
      if ((charlie >= '0') && (charlie <= '4')) 
      {
        //display.clearDisplay();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("Hello, world!"));
        Serial.println("Hello, world!");
        display.display();
      }
      else if ((charlie >= '5') && (charlie <= '9'))
      {
        display.clearDisplay();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_BLACK);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F(" "));
        Serial.println("Nothing");
        display.display();      
      } 
    }
}    
