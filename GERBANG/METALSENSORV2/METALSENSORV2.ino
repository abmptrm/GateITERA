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

void loop() {
  // Pengecekan status pin di loop untuk menanggapi interupsi yang terjadi
  if (lastStateD0 == LOW) {
    mode_kirim();
    Serial.print("IN:METAL1:TRUE\n");
    lastStateD0 = HIGH;  // Update status
    mode_terima();
  }
  if (lastStateD1 == LOW) {
    mode_kirim();
    Serial.print("IN:METAL2:TRUE\n");
    lastStateD1 = HIGH;  // Update status
    mode_terima();
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
