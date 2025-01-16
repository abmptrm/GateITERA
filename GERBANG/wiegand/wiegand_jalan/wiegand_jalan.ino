// Pin untuk Wiegand D0 dan D1
#define WIEGAND_D0_PIN 6  // PA6
#define WIEGAND_D1_PIN 7  // PA7

// Variabel untuk menyimpan data Wiegand
volatile unsigned long bitBuffer = 0;
volatile int bitCount = 0;
volatile bool dataReady = false;

unsigned long lastBitTime = 0;
const unsigned long WIEGAND_TIMEOUT = 100; // Timeout untuk frame data Wiegand (3 ms)

void setup() {
  // Inisialisasi serial
  Serial.begin(115200);

  // Konfigurasi pin untuk D0 dan D1
  pinMode(WIEGAND_D0_PIN, INPUT_PULLUP);
  pinMode(WIEGAND_D1_PIN, INPUT_PULLUP);

  // Mengaktifkan interrupt untuk PA6 (D0) dan PA7 (D1)
  PCMSK0 |= (1 << PCINT6) | (1 << PCINT7); // Enable interrupt untuk D0 dan D1
  GIMSK |= (1 << PCIE0); // Enable Pin Change Interrupt untuk port A

  // Inisialisasi variabel
  bitBuffer = 0;
  bitCount = 0;
  lastBitTime = millis();
}

void loop() {
  // Cek apakah ada data yang siap
  if (dataReady) {
    dataReady = false;

    // Validasi jumlah bit
    if (bitCount == 26 || bitCount == 34) { // Misalnya, Wiegand 26 atau 34
      // Mengambil Facility Code (bit 2-9)
      unsigned char facilityCode = (bitBuffer >> 17) & 0xFF; // Ambil 8 bit dari bit 2-9
      // Mengambil Card Code (bit 10-25)
      unsigned long cardCode = (bitBuffer >> 1) & 0xFFFF; // Ambil 16 bit dari bit 10-25

      // Gabungkan facility code dan card code menjadi format HEX
      char output[8];
      sprintf(output, "%02X%04X", facilityCode, cardCode); // Format 2 Hex + 4 Hex

      // Serial.print("Combined Data (Hex): ");
      Serial.println(output); // Menampilkan hasil gabungan
    } else {
      Serial.println("Error: Invalid bit count");
    }

    // Reset buffer setelah data ditampilkan
    bitBuffer = 0;
    bitCount = 0;
  }

  // Cek timeout jika tidak ada bit baru dalam rentang waktu tertentu
  if (bitCount > 0 && (millis() - lastBitTime) > WIEGAND_TIMEOUT) {
    dataReady = true;
  }
}

// Fungsi Interrupt untuk Pin Change pada PA6 (D0) dan PA7 (D1)
ISR(PCINT0_vect) {
  // Jika PA7 (D1) adalah LOW, maka bit 1 diterima
  if (digitalRead(WIEGAND_D1_PIN) == LOW) {
    bitBuffer <<= 1;  // Geser buffer ke kiri
    bitBuffer |= 1;   // Tambahkan bit 1
    bitCount++;
    lastBitTime = millis(); // Reset timer
    // Serial.println("D1 Triggered (bit 1)"); // Debug print dihapus
  }
  
  // Jika PA6 (D0) adalah LOW, maka bit 0 diterima
  if (digitalRead(WIEGAND_D0_PIN) == LOW) {
    bitBuffer <<= 1;  // Geser buffer ke kiri
    // Tidak perlu menambahkan bit 0 secara eksplisit
    bitCount++;
    lastBitTime = millis(); // Reset timer
    // Serial.println("D0 Triggered (bit 0)"); // Debug print dihapus
  }
}
