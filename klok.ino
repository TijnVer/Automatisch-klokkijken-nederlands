#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

DS3231 clock;
RTCDateTime dt;

LiquidCrystal_I2C lcd(0x27, 16, 2);  
void setup()
{
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__); // pakt tijd van laptop
  lcd.init(); 
  lcd.backlight();

  // Initialize DS3231
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Checking the");
  lcd.setCursor(0, 1);
  lcd.print("current time");
  Serial.println("Initialize DS3231");
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  


}

void loop()
{
  dt = clock.getDateTime();

  // For leading zero look to DS3231_dateformat example

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
   if(dt.second<10){
    lcd.print("0");
  }
  lcd.print(dt.second); lcd.print(" ");
  lcd.print(dt.day);    lcd.print("-");
  lcd.print(dt.month);  lcd.print("-");
  lcd.print("21");   
  
  
  lcd.setCursor(0, 1);
  if((dt.second & 1) == 0)
      pinMode(LED_BUILTIN, HIGH);
    else
    {
      pinMode(LED_BUILTIN, LOW);
    }
    Serial.println();
  
                                          // Tijd zeg minuten
  if(dt.minute==0){
    if(dt.hour<13){
    lcd.print(dt.hour); lcd.print(" uur");
    }
    if(dt.hour>=13){
    lcd.print(dt.hour-12); lcd.print(" uur");  
    }
  }
  if(dt.minute>0 && dt.minute<15){
    lcd.print(dt.minute); lcd.print(" over ");
  }
  if(dt.minute==15){
    lcd.print("kwart over ");
  }
  if(dt.minute<20 && dt.minute>15){
    lcd.print(dt.minute); lcd.print(" over ");
  }

  if(dt.minute>=20 && dt.minute<30){
    lcd.print(30-dt.minute); lcd.print(" voor half ");
  }
    if(dt.minute==30){
    lcd.print("half ");
  }
  if(dt.minute<=40 && dt.minute>30){
    lcd.print(dt.minute-30); lcd.print(" over half ");
  }
  if(dt.minute<45 && dt.minute>40){
    lcd.print(60-dt.minute); lcd.print(" voor ");
  }
  if(dt.minute==45){
    lcd.print("kwart voor ");
  }
  if(dt.minute<60 && dt.minute>45){
    lcd.print(60-dt.minute); lcd.print(" voor ");
  }

                                              // Tijd zeg uren

  if(dt.hour>0 && dt.hour<12){
    if(dt.minute>0 && dt.minute<20){
      lcd.print(dt.hour);
    }
    if(dt.minute>=20 && dt.minute<60){
      lcd.print(dt.hour+1);
    }
  } 
  if(dt.hour==12){
    if(dt.minute>0 && dt.minute<20){
      lcd.print(dt.hour);
    }
    if(dt.minute>=20 && dt.minute<60){
      lcd.print(dt.hour-11);
    }
  } 
  if(dt.hour<24 && dt.hour>12){
    if(dt.minute>0 && dt.minute<20){
      lcd.print(dt.hour-12);
    }
    if(dt.minute>=20 && dt.minute<60){
      lcd.print(dt.hour-11);
    }
  }                                           
  delay(1000);
}
