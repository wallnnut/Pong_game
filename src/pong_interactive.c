#include <stdio.h>
#include <ncurses.h>

void screenRendering(const int FIRST_RACKET_X, const int SECOND_RACKET_X, int firstRacketY, int secondRacketY,
                     int ballX, int ballY, const int HEIGHT_OF_GAME, const int WIDTH_OF_GAME,
                     int PLAYER_1_SCORE,
                     int PLAYER_2_SCORE);  // Функция отрисовки всего
int moveFirstRocket(int rocket_1_Y, int height, char symbol);
int moveSecondRocket(int rocket_2_Y, int height, char symbol);
int ballMoveY(int ballY, int booleanForBallY);
int ballMoveX(int ballX, int booleanForBallX);
int changingBooleanY(int ballY, int booleanForBallY);
int changingBooleanX(int ballY, int firstRacketY, int ballX, const int FIRST_RACKET_X, int secondRacketY,
                     const int SECOND_RACKET_X, int booleanForBallX);

int main() {
    initscr();
    noecho();
    cbreak();
    timeout(100);
    const int FIRST_RACKET_X = 3,
              SECOND_RACKET_X = 77;  // Константные координаты первой и второй ракетки
    const int HEIGHT_OF_GAME = 25,
              WIDTH_OF_GAME = 80;  // Константные координаты полей игры
    int firstRacketY = 13,
        secondRacketY = 13;      // Изначальные координаты ракеток по Y
    int ballX = 40, ballY = 13;  // Изначальные координаты мяча
    int PLAYER_1_SCORE = 0, PLAYER_2_SCORE = 0;
    int booleanForBallX = 0;
    int booleanForBallY = 0;
    while (1) {  // Бесконечный цикл
        screenRendering(FIRST_RACKET_X, SECOND_RACKET_X, firstRacketY, secondRacketY, ballX, ballY,
                        HEIGHT_OF_GAME, WIDTH_OF_GAME, PLAYER_1_SCORE, PLAYER_2_SCORE);
        if (PLAYER_1_SCORE == 21) {
            printw("\n                              - PLAYER ONE WINS -\n\n");
            refresh();
            return 0;
        } else if (PLAYER_2_SCORE == 21) {
            printw("\n                              - PLAYER TWO WINS -\n\n");
            refresh();
            return 0;
        }
        char filteredChar;
        filteredChar = getch();
        firstRacketY = moveFirstRocket(firstRacketY, HEIGHT_OF_GAME, filteredChar);
        secondRacketY = moveSecondRocket(secondRacketY, HEIGHT_OF_GAME, filteredChar);
        ballX = ballMoveX(ballX, booleanForBallX);
        ballY = ballMoveY(ballY, booleanForBallY);
        booleanForBallY = changingBooleanY(ballY, booleanForBallY);
        booleanForBallX = changingBooleanX(ballY, firstRacketY, ballX, FIRST_RACKET_X, secondRacketY,
                                           SECOND_RACKET_X, booleanForBallX);
        if (ballX == 0) {
            PLAYER_2_SCORE++;
            ballX = 40;
            ballY = 13;
        }
        if (ballX == 80) {
            PLAYER_1_SCORE++;
            ballX = 40;
            ballY = 13;
        }
    clear();
    }
    endwin();
    return 0;
}

int changingBooleanX(int ballY, int firstRacketY, int ballX, const int FIRST_RACKET_X, int secondRacketY,
                     const int SECOND_RACKET_X, int booleanForBallX) {
    if ((ballY == firstRacketY || ballY == firstRacketY - 1 || ballY == firstRacketY + 1) &&
        ballX == FIRST_RACKET_X + 1)
        booleanForBallX = 1;
    if ((ballY == secondRacketY || ballY == secondRacketY - 1 || ballY == secondRacketY + 1) &&
        ballX == SECOND_RACKET_X - 1)
        booleanForBallX = 0;
    return booleanForBallX;
}

int changingBooleanY(int ballY, int booleanForBallY) {
    if (ballY == 24) booleanForBallY = 0;
    if (ballY == 1) booleanForBallY = 1;
    return booleanForBallY;
}

void screenRendering(const int FIRST_RACKET_X, const int SECOND_RACKET_X, int firstRacketY, int secondRacketY,
                     int ballX, int ballY, const int HEIGHT_OF_GAME, const int WIDTH_OF_GAME,
                     int PLAYER_1_SCORE, int PLAYER_2_SCORE) {
    printw(
        "--PlayerOne %d--                       SCORE                       "
        "--PlayerTwo %d--\n",
        PLAYER_1_SCORE, PLAYER_2_SCORE);
    for (int i = 0; i <= HEIGHT_OF_GAME; i++) {
        for (int j = 0; j <= WIDTH_OF_GAME; j++) {
            if (i == 0 || i == HEIGHT_OF_GAME)
                printw("-");
            else if (j == 0 || j == WIDTH_OF_GAME)
                printw("|");

            else if (i == ballY && j == ballX)  // Отрисовка мяча
                printw("o");
            else if ((i == firstRacketY && j == FIRST_RACKET_X) ||
                     (i == secondRacketY && j == SECOND_RACKET_X) ||
                     (i == firstRacketY + 1 && j == FIRST_RACKET_X) ||
                     (i == secondRacketY + 1 && j == SECOND_RACKET_X) ||
                     (i == firstRacketY - 1 && j == FIRST_RACKET_X) ||
                     (i == secondRacketY - 1 && j == SECOND_RACKET_X))  // Отрисовка ракеток
                printw("#");
            else  // Заполнение пустого пространства пробелом
                printw(" ");
        }
        printw("\n");
    }
}

int moveFirstRocket(int rocket_1_Y, int height, char symbol) {
    switch (symbol) {
        case 97:
            if (rocket_1_Y - 2 == 0) {
                return rocket_1_Y;
            } else {
                return rocket_1_Y - 1;
            }
            break;
        case 122:
            if (rocket_1_Y + 2 == height) {
                return rocket_1_Y;
            } else {
                return rocket_1_Y + 1;
            }
            break;

        default:
            return rocket_1_Y;
    }
}
int moveSecondRocket(int rocket_2_Y, int height, char symbol) {
    switch (symbol) {
        case 109:
            if (rocket_2_Y + 2 == height) {
                return rocket_2_Y;
            } else {
                return rocket_2_Y + 1;
            }
            break;
        case 107:
            if (rocket_2_Y - 2 == 0) {
                return rocket_2_Y;
            } else {
                return rocket_2_Y - 1;
            }
            break;
        default:
            return rocket_2_Y;
    }
}

int ballMoveX(int ballX, int booleanForBallX) {
    if (booleanForBallX == 1) return ballX + 2;
    return ballX - 2;
}

int ballMoveY(int ballY, int booleanForBallY) {
    if (booleanForBallY == 1) return ballY + 1;
    return ballY - 1;
}
