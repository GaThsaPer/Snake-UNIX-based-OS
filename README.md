# Snake UNIX-base Systems
This is a traditional Snake game created to intergrate with UNIX-based Systems. The game runs in the terminal and uses the library called ncurses. 
## Requirements
1. UNIX-based Operating System
2. Ncurses library
3. g++ compiler
## Instalation
First, you need to install ncurses library:
```bash 
brew install ncurses
```
Then, navigate to the directory where you want to download Snake and open it using the command cd and use following commands: 
```bash 
git clone https://github.com/GaThsaPer/Snake-on-MacOS.git
cd Snake-on-MacOS
```
If you don't want unnecessary files, run the following commands:
```bash
rm ./.gitignore
rm -rf ./.git
rm -rf ./Images
```
If you don't have a g++ compiler, you need to install GCC (GNU Compiler Collection):
```bash
#Linux
apt install gcc
apt install g++
#MacOS
brew install gcc
brew install g++
```
Then, to compile files, run:
```bash
g++ -std=c++17 -o Snake main.cpp Snake_MacOS.cpp -lncurses
```
Then you can then play by typing the following in the terminal: 
```bash
./Snake
```
## Gameplay 
To change trajectory of snake movement use wsad keys. </br>
Remember if head will touch wall or tail you will lose.
## Visualization
<img src="Images/_1.png" width=400 alt="Screenshot of the beginning of the game"> <img src="Images/_2.png" width=400 alt="Screenshot during gameplay">
<img src="Images/_3.png" width=400 alt="Screenshot during gamplay"> <img src="Images/_4.png" width=400 alt="Screenshot of Game Over">
## Technology and Functionality
### vec2
Basic class, used to inheried to other objects like apple and snake parts. Contains coordinates and overloaded operators.
```c++
class vec2 {
    public:
    int x, y;
    vec2() : x(0), y(0) {}
    vec2(int x, int y) : x(x), y(y) {}
    vec2& operator+(const vec2& v){}
    vec2& operator-(const vec2& v){}
    vec2& operator=(const vec2& v){}
    bool operator==(const vec2& v){}
};
```
### Body and Head
Contains simple overloaded operators and coords to allow build the Snake.
Body:
```c++
class Body : public vec2
{
    public:
    Body() : vec2() {}
    Body(const vec2& v) : vec2(v) {}
    Body(int x, int y) : vec2(x, y) {}
    Body& operator= (const vec2& v){}
    bool operator==(const vec2& b)const {}
};
```
Head:
```c++
class Head : public vec2
{
    public:
    Head() : vec2() {}
    Head(const vec2& v) : vec2(v) {}
    Head(int x, int y) : vec2(x, y) {}
    Head& operator= (const vec2& v){}
    bool operator==(const Body& b){}
};
```
### Snake
Main class to construct and contain a snake part objects and some usefull methods.
```c++
class Snake {
    Head head;
    std::vector<Body> body;
public:
    Snake(int width, int height);
    Head getHead() const {}
    void setHead(Head h) {}
    void moveBody(int x, int y);
    std::vector<Body> getBody() const {}
    void grow(vec2 p) {}
};
```
* getHead - Used to return `Head` object.
* setHead - Set new value for `Head` object.
* moveBody - Method to move the tail of Snake.
* getBody - Returns the vector of `Body` objects.
* grow - Adds new object to the tail.

### Apple 
Only contains coorinates and constructor.
```c++
class Apple : public vec2
{
public:
    Apple(int width, int height, const std::vector<Body> vec);
};
```
### Board
Main class to display all the game to screen. Contains every objects used like Apple, Snake, size of the map and time.
```c++
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
```
* Draw - Main method used to display the game on the screen.
* Move - Process the pressed key and updates Snake movement direction.
* gameOver - Boolean which checks whether player hit into tail or border.
* printGameOver - Displays the "Game Over" message on the screen.
* Time - Return the current duration of the game.

## Contact 
You can find contact to me on my [My GitHub](https://github.com/GaThsaPer) account, or text on [Instagram](https://www.instagram.com/gathasper/).
