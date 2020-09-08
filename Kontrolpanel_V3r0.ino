/*Kontrolpanel a MaM 2020 robothoz
 *-------------------------------- 
 * V3r0
 * Képes bluetooth-on kommunikálni Master --> Slave(notBLM) módban
 * Kiírja az Adafruit_SSD1306 OLED kijelzőre az adatokat
 * 
 * Módosítva 2020.09.08 - Ármin A. Rába 
 */

#include <SPI.h>
#include <Wire.h>
//Meghívja az Adafruit kijelzőjéhez való könyvtárakat 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Adafruit_SSD1306 OLED kijelző
#define SCREEN_WIDTH 128 // OLED kijelző szélesség, pixelekben
#define SCREEN_HEIGHT 32 // OLED kijelző magasság, pixelekben

// Deklarálja a(z) SSD1306 kijelzőt a(z) I2C-hez (SDA, SCL pins)
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define ATpin 53 //Itt a Bluetooth modul Mode lábát definiáljuk

#define POT A1 //Potméter

//A kapcsolók balról jobbra olvasandók, tehát 1, 2, 3, 4 ha frontból nézzük a táblát 
#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5

//Gombok
#define BA 6 //Piros gomb
#define BB 7 //Fekete gomb

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

String comma = ","; //A serial_write() függvénynél használatos

char inChar;
String strWrite = ""; //Erre a sztringre írjuk rá a kapcsolókról, gombokról és a potméterről beérkező adatokat

void setup() {
  //A kapcsolók balról jobbra olvasandók, tehát 1, 2, 3, 4 ha frontból nézzük a táblát 
  pinMode(SW1,INPUT_PULLUP); //1-es kapcsoló
  pinMode(SW2,INPUT_PULLUP); //2-es kapcsoló
  pinMode(SW3,INPUT_PULLUP); //3-as kapcsoló
  pinMode(SW4,INPUT_PULLUP); //4-es kapcsoló
  pinMode(BA,INPUT_PULLUP); //Piros gomb
  pinMode(BB,INPUT_PULLUP); //Fekete gomb

  Serial.begin(9600); //Soros monitor

  //Bluetooth eleje
  Serial3.begin(38400); //Bluetooth kommunikációs baudrate
  pinMode(ATpin,OUTPUT); //Beállítjuk a bluetooth modul Mode nevű lábát kimenetre
  
  /*digitalWrite(ATpin,HIGH); //Bekapcsol az AT command mód
  Serial3.println("AT+STATE?"); //A program indulásakor megkérdezi hogy milyen állapotban van a bluetooth kapcsolati státusza
  while(!Serial3.read == 1);
  Serial.println("CONNECTED");*/
  
  digitalWrite(ATpin,LOW);   
  /*Ha LOW-on van, tud kommunikálni a környező bluetooth eszközökkel.
    Míg ha HIGH-on, bekapcsol az AT command mód, 
    ahol a modul beálításait lehet állítani.
  */
  //Bluetooth vége
  
  //OLED SSD1306 kijelző eleje
  // inicializálja a I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);       

  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(INVERSE);
  display.display(); 
  //OLED SSD1306 kijelző vége
} 

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
  byte mappedValue = map(potV, 0, 1023, 1, 7); //A potméter 30-930 között működik 2020.09.08
  //Serial.println(mappedValue);
  
  switch(mappedValue) //A mappedValue értékének megfelelően küldi el a protokolnak megfelelő sztringet
  {
    case 1:   gear = "000,";
              break;
    case 2:   gear = "001,";
              break;
    case 3:   gear = "002,";
              break;
    case 4:   gear = "003,";
              break;
    case 5:   gear = "004,";
              break;
    case 6:   gear = "005,";
              break;       
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

void serial_write()
{
  //Az adat kezdete
  strWrite = ("#"+switchOne+gear+switchTwo+gear+switchThree+gear+switchFour+gear+buttonValue+comma+gear+buttonValue+comma+buttonValue+comma+gear+buttonValue+comma+gear+buttonValue+comma+gear+"*"); //Az adat vége
  Serial3.println(strWrite); //Kiírja a bluetooth sorosportjára(38400)
  Serial.println(strWrite); //Kiírja a sorosportra(9600)
}

void display_write()
{  
    display.clearDisplay();
    inChar = Serial.read();
    strWrite+=inChar;               
    display.setCursor(0,0); 
    display.print(strWrite);               
    display.display();
    //delay(10);   
    if(inChar == '\r')display.clearDisplay();        
}

void function_addition() //Itt történik a különböző függvények összefogása egy fő függvénybe
{
  scanner();
  pot_evaluation();
  switch_evaluation();
  button_evaluation();
  serial_write();
  display_write();
  delay(10);      
}

void loop() 
{
  function_addition(); // Meghívja a function_addition() nevű függvényt
}
