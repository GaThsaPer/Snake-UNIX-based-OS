#ifndef SNAKE_MACOS_H
#define SNAKE_MACOS_H

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <random>
#include <ncurses.h>
#include <unistd.h>
#include <chrono>

// Kierunki ruchu węża
enum Direction {UP, DOWN, LEFT, RIGHT};

class vec2 {
    public:
    int x, y;
    vec2() : x(0), y(0) {}
    vec2(int x, int y) : x(x), y(y) {}
    vec2& operator+(const vec2& v){
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2& operator-(const vec2& v){
        x -= v.x;
        y -= v.y;
        return *this;
    }
    vec2& operator=(const vec2& v){
        x = v.x;
        y = v.y;
        return *this;
    }
    bool operator==(const vec2& v){
        return x == v.x && y == v.y;
    }
};

class Body : public vec2
{
    public:
    Body() : vec2() {}
    Body(const vec2& v) : vec2(v) {}
    Body(int x, int y) : vec2(x, y) {}
    Body& operator= (const vec2& v){
        x = v.x;
        y = v.y;
        return *this;
    }
    bool operator==(const vec2& b)const {
        return x == b.x && y == b.y;
    }
};

class Head : public vec2
{
    public:
    Head() : vec2() {}
    Head(const vec2& v) : vec2(v) {}
    Head(int x, int y) : vec2(x, y) {}
    Head& operator= (const vec2& v){
        x = v.x;
        y = v.y;
        return *this;
    }
    bool operator==(const Body& b){
        return x == b.x && y == b.y;
    }
};

// Klasa reprezentująca węża
class Snake {
    Head head;
    std::vector<Body> body;
public:
    Snake(int width, int height);
    Head getHead() const { return head; }
    void setHead(Head h) { head = h; }
    void moveBody(int x, int y);
    std::vector<Body> getBody() const { return body; }
    void grow(vec2 p) { body.push_back(p); }
};

// Klasa reprezentująca jabłko
class Apple : public vec2
{
public:
    Apple(int width, int height, const std::vector<Body> vec);
};

// Klasa reprezentująca planszę
class Board {
    int width, height;
    Snake *snake;
    Apple *apple;
    int time;
public:
    Board(int width, int height);
    ~Board();
    void Draw() const;
    void Move(Direction d);
    bool gameOver() const;
    void printGameOver() const;
    int Time() const { return time; }
};


#endif // SNAKE_MACOS_H