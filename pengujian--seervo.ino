#include <Servo.h>

// Membuat objek servo
Servo pintuServo;

// Pin Sinyal (Kabel Oranye) tetap di Pin 3
const int pinServo = 3;

void setup() {
  Serial.begin(9600);
  
  // Menghubungkan objek servo ke pin digital 3
  pintuServo.attach(pinServo);
  
  // Memastikan posisi awal di 0 derajat
  pintuServo.write(0);
  
  Serial.println("--- Pengetesan Servo MG996R (0 - 30 Derajat) ---");
}

void loop() {
  // 1. Gerakkan ke posisi 30 derajat
  Serial.println("Bergerak ke: 30 Derajat");
  pintuServo.write(30); 
  delay(2000); // Tunggu 2 detik agar servo selesai bergerak

  // 2. Kembali ke posisi 0 derajat
  Serial.println("Kembali ke: 0 Derajat");
  pintuServo.write(0); 
  delay(2000); // Tunggu 2 detik sebelum mengulang
}