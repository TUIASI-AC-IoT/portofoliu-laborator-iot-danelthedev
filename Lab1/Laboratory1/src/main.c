#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO 4
#define GPIO_OUTPUT_PIN_SEL (1ULL << GPIO_OUTPUT_IO)

#define GPIO_INPUT_IO_2 2
#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_2)

#define ESP_INTR_FLAG_DEFAULT 0

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

int counter = 0;

static void gpio_task(void* arg)
{
    uint32_t io_num;
    for (;;) {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            if(gpio_get_level(io_num) == 1){
                counter ++;
                printf("Button was pressed: %d times\n", counter);

            }
        }
    }
}
  
void app_main()
{
    // zero-initialize the config structure.
    gpio_config_t io_conf = {};
    // disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    // set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    // bit mask of the pins that you want to set
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    // disable pull-down mode
    io_conf.pull_down_en = 0;
    // disable pull-up mode
    io_conf.pull_up_en = 0;
    // configure GPIO with the given settings
    gpio_config(&io_conf);

    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins, use GPIO 2 here
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);


    //change gpio interrupt type for one pin
    gpio_set_intr_type(GPIO_INPUT_IO_2, GPIO_INTR_ANYEDGE);

    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    
    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(GPIO_INPUT_IO_2, gpio_isr_handler, (void*) GPIO_INPUT_IO_2);

    //start gpio task
    xTaskCreate(gpio_task, "gpio_task", 2048, NULL, 10, NULL);
    
    int press_time_counter = 0;
    int blink_time = 100;
    bool blinking = false;

    while (1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        if(gpio_get_level(GPIO_INPUT_IO_2) == 0){
            press_time_counter ++;
            printf("increasing pressed count\n");

            if(press_time_counter == 10){
                blinking = !blinking;
                printf("setting blink to %d\n", blinking);
            }
        }else{
            printf("button is no longer pressed\n");
            press_time_counter = 0;
            
            if(blinking){
                for(int i = 0; i < 10; i++){
                    vTaskDelay(100 / portTICK_PERIOD_MS);
                    gpio_set_level(GPIO_OUTPUT_IO, i%2);
                }
            }
        }
    }

}