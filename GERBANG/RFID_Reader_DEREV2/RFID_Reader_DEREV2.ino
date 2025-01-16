#include <Wiegand.h>
WIEGAND wg;
#define pin_DE_RE 13

void setup() {
  Serial.begin(4800);  
  wg.begin(4,5);
  pinMode(pin_DE_RE, OUTPUT);
}

void loop() {
  if(wg.available())
  {

    if (Serial.available())
      {
        mode_terima();
        delay(100);
        mode_kirim();
        delay(10);
        Serial.print("IN:LRFID:");
        // delay(30);
        Serial.print(wg.getCode(),HEX);
        delay(30);
        Serial.print('\n');
        delay(7);
        mode_terima();
      }else
      {
        mode_kirim();
        delay(10);
        Serial.print("IN:LRFID:");
        // delay(30);
        Serial.print(wg.getCode(),HEX);
        delay(30);
        Serial.print('\n');
        delay(7);
        mode_terima();
        
      }

  }

}

void mode_kirim() 
{
  digitalWrite(pin_DE_RE, HIGH); //kondisikan posisi kirim data
  delay(10);
}

void mode_terima() 
{
  digitalWrite(pin_DE_RE, LOW); //kondisikan posisi terima data
  delay(5);
}