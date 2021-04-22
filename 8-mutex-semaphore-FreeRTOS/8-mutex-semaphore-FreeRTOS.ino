//----------------------------------------------------------
// Mutex: using FreeRTOS semaphore
//----------------------------------------------------------

#include <Arduino_FreeRTOS.h>

void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

volatile int a=0;
volatile boolean myMutex = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Create tasks
  // xTaskCreate params:  Task, task name, task memory (don't worry about it for now), priority, task handler
  // Priority: The highest priority, it will run first
  xTaskCreate(Task_Print1, "Tasks1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(Task_Print2, "Tasks2", 100, NULL, 1, &Task_Handle2);
}

void loop() {
  // Don't put code right here
}

void Task_Print1(void *param){
  (void) param;

  // Infinite loop
  while(1){
    while(myMutex == true);
    a = a+1;
    Serial.println(a);
    vTaskDelay(10/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
    myMutex = true; // Then this task go to infinite loop
  }
}

void Task_Print2(void *param){
  (void) param;

  // Infinite loop
  while(1){
    while(myMutex == false);
    a = a+1;
    Serial.println(a);
    vTaskDelay(10/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
    myMutex = false;
  }
}
