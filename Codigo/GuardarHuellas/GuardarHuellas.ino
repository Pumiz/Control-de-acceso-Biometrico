#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

uint8_t id;

uint8_t getFingerprintEnroll();

SoftwareSerial mySerial(3, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  while (!Serial)
    ;
  delay(500);
  Serial.begin(9600);
  Serial.println("Iniciando detección del módulo FingerPrint");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor de Huellas conectado correctamente!");
  } else {
    Serial.println("No se ha encontrado un Sensor de Huellas :(");
    while (1)
      ;
  }
}

uint8_t readnumber(void) {
  uint8_t num = 0;
  boolean validnum = false;
  while (1) {
    while (!Serial.available())
      ;
    char c = Serial.read();
    if (isdigit(c)) {
      num* = 10;
      num + = c - '0';
      validnum = true;
    } else if (validnum) {
      return num;
    }
  }
}

void loop() {
  Serial.println("Listo para guardar su huella! Porfavor ingrese un numero el cual será su ID #");
  id = readnumber();
  Serial.print("Creando ID #");
  Serial.println(id);

  while (!getFingerprintEnroll())
    ;
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Porfavor coloca el dedo");
  Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagen tomada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Error de comunicación");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Error en la imagen");
        break;
      default:
        Serial.println("Error desconocido.");
        break;
    }
  }


  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demaciado borrosa");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se encontraron las tomas del sensor");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se encontraron las tomas del sensor");
      return p;
    default:
      Serial.println("Error desconocido.");
      return p;
  }

  Serial.println("Remueva el dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID ");
  Serial.println(id);
  p = -1;
  Serial.println("Porfavor, vuela a colocar el mismo dedo");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagen tomada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Error de comunicacion");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Error en la imagen");
        break;
      default:
        Serial.println("Error desconocido");
        break;
    }
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demaciado borrosa");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se encontraron las tomas del sensor");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se encontraron las tomas del sensor");
      return p;
    default:
      Serial.println("Error desconocido.");
      return p;
  }

  Serial.print("Creando modelo para el ID #");
  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Huellas encontradas!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de cominicación");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("No hay coincidencias en las huellas");
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  Serial.print("ID ");
  Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Guardado!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("No se puede almacenar en esa ubicación");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error al escribir en flash");
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }
}