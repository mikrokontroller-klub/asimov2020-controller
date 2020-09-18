/*==========================================================================
 * Project: sprintf functionality
 * Author:  Scott C
 * Date created: 06 May 2019
 * Arduino IDE version: 1.8.5
 * Operating System: Windows 10 Pro
 * Tutorial Link: https://arduinobasics.blogspot.com/2019/05/sprintf-function.html
 * 
 * Acknowledgements:
 * The following resource was a key element of this tutorial: http://www.cplusplus.com/reference/cstdio/printf/
 * Another useful resource can be found here: https://en.wikipedia.org/wiki/C_data_types
 * 
 *------------------------------------------------------------------------------
 * Code Explanation
 * -----------------------------------------------------------------------------
 * Begin serial communication at a baud rate of 9600
 * Wait until Serial communication has established before continuing
 * 
 * The sprintf function will write the formatting string and the variables into the "data" character array.
 * You provide a formatting string template, that contains placeholders for variables that you plan to insert.
 * These placeholders have a percentage sign (%) prefix.  Eg.  %s, %d, %f etc.
 * The number of placeholders must match the number of variables.
 * The variables are inserted at the placeholder position, and formatted based on the type of placeholder used.
 * %d = signed integer               %f = floating point number  
 * %s = string                     %.1f = float to 1 decimal place
 * %c = character                  %.3f = float to 3 decimal places
 * %e = scientific notation          %g = shortest representation of %e or %f                
 * %u = unsigned integer             %o = unsigned octal
 * %x = unsigned hex (lowercase)     %X = unsigned hex (uppercase)
 * %hd = short int                  %ld = long int
 * %lld = long long int
 * =============================================================================  */

#include <Arduino.h>

char data[100];
char* myName = "ArduinoBasics";
char* myBlog = "https://arduinobasics.blogspot.com";
int year = 2019;
int num = 49;
char myChar = 'a';
float myFloat = 99.9911;
long long int vLong = 1234567890123456789LL;


void setup() {
  Serial.begin(9600);
   while (!Serial) {
    delay(10); 
   }

  sprintf(data, "Tutorial by: %s", myName);
  Serial.println(data);
  
  sprintf(data, "Year: %u, Blog Link: %s",year,myBlog);
  Serial.println(data);

  Serial.println();

  sprintf(data, "Character: %c , %c", num, myChar);
  Serial.println(data);

  sprintf(data, "Integer (d): %d , Width(8d): %8d , Zero Prefix Width(07d): %07d", num, num, num);
  Serial.println(data);

  sprintf(data, "Floats f: %f , .1f: %.1f , .3f: %.3f", myFloat, myFloat, myFloat);
  Serial.println(data);

  sprintf(data, "Scientific e: %e , g: %g", myFloat , myFloat);
  Serial.println(data);

  sprintf(data, "Radices u: %u , #o: %#o , x: %x , #x: %#x ", num, num, num, num);
  Serial.println(data);

  sprintf(data, "Big Number lld: [%lld  + 1 = %lld]", vLong, vLong+1);
  Serial.println(data);
}

void loop() {
  //do nothing
}