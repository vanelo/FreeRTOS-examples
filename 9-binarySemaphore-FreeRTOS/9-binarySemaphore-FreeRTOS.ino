//----------------------------------------------------------
// FreeRTOS binary semaphore
//----------------------------------------------------------

/*
 * https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial-using-semaphore-and-mutex-in-freertos-with-arduino
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 */

//----------------------------------------------------------
//  binary semaphore is used for synchronization between tasks or between tasks and interrupt.
//----------------------------------------------------------


#include <Arduino_FreeRTOS.h>
#include <semphr.h>

long debouncing_time = 150; 
volatile unsigned long last_micros;
 
SemaphoreHandle_t interruptSemaphore;
 
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);

  xTaskCreate(TaskLed,  "Led", 128, NULL, 0, NULL );
  xTaskCreate(TaskBlink,  "LedBlink", 128, NULL, 0, NULL );

  interruptSemaphore = xSemaphoreCreateBinary();
  if (interruptSemaphore != NULL) {
    // Parameters of attachInterrupt: number of interrupt, ISR, mode
    /*  - number of the interrupt: Allowed data types: int
     *  - ISR: the ISR to call when the interrupt occurs; this function must take no parameters and return nothing. This function is sometimes referred to as an interrupt service routine.
     *  - mode: defines when the interrupt should be triggered. Four constants are predefined as valid values:
     *    - LOW to trigger the interrupt whenever the pin is low,
     *    - CHANGE to trigger the interrupt whenever the pin changes value
     *    - RISING to trigger when the pin goes from low to high,
     *    - FALLING for when the pin goes from high to low.
     */
    
    attachInterrupt(digitalPinToInterrupt(2), debounceInterrupt, LOW);
  }
}
 
void loop() {}
 
void interruptHandler() {
  Serial.println("interruptHandler was executed");
  xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}
 
void TaskLed(void *pvParameters)
{
  (void) pvParameters;
  pinMode(8, OUTPUT);
  for (;;) {
    //if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdTRUE){ // pdTRUE if the semaphore was obtained. pdFALSE if xTicksToWait expired without the semaphore becoming available.
      Serial.println("Semaphore taken");
      digitalWrite(8, !digitalRead(8));
    }
  }
}

void TaskBlink(void *pvParameters)
{
  (void) pvParameters;
  pinMode(7, OUTPUT);
  for (;;) {
      digitalWrite(7, HIGH);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      digitalWrite(7, LOW);
      vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    interruptHandler();
    last_micros = micros();
    Serial.println(last_micros);
  }
}
 
