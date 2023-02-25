#ifndef SNAKE_GRID_H
#define SNAKE_GRID_H

#include "Snake.h"

class Grid {
private:
    Snake *snake;
    int width;
    int height;
    int appleX;
    int appleY;

public:
    Grid(int width, int height) : width(width), height(height) {
        snake = new Snake(width / 2, height / 2, width, height);
    };

    int getWidth() { return width; };
    int getHeight() { return height; };

    Snake *getSnake() { return snake; };

    void display() {

        system("clear");

        for (int x = 0; x < width; x++) {
            std::cout << "---";
        }
        std::cout << std::endl;

        for (int y = 0; y < height; y++) {
            std::cout << "|";
            for (int x = 0; x < width; x++) {
                bool snakeFound = false;
                for (Cell *current = snake->getHead(); current != nullptr; current = current->getNext()) {
                    if (current->getX() == x && current->getY() == y) {
                        std::cout << " O ";
                        snakeFound = true;
                        break;
                    }
                }

                if (x == appleX && y == appleY) {
                    std::cout << " A ";
                    snakeFound = true;
                }

                if (!snakeFound) {
                    std::cout << "   ";
                }
            }
            std::cout << "|";
            std::cout << std::endl;
        }

        for (int x = 0; x < width; x++) {
            std::cout << "---";
        }
        std::cout << std::endl;
    };

    void generateApple() {
        srand(time(0));
        this->appleX = rand() % width;
        this->appleY = rand() % height;
    };

    void play() {

        generateApple();
        this->snake->setApple(appleX, appleY);

        bool running = true;
        while (running) {
            display();

            char input;

            std::cin >> input;

            switch (input) {
                case 'z':
                    this->snake->setDirection(Direction::UP);
                    running = this->snake->move(this->snake->getHead()->getX(), this->snake->getHead()->getY() - 1);
                    break;
                case 'd':
                    this->snake->setDirection(Direction::RIGHT);
                    running = this->snake->move(this->snake->getHead()->getX() + 1, this->snake->getHead()->getY());
                    break;
                case 's':
                    this->snake->setDirection(Direction::DOWN);
                    running = this->snake->move(this->snake->getHead()->getX(), this->snake->getHead()->getY() + 1);
                    break;
                case 'q':
                    this->snake->setDirection(Direction::LEFT);
                    running = this->snake->move(this->snake->getHead()->getX() - 1, this->snake->getHead()->getY());
                    break;
                default:
                    break;
            }

            if (this->snake->getHead()->getX() == appleX && this->snake->getHead()->getY() == appleY) {
                generateApple();
                this->snake->setApple(appleX, appleY);
                while (this->snake->checkApplePosition()) {
                    generateApple();
                    this->snake->setApple(appleX, appleY);
                }
            }
        }
        std::cout << "Game over | Point : " << this->snake->getPoint() << std::endl;
    };
};


#endif //SNAKE_GRID_H
