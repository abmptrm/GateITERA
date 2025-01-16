// #include <SoftwareSerial.h>

#define METAL1_D0_PIN 9  // PB0
#define METAL2_D1_PIN 10  // PB1

#define pin_DE_RE 10


// SoftwareSerial mySerial(8, 9);


void setup() {
  // mySerial.begin(38400);
  Serial.begin(38400); 
  pinMode(pin_DE_RE, OUTPUT);  
  // pinMode(pin_METAL, INPUT_PULLUP);


  // Konfigurasi pin untuk D0 dan D1
  pinMode(METAL1_D0_PIN, INPUT_PULLUP);
  pinMode(METAL2_D1_PIN, INPUT_PULLUP);

  // Mengaktifkan interrupt untuk PB0 (D0) dan PB1 (D1)
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9); // Enable interrupt untuk D0 dan D1
  GIMSK |= (1 << PCIE1); // Enable Pin Change Interrupt untuk port B


}

void loop() {
  int state = digitalRead(pin_METAL);
  delay(10);

  if (state == HIGH) {
    mode_kirim(); 
    Serial.print("IN:METAL1:TRUE"); 
    delay(30);
    Serial.print('\n');
    delay(7);
  } 
  
  delay(1000);
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


