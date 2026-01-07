/*****************************************
 * Salinity Measurement (ppt)
 * Sensor + DMS + Arduino
 * Board : Arduino Uno / Nano
 *****************************************/

#define SALINITY_PIN A0   // Output data dari DMS
#define DMS_PIN 6         // Kontrol DMS (LOW = aktif)
#define INDIKATOR 13      // LED indikator (opsional)

int adcValue;
float ppt;

void setup() {
  Serial.begin(9600);

  pinMode(DMS_PIN, OUTPUT);
  pinMode(INDIKATOR, OUTPUT);

  // Kondisi awal
  digitalWrite(DMS_PIN, HIGH);   // DMS non-aktif
  digitalWrite(INDIKATOR, LOW);

  Serial.println("Monitoring Salinitas Air (ppt)");
}

void loop() {

  // =====================
  // AKTIFKAN DMS
  // =====================
  digitalWrite(DMS_PIN, LOW);    // DMS ON
  digitalWrite(INDIKATOR, HIGH);
  delay(10000);                  // waktu stabilisasi DMS (10 detik)

  // =====================
  // BACA ADC (A0)
  // =====================
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(SALINITY_PIN);
    delay(20);
  }
  adcValue = total / 10;

  // =====================
  // MATIKAN DMS
  // =====================
  digitalWrite(DMS_PIN, HIGH);   // DMS OFF
  digitalWrite(INDIKATOR, LOW);

  // =====================
  // KONVERSI ADC → SALINITAS (ppt)
  // (Rumus kalibrasi kamu)
  // =====================
  if (adcValue <= 710) {
    ppt = 0.2 * (adcValue - 559.6);
  } else {
    ppt = 1.75 * (adcValue - 709.6) + 30;
  }

  // Batas nilai
  if (ppt < 0) ppt = 0;
  if (ppt > 60) ppt = 60;

  // =====================
  // OUTPUT SERIAL
  // =====================
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Salinitas: ");
  Serial.print(ppt, 2);
  Serial.println(" ppt");

  delay(2000);   // waktu istirahat DMS
}
