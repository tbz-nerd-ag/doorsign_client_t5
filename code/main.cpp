#include <Arduino.h>

#include "epd_driver.h"
#include "utilities.h"

#include <header.h>

int battery = -1;
bool readroom = false;
uint8_t *framebuffer;

void doorsign_init();

void setup() {
    //begin things
    Serial.begin(115200);
    Serial.println("Start DoorSign Client ...");

    Serial.println("Framebuffer init ...");
    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer){
        Serial.println("Framebuffer init didn`t work!");
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    Serial.println("EPD init ...");
    epd_init();

    readEEPROM();
    connectwifi("normal");
    rtctimeset();

    if (!readRoom()) {
        doorsign_init();
    }

    connectmqtt();
    sendmqtthello();

    esp_sleep_enable_timer_wakeup(300000000);
    esp_deep_sleep_start();
}

void loop() {

}

void doorsign_init() {
    bool initmessage = false;
    Serial.println("Printing Error Picture ...");

    errormenu(1);

    delay(2000);

    connectmqtt();
    sendmqtthello();

    if (!initmessage) {
        waitofinitmsg();
    }

    esp_sleep_enable_timer_wakeup(300000000);
    esp_deep_sleep_start();
}
