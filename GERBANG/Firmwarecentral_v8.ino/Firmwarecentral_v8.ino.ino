#include <Arduino.h>
#include <SoftwareSerial.h>

const int RX_PIN_1 = 16; // SoftSerial1 RX pin for gate in
const int TX_PIN_1 = 17; // SoftSerial1 TX pin for gate in
const int pin_DE_RE1 = 19; // MAX485 Serial gate in
const int pin_DE_RE2 = 21; // MAX485 Serial gate out

SoftwareSerial softSerial(RX_PIN_1, TX_PIN_1); // RX, TX


String rawdataserial1 = "";
String rawdataserial2 = "";
String rawdataserial3 = "";

void setup() {
  Serial.begin(115200);
  softSerial.begin(4800);
  pinMode(pin_DE_RE1, OUTPUT);
  pinMode(pin_DE_RE2, OUTPUT);
  mode_terima();
}

void loop() {
    mode_terima();
    // delay(10);
  if (softSerial.available()) {
    char c = softSerial.read();
    if (c == '\n') {
    // End of transmission, process data
    Serial.println(rawdataserial1);
    delay(100);
    rawdataserial1="";
    } else {
      rawdataserial1 += c;
    }
  }
  if (Serial.available()) {
    mode_kirim() ;
    delay(20);
    char c = Serial.read();
    if (c == '\n') {
    // End of transmission, process data
    softSerial.print(rawdataserial3);
    delay(10);
    softSerial.print('\n');
    delay(7);
    rawdataserial3="";
    mode_terima();
    } else {
      rawdataserial3 += c;
    }
  }
}
void mode_kirim() 
{
  digitalWrite(pin_DE_RE1, HIGH); //kondisikan posisi kirim data
  digitalWrite(pin_DE_RE2, HIGH); //kondisikan posisi kirim data
  delay(7);
}

void mode_terima() 
{
  digitalWrite(pin_DE_RE1, LOW); //kondisikan posisi terima data
  digitalWrite(pin_DE_RE2, LOW); //kondisikan posisi terima data
  delay(5);
}