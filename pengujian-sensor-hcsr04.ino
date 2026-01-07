// Pin Ultrasonik
const int trigPin = 9;
const int echoPin = 10;

// --- KALIBRASI WAJIB ---
// Masukkan jarak antara sensor dan dasar wadah (saat air kosong)
// Contoh: Jika sensor dipasang 10 cm di atas dasar, isi 10.0
const float jarakSensorKeDasar = 10.0; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Tes Monitoring Tinggi Air (0 - 5 cm)");
}

void loop() {
  // 1. Kirim sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 2. Baca pantulan sinyal
  long duration = pulseIn(echoPin, HIGH);
  
  // 3. Hitung jarak dari sensor ke permukaan air
  float distance = duration * 0.034 / 2; 

  // 4. Logika Perhitungan Tinggi Air
  // Tinggi Air = Jarak dari sensor ke dasar - Jarak yang dibaca sensor saat ini
  float waterLevel = jarakSensorKeDasar - distance;

  // 5. Pembatasan Deteksi (Hanya 0 - 5 cm)
  // Jika air di bawah 0 (karena error sensor), set ke 0
  if (waterLevel < 0) {
    waterLevel = 0;
  }
  // Jika air lebih dari 5 cm, set ke 5
  if (waterLevel > 5) {
    waterLevel = 5;
  }

  // 6. Tampilkan hasil akhir saja
  Serial.print("Tinggi Air Terdeteksi: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  delay(1000); // Update data setiap 1 detik
}