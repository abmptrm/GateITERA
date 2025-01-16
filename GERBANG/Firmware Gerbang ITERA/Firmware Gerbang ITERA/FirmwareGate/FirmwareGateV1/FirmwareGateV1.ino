char data[10];  // Ukuran array sesuai kebutuhan (5 karakter + 1 null terminator)
#define Hitam 9
#define Kuning 10
#define Hijau 11

void setup() {
  Serial.begin(9600);
  pinMode (Hitam, OUTPUT);
  pinMode (Kuning, OUTPUT);
  pinMode (Hijau, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();

    if (receivedChar == '\n') {
      // Tambahkan null terminator untuk menandai akhir array
      data[7] = '\0';

      // Tampilkan char array yang sudah diisi
      Serial.println(data);

      // Proses ketika kondisi tertentu terpenuhi (contoh: data[0] sampai data[3] adalah "BUKA")
      if (strcmp(data, "BUKA") == 0) {
        atas();
        delay (500);
        standby ();
      }
      if (strcmp(data, "TUTUP") == 0) {
        bawah ();
        delay (500);
        standby ();
      }
      if (strcmp(data, "STOP") == 0) {
        stop ();
        delay (500);
        standby ();
      }


      // Reset array untuk menerima karakter berikutnya
      memset(data, 0, sizeof(data));
    } else {
      // Selama belum menerima newline, tambahkan karakter ke array
      data[strlen(data)] = receivedChar;
    }
  }
  // Put your main code here, to run repeatedly:
}

void bawah () {

  digitalWrite (Hitam, LOW);
  digitalWrite (Kuning, HIGH);
  digitalWrite (Hijau, LOW);

}

void atas () {

  digitalWrite (Hitam, LOW);
  digitalWrite (Kuning, LOW);
  digitalWrite (Hijau, HIGH);
}

void stop () {

  digitalWrite (Hitam, HIGH);
  digitalWrite (Kuning, LOW);
  digitalWrite (Hijau, LOW);
}

void standby () {

  digitalWrite (Hitam, LOW);
  digitalWrite (Kuning, LOW);
  digitalWrite (Hijau, LOW);
}
