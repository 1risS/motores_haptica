#define MOTOR_PIN_00 13 // Motor conectado al pin 13
#define MOTOR_PIN_01 12
#define MOTOR_PIN_02 14
#define MOTOR_PIN_03 27
#define MOTOR_PIN_04 26
#define MOTOR_PIN_05 25

void setup()
{
    Serial.begin(115200);
    delay(2000);
    Serial.println("Control de Motor con PWM estándar");

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

void loop()
{
    // Demostración 1: Velocidad baja
    Serial.println("Velocidad baja");
    analogWrite(MOTOR_PIN_00, 64); // ~25% de potencia
    analogWrite(MOTOR_PIN_01, 64);
    analogWrite(MOTOR_PIN_02, 64);
    analogWrite(MOTOR_PIN_03, 64);
    analogWrite(MOTOR_PIN_04, 64);
    analogWrite(MOTOR_PIN_05, 64);
    delay(2000);

    // Demostración 2: Velocidad media
    Serial.println("Velocidad media");
    analogWrite(MOTOR_PIN_00, 128); // 50% de potencia
    analogWrite(MOTOR_PIN_01, 128);
    analogWrite(MOTOR_PIN_02, 128);
    analogWrite(MOTOR_PIN_03, 128);
    analogWrite(MOTOR_PIN_04, 128);
    analogWrite(MOTOR_PIN_05, 128);
    delay(2000);

    // Demostración 3: Velocidad alta
    Serial.println("Velocidad alta");
    analogWrite(MOTOR_PIN_00, 255); // 100% de potencia
    analogWrite(MOTOR_PIN_01, 255);
    analogWrite(MOTOR_PIN_02, 255);
    analogWrite(MOTOR_PIN_03, 255);
    analogWrite(MOTOR_PIN_04, 255);
    analogWrite(MOTOR_PIN_05, 255);
    delay(2000);

    // Demostración 4: Motor apagado
    Serial.println("Motor apagado");
    analogWrite(MOTOR_PIN_00, 0); // 0% - apagado
    analogWrite(MOTOR_PIN_01, 0);
    analogWrite(MOTOR_PIN_02, 0);
    analogWrite(MOTOR_PIN_03, 0);
    analogWrite(MOTOR_PIN_04, 0);
    analogWrite(MOTOR_PIN_05, 0);
    delay(2000);

    // Demostración 5: Incremento gradual
    Serial.println("Incrementando velocidad...");
    for (int i = 0; i <= 255; i += 5)
    {
        analogWrite(MOTOR_PIN_00, i);
        analogWrite(MOTOR_PIN_01, i);
        analogWrite(MOTOR_PIN_02, i);
        analogWrite(MOTOR_PIN_03, i);
        analogWrite(MOTOR_PIN_04, i);
        analogWrite(MOTOR_PIN_05, i);
        Serial.print("Velocidad: ");
        Serial.println(i);
        delay(100);
    }

    // Demostración 6: Decremento gradual
    Serial.println("Disminuyendo velocidad...");
    for (int i = 255; i >= 0; i -= 5)
    {
        analogWrite(MOTOR_PIN_00, i);
        analogWrite(MOTOR_PIN_01, i);
        analogWrite(MOTOR_PIN_02, i);
        analogWrite(MOTOR_PIN_03, i);
        analogWrite(MOTOR_PIN_04, i);
        analogWrite(MOTOR_PIN_05, i);
        Serial.print("Velocidad: ");
        Serial.println(i);
        delay(100);
    }
}