//Változók: motorok statikusak, a pot változó, a szervók globális változók
void P1()//Előre menet
{
  //Serial.println("Elore");
  while (scanner() != 0)
  {
    int btA = digitalRead(BA);
    int btB = digitalRead(BB);
    if (btA == 0)
    {
      int potV = analogRead(POT);
      potV = map(potV,POTMETER_MIN,POTMETER_MAX,0,6);
      Serial.println("BALRA ELORE"); 
    }
    if (btB == 0)
    {
      int potV = analogRead(POT);
      potV = map(potV,POTMETER_MIN,POTMETER_MAX,0,6);
      Serial.println("JOBBRA ELORE");
    }
    if (btA == 1 && btB == 1)
    {
      int potV = analogRead(POT);
      potV = map(potV,POTMETER_MIN,POTMETER_MAX,0,6);
      if(potV > 0)
      {
      Serial.println("ELORE");
      }
      else
      {
        Serial.println("STOP"); 
      }
    }        
  }
}
