#include <Arduino.h>

char data[10];
char* begin = "#";
int potV = 330;
char* motB = "1";
char* motJ = "0";
int s_Servo = 120;
int h_Servo = 110;
int g_Servo = 100;
int x_Servo = 90;
char* end = "*";

void setup() {
  Serial.begin(9600);
   while (!Serial) {
    delay(10); 
   }
  sprintf(data,"%s,%d,%s,%s,%d,%d,%d,%d,%s",begin,potV,motB,motJ,s_Servo,h_Servo,g_Servo,x_Servo,end);
  Serial.println(data);
  //char,int,char,char,int,int,int,int,char
}

void loop() {

}

