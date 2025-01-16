char data[15];  // Ukuran array sesuai kebutuhan (5 karakter + 1 null terminator)
#define Hitam 9
#define Kuning 10
#define Hijau 11
#define pin_DE_RE 13

// #define Hitam A0
// #define Kuning A1
// #define Hijau A2
// char receivedChar;
String Text;

void setup() {
  Serial.begin(4800);
  pinMode(Hitam, OUTPUT);
  pinMode(Kuning, OUTPUT);
  pinMode(Hijau, OUTPUT);
  pinMode(pin_DE_RE, OUTPUT);
}
void loop() {
  if (Serial.available()) {
    // Serial.println("detect");
    mode_terima();
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {
      // Text = String(receivedChar);
      if (strcmp(data, "OUT:GATE:OPEN") == 0) {
        open();
        delay(500);
        // stop();
      }
      if (strcmp(data, "OUT:GATE:CLOSE") == 0) {
        close();
        delay(500);
        // stop();
      }
      if (strcmp(data, "OUT:GATE:STOP") == 0) {
        stop();
        delay(500);
        // standby();
      }
      // Reset array untuk menerima karakter berikutnya
      memset(data, 0, sizeof(data));
      receivedChar = "";
      // Reset array untuk menerima karakter berikutnya
      // memset(data, 0, sizeof(data));
    } else {
      // Selama belum menerima newline, tambahkan karakter ke array
      // data[strlen(data)] = receivedChar;
      data[strlen(data)] = receivedChar;
    }
  }

}

void open() {
  digitalWrite(Hitam, LOW);
  digitalWrite(Kuning, LOW);
  digitalWrite(Hijau, HIGH);
}

void close() {
  digitalWrite(Hitam, LOW);
  digitalWrite(Kuning, HIGH);
  digitalWrite(Hijau, LOW);
}

void stop() {

  digitalWrite(Hitam, LOW);
  digitalWrite(Kuning, HIGH);
  digitalWrite(Hijau, HIGH);
}

void standby() {

  digitalWrite(Hitam, LOW);
  digitalWrite(Kuning, LOW);
  digitalWrite(Hijau, LOW);
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