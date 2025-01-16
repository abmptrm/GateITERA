#include <SPI.h>
#include <RF24.h>

// Inisialisasi objek RF24
RF24 radio(2, 4); // Pin CE dan CSN

// Alamat yang akan diterima
uint64_t address = 0xF0F0F0F0E1LL;

void setup() {
  Serial.begin(9600);
  radio.begin();
  
  // Mengatur alamat penerima (pipe 1)
  radio.openReadingPipe(1, address);
  
  // Mengaktifkan penerima
  radio.startListening();
  
  Serial.println("Penerima NRF24L01 siap");
}

void loop() {
  if (radio.available()) {
    // Jika ada data tersedia, baca data
    char receivedMessage[32] = {0};
    radio.read(receivedMessage, sizeof(receivedMessage));
    
    // Tampilkan data yang diterima dalam bentuk hexadecimal
    Serial.print("Diterima (hex): ");
    for (int i = 0; i < sizeof(receivedMessage); i++) {
      Serial.print(receivedMessage[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    
    // Tampilkan data yang diterima dalam bentuk karakter ASCII
    Serial.print("Diterima (ASCII): ");
    Serial.println(receivedMessage);
  }
}
