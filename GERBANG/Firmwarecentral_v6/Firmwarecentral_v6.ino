#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

const int RX_PIN_1 = 16; // SoftSerial1 RX pin for gate in
const int TX_PIN_1 = 17; // SoftSerial1 TX pin for gate in
const int RX_PIN_2 = 12; // SoftSerial2 RX pin for gate out
const int TX_PIN_2 = 14; // SoftSerial2 TX pin for gate out
const int pin_DE_RE1 = 19; // MAX485 Serial gate in
const int pin_DE_RE2 = 21; // MAX485 Serial gate out

HardwareSerial SerialPort(2); // RX, TX
SoftwareSerial softSerial2(RX_PIN_2, TX_PIN_2); // RX, TX

String rawdataserial1 = "";
String rawdataserial2 = "";
String rawdataserial3 = "";

void setup() {
  Serial.begin(115200);
  SerialPort.begin(4800, SERIAL_8N1, RX_PIN_1, TX_PIN_1);
  softSerial2.begin(4800);
  pinMode(pin_DE_RE1, OUTPUT);
  pinMode(pin_DE_RE2, OUTPUT);
  mode_terima();
}

void loop() {
    mode_terima();
    // delay(10);
  if (SerialPort.available()) {
    // Serial.println("ini data dari HARDWARE");
    char c = SerialPort.read();
    if (c == '\n') {
    // End of transmission, process data
    // Serial.println("ini data dari softserial1");
    Serial.println(rawdataserial1);
    delay(100);
    rawdataserial1="";
    } else {
      rawdataserial1 += c;
      //Serial.println(rawdataserial1);
    }
  }

  // if (softSerial2.available()) {
  //   char c = softSerial2.read();
  //   if (c == '\n') {
  //   // End of transmission, process data
  //   Serial.println("ini data dari softserial2");
  //   Serial.println(rawdataserial2);
  //   rawdataserial2="";
  //   } else {
  //     rawdataserial2 += c;
  //     //Serial.println(rawdataserial1);
  //   }
  // }
  if (Serial.available()) {
    mode_kirim() ;
    // delay(20);
    char c = Serial.read();
    if (c == '\n') {
    // End of transmission, process data
    // Serial.println("ini data dari softserial1");
    SerialPort.println(rawdataserial3);
    delay(100);
    // Serial.println(rawdataserial3);
    // Serial.println(rawdataserial3);
    // Serial.println(rawdataserial3);
    rawdataserial3="";

    // mode_terima(); 
    } else {
      rawdataserial3 += c;
      //Serial.println(rawdataserial1);
    }
  }

}

void mode_kirim() 
{
  digitalWrite(pin_DE_RE1, LOW); //kondisikan posisi kirim data
  digitalWrite(pin_DE_RE2, LOW); //kondisikan posisi kirim data
  delay(20);
}

void mode_terima() 
{
  digitalWrite(pin_DE_RE1, HIGH); //kondisikan posisi terima data
  digitalWrite(pin_DE_RE2, HIGH); //kondisikan posisi terima data
  delay(5);
}