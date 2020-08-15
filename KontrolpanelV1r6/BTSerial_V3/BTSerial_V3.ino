/*Kontrolpanel a MaM 2020 robothoz
 *-------------------------------- 
 *
 * A panel dokumentációját az alábbi linken lehet elérni:
 * https://docs.google.com/spreadsheets/d/1e9qsqP2QveqOh3FMOY1uAww785WbkKQVrQv1eEnR9x0/edit?usp=sharing
 *
 */

#include "KontrolpanelV1r6.h"

//Led
#define ledPin 13

int state = 0;

// Beállítjuk az összes lábat kimenetre
void setup() {
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(BA,INPUT_PULLUP);
  pinMode(BB,INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  /* Egy troll szerint a default kommunikációs baudrate 38400, 
  ami hülyeség mivel a Bluetooth 9600-os működik a dokuk szerint, 
  de a jelenlegi program kód a 115200-al műkdöik rendesen*/
  Serial.begin(115200);
} 
void loop() {
  Kontrolpanel(); // Meghívja a kontrolpanel nevű függvényt a KontrolpanelV1r5.h nevű fájlból
  
  //Teszteléshez használatos kód
  if(Serial.available() > 0){ // Ellenőrzi hogy jött-e adat soros porton
    state = Serial.read(); // Elolvassa az adatot a soros portról
 }
 if (state == '0') {
  digitalWrite(ledPin, LOW); // Kapcsold LED OFF
  Serial.println("LED: OFF"); // Visszaküldi a telefonra a stringet "LED: ON"
  state = 0;
  Serial.print("State0:");
  Serial.println(state);
 }
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");;
  state = 1;
  Serial.print("State1:");
  Serial.println(state);
 }
 state = 0; 
}
