//----------------------------------------------------------
// To control the led and print to serial monitor at the same time
//----------------------------------------------------------

#include <Arduino_FreeRTOS.h>

void Task_Controlled(void *param);
void Task_Print(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(8, INPUT_PULLUP);

  // Create task
  xTaskCreate(Task_Controlled, "Task_Controlled", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(Task_Print, "Task2", 100, NULL, 1, &Task_Handle2);
}

void loop() { }

void Task_Controlled(void *param){
  (void) param;

  // Infinite loop
  for(;;){
    if(digitalRead(8) == 0){
      digitalWrite(13, LOW); // Turn on
      while(digitalRead(8) == 0);
    }else digitalWrite(13, HIGH); // Turn off
    vTaskDelay(1000/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
  }
}


void Task_Print(void *param){
  (void) param;

  // Infinite loop
  for(;;){
    Serial.println("Task Print");
    vTaskDelay(1000/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
  }
}
