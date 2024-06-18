#include "Snake_MacOS.h"

// Konstruktory klas
Apple::Apple(int width, int height, const std::vector<Body> vec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(0, (width / 2) - 1), disY(0, height - 1);
    do {
        x = disX(gen);
        y = disY(gen);
    } while (vec.size() > 0 && std::find(vec.begin(), vec.end(), vec2(x, y)) != vec.end());
}

Snake::Snake(int width, int height) {
    head = vec2(width / 4, height / 2);
}

Board::Board(int width, int height): width(width), height(height), time(1000000) {
    snake = new Snake(width, height);
    apple = new Apple(width, height, snake->getBody());
}

// Destruktor klas
Board::~Board() {
    delete snake;
    delete apple;
}

//Metody klas
void Snake::moveBody(int x, int y) {
    if(body.size() > 0){
        body.erase(body.begin());
        body.push_back(vec2(x, y));
    }
}

bool Board::gameOver() const {
    vec2 head = snake->getHead();
    std::vector<Body> body = snake->getBody();
    if(head.x < 0 || head.x >= (width / 2)  || head.y < -1 || head.y >= height)
        return false;
    int j = snake->getBody().size();
    for(int i = 0; i < j; i++){
        if(head == body.at(i))
            return false;
    }
    return true;
}

void Board::Draw() const {
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_GREEN);     //1 - kolor glowy węza
    init_pair(2, COLOR_RED, COLOR_RED);         //2 - kolor czerwonego owocu
    init_pair(3, COLOR_WHITE, COLOR_WHITE);     //3 - kolor ramki
    init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA); //4 - kolor ciała węża
    attron(COLOR_PAIR(3));
    for(int i=0; i<width + 2; i++){
        mvprintw(0, i, " ");
        mvprintw(0, width + 2, " ");
        mvprintw(0, width + 3, " ");
        mvprintw((i + 2) / 2, 0, " ");
        mvprintw((i + 2) / 2, 1, " ");
        mvprintw(height + 2, i, " ");
        mvprintw(height + 2, width + 2, " ");
        mvprintw(height + 2, width + 3, " ");
        mvprintw((i + 2) / 2, width + 3, " ");
        mvprintw((i + 2) / 2, width + 2, " ");
    }
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    mvprintw(snake->getHead().y + 2, (snake->getHead().x * 2) + 2, " ");
    mvprintw(snake->getHead().y + 2, (snake->getHead().x * 2) + 3, " ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(4));
    for(auto i : snake->getBody()){
        mvprintw(i.y + 2, (i.x * 2) + 2, " ");
        mvprintw(i.y + 2, (i.x * 2) + 3, " ");
    }
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(2));
    mvprintw(apple->y + 2, (apple->x * 2) + 2, " ");
    mvprintw(apple->y + 2, (apple->x * 2) + 3, " ");
    attroff(COLOR_PAIR(2));
    mvprintw(height+3, 0, "Your tail length: %d", snake->getBody().size());
    }

void Board::Move(Direction d){
    int x = snake->getHead().x, y = snake->getHead().y;
    switch(d){
        case UP:
            snake->setHead(Head(snake->getHead() - vec2(0, 1)));
            break;
        case DOWN:
            snake->setHead(Head(snake->getHead() + vec2(0, 1)));
            break;
        case LEFT:
            snake->setHead(Head(snake->getHead() - vec2(1, 0)));
            break;
        case RIGHT:
            snake->setHead(Head(snake->getHead() + vec2(1, 0)));
            break;
    }
    
    if(snake->getHead() == vec2(apple->x, apple->y)){
        delete apple;
        apple = new Apple(width, height, snake->getBody());
        snake->grow(vec2(x, y));
        if(snake->getBody().size()%5 == 0){
        time *= 0.9;
    }
    }
    else{

        snake->moveBody(x, y);
    }
}

void Board::printGameOver() const {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    for(int i=0; i<width + 2; i++){
        mvprintw((height / 2) -6, i, " ");
        mvprintw((height / 2) -5, i, " ");
        mvprintw((height / 2) -4, i, " ");
        mvprintw((height / 2) -3, i, " ");
        mvprintw((height / 2) -2, i, " ");
        mvprintw((height / 2) -1, i, " ");
        mvprintw((height / 2), i, " ");
        mvprintw((height / 2) +1, i, " ");
        mvprintw((height / 2) +2, i, " ");
        
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw((height / 2) - 4, (width / 2) - 4, "GAME OVER");
    attroff(COLOR_PAIR(2));
    refresh();
    sleep(2);
}