#include <Arduino.h>
#include <pins.h>

void setup() {
    pinMode(ROCK1, INPUT);
    pinMode(PAPER1, INPUT);
    pinMode(SCISSOR1, INPUT);
    pinMode(ROCK2, INPUT);
    pinMode(PAPER2, INPUT);
    pinMode(SCISSOR2, INPUT);
}

void loop() {
    if (digitalRead(ROCK1) == LOW)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    } else digitalWrite(LED_BUILTIN, LOW);
}