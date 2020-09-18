
void P1() //Előre menet
{
  //Ha a potméter 0, akkor ne csinálon semmit ,ne leheseen forogni vagy akármit csinálni 
  char data[27]; //Karakterek megszámolása FONTOS!
  while (scanner() != 0) //Amíg az érték nem egyenlő a nullával, csinálja az alábbit:
  {
    int btA = digitalRead(BA);
    int btB = digitalRead(BB);
    if (btA == 0) //Ha a baloldali piros gomb le van nyomva, menjen balra
    {
      int potV = analogRead(POT);
      potV = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6);
      Serial.println("BALRA ELORE");
      sprintf(data, "#,%d,0,1,%d,%d,%d,0,*", potV, v_Servo_angle, h_Servo_angle, g_Servo_angle);
      //#int,x,x,int,int,int,int*
      Serial.println(data);
      Serial3.println(data);
    }
    if (btB == 0) //Ha a jobbldali fekete gomb le van nyomva, menjen jobbra
    {
      int potV = analogRead(POT);
      potV = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6);
      Serial.println("JOBBRA ELORE");
      sprintf(data, "#,%d,1,0,%d,%d,%d,0,*", potV, v_Servo_angle, h_Servo_angle, g_Servo_angle);
      //#int,x,x,int,int,int,int*
      Serial.println(data);
      Serial3.println(data);
    }
    if (btA == 1 && btB == 1) //Ha a baloldali piros és jobbldali fekete gombok nincsenek lenyomva
    {
      int potV = analogRead(POT);
      potV = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6);
      if (potV > 0) //Ha a sebesség nagyobb mint 0, menjen előre
      {
        Serial.println("ELORE");
        sprintf(data, "#,%d,1,1,%d,%d,%d,0,*", potV, v_Servo_angle, h_Servo_angle, g_Servo_angle);
        //#int,x,x,int,int,int,int*
        Serial.println(data);
        Serial3.println(data);
      }
      else //Különben álljon meg
      {
        Serial.println("STOP");
        sprintf(data, "#,%d,1,1,%d,%d,%d,0,*", potV, v_Servo_angle, h_Servo_angle, g_Servo_angle);
        //#int,x,x,int,int,int,int*
        Serial.println(data);
        Serial3.println(data);
        //Ha minden 0 akkor a léptető motorok ne mozduljanak meg, a szervók tartsák az eredeti pozíciójukat, ne forogjon
      }
    }
    delay(1000); //ki kell kapcsolni
  }
}
