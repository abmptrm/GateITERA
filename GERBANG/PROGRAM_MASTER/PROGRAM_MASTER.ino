#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

const int RX_PIN_1 = 16; // SoftSerial1 RX pin for gate in
const int TX_PIN_1 = 17; // SoftSerial1 TX pin for gate in
const int RX_PIN_2 = 12; // SoftSerial2 RX pin for gate out
const int TX_PIN_2 = 14; // SoftSerial2 TX pin for gate out
int pin_DE_RE1 = 19; // MAX485 Serial gate in
int pin_DE_RE2 = 21; // MAX485 Serial gate out

HardwareSerial SerialPort(2); // RX, TX
SoftwareSerial softSerial2(RX_PIN_2, TX_PIN_2); // RX, TX

String rawdataserial1 = "";
String rawdataserial2 = "";

//-----------------------------------------------
// int pin_DE_RE = 2;

char kode_ID_1 = 'A';
char kode_ID_2 = 'B';
char kode_ID_3 = 'C';
String terima_string = "";
String datanya = "";
String data_str1 = "0";
String data_str2 = "0";
String data_str3 = "0";
char kode_akhir = '#';
bool status_request = false;
bool jalur_485 = true;

int data_ID_1 = 0;
int data_ID_2 = 0;
int data_ID_3 = 0;
byte slave_ID = 0;

void setup() {

    // Serial.begin(9600); //aktifkan jalur serial dengan baudrate 9600 bps
    Serial.begin(115200);
    SerialPort.begin(4800, SERIAL_8N1, RX_PIN_1, TX_PIN_1);
    softSerial2.begin(4800);
    pinMode(pin_DE_RE1, OUTPUT);
    pinMode(pin_DE_RE2, OUTPUT);
    
    mode_kirim(); 
    kirim_tanda_selesai();
    mode_terima();
     Serial.println("init selesai");
}

   void mode_kirim()
{
    digitalWrite(pin_DE_RE1, HIGH);  
    digitalWrite(pin_DE_RE2, HIGH); 
    delay(10);
}

void mode_terima()
{
    digitalWrite(pin_DE_RE1, LOW);  
    digitalWrite(pin_DE_RE2, LOW); 
    delay(5);
}

void kirim_tanda_selesai()
{
    if(slave_ID == 1){Serial.print(kode_ID_1);}  
    if(slave_ID == 2){Serial.print(kode_ID_2);}  
    if(slave_ID == 3){Serial.print(kode_ID_3);}  
    Serial.print('*');  
    delay(5);
}

void tampilkan_data()
{
  Serial.println("Terima Data Slave");
  Serial.println("Slave 1: ");
  Serial.println(data_str1);
  Serial.println("Slave 2: ");
  Serial.println(data_str2);
  Serial.println("Slave 3: ");
  Serial.println(data_str3);
  delay(1000);
}

void loop() 
{

  // old program

    if (SerialPort.available()) {
    char c = SerialPort.read();
    // Serial.print(c);
    if (c == '\n') {
      Serial.println(rawdataserial1);
      delay(500);
    // End of transmission, process data
    // Serial.println("ini data dari softserial1");
    // Serial.println(rawdataserial1);
    rawdataserial1="";
    } else {
      rawdataserial1 += c;
      //Serial.println(rawdataserial1);
    }
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

  //sampai sini
//   if (SerialPort.available()) 
// {   Serial.println("serialPort Available");
//     char karakter_masuk = (char)SerialPort.read();
// Serial.println(karakter_masuk);
//     if (karakter_masuk == '*') 
//     {
//         Serial.println("* dan jalur_485 = false");
//         jalur_485 = false;
//     } 
//     else if (karakter_masuk == 'A') 
//     {
//         Serial.println("slave_ID = 1");
//         slave_ID = 1;
//     } 
//     else if (karakter_masuk == 'B') 
//     {
//         Serial.println("slave_ID = 2");
//         slave_ID = 2;
//     } 
//     else if (karakter_masuk == 'C') 
//     {
//         Serial.println("slave_ID = ");
//         slave_ID = 3;
//     } 
//     else if (karakter_masuk == '!')
//     {
//       Serial.println("!");
//       if (slave_ID == 1) { data_str1 = terima_string; }
//       if (slave_ID == 2) { data_str2 = terima_string; }
//       if (slave_ID == 3) { data_str3 = terima_string; }

//       terima_string = ""; 
//       tampilkan_data(); 
//       mode_kirim(); 
//       kirim_tanda_selesai(); 
//       jalur_485 = true; 
//       mode_terima(); 

//   }
//   else 
//     {
//       if (jalur_485 == false) { terima_string += karakter_masuk; }
//     }
//   }
// }