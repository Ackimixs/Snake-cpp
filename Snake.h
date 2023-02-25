#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <iostream>

enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

class Cell {
private:
    int x = 0;
    int y = 0;
    Direction direction = Direction::UP;
    Cell *next = nullptr;
public:
    Cell(int x, int y) : x(x), y(y), next(nullptr), direction(Direction::UP) {};
    Cell(const Cell &cell) : x(cell.x), y(cell.y), next(cell.next), direction(cell.direction) {};
    int getX() { return x; };
    int getY() { return y; };

    void setX(int x) { this->x = x; };
    void setY(int y) { this->y = y; };

    Direction getDirection() { return direction; };
    void setDirection(Direction direction) { this->direction = direction; };

    void setNext(Cell *next) { this->next = next; };
    Cell *getNext() { return next; };

    void move(int x, int y, Direction direction) { this->x = x; this->y = y; this->direction = direction; };
};


class Snake {
private:
    int size = 0;
    Cell *head = nullptr;
    Cell *tail = nullptr;
    Direction direction = Direction::UP;
    int gridWidth;
    int gridHeight;
    int appleX;
    int appleY;
    int point;

public:
    Snake(int x, int y, int gridWidth, int gridHeight) : gridWidth(gridWidth), gridHeight(gridHeight), appleX(0), appleY(0), point(0) {
        head = new Cell(x, y);
        tail = head;
        size = 1;
    };

    void setDirection(Direction direction) { this->direction = direction; };
    Direction getDirection() { return direction; };

    void setApple(int appleX, int appleY) { this->appleX = appleX; this->appleY = appleY; };

    int getSize() { return size; };

    int getPoint() { return point; };

    Cell *getHead() { return head; };

    void grow() {

        int newX, newY;

        switch (tail->getDirection()) {
            case Direction::UP:
                newX = tail->getX();
                newY = tail->getY()+1;
                break;
            case Direction::RIGHT:
                newX = tail->getX()-1;
                newY = tail->getY();
                break;
            case Direction::DOWN:
                newX = tail->getX();
                newY = tail->getY()-1;
                break;
            case Direction::LEFT:
                newX = tail->getX()+1;
                newY = tail->getY();
                break;
        }

        Cell *newCell = new Cell(newX, newY);
        tail->setNext(newCell);
        tail = newCell;
        size++;
    };

    bool move(int x, int y) {
        Cell *current = head;
        while (current->getNext() != nullptr) {
            Cell* temp = new Cell(*(current->getNext()));
            current->getNext()->move(current->getX(), current->getY(), current->getDirection());
            current = temp;
        }

        if (x < 0) {
            x = gridWidth-1;
        } else if (x >= gridWidth) {
            x = 0;
        }

        if (y < 0) {
            y = gridHeight-1;
        } else if (y >= gridHeight) {
            y = 0;
        }

        head->move(x, y, direction);

        if (head->getX() == appleX && head->getY() == appleY) {
            grow();
            point++;
        }

        if (checkCollision()) {
            return false;
        } else {
            return true;
        }
    };

    bool checkCollision() {
        Cell *current = head->getNext();
        while (current != nullptr) {
            if (current->getX() == head->getX() && current->getY() == head->getY()) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    };

    bool checkApplePosition() {
        Cell *current = head;
        while (current != nullptr) {
            if (current->getX() == appleX && current->getY() == appleY) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    };

};



#endif //SNAKE_SNAKE_H
