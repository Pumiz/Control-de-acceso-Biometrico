#define PIN_PULSADOR A3
int estado_push;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_PULSADOR, INPUT_PULLUP);
}

void loop() {
  estado_push = digitalRead(PIN_PULSADOR);
  Serial.println(estado_push);
  delay(150);

}
