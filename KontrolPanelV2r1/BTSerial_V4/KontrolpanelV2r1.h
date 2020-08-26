/*Kontrolpanel a MaM 2020 robothoz
 *-------------------------------- 
 *
 * V2r1
 *
 */

//Potméter
#define POT A1

//Kapcsolók  
#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5

//Gombok
#define BA 6
#define BB 7

//Sebesség
#define minSV 1365 //minimumSpeedValue
#define maxSV 2730 //maximumSpeedValue

//Változók
boolean vs1 = 0; //Kapcsoló 1
boolean vs2 = 0; //Kapcsoló 2
boolean vs3 = 0; //Kapcsoló 3
boolean vs4 = 0; //Kapcsoló 4
boolean A = 0; //Gomb A(piros gomb)
boolean B = 0; //Gomb B(fekete gomb)

int potV = 0; //Potméter érték

//A lábak kiértékelése után ezeket a változókat fogjuk összeadni
int av = 0;
int bv = 0;
int sw1V = 0;
int sw2V = 0;
int sw3V = 0;
int sw4V = 0;


int buttonValue = 90; //Ez a szervó motorok kezdő értéke

int additionV = 0; //Az összeadások értékét tartalmazza

int Speed = 0; //Ez lesz a potméterrel állított sebesség

String gear = ""; //Ebbe a sztringbe töltjük bele a későbbiekben a potméter sebességeit

//Ezekbe a sztringekbe töltjük bele későbbiekben a kapcsolók értékeit
String switchOne = ""; 
String switchTwo = "";
String switchThree = "";
String switchFour = "";

void scanner() //Az alábbi fügvény kiértékeli az összes láb értékét 
{
  potV = analogRead(POT);
  vs1 = digitalRead(SW1);
  vs2 = digitalRead(SW2);
  vs3 = digitalRead(SW3);
  vs4 = digitalRead(SW4);
  A = digitalRead(BA);
  B = digitalRead(BB);  
}

void pot_evaluation() //Itt a potméter értékeinek elosztása és sebesség megadása történik
{
  if (potV > 0 && potV < 180)
  {
    gear = "000,"; 
  }
  else if (potV > 183 && potV < 330)
  {
    gear = "001,"; 
  }
  else if (potV > 333 && potV < 480)
  {
    gear = "002,"; 
  }
  else if (potV > 483 && potV < 630)
  {
    gear = "003,"; 
  }
  else if (potV > 633 && potV < 780)
  {
    gear = "004,"; 
  }
  else if (potV > 783 && potV < 930)
  {
    gear = "005,"; 
  }   
}

/*
* Itt a kapcsolók kiértékelése és érték megadása történik
* Itt maradt a 2. verziós protokol szerinti 3 karakteres érték megadás
*/
void switch_evaluation() 
{
  if(vs1==HIGH)
  {
    switchOne = "001,";
  }
  else
  {
    switchOne = "000,";
  }
  
  if(vs2==HIGH)
  {
    switchTwo = "002,";
  }
  else
  {
    switchTwo = "000,";  
  }
  
  if(vs3==HIGH)
  {
   switchThree = "003,";
  }
  else
  {
    switchThree = "000,";  
  }
  
  if(vs4==HIGH)
  {
   switchFour = "004,";
  }
  else
  {
    switchFour = "000,";
  }          
}

void button_evaluation() //Ebben a függvényben a gombok kiértékelése történik
{
  int lowerLimit = 0;
  int upperLimit = 180;  
  if(A==LOW)
  {
    buttonValue += 10;
    if(buttonValue >= upperLimit) //Ha nagyobb a gomb értéke mint 180, akkor az értéke legyen 180
    {
      buttonValue = upperLimit;
    }
    if(buttonValue <= lowerLimit) //Ha kissebb a gomb értéke mint 0, akkor az értéke legyen 0
    {
      buttonValue = lowerLimit;
    }
  }
  if(B==LOW)
  {
    buttonValue -= 10;
    if(buttonValue >= upperLimit) //Ha nagyobb a gomb értéke mint 180, akkor az értéke legyen 180
    {
      buttonValue = upperLimit;
    }
    if(buttonValue <= lowerLimit) //Ha kissebb a gomb értéke mint 0, akkor az értéke legyen 0
    {
      buttonValue = lowerLimit;
    }
    
  }
}

void value_addition() //Itt történik a különböző függvények összefogása egy függvénybe
{
  scanner();
  pot_evaluation();
  switch_evaluation();
  button_evaluation();  
}

void serial_monitor() //Itt iratjuk ki a soros monitorra az értékeket
{
  Serial.print("#"); //Az adat kezdete
  Serial.print(switchOne);
  Serial.print(gear);
  Serial.print(switchTwo);
  Serial.print(gear);   
  /*Serial.print(switchThree);
  Serial.print(gear);  
  Serial.print(switchFour);
  Serial.print(gear);*/
  Serial.print(buttonValue);
  Serial.print(",");
  Serial.print(gear);
  Serial.print(buttonValue);
  Serial.print(",");  
  Serial.print(gear);
  Serial.print(buttonValue);
  Serial.print(",");  
  Serial.print(gear);
  Serial.print(buttonValue);
  Serial.print(",");  
  Serial.print(gear);         
  Serial.println("*"); //Az adat vége
}

void Kontrolpanel() //Itt fogjuk össze az összeadásért és a soros minmotta kiíró függvényenyeket, aztán ezt a függvényt(Kontrolpanel) rakjuk be a fő programba a loopba
{
  value_addition();
  serial_monitor();
  
  delay(100);
}
