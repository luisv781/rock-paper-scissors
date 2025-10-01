#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <pins.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64);

String moves[3] = {"Rock", "Paper", "Scissors"};

void setup() {
    pinMode(ROCK1, INPUT_PULLUP);
    pinMode(PAPER1, INPUT_PULLUP);
    pinMode(SCISSOR1, INPUT_PULLUP);
    pinMode(ROCK2, INPUT_PULLUP);
    pinMode(PAPER2, INPUT_PULLUP);
    pinMode(SCISSOR2, INPUT_PULLUP);

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
}

bool pressAnyButton() {
    for (int i = 0; i < 6; i++) {
        constexpr uint8_t buttons[] = {ROCK1, PAPER1, SCISSOR1, ROCK2, PAPER2, SCISSOR2};
        if (digitalRead(buttons[i]) != HIGH)
            return true;
    }
    return false;
}

void intro() {
    display.setCursor(5, 16);
    display.println("Rock");
    display.display();
    delay(1000);
    display.setCursor(5, 32);
    display.println("Paper");
    display.display();
    delay(1000);
    display.setCursor(5, 48);
    display.println("Scissors");
    display.display();
    delay(1000);

    while (!pressAnyButton()) {
        for (int i = 0; i < 5; ++i) {
            display.fillRect(0, 0, 128, 30, BLACK);
            display.display();
            delay(200);

            display.fillRect(0, 0, 128, 46, BLACK);
            display.display();
            delay(200);

            display.fillRect(0, 0, 128, 64, BLACK);
            display.setCursor(5, 16);
            display.println("Rock");
            display.display();
            delay(200);

            display.setCursor(5, 32);
            display.println("Paper");
            display.display();
            delay(200);

            display.setCursor(5, 48);
            display.println("Scissors");
            display.display();
            delay(200);

            if (pressAnyButton()) break;
        }

        display.clearDisplay();
        display.display();
        delay(200);

        for (int i = 0; i < 3; ++i) {
            display.setCursor(5, 16);
            display.println("Press");
            display.setCursor(5, 32);
            display.println("Any");
            display.setCursor(5, 48);
            display.println("Button");
            display.display();
            delay(200);

            display.clearDisplay();
            display.display();
            delay(200);

            if (pressAnyButton()) break;
        }
    }

    display.clearDisplay();
    display.display();
}

uint8_t getPlayerMove(const bool player) {
    for (int move = 0; move < 3; move++) {
        constexpr uint8_t player1Moves[] = {ROCK1, PAPER1, SCISSOR1};
        constexpr uint8_t player2Moves[] = {ROCK2, PAPER2, SCISSOR2};
        if (digitalRead((!player) ? player1Moves[move] : player2Moves[move]) != HIGH)
            return move + 1;
    }

    return 0;
}

void playerMove() {
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

    display.clearDisplay();
    display.display();
}

void loop() {
    intro();
    delay(500);
    while (true) {
        playerMove();
    }
}
