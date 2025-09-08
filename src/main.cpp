#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <pins.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 32);

void setup() {
    pinMode(ROCK1, INPUT);
    pinMode(PAPER1, INPUT);
    pinMode(SCISSOR1, INPUT);
    pinMode(ROCK2, INPUT);
    pinMode(PAPER2, INPUT);
    pinMode(SCISSOR2, INPUT);

    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.display();
    delay(2000);
    display.clearDisplay();

    display.drawLine(0, 16, 127, 16, WHITE);
    display.display();
    delay(1000);
}

void loop() {
    if (digitalRead(ROCK1) == HIGH)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        display.setCursor(10, 16);
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.println("Rock");
        display.display();

        delay(500);
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(500);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(500);
    } else
    {
        digitalWrite(LED_BUILTIN, LOW);
        display.clearDisplay();
        display.display();
    }
    delay(200);
}