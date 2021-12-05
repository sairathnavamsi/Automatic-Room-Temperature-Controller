
  const int temp_trans_pin = A0, Heater_pin = 10, FAN_pin = 6;

  float MinTemp = 20, MaxTemp = 25;

  #include <LiquidCrystal.h>


  LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

  void setup() { //setup phase
      
    LCD.begin(16, 2);
    pinMode(Heater_pin, OUTPUT); //Initialise pinmodes
    pinMode(FAN_pin, OUTPUT);

    
    LCD.print("Temp Range:"); // print optimal temperature
    LCD.setCursor(2,1);
    LCD.print(MinTemp); LCD.print("-");LCD.print(MaxTemp);
    
    delay(5000);
 }

 void loop() { //loop phase
   
   float Eqv_volt, SensorTemp;
 
   
   Eqv_volt = analogRead(temp_trans_pin) * 5.0 / 1023; //calculate temperature from sensor output
   SensorTemp = 100.0 * Eqv_volt-50.0;  
  
   if(SensorTemp > MaxTemp){ // high temperature
      LCD.clear();
      LCD.print("High temp:");
      LCD.print(SensorTemp);
	  LCD.setCursor(2,1);
      LCD.print("Cooler ON"); //turn on cooler
      int spd = map(SensorTemp, 25, 45, 0, 255);
      analogWrite(Heater_pin, 0); //turn off heater
      analogWrite(FAN_pin, spd);
      }
   
  else if(SensorTemp < MinTemp){ // low temperature
      LCD.clear();
      LCD.print("Low temp:");
      LCD.print(SensorTemp);
	  LCD.setCursor(2,1);
      LCD.print("Heater ON"); //turn on heater
      int spd = map(analogRead(temp_trans_pin), 143, 20, 0, 255);
      analogWrite(FAN_pin, 0); //turn off cooler
      analogWrite(Heater_pin, spd);

      }
  
   else if(SensorTemp > MinTemp && SensorTemp < MaxTemp){//optimal temperature
      LCD.clear();
      LCD.print("Normal temp:");
	  LCD.print(SensorTemp);
	  LCD.setCursor(2,1);
      LCD.print("Idle");     
      analogWrite(FAN_pin, 0); //turn off cooler
      digitalWrite(Heater_pin, LOW); //turn off cooler

   }
  else {
      LCD.clear();
      LCD.print("Something is");
      LCD.setCursor(2,1); LCD.print("Wrong");
      delay(1000);
      LCD.clear();
    }
    delay(1000);
   } 