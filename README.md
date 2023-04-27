# Proyecto simulación de semaforo en Arduino


## Integrantes: 

Facundo Moriconi

## Descripcion:

En este proyecto llevado a cabo en la plataforma Tinkercad se logro realizar una simulacion de un semáforo, el mismo integra un sistema de alerta para las personas no videntes, avisando de manera sonora el cambio de señalización. Cuando el semaforo se encuentra en verde, no emite sonido a diferencia que cuando esta en amarillo o rojo emite distintas señales acusticas en un determinado tiempo según el color de señalización(Amarillo es una señal mas fuerte y menos repetitiva y en rojo es una señal mas débil pero mas repetitiva).


## Funcion principal:

Tenemos la función principal "loop" que justamente no es más que un bucle en el cual se desarrollan las funcionalidades del semáforo.

void loop()
{
  // Encender el LED_GREEN durante 10 segundos
  TimerLed(LED_GREEN, LedTimeGreen);

  // Encender el LED_YELLOW durante 3 segundos y activar el buzzer cada 2 segundos
  TimerLedWithBuzzer(LED_YELLOW, LedTimeYellow, intervalYellowBuzzer);

  // Encender el LED_RED durante 5 segundos y activar el buzzer cada 1 segundo
  TimerLedWithBuzzer(LED_RED, LedTimeRed, intervalRedBuzzer);
}


## Funciones secundarias:

### TimerLed:

TimerLed es una función en la cual manejamos el encendido y apagado de los leds del semaforo, tiene dos argumentos en el cual se debe especificar el numero de LED, y el tiempo de duración de encendido del mismo.


```cpp
void TimerLed(int LED, unsigned long TIME)
{
digitalWrite(LED, HIGH);
delay(TIME);
digitalWrite(LED, LOW);
}
```




### TimerLedWithBuzzer:


TimerLedWithBuzzer es una función en la cual se maneja el encendido de la luz Led del semaforo en conjunto del encendido del Buzzer(controlador con el cual se emite la señal acustica). Esto se puede llevar acabo principalmente por el uso de la funcion millis(), con esta función podemos determinar el transcurso del tiempo desde que se ejecuto el Arduino como así tambien por ejemplo podemos declararla en una variable y usarlo como punto de control para obtener el tiempo transcurrido desde que se ejecuto una función como hacemos en este caso.

```cpp
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
```

### activateBuzzer: 

activateBuzzer es una función simple en la cual manejamos el Buzzer atravez de la funcion tone(pinBuzzer, Frecuencia) y noTone(pinBuzzer) en conjunto con delay()

```cpp
void activateBuzzer(int POWER)
{
  tone(BUZZER, POWER);
  delay(100);
  noTone(BUZZER);
  delay(100);
}
```
