void P0()//Minden léptető motor áll, a szervók abban az állapotban ahogy előtte állnak. | 1.
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
        Serial3.println("#","0","0","0","0","0","0","0","0","0","0","0","0","*");
        //#,0,0,0,0,0,0,0,0,0,0,0,0,*      
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void P1()//Előre | 2.
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 1)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue > 0)
      {
        Serial.println("ELŐRE");
        Serial3.println("#","1"+mappedValue+"1"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"*");      
        //#,1,pot,1,pot,0,pot,0,pot,0,pot,0,pot,*     
       }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void P2()//Hátra | 3. 
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 2)
  {
    if (BA == 0 && BB == 0)
    {
      if (mappedValue > 0)
      {
        Serial.println("HÁTRA");
        Serial3.println("#","2"+mappedValue+"2"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"*");      
        //#,2,pot,2,pot,0,pot,0,pot,0,pot,0,pot,* 
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

void Px()//Gyorsan előre balra | 4.
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 1)
  {
    if (BA == 1 && BB == 0)//A megfelelő értékkel ki kell majd helyettesíteni az 1-et és 0-t
    {
      if (mappedValue > 0)
      {
        Serial.println("GYORSAN ELŐRE  BALRA");
        Serial3.println("#","2"+mappedValue+"1"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"*");      
        //#,2,pot,1,pot,0,pot,0,pot,0,pot,0,pot,* 
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void Px()//Gyorsan előre jobbra | 5.
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 1)
  {
    if (BA == 0 && BB == 1)//A megfelelő értékkel ki kell majd helyettesíteni az 0-t és az 1-et
    {
      if (mappedValue > 0)
      {
        Serial.println("GYORSAN ELŐRE JOBBRA");
        Serial3.println("#","1"+mappedValue+"2"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"*");      
        //#,1,pot,2,pot,0,pot,0,pot,0,pot,0,pot,* 
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void Px()//Balra | 6.
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 0)
  {
    if (BA == 1 && BB == 0)//A megfelelő értékkel ki kell majd helyettesíteni az 1-et és 0-t
    {
      if (mappedValue > 0)
      {
        Serial.println("BALRA");
        Serial3.println("#","0"+mappedValue+"1"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"*");      
        //#,0,pot,1,pot,0,pot,0,pot,0,pot,0,pot,* 
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}

void Px()//Jobbra | 7.
{
  int potV = analogRead(POT); 
  byte mappedValue = map(potV, POTMETER_MIN, POTMETER_MAX, 0, 6); 
  if (stateSumma == 0)
  {
    if (BA == 0 && BB == 1)//A megfelelő értékkel ki kell majd helyettesíteni az 1-et és 0-t
    {
      if (mappedValue > 0)
      {
        Serial.println("JOBBRA");
        Serial3.println("#","1"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"0"+mappedValue+"*");      
        //#,1,pot,0,pot,0,pot,0,pot,0,pot,0,pot,* 
      }
    }
  }
  else
  {
    control_panel();  
  }
  delay(1000);
}
