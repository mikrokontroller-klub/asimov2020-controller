/*Kontrolpanel a MaM 2020 robothoz
 *-------------------------------- 
 *
 * V4
 *
 */

#include "KontrolpanelV2r1.h"

// Beállítjuk az összes lábat kimenetre
void setup() {
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(BA,INPUT_PULLUP);
  pinMode(BB,INPUT_PULLUP);

  Serial.begin(115200);
} 
void loop() {
  Kontrolpanel(); // Meghívja a Kontrolpanel nevű függvényt a KontrolpanelV1r5.h nevű fájlból
}
