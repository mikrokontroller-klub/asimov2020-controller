//Potméter
#define POT A7

//Kapcsolók
#define SW1 2
#define SW2 4
#define SW3 6
#define SW4 8

//Gombok
#define BA 10
#define BB 12

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

int Speed = 0; //Ez lesz a potméterrel állított sebesség

int additionV = 0; //Az összeadások értékét tartalmazza

void scanner()
{
  delay(100);
  potV = analogRead(POT);
  Serial.print("x:");
  Serial.println(potV);
  vs1 = digitalRead(SW1);
  vs2 = digitalRead(SW2);
  vs3 = digitalRead(SW3);
  vs4 = digitalRead(SW4);
  A = digitalRead(BA);
  B = digitalRead(BB);  
}

void pot_evaluation() //Itt történik a potméter értékeinek szétosztása
{
  //scanner();
//A megoldas (ezzel pontosabban lehet beállítani)
/*  if (potV<minSV)
      {
        Speed = 1;
      }
      else if(potV>maxSV)
            {
              Speed = 3;
            }
            else 
            {
              Speed = 2;
            }
 */
// B megoldas (ezzel kevésbé pontosabb)         
  Speed = potV;
  //1366+1;   
}

void value_evaluation() //Itt folyik a lábak kiértékelése
{
  //scanner();
//--------------  
  if(vs1==HIGH)
  {
   sw1V = 1;
  }
    else
     {
      sw1V = 64; 
     }
  if(vs2==HIGH)
  {
   sw2V = 2;
  }
    else
    {
     sw2V = 128;  
    }
  if(vs3==HIGH)
  {
   sw3V = 4; 
  }
    else
    {
      sw3V = 256;     
    }
  if(vs4==HIGH)
  {
   sw4V = 8; 
  }
    else
    {
     sw4V = 512; 
    }
//--------------
  if(A==LOW)
  {
   av = 1024; 
  }
    else
    {
      av = 16;
    }
  if(B==LOW)
  {
   bv = 2048; 
  }
    else
    {
      bv = 32;
    }        
}

void value_addition() //Itt történik a különböző változók öesszeadása egy változóvá
{
  scanner();
  value_evaluation();
  pot_evaluation();  
  //additionV = sw1V + sw2V + sw3V + sw4V +  av + bv; //Összeadja a kiértékeléskor kapott változókat 
                                                      //A V1r3-as verzió ezzel működik, ezt kell kiíratni a soros monitorra
}

void serial_monitor()
{
  Serial.print("Kapcsolók: "); 
  Serial.print(sw1V); //1-es kapcsoló
  Serial.print("|");
  Serial.print(sw2V); //2-es kapcsoló
  Serial.print("|");
  Serial.print(sw3V); //3-as kapcsoló
  Serial.print("|");
  Serial.println(sw4V); //4-es kapcsoló
  Serial.print("Gombok: ");
  Serial.print(av); //A gomb
  Serial.print("|");
  Serial.println(bv); //B gomb
  Serial.print("Potméter: ");
  Serial.println(Speed);
  Serial.println("--------------------------");
}

void binary_translator() //Terveben lévő függvény az egyszerűb adat küldés miatt
{
  
}

void Kontrolpanel() 
{
  value_addition();
  serial_monitor();
  
  delay(500);
}
