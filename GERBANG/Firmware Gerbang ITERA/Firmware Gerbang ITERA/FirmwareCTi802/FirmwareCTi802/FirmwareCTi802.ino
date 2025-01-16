#include <Wiegand.h>

WIEGAND wg;
#define PB4 13

void setup() {
  Serial.begin(4800);  
  wg.begin(4,5);
  digitalWrite(PB4, HIGH);
}

void loop() {
  if(wg.available())
  {
    Serial.print("OUT:TRFID:");
    Serial.println(wg.getCode(),HEX);
    //delay(10);
    //Serial.flush();

  }
//  Serial.println("SERIAL OK");
//delay (100);
}
