#include <SoftwareSerial.h>
#include <Servo_ATTinyCore.h>
// bekerja sebagai output
#define OUT_SERVO 3
#define NUM_LEDS 1 
Servo myServo;
// Output pada WS2812B atau Max487
#define OUT_WS2812_MAX487_EN 4 
// Jika Buzzer sebagai Output (Pin 2 harus Disable sebagai input)
#define OUT_BUZZER 2
// Aktivasi software serial pada ATTiny85
SoftwareSerial mySerial(0, 1); // RX, TX : Pin 0 dan Pin 1 harus Disable sebagai input
char data[15];  // Ukuran array sesuai kebutuhan (5 karakter + 1 null terminator)

void setup() {
  //Inisiasi Serial
  mySerial.begin(4800);

  //definisikan status pin sebagai output
  pinMode(OUT_SERVO, OUTPUT);
  myServo.attach(OUT_SERVO);
  delay(15);
  pinMode(OUT_WS2812_MAX487_EN, OUTPUT);
  pinMode(OUT_BUZZER, OUTPUT);

  //Test the Buzzer
  digitalWrite(OUT_BUZZER, HIGH);
  digitalWrite(OUT_WS2812_MAX487_EN, HIGH);
  delay(500);
  digitalWrite(OUT_BUZZER, LOW);
  delay(100);
  digitalWrite(OUT_BUZZER, HIGH);
  delay(750);

  // Set the pin low
  digitalWrite(OUT_WS2812_MAX487_EN, LOW);
  digitalWrite(OUT_BUZZER, LOW);
  mode_terima();  
}
void loop() {
  if (mySerial.available()) {
    mode_terima();  
    char receivedChar = mySerial.read();
    if (receivedChar == '\n') {
      
      if (strcmp(data, "OUT:GATE:OPEN") == 0) {
        mode_kirim();
        delay(10);
        mySerial.println("OUT:GATE:PROCESSING");
        gerbang("open", 1);
        mySerial.println("OUT:GATE:OPEN:DONE");
        delay(30);
        mode_terima();
      }
      if (strcmp(data, "OUT:GATE:CLOSE") == 0) {
        mode_kirim();
        delay(10);
        mySerial.println("OUT:GATE:PROCESSING");
        gerbang("close", 2);
        mySerial.println("OUT:GATE:CLOSE:DONE");
        delay(30);
        mode_terima();
      }
      mode_terima();
      // Reset array untuk menerima karakter berikutnya
      memset(data, 0, sizeof(data));
    } else {
      // Selama belum menerima newline, tambahkan karakter ke array
      data[strlen(data)] = receivedChar;
    }
  }
}
void gerbang(String status, int jeda){
  if (status == "close"){
    for(int pos = 90; pos < 180; pos += 1) { 
      myServo.write(pos);              
      digitalWrite(OUT_BUZZER, LOW);
      delay(jeda*2);
      delay(2);      
      digitalWrite(OUT_BUZZER, HIGH);
      delay(jeda*5);
      digitalWrite(OUT_BUZZER, LOW);
    } 
  }

  else if(status == "open"){
    for(int pos = 180; pos >= 90; pos -= 1) {                              
      myServo.write(pos);              
      digitalWrite(OUT_BUZZER, LOW);
      delay(jeda*2);
      delay(1); 
      digitalWrite(OUT_BUZZER, HIGH);
      delay(jeda*5);
      digitalWrite(OUT_BUZZER, LOW);
     
    } 
  } 

}

void mode_kirim() 
{
  digitalWrite(OUT_WS2812_MAX487_EN, HIGH); //kondisikan posisi kirim data
  delay(10);
}

void mode_terima() 
{
  digitalWrite(OUT_WS2812_MAX487_EN, LOW); //kondisikan posisi terima data
  delay(5);
}
