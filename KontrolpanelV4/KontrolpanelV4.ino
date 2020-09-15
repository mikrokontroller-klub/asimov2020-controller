/*MOM 2019 Controll Panel*/
//############################################# INCLUDE ######################################################

//############################################# DEFINE #######################################################

#define ATpin 53 //Itt a Bluetooth BTM-5 RevA modul Mode lábát definiáljuk
#define ModeSwitch 8
#define POT A1 //Potméter
#define POTMETER_MIN 0
#define POTMETER_MAX 1024

//A kapcsolók balról jobbra olvasandók, tehát 1, 2, 3, 4 ha frontból nézzük a táblát
#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5

//Gombok
#define BA 6 //Piros gomb
#define BB 7 //Fekete gomb
//############################################# VARIABLES ###################################################
int buttonsState[4] = {0};
int oldState = 0;
int stateSumma = 0;

//Szervók
int v_Servo = 0;
int h_Servo = 0;
int g_Servo = 0;
//############################################# FUNCTIONS ###################################################

//############################################# SETUP #######################################################

void setup() {
  pinMode(SW1, INPUT_PULLUP); //1-es kapcsoló
  pinMode(SW2, INPUT_PULLUP); //2-es kapcsoló
  pinMode(SW3, INPUT_PULLUP); //3-as kapcsoló
  pinMode(SW4, INPUT_PULLUP); //4-es kapcsoló
  pinMode(BA, INPUT_PULLUP); //Piros gomb
  pinMode(BB, INPUT_PULLUP); //Fekete gomb
  pinMode(ModeSwitch, INPUT_PULLUP); //Üzemmód választó kapcsoló
  Serial.begin(38400);
  Serial3.begin(38400);
}
void debug()
{
  Serial.println("Test mode");

  delay(1000);
}

void control_panel()
{
  scanner(); //A gombok állapotát olvassa be
  //Kiszámolja a gomb állapot összegét
  stateSumma = buttonsState[0] * 1 + buttonsState[1] * 2 + buttonsState[2] * 4 + buttonsState[3] * 8;

  //Adat feldolgozás szükségessége
  if (stateSumma != oldState)
  {
    program_valaszto(stateSumma);
  }

  oldState = stateSumma;
  delay(10);//Ez törlendő

}

void scanner()
{

  buttonsState[0] = digitalRead(SW1);
  buttonsState[1] = digitalRead(SW2);
  buttonsState[2] = digitalRead(SW3);
  buttonsState[3] = digitalRead(SW4);
  }

//############################################# SELECT PROGRAMS #############################################
void program_valaszto(int program)
{
  Serial.println(program);
  //A programok akkor indulnak mikor kiválasztjuk a programot és megnyomjuk valamelyik nyomógombot!!!!!!!!
  switch (program)
  {
    case 0://Minden áll
      P0();
      break;
    case 1://Előre menet
      P1();
      break;
    case 2://Hátra menet
      P2();
      break;
    case 4://Golyó felvétel
      P4();
      break;
    case 8://Bedobni az űrhajóba
      P8();
    case 16://Balra
      Px1();
      break;
    case 32://Jobbra
      Px2();
      break;      
    // ide kell a tobbi servo allapot 
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}
//############################################# INCLUDE #####################################################
void P0()//Minden léptető motor áll, a szervók abban az állapotban ahogy előtte állnak.
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 0)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue == 0)
      {
        Serial.println("STOP");
        Serial3.println((String)"#,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"*");
        //#,0,0,0,0,0,0,0,0,0,0,0,0,* - ez csak egy példa       
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void P1()//Előre
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 1)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue > 0)
      {
        Serial.println("Előre");
        Serial3.println((String)"#,"+"1,"+mappedValue+"1,"+mappedValue+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"*");        
        //#,1,x,1,x,0,0,0,0,0,0,0,0,* - ez csak egy példa       
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void P2()//Hátra
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 2)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue > 0)
      {
        Serial.println("Hátra");
        Serial3.println((String)"#,"+"0,"+mappedValue+"0,"+mappedValue+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"*");
        //#,0,x,0,x,0,0,0,0,0,0,0,0,* - ez csak egy példa       
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void P4()//Golyó felvétel
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 8)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue > 0)
      {
        v_Servo = 90;
        h_Servo = 120;
        g_Servo = 150;                
        Serial.println("Felvétel");
        Serial3.println((String)"#,"+"0,"+mappedValue+"0,"+mappedValue+"0,"+v_Servo+mappedValue+h_Servo+mappedValue+g_Servo+mappedValue+"0,"+"*");     
        //#,1,x,0,x,90,0,120,0,150,0,0,0,* - ez csak egy példa       
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void P8()//Bedobni az űrhajóba
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 24)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue > 0)
      {
        v_Servo = 150;
        h_Servo = 120;
        g_Servo = 90;          
        Serial.println("Űrhajóba");
        Serial3.println((String)"#,"+"0,"+mappedValue+"0,"+mappedValue+"0,"+v_Servo+mappedValue+h_Servo+mappedValue+g_Servo+mappedValue+"0,"+"*");     
        //#,1,x,0,x,150,0,120,0,90,0,0,0,* - ez csak egy példa    
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}


void Px1()//Balra
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 1 || stateSumma == 2 || stateSumma == 0)
  {
    if (BA == 1 && BB == 0)
    {
      if (mappedValue > 0)
      {
        Serial.println("Balra");
        Serial3.println((String)"#,"+"0,"+mappedValue+"1,"+mappedValue+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"*");
        //#,0,x,1,x,0,0,0,0,0,0,0,0,* - ez csak egy példa       
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void Px2()//Jobbra
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 1 || stateSumma == 2 || stateSumma == 0)
  {
    if (BA == 0 && BB == 1)
    {
      if (mappedValue > 0)
      {
        Serial.println("Jobbra");
        Serial3.println((String)"#,"+"1,"+mappedValue+"0,"+mappedValue+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"0,"+"*");     
        //#,1,x,0,x,0,0,0,0,0,0,0,0,* - ez csak egy példa       
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}
//############################################# MAIN ########################################################
void loop() {
  int mode = digitalRead(ModeSwitch);
  if (mode == 1 ) {
    debug();
  }
  else
  {
    control_panel();
  }
}
