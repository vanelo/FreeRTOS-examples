//----------------------------------------------------------
// Mutex: manual mutex
//----------------------------------------------------------

// Using Mutex to handle Multiple Task
/* Mutex (https://stackoverflow.com/questions/34524/what-is-a-mutex) 
  A Mutex is a mutually exclusive flag.
  It acts as a gate keeper to a section of code allowing one thread in and blocking access to all others.
  This ensures that the code being controled will only be hit by a single thread at a time.
*/

// Concurrency: using mutex  and priority to solve concurrency problem
// the maximun priority in the system is level 15

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
