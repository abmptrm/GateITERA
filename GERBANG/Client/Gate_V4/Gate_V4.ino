char data[17];  // Ukuran array sesuai kebutuhan (5 karakter + 1 null terminator)
#define Hitam 9
#define Kuning 10
#define Hijau 11
#define pin_DE_RE 13
String Text;
const uint8_t pin5 = 5;
bool pin5Status = HIGH;
const unsigned long interval = 500;
unsigned long previousMillis = 0;

void setup() {
  // Inisialisasi Serial untuk debug
  Serial.begin(4800);
  pinMode(Hitam, OUTPUT);
  pinMode(Kuning, OUTPUT);
  pinMode(Hijau, OUTPUT);
  pinMode(pin_DE_RE, OUTPUT);
  // Set pin 5 sebagai input dengan pull-up internal
  pinMode(pin5, INPUT_PULLUP);
  pin5Status = digitalRead(pin5);  // Simpan status awal pin

  // Serial.println("Monitoring pin 5...");
}

void loop() {
    // Serial.println("WAIT");
    
    if (Serial.available()) {
      mode_terima();
      char receivedChar = Serial.read();
      // Serial.print(receivedChar);
      if (receivedChar == '\n') {
        // Text = String(receivedChar);
        // Serial.print(receivedChar);
        // Serial.print(strlen(data));
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

      sensor_suhu();

    }

    void sensor_suhu(){


    }
    // Cek waktu untuk menjalankan loop
    // unsigned long currentMillis = millis();

    // if (currentMillis - previousMillis >= interval) {
    //   previousMillis = currentMillis;

      // Cek status pin 5
      bool currentStatus = digitalRead(pin5);

      // Jika status pin berubah, laporkan ke Serial
      if (currentStatus != pin5Status) {
        pin5Status = currentStatus;  // Perbarui status terbaru
        mode_kirim();
        delay(50);
        // Serial.println("detect sensor");
        // Kirim status pin baru ke Serial
        if (currentStatus == LOW) {
          Serial.print("OUT:ROAD:TRUE");
          Serial.print('\n');
        } else {
          Serial.print("OUT:ROAD:FALSE");
          Serial.print('\n');
        }
        delay(50);
      }
      
  // }
  
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
