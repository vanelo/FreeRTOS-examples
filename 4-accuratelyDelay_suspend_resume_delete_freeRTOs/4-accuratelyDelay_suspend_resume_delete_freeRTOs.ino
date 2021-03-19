//----------------------------------------------------------
// Print to Serial monitor using 2 tasks
// Accurately dalay
// Delete, Suspend and resume functions
//----------------------------------------------------------

#include <Arduino_FreeRTOS.h>

void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

int counter = 0;

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

  TickType_t getTick;
  // the getTick will get time from systick of SO
  // systick generates interrupt requests, this allows an OS to carry out context switching to support multiple tasking
  getTick = xTaskGetTickCount();

  // Infinite loop
  while(1){
    Serial.println("Task1");
    
    counter ++;

    if(counter == 7){
      Serial.println(counter);
      // Resume task
//      vTaskResume(Task_Handle2);
    }
    
    xTaskDelayUntil(&getTick, 1000 / portTICK_PERIOD_MS); // More accuracy delay
    // vTaskDelay(1000/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
  }
}

void Task_Print2(void *param){
  (void) param;

  // Infinite loop
  while(1){

    Serial.println("Task2");
    if(counter == 15){
        Serial.println(counter);
        // Delete task
         vTaskDelete(Task_Handle2); // Then you cannot call and re run the task again

        // Suspend task
//        vTaskSuspend(Task_Handle2);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS); // portTICK_PERIOD_MS is the value of each millisecond
  }
}
