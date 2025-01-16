#define METAL1_D0_PIN 0   // PB0 (Interrupt Pin 1)
#define METAL2_D1_PIN 1   // PB1 (Interrupt Pin 2)
#define pin_DE_RE 10      // Pin untuk mode kirim/terima data

// Variabel untuk melacak status pin sebelumnya
volatile int lastStateD0 = HIGH;
volatile int lastStateD1 = HIGH;

void setup() {
  Serial.begin(38400);       // Inisialisasi komunikasi Serial
  pinMode(pin_DE_RE, OUTPUT); // Set pin DE_RE untuk mode kirim/terima

  // Konfigurasi pin untuk D0 dan D1 sebagai input dengan pull-up
  pinMode(METAL1_D0_PIN, INPUT_PULLUP); 
  pinMode(METAL2_D1_PIN, INPUT_PULLUP);

  // Konfigurasi interupsi untuk pin PB0 dan PB1
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9); // Enable interrupt untuk PB0 dan PB1
  GIMSK |= (1 << PCIE1); // Enable Pin Change Interrupt untuk port B

  // Untuk memastikan interupsi sudah di-enable
  sei(); // Aktifkan global interrupt flag
  mode_terima(); // Set mode terima data di awal
}

bool sentStatusD0 = false; // Menandakan apakah sudah mengirim status untuk D0
bool sentStatusD1 = false; // Menandakan apakah sudah mengirim status OFF

void loop() { 
  int currentStateD0 = digitalRead(METAL1_D0_PIN); // Baca status sensor D0
    int currentStateD1 = digitalRead(METAL2_D1_PIN); // Baca status sensor D1

    // Mengecek apakah ada perubahan status pada sensor METAL1 (D0)
    if (currentStateD0 == LOW && !sentStatusD0) {
      // Kirim status ON untuk sensor D0 hanya sekali jika belum dikirim
      mode_kirim();
      delay(30);
      Serial.print("IN:M1:ON");
      Serial.print("_M2:");
      Serial.print((currentStateD1 == LOW) ? "ON" : "OFF");
      Serial.print('\n');
      delay(30);
      mode_terima();  // Kembali ke mode terima
      sentStatusD0 = true; // Tandai bahwa sudah mengirim status untuk D0
    } 
    else if (currentStateD0 == HIGH && sentStatusD0) {
      // Kirim status OFF untuk sensor D0 hanya sekali jika sensor sebelumnya terdeteksi (LOW)
      mode_kirim();
      delay(30);
      Serial.print("IN:M1:OFF");
      Serial.print("_M2:");
      Serial.print((currentStateD1 == LOW) ? "ON" : "OFF");
      Serial.print('\n');
      delay(30);
      mode_terima();
      sentStatusD0 = false; // Reset sentStatusD0 ketika sensor D0 tidak terdeteksi (HIGH)
    }

    // Mengecek apakah sensor METAL2 (D1) terdeteksi (LOW) atau tidak terdeteksi (HIGH)
    if (currentStateD1 == LOW && !sentStatusD1) {
      // Kirim status ON untuk sensor D1 hanya sekali jika belum dikirim
      mode_kirim();
      delay(30);
      Serial.print("IN:M1:");
      Serial.print((currentStateD0 == LOW) ? "ON" : "OFF");
      Serial.print("_M2:ON\n");
      delay(30);
      mode_terima();  // Kembali ke mode terima
      sentStatusD1 = true; // Tandai bahwa sudah mengirim status untuk D1
    }
    else if (currentStateD1 == HIGH && sentStatusD1) {
      // Kirim status OFF untuk sensor D1 hanya sekali jika sensor sebelumnya terdeteksi (LOW)
      mode_kirim();
      delay(30);
      Serial.print("IN:M1:");
      Serial.print((currentStateD0 == LOW) ? "ON" : "OFF");
      Serial.print("_M2:OFF\n");
      delay(30);
      mode_terima();  // Kembali ke mode terima
      sentStatusD1 = false; // Reset sentStatusD1 ketika sensor D1 tidak terdeteksi (HIGH)
    }

    // Jika kedua sensor tidak terdeteksi (HIGH)
    if (currentStateD0 == HIGH && currentStateD1 == HIGH) {
      if (sentStatusD0 || sentStatusD1) {
        // Kirim status OFF untuk kedua sensor hanya jika ada status yang sebelumnya dikirim
        mode_kirim();
        delay(30);
        Serial.print("IN:M1:OFF_M2:OFF\n");
        delay(30);
        mode_terima(); // Kembali ke mode terima
        sentStatusD0 = false; // Reset status pengiriman D0
        sentStatusD1 = false; // Reset status pengiriman D1
      }
    }
}




// ISR untuk menangani interupsi pada pin PB0 dan PB1
ISR(PCINT1_vect) {
  // Mengecek perubahan status pin PB0 (METAL1_D0_PIN)
  if (digitalRead(METAL1_D0_PIN) == LOW && lastStateD0 == HIGH) {
    // Rising edge terdeteksi pada METAL1_D0_PIN
    lastStateD0 = LOW;  // Update status pin
  }

  // Mengecek perubahan status pin PB1 (METAL2_D1_PIN)
  if (digitalRead(METAL2_D1_PIN) == LOW && lastStateD1 == HIGH) {
    // Rising edge terdeteksi pada METAL2_D1_PIN
    lastStateD1 = LOW;  // Update status pin
  }
}

// Fungsi untuk mengatur mode kirim data
void mode_kirim() {
  digitalWrite(pin_DE_RE, HIGH); // Kondisikan posisi kirim data
  delay(10);  // Delay untuk stabilisasi
}

// Fungsi untuk mengatur mode terima data
void mode_terima() {
  digitalWrite(pin_DE_RE, LOW); // Kondisikan posisi terima data
  delay(5);  // Delay untuk stabilisasi
}
