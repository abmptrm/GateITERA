#include <SoftwareSerial.h>

// bekerja sebagai output
#define OUT_SERVO 3
#define NUM_LEDS 1 

// Output pada WS2812B atau Max487
#define OUT_WS2812_MAX487_EN 4 

// Jika Buzzer sebagai Output (Pin 2 harus Disable sebagai input)
#define OUT_BUZZER 2

// Aktivasi software serial pada ATTiny85
SoftwareSerial mySerial(0, 1); // RX, TX : Pin 0 dan Pin 1 harus Disable sebagai input


char data[15];  // Ukuran array sesuai kebutuhan (5 karakter + 1 null terminator)


// char receivedChar;
String Text;

void setup() {
  //Inisiasi Serial
  mySerial.begin(4800);

  //definisikan status pin sebagai output
  pinMode(OUT_SERVO, OUTPUT);
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
    // Serial.println("detect");
    
    char receivedChar = mySerial.read();
    if (receivedChar == '\n') {
      // Text = String(receivedChar);
      mode_kirim();
      if (strcmp(data, "OUT:GATE:OPEN") == 0) {
        open();
        // mySerial.println("OPEN");
        buzzer_beep(100);
        delay(500);
        // stop();
      }
      if (strcmp(data, "OUT:GATE:CLOSE") == 0) {
        close();
        // mySerial.println("CLOSE");
        buzzer_beep(300);
        delay(500);
        // stop();
      }
      if (strcmp(data, "OUT:GATE:STOP") == 0) {
        // stop();
        mySerial.println("STOP");
        buzzer_beep(600);
        delay(500);
        // standby();
      }
      // Reset array untuk menerima karakter berikutnya
      memset(data, 0, sizeof(data));
      // receivedChar = "";
      // Reset array untuk menerima karakter berikutnya
      // memset(data, 0, sizeof(data));
      mode_terima();
    } else {
      // Selama belum menerima newline, tambahkan karakter ke array
      // data[strlen(data)] = receivedChar;
      data[strlen(data)] = receivedChar;
    }
  }

}

void open() {

}

void close() {

}

void stop() {

}

void standby() {

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

void buzzer_beep(int jeda){
  digitalWrite(OUT_BUZZER, HIGH);
  delay(jeda*5);
  digitalWrite(OUT_BUZZER, LOW);
  delay(jeda);
  digitalWrite(OUT_BUZZER, HIGH);
  delay(jeda*8);
  digitalWrite(OUT_BUZZER, LOW);
}