/*MOM 2019 Controll Panel*/
//############################################# INCLUDE ########################################################

//########################################## DEFINE #########################################################

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
//############################################# VARIABLES #####################################################
int buttonsState[4] = {0};
int oldState = 0;
char bttest_c = ' ';//bt modul tesztelesehez
int v_Servo_angle = 90; //180-40 mozgastartomány
int h_Servo_angle = 90;
int g_Servo_angle = 90;
//############################################# FUNCTIONS #####################################################

//############################################# SETUP ##########################################################

void setup() {
  pinMode(SW1, INPUT_PULLUP); //1-es kapcsoló
  pinMode(SW2, INPUT_PULLUP); //2-es kapcsoló
  pinMode(SW3, INPUT_PULLUP); //3-as kapcsoló
  pinMode(SW4, INPUT_PULLUP); //4-es kapcsoló
  pinMode(BA, INPUT_PULLUP); //Piros gomb
  pinMode(BB, INPUT_PULLUP); //Fekete gomb
  pinMode(ModeSwitch, INPUT_PULLUP); //üzemmód választó kapcsoló
  Serial.begin(38400);
  Serial3.begin(38400);
}
void test()
{
  Serial.println("                                       Test mode");
  Serial.println();
  scanner();
  Serial.println("#####################################################################################");
  Serial.println("##");
  Serial.print("##                                A potméter= ");
  Serial.println(analogRead(POT));
   Serial.println("##");
  Serial.print("##                         SW1-");
  Serial.print( buttonsState[0]);
  Serial.print(" SW2-");
  Serial.print( buttonsState[1]);
  Serial.print(" SW3-");
  Serial.print( buttonsState[2]);
  Serial.print(" SW4-");
  Serial.print( buttonsState[3]);
  Serial.print(" BA-");
  int ba = digitalRead(BA);
  if (ba == 1)
  {
    ba = 0;
  }
  else
  {
    ba = 1;
  }
  Serial.print(ba);
  Serial.print(" BB-");
  int bb = digitalRead(BB);
  if (bb == 1)
  {
    bb = 0;
  }
  else
  {
    bb = 1;
  }
  Serial.println(bb);
  Serial.println("##");
  Serial.println("#####################################################################################");

  Serial3.println("hello");
  /*char x[5];
  bttest_c =Serial3.readbytes(x,5);
  Serial.write(bttest_c);*/
  Serial3.readStringUntil("o");
  Serial.println();
  delay(3000);
}
void control_panel()
{
  int stateSumma = 0;
  
  //kiszámolja a gomb állapot összegét
  stateSumma = scanner(); // a gombok állapotát olvassa be

  //adat feldolgozás szükségessége
  if (stateSumma != oldState)
  {
    program_valaszto(stateSumma);
  }

  oldState = stateSumma;
  delay(10);//  ez törlendő

}

int scanner()
{
  int summa;
  buttonsState[0] = digitalRead(SW1);
  buttonsState[1] = digitalRead(SW2);
  buttonsState[2] = digitalRead(SW3);
  buttonsState[3] = digitalRead(SW4);
  summa = buttonsState[0] * 1 + buttonsState[1] * 2 + buttonsState[2] * 4 + buttonsState[3] * 8;
  return summa;

  
  }

//######################################################### SELECT PROGRAMS ##########################################
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
    case 4:// Golyó felvétel
      P4();
      break;
    case 8:// Bedobni az űrhajóba
      P8();
    // ide kell a tobbi gomb állapot 
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}
//################################################## SUBPROGRAMS ##########################################
void P0()//Minden léptető motor áll, a szervók abban az állapotban ahogy előtte állnak. És helyben forgás
{
  Serial.println("STOP");
  //ide jön a buli
  delay(1000);
}
void P1()//Előre menet
{
  Serial.println("Elore");

  Serial.println(analogRead(POT));
  delay(1000);
}

void P2()//Hátra menet
{
  Serial.println("Hatra");

  Serial.println(analogRead(POT));
  delay(1000);
}
void P4()//Golyó felvétel
{
  Serial.println("Golyo fel");

  Serial.println(analogRead(POT));
  delay(1000);
}
void P8()//Bedobni az űrhajóba
{
  Serial.println("Urhajoba");

  Serial.println(analogRead(POT));
  delay(1000);
}

//############################################ MAIN ###########################################
void loop() {
  int mode = digitalRead(ModeSwitch);
  if (mode == 1 ) {
    test();
  }
  else
  {
    control_panel();
  }


}
