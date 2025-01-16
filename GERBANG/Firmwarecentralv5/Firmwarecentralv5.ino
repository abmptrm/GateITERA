#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

const int RX_PIN_1 = 16; // SoftSerial1 RX pin for gate in
const int TX_PIN_1 = 17; // SoftSerial1 TX pin for gate in
const int RX_PIN_2 = 12; // SoftSerial2 RX pin for gate out
const int TX_PIN_2 = 14; // SoftSerial2 TX pin for gate out
const int CH_CTRL1 = 19; // MAX485 Serial gate in
const int CH_CTRL2 = 21; // MAX485 Serial gate out

// SoftwareSerial softSerial1(RX_PIN_1, TX_PIN_1); // RX, TX
SoftwareSerial softSerial2(RX_PIN_2, TX_PIN_2); // RX, TX

String rawdataserial1 = "";
String rawdataserial2 = "";

String lrfcard_in = "";
String trfcard_in = "";
String lrfcard_out = "";
String trfcard_out = "";

void setup() {
  Serial.begin(115200);
  // softSerial1.begin(4800);
  softSerial2.begin(4800);
  digitalWrite(CH_CTRL1, LOW);
  digitalWrite(CH_CTRL2, LOW);
}

void loop() {
  // if (softSerial1.available()) {
  //   char c = softSerial1.read();
  //   if (c == '\n') {
  //   // End of transmission, process data
  //   Serial.println("ini data dari softserial1");
  //   Serial.println(rawdataserial1);
  //   rawdataserial1="";
  //   } else {
  //     rawdataserial1 += c;
  //     //Serial.println(rawdataserial1);
  //   }
  // }

  if (softSerial2.available()) {
    char c = softSerial2.read();
    if (c == '\n') {
    // End of transmission, process data
    Serial.println("ini data dari softserial2");
    Serial.println(rawdataserial2);
    rawdataserial2="";
    } else {
      rawdataserial2 += c;
      //Serial.println(rawdataserial1);
    }
  }
}

// void processSerialData(int serialNum) {
//   if (serialNum == 1) {
//     if (rawdataserial1.indexOf("LRF") != -1) {
//       lrfcard_in = rawdataserial1.substring(rawdataserial1.indexOf("LRF") + 4);
//     } else if (rawdataserial1.indexOf("TRF") != -1) {
//       trfcard_in = rawdataserial1.substring(rawdataserial1.indexOf("TRF") + 4);
//     }
//   } else if (serialNum == 2) {
//     if (rawdataserial2.indexOf("LRF") != -1) {
//       lrfcard_out = rawdataserial2.substring(rawdataserial2.indexOf("LRF") + 4);
//     } else if (rawdataserial2.indexOf("TRF") != -1) {
//       trfcard_out = rawdataserial2.substring(rawdataserial2.indexOf("TRF") + 4);
//     }
//   }

//   // Clear raw data strings
//   rawdataserial1 = "";
//   rawdataserial2 = "";

//   // Create JSON object
//   StaticJsonDocument<200> doc;
//   JsonObject data_in = doc.createNestedObject("data_in");
//   JsonObject data_out = doc.createNestedObject("data_out");
//   data_in["lrfcard"] = lrfcard_in;
//   data_in["trfcard"] = trfcard_in;
//   data_out["lrfcard"] = lrfcard_out;
//   data_out["trfcard"] = trfcard_out;

//   // Serialize JSON to string
//   String output;
//   serializeJson(doc, output);

//   // Send JSON via main serial
//   Serial.println(output);

//   // Clear card data strings
//   lrfcard_in = "";
//   trfcard_in = "";
//   lrfcard_out = "";
//   trfcard_out = "";
// }
