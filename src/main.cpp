#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <string>
#include <pins.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 32);

std::string moves[3] = {"Rock", "Paper", "Scissors"};

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

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();
}

void loop() {
    uint8_t player1Move = 0;
    uint8_t player2Move = 0;

    if (digitalRead(ROCK1) == HIGH)
        player1Move = 1
    else if (digitalRead(PAPER1) == HIGH)
        player1Move = 2
    else if (digitalRead(SCISSOR1) == HIGH)
        player1Move = 3
    else player1Move = 0

    if (digitalRead(ROCK2) == HIGH)
        player2Move = 1
    else if (digitalRead(PAPER2) == HIGH)
        player2Move = 2
    else if (digitalRead(SCISSOR2) == HIGH)
        player2Move = 3
    else player2Move = 0

    display.setCursor(10, 16);
    if (player1Move != 0 && player1Move < 4)
    {
        display.println(moves[player1Move]);
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
        display.clearDisplay();
        display.display();
    }
    delay(200);
}
