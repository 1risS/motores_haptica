
#include <DFPlayerMini_Fast.h>

// Pines según lo indicado: TX del ESP32 en GPIO19, RX en GPIO21
#define DFPLAYER_TX 19  // TX del ESP32 → RX del DFPlayer
#define DFPLAYER_RX 21  // RX del ESP32 ← TX del DFPlayer


#define MOTOR_PIN_00 13        // Motor conectado al pin 13
#define MOTOR_PIN_01 12  
#define MOTOR_PIN_02 14
#define MOTOR_PIN_03 27
#define MOTOR_PIN_04 26
#define MOTOR_PIN_05 25

#define DISTANCIA_INFRA 36  

#define TRIG_PIN 23 // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin

float duration_us, distance_cm;
float distance_old;
float counter;

HardwareSerial dfSerial(2);  // UART2 del ESP32
DFPlayerMini_Fast myDFPlayer;

//// Control de los tiempos
unsigned long previousMillisEscena = 0;
unsigned long previousMillisSensor = 0;
unsigned long interval = 50; // Interval for updating brightness (milliseconds)

//// Setup de la potencia inicial
float potencia = 0;

// Pines de botones
const int BTN_PLAY_PAUSE = 15;
const int BTN_STOP       = 4;
const int BTN_VOL_DOWN   = 16;
const int BTN_VOL_UP     = 17;

// Estados anteriores para detección de flanco
bool lastPlayPauseState = HIGH;
bool lastStopState      = HIGH;
bool lastVolDownState   = HIGH;
bool lastVolUpState     = HIGH;

bool isPlaying = false;
int currentTrack = 1;
int volume = 20;  // Volumen inicial (0–30)



void setup() {
 // Inicializar comunicación Serial
  Serial.begin(115200);
  delay(3000); // Esperar a que se estabilice la comunicación serial
  Serial.println("Serial iniciado ok");
  Serial.println("---------------------------------------------");

// inicialización del audio
  dfSerial.begin(9600, SERIAL_8N1, DFPLAYER_RX, DFPLAYER_TX);

  Serial.println("Inicializando DFPlayer...");
  if (!myDFPlayer.begin(dfSerial)) {
    Serial.println("Error: no se pudo inicializar DFPlayer Mini.");
    while (true);  // Detener ejecución si falla
  }

  myDFPlayer.volume(volume);
  Serial.println("DFPlayer listo para reproducir.");

    // Configurar botones con resistencia pull-up interna
  pinMode(BTN_PLAY_PAUSE, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_VOL_DOWN, INPUT_PULLUP);
  pinMode(BTN_VOL_UP, INPUT_PULLUP);
}

  distance_old = 0.0;
  counter = 0.0;

// configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  
  // Configurar el pin como salida
  pinMode(MOTOR_PIN_00, OUTPUT);
  pinMode(MOTOR_PIN_01, OUTPUT);
  pinMode(MOTOR_PIN_02, OUTPUT);
  pinMode(MOTOR_PIN_03, OUTPUT);
  pinMode(MOTOR_PIN_04, OUTPUT);
  pinMode(MOTOR_PIN_05, OUTPUT);
  
  // Inicialmente motor apagado
  analogWrite(MOTOR_PIN_00, 0);
  analogWrite(MOTOR_PIN_01, 0);
  analogWrite(MOTOR_PIN_02, 0);
  analogWrite(MOTOR_PIN_03, 0);
  analogWrite(MOTOR_PIN_04, 0);
  analogWrite(MOTOR_PIN_05, 0);
}

void loop() {

  sensar();
  escena1();

  counter += 1;
  delay(25);
}

void sensar() {
  float intervalo_sensado = 100;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensor >= intervalo_sensado) {
    previousMillisSensor = currentMillis;

    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(ECHO_PIN, HIGH);

    // // calculate the distance
    distance_cm = 0.017 * duration_us;
    distance_old = distance_old * 0.8 + distance_cm * 0.2;
  }
}

void escena1() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillisEscena >= interval) {
    previousMillisEscena = currentMillis;

    float divisor = (distance_old);
    float potenciaExtra = 70 - distance_old;
    Serial.println(divisor);

    // Calcular el brillo de la luz basado en una sinusoide
    float sineWave = (
      sin(
        counter/divisor
        ) + 1.0
    ) / 2.0; // Scaled to 0-1 range
    potencia = int(sineWave * 128 + sineWave * potenciaExtra);

    setTodos(potencia);


    Serial.print("potencia: ");
    Serial.println(potencia);
  }
}

// void escena2() {
//   if distancia <= 60.0 && distancia >= 30 {
//     setTodos(128);
//   }
// }

void setTodos(int potencia) {
  analogWrite(MOTOR_PIN_00, potencia);  // ~25% de potencia
  analogWrite(MOTOR_PIN_01, potencia);
  analogWrite(MOTOR_PIN_02, potencia);
  analogWrite(MOTOR_PIN_03, potencia);
  analogWrite(MOTOR_PIN_04, potencia);
  analogWrite(MOTOR_PIN_05, potencia);
}
