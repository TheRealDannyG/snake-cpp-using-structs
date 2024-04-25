#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h> // To make spawn value more random
using namespace std;

struct Point {
    int x;
    int y;
};

struct Snake {
    Point head;
    Point tail[100];
    int length;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir;
};

struct Game {
    bool gameOver;
    const int width = 20;
    const int height = 20;
    int score;
    Point fruit;
};

void Setup(Game& game, Snake& snake) {
    game.gameOver = false;
    snake.dir = snake.STOP;
    snake.head.x = game.width / 2;
    snake.head.y = game.height / 2;
    game.fruit.x = rand() % game.width;
    game.fruit.y = rand() % game.height;
    game.score = 0;
    snake.length = 0;
}

void Draw(const Game& game, const Snake& snake) {
    system("cls"); //system("clear");
    cout << endl;
    cout << " ";
    for (int i = 0; i < game.width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < game.height; i++) {
        for (int j = 0; j < game.width; j++) {
            if (j == 0)
                cout << " #";
            if (i == snake.head.y && j == snake.head.x)
                cout << "O";
            else if (i == game.fruit.y && j == game.fruit.x)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < snake.length; k++) {
                    if (snake.tail[k].x == j && snake.tail[k].y == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == game.width - 1)
                cout << "#";
        }
        cout << endl;
    }

    cout << " ";
    for (int i = 0; i < game.width + 2; i++)
        cout << "#";
    cout << endl;
    cout << " Score:" << game.score << endl;
}

void Input(Snake& snake) {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            snake.dir = snake.LEFT;
            break;
        case 'd':
            snake.dir = snake.RIGHT;
            break;
        case 'w':
            snake.dir = snake.UP;
            break;
        case 's':
            snake.dir = snake.DOWN;
            break;
        case 'x':
            exit(0);
        default:
            break;
        }
    }
}

void Logic(Game& game, Snake& snake) {
    Point prev = snake.head;
    Point prev2;
    snake.tail[0] = snake.head;
    for (int i = 1; i < snake.length; i++) {
        prev2 = snake.tail[i];
        snake.tail[i] = prev;
        prev = prev2;
    }
    switch (snake.dir) {
    case Snake::LEFT:
        snake.head.x--;
        break;
    case Snake::RIGHT:
        snake.head.x++;
        break;
    case Snake::UP:
        snake.head.y--;
        break;
    case Snake::DOWN:
        snake.head.y++;
        break;
    default:
        break;
    }
    if (snake.head.x >= game.width || snake.head.x < 0 || snake.head.y >= game.height || snake.head.y < 0)
        game.gameOver = true;

    for (int i = 0; i < snake.length; i++)
        if (snake.tail[i].x == snake.head.x && snake.tail[i].y == snake.head.y)
            game.gameOver = true;

    if (snake.head.x == game.fruit.x && snake.head.y == game.fruit.y) {
        srand(time(0)); // Random seed value for rand based on time
        game.score += 10;
        game.fruit.x = rand() % game.width;
        game.fruit.y = rand() % game.height;
        snake.length++;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    system("MODE con cols=24 lines=25");
    Game game;
    Snake snake;
    Setup(game, snake);
    while (!game.gameOver) {
        Draw(game, snake);
        Input(snake);
        Logic(game, snake);
        Sleep(50);
    }
    return 0;
}
