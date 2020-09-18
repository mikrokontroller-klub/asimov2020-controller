/*Létrehozott változók
* char data[10]; //Ebben(a bufferben) tároljuk a protokol szerinti értékeket - GLOBÁLIS
* char* bgn = "#"; //Ezzel Kezdődik - GLOBÁLIS
* char* motB = "1"; //Baldldali motor - LOKÁLIS
* char* motJ = "0"; //Jobboldali motor - LOKÁLIS
* char* nd = "*"; //Ezzel végződik - GLOBÁLIS
* A 4. szervónak x_Servo nevet adtam, hogy tudjak haladni a programmal
*/

void P1() //Előre menet
{
  char *motB = ""; //Baloldali motor
  char *motJ = ""; //Jobboldali motor
  while (scanner() != 0) //Amíg az érték nem egyenlő a nullával, csinálja az alábbit:
  {
    int btA = digitalRead(BA);
    int btB = digitalRead(BB);
    if (btA == 0) //Ha a baloldali piros gomb le van nyomva, menjen balra
    {
      int potV = analogRead(POT);
      potV = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6);
      motB = "0";
      motJ = "1";
      Serial.println("BALRA ELORE");
      sprintf(data, "%s,%d,%s,%s,%d,%d,%d,%d,%s", bgn, potV, motB, motJ, s_Servo, h_Servo, g_Servo, x_Servo, nd);
      //char,int,char,char,int,int,int,int,char
      Serial.println(data);
      Serial3.println(data);
    }
    if (btB == 0) //Ha a jobbldali fekete gomb le van nyomva, menjen jobbra
    {
      int potV = analogRead(POT);
      potV = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6);
      motB = "1";
      motJ = "0";
      Serial.println("JOBBRA ELORE");
      sprintf(data, "%s,%d,%s,%s,%d,%d,%d,%d,%s", bgn, potV, motB, motJ, s_Servo, h_Servo, g_Servo, x_Servo, nd);
      //char,int,char,char,int,int,int,int,char
      Serial.println(data);
      Serial3.println(data);
    }
    if (btA == 1 && btB == 1) //Ha a baloldali piros és jobbldali fekete gombok nincsenek lenyomva
    {
      int potV = analogRead(POT);
      potV = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6);
      if (potV > 0) //Ha a sebesség nagyobb mint 0, menjen előre
      {
        motB = "1";
        motJ = "1";
        Serial.println("ELORE");
        sprintf(data, "%s,%d,%s,%s,%d,%d,%d,%d,%s", bgn, potV, motB, motJ, s_Servo, h_Servo, g_Servo, x_Servo, nd);
        //char,int,char,char,int,int,int,int,char
        Serial.println(data);
        Serial3.println(data);
      }
      else //Különben álljon meg
      {
        motB = "0";
        motJ = "0";
        Serial.println("STOP");
        sprintf(data, "%s,%d,%s,%s,%d,%d,%d,%d,%s", bgn, potV, motB, motJ, s_Servo, h_Servo, g_Servo, x_Servo, nd);
        //char,int,char,char,int,int,int,int,char
        Serial.println(data);
        Serial3.println(data);
      }
    }
  }
}