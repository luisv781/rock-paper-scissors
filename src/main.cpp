#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <pins.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64);

String moves[3] = {"Paper", "Rock", "Scissors"};


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

    uint8_t playerChosenMove = getPlayerChosenMove(player);

    if (playerChosenMove)
    {
        // display.clearDisplay();
        // display.display();

        // display.setCursor(10, 16);
        // display.println(!player ? "Player 1:" : "Player 2:");

        // display.setCursor(10, 40);
        // display.println(moves[playerChosenMove - 1]);
        // display.display();

        // scrollScreen();
        return playerChosenMove;
    }

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
    delay(2000);

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();

    intro();
    delay(500);
}

void loop() {
    uint8_t player1Move = 0;
    uint8_t player2Move = 0;

    display.clearDisplay();
    display.setCursor(0, 16);
    display.println("Player 1's");
    display.setCursor(30, 40);
    display.println("Turn");
    display.display();

    player1Move = playerMove(false);

    display.setCursor(0, 16);
    display.println("Player 2's");
    display.setCursor(30, 40);
    display.println("Turn");
    display.display();

    player2Move = playerMove(false);


    display.setCursor(0, 16);
    switch (player2Move - player1Move)
    {
    case 1:
    case -2:
        display.setCursor(0, 16);
        display.println("Player 1");
        display.setCursor(30, 40);
        display.println("Wins");
        break;

    case -1:
    case 2:
        display.setCursor(0, 16);
        display.println("Player 2");
        display.setCursor(30, 40);
        display.println("Wins");
        break;
    
    default:
        display.setCursor(32, 28);
        display.println("Tie");
        break;
    }
    display.display();
    delay(3000);
}
