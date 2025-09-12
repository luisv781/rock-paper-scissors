#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <pins.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64);

String moves[3] = {"Rock", "Paper", "Scissors"};

void setup() {
    pinMode(ROCK1, INPUT);
    pinMode(PAPER1, INPUT);
    pinMode(SCISSOR1, INPUT);
    pinMode(ROCK2, INPUT);
    pinMode(PAPER2, INPUT);
    pinMode(SCISSOR2, INPUT);

    Serial.begin(9600);

    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.display();
    delay(2000);

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();
}

void scrollScreen() {
    delay(500);
    display.startscrollright(0x00, 0x20);
    delay(2200);
    display.stopscroll();
    delay(500);
    display.startscrollleft(0x00, 0x20);
    delay(2200);
    display.stopscroll();
    delay(500);
}

uint8_t getPlayerMove(bool player) {
    if (!player) {
        if (digitalRead(ROCK1) == HIGH)
            return 1;
        if (digitalRead(PAPER1) == HIGH)
            return 2;
        if (digitalRead(SCISSOR1) == HIGH)
            return 3;
    } else {
        if (digitalRead(ROCK2) == HIGH)
            return 1;
        if (digitalRead(PAPER2) == HIGH)
            return 2;
        if (digitalRead(SCISSOR2) == HIGH)
            return 3;
    }

    return 0;
}

void loop() {
    uint8_t player1Move = getPlayerMove(false);
    uint8_t player2Move = getPlayerMove(true);

    if (player1Move != 0 && player1Move < 4)
    {
        display.setCursor(10, 16);
        display.println("Player 1:");

        display.setCursor(10, 40);
        display.println(moves[player1Move - 1]);
        display.display();

        scrollScreen();
    } else if (player2Move != 0 && player2Move < 4) {
        display.setCursor(10, 16);
        display.println("Player 2:");

        display.setCursor(10, 40);
        display.println(moves[player2Move - 1]);
        display.display();

        scrollScreen();
    }
    player2Move = 0;
    player1Move = 0;

    display.clearDisplay();
    display.display();
}
