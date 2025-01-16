char kode_ID;
char kode_request = '*';
byte slave_ID;
bool jalur_485 = true;
String data_kirim;
int pin_DE_RE = 13;
int data_slave = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_DE_RE, OUTPUT);
  cek_slave_id();
  // mode_terima();
  mode_kirim(); 
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

void cek_slave_id() {
  slave_ID = 1;

  //-----
  if (slave_ID == 1) { kode_ID = 'A'; }
  if (slave_ID == 2) { kode_ID = 'B'; }
  if (slave_ID == 3) { kode_ID = 'C'; }
}

void loop() {
  // int cek_tombol = digitalRead(pin_tombol);
  // if (cek_tombol == LOW) 
  // {
    // if (jalur_485 == true) 
    // {
      data_slave++;
      String data_kirim;
      data_kirim = kode_ID + String(data_slave);
      // digitalWrite(pin_led_terima, HIGH);
      if (Serial.available())
      {
        mode_terima();
        delay(100);
      }else
      { 
        mode_kirim();
        Serial.println("Device 4 : PPQQRRSSTT");
        delay(100);
        // mode_terima();
        // // Serial.flush();
        // delay(5);
        // mode_terima();
        // delay(100);
      }     
      // mode_kirim();
      // Serial.print('#');
      // delay(5);
      // Serial.print(data_kirim);
      // Serial.println("Device 4 : PPQQRRSSTT");
      // delay(100);
      // Serial.print('*');
      // delay(1);
      // mode_terima();
      // jalur_485 = false;
      // delay(100);
      

    // }
  // }
  // if (Serial.available() > 0) 
  // {
  //   Serial.println("S_available");
  // char karakter_masuk = (char)Serial.read();
  
  // if (karakter_masuk == '*') 
  // {
  //   // digitalWrite(pin_led_jalur, LOW);
  //   Serial.println("karakter_masuk == '*'");
  //   mode_terima();
  //   jalur_485 = false; 
  // } 
  // else if (karakter_masuk == '#') 
  // { 
  //   // digitalWrite(pin_led_jalur, HIGH); 
  //   Serial.println("karakter_masuk == '#'");
  //   mode_terima(); 
  //   jalur_485 = true; 
  //   delay(10);
  // } 
  // else if (karakter_masuk == kode_ID) 
  // {
  //     // digitalWrite(pin_led_terima, LOW);
  //           Serial.println("karakter_masuk == '#'");
  //   }
  // }
}



