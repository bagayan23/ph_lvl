#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
float calibri_val =21.34;
int phval=0;
unsigned long int avgval;
int buffer_arr[10], temp;

void setup() {
Serial.begin(115200);
lcd.init();
lcd.begin(16, 2);
lcd.backlight();
lcd.setCursor(2,0);
lcd.print("PH");
lcd.setCursor(3,1);
lcd.print("Level");
delay(3000);
lcd.clear();
}

void loop() {
for(int i=0;i<10;i++) 
  { 
    buffer_arr[i]=analogRead(A0);
    delay(30);
  }
  for(int i=0;i<9;i++)
    {
    for(int j=i+1;j<10;j++)
      {
        if(buffer_arr[i]>buffer_arr[j])
      {
        temp=buffer_arr[i];
        buffer_arr[i]=buffer_arr[j];
        buffer_arr[j]=temp;
      }
    }  
  }
  avgval=0;
    for(int i=2;i<8;i++)
  avgval+=buffer_arr[i];
    float volt=(float)avgval*3.3/4096.0/6;  
    float ph_act = -4.34 * volt + calibri_val;
  lcd.setCursor(0, 0);
  lcd.print("PH Value:");
  lcd.setCursor(10, 0);
  lcd.print(ph_act);
  Serial.println(ph_act);
  delay(500);
}