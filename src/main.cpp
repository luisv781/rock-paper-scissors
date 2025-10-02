#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <pins.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64);

String moves[3] = {"Paper", "Rock", "Scissors"};

int8_t points = 0;

void scrollScreen() {
    delay(500);
    display.startscrollright(0x00, 0x20);
    delay(2200);
    display.stopscroll();
    delay(500);
}

bool pressAnyButton(const unsigned long ms = 20) {
    const unsigned long start = millis();
    while (millis() - start < ms) {
        for (int i = 0; i < 6; i++) {
            constexpr uint8_t buttons[] = {ROCK1, PAPER1, SCISSOR1, ROCK2, PAPER2, SCISSOR2};
            if (digitalRead(buttons[i]) != HIGH)
                return true;
        }
        delay(20);
    }
    return false;
}

void intro() {
    display.clearDisplay();
    display.setCursor(15, 16);
    display.println("Rock");
    display.display();
    if (pressAnyButton(1000)) return;
    display.setCursor(15, 32);
    display.println("Paper");
    display.display();
    if (pressAnyButton(1000)) return;
    display.setCursor(15, 48);
    display.println("Scissors");
    display.display();
    if (pressAnyButton(1000)) return;

    while (true) {
        for (int i = 0; i < 5; ++i) {
            display.fillRect(0, 0, 128, 30, BLACK);
            display.display();
            if (pressAnyButton(200)) return;

            display.fillRect(0, 0, 128, 46, BLACK);
            display.display();
            if (pressAnyButton(200)) return;

            display.fillRect(0, 0, 128, 64, BLACK);
            display.setCursor(15, 16);
            display.println("Rock");
            display.display();
            if (pressAnyButton(200)) return;

            display.setCursor(15, 32);
            display.println("Paper");
            display.display();
            if (pressAnyButton(200)) return;

            display.setCursor(15, 48);
            display.println("Scissors");
            display.display();
            if (pressAnyButton(200)) return;
        }

        display.clearDisplay();
        display.display();
        if (pressAnyButton(200)) return;

        for (int i = 0; i < 5; ++i) {
            display.setCursor(35, 16);
            display.println("Press");
            display.setCursor(50, 32);
            display.println("Any");
            display.setCursor(30, 48);
            display.println("Button");
            display.display();
            if (pressAnyButton(200)) return;

            display.clearDisplay();
            display.display();
            if (pressAnyButton(200)) return;
        }
    }
}

uint8_t getPlayerChosenMove(const bool player) {
    for (int move = 0; move < 3; move++) {
        constexpr uint8_t player1Moves[] = {PAPER1, ROCK1, SCISSOR1};
        constexpr uint8_t player2Moves[] = {PAPER2, ROCK2, SCISSOR2};
        if (digitalRead((!player) ? player1Moves[move] : player2Moves[move]) != HIGH)
            return move + 1;
    }

    return 0;
}

uint8_t playerMove(const bool player) {
    while (!getPlayerChosenMove(player)) {
        delay(20);
    }

    const uint8_t playerChosenMove = getPlayerChosenMove(player);

    if (playerChosenMove)
        return playerChosenMove;

    display.clearDisplay();
    display.display();

    return 0;
}

void setup() {
    pinMode(ROCK1, INPUT_PULLUP);
    pinMode(PAPER1, INPUT_PULLUP);
    pinMode(SCISSOR1, INPUT_PULLUP);
    pinMode(ROCK2, INPUT_PULLUP);
    pinMode(PAPER2, INPUT_PULLUP);
    pinMode(SCISSOR2, INPUT_PULLUP);

    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.display();

    display.setTextSize(2);
    display.setTextColor(WHITE);

    intro();
    display.clearDisplay();
    display.display();
    delay(1000);
}

void loop() {
    if (points == 3 || points == -3) {
        if (points == 3) {
            display.setCursor(15, 16);
            display.println("Player 1");
            display.setCursor(40, 40);
            display.println("Wins");
            points = 0;
        } else if (points == -3) {
            display.setCursor(15, 16);
            display.println("Player 2");
            display.setCursor(40, 40);
            display.println("Wins");
            points = 0;
        }
        display.display();
        delay(3000);

        intro();
        display.clearDisplay();
        display.display();
        delay(500);
    }

    uint8_t player1Move = 0;
    uint8_t player2Move = 0;

    display.clearDisplay();
    display.setCursor(5, 16);
    display.println("Player 1's");
    display.setCursor(40, 40);
    display.println("Turn");
    display.display();
    player1Move = playerMove(false);

    display.clearDisplay();
    display.setCursor(5, 16);
    display.println("Player 2's");
    display.setCursor(40, 40);
    display.println("Turn");
    display.display();
    player2Move = playerMove(true);

    display.clearDisplay();
    display.setCursor(0, 16);
    switch (player2Move - player1Move) {
        case 1:
        case -2:
            display.setCursor(15, 16);
            display.println("Player 1");
            display.setCursor(50, 40);
            display.println("+1");
            points++;
            break;

        case -1:
        case 2:
            display.setCursor(15, 16);
            display.println("Player 2");
            display.setCursor(50, 40);
            display.println("+1");
            points--;
            break;
        
        default:
            display.setCursor(45, 28);
            display.println("Tie");
            break;
    }
    display.display();
    delay(3000);

    display.clearDisplay();
}
