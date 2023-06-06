#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

uint8_t getFingerprintEnroll(uint8_t id);

SoftwareSerial mySerial(3, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  Serial.println("Retire el dedo");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Se establecio la conceccion con el sensor");
  } else {
    Serial.println("No se pudo establecer la coneccion con el sensor :(");
    while (1)
      ;
  }
}

void loop() {
  while (!Serial)
    ;
  delay(500);

  Serial.println("Ingrese el numero de ID # que desea eliminar...");
  uint8_t id = 0;
  while (true) {
    while (!Serial.available())
      ;
    char c = Serial.read();
    if (!isdigit(c)) break;
    id *= 10;
    id += c - '0';
  }
  Serial.print("Eliminando ID #");
  Serial.println(id);

  deleteFingerprint(id);
}

uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Eliminado!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicacion");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("No se puede eliminar en esa ubicacion");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error al escribir en Flash");
    return p;
  } else {
    Serial.print("Error desconocido: 0x");
    Serial.println(p, HEX);
    return p;
  }
}