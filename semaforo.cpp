// Definimos los pines de salida de la placa de Arduino correspondiente a cada LED
const int LED_RED = 12;
const int LED_YELLOW = 9;
const int LED_GREEN = 6;
const int BUZZER = 13;

unsigned long previousTimeYellowBuzzer = 0;
unsigned long previousTimeRedBuzzer = 0;
unsigned long intervalYellowBuzzer = 2000; // Intervalo de 2 segundos para el LED_YELLOW
unsigned long intervalRedBuzzer = 1000;    // Intervalo de 1 segundo para el LED_RED

// Intervalos LED//

const int LedTimeGreen = 10000;
const int LedTimeYellow = 3000;
const int LedTimeRed = 5000;

void setup()
{
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop()
{
  // Encender el LED_GREEN durante 10 segundos
  TimerLed(LED_GREEN, LedTimeGreen);

  // Encender el LED_YELLOW durante 3 segundos y activar el buzzer cada 2 segundos
  TimerLedWithBuzzer(LED_YELLOW, LedTimeYellow, intervalYellowBuzzer);

  // Encender el LED_RED durante 5 segundos y activar el buzzer cada 1 segundo
  TimerLedWithBuzzer(LED_RED, LedTimeRed, intervalRedBuzzer);
}

void TimerLed(int LED, unsigned long TIME)
{
  digitalWrite(LED, HIGH);
  delay(TIME);
  digitalWrite(LED, LOW);
}

void TimerLedWithBuzzer(int LED, unsigned long TIME, unsigned long interval)
{
  digitalWrite(LED, HIGH);
  unsigned long functionCurrentTime = millis();
  

  while (millis() - functionCurrentTime < TIME) // (millis() - functionCurrentTime) -> Tiempo de ejecucion de Arduino - Tiempo ejecucion de funcion = currentTime.
  {
    // Controlar el buzzer según el intervalo especificado
    if (LED == LED_YELLOW && millis() - previousTimeYellowBuzzer >= interval)
    {
      previousTimeYellowBuzzer = millis(); // Tiempo desde que se ejecuto el buzzer.
      activateBuzzer(500);
    }
    else if (LED == LED_RED && millis() - previousTimeRedBuzzer >= interval)
    {
      previousTimeRedBuzzer = millis(); //Tiempo desde que se ejecuto el buzzer.
      activateBuzzer(1000);
    }
  }

  digitalWrite(LED, LOW);
}

void activateBuzzer(int POWER)
{
  tone(BUZZER, POWER);
  delay(100);
  noTone(BUZZER);
  delay(100);
}
