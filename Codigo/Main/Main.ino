#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial mySerial(3, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int ServoCerradura = 8;
int LED = 13;
String m = String("Martin");
String r = String("Rami");
String l = String("Legui");
String u = String("Uriel");
String nombre;

String numID;



void setup() {
  while (!Serial)
    ;
  Serial.begin(9600);
  pinMode(ServoCerradura, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("Inicio detección del módulo fingerprint");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor de Huellas conectado correctamente!");
  } else {
    Serial.println("No se ha encontrado un Sensor de Huellas :(");
    while (1)
      ;
  }
  Serial.println("Esperando huella");
  //Llamado de la función, para arrancar el display con "Ingrese huella"
}

void loop() {
  datosFingerprint();
  delay(50);
}
// Devuelve -1 si falla, de lo contrario devuelve ID #
int datosFingerprint() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  if (finger.fingerID == -1) {
    Serial.println("No se encontraron coincidencias... :(");
  }
  if (finger.fingerID == 1) {
    nombre = m;
  }
  if (finger.fingerID == 2) {
    nombre = r;
  }
  if (finger.fingerID == 3) {
    nombre = l;
  }
  if (finger.fingerID == 4) {
    nombre = u;
  }

  Serial.print("Huella ID #");
  Serial.print(finger.fingerID);
  Serial.print(" corresponde a: ");
  Serial.println(nombre);

  /*   Accion si coinciden las huellas.
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  numID = String(finger.fingerID);  //Convierte el id en cadena para ser compatible con el display
  digitalWrite(ServoCerradura, HIGH);
  delay(3000);
  digitalWrite(ServoCerradura, LOW);
  //Pasado el tiempo vuelve a mostrar en el display "ingrese huella"
  return finger.fingerID;
  */

}
/*
//Nos muestra en el display Ingrese huella
 void displayOled(){
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
 //   u8g2.drawStr(0,24,"Huella #"+ numID);
    u8g2.drawStr(0,24,"Ingrese huella");
  
    } while ( u8g2.nextPage() );
}
//Nos muestra en el display el número de la huella obtenida "Huella #"
 void displayOled2(){
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
   
   u8g2.drawStr(0,24,"Huella #");
   u8g2.drawStr(65, 24, numID.c_str()); 
    } while ( u8g2.nextPage() );
}
*/