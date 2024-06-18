#include "Snake_MacOS.h"

int main() {
    Board board(40, 20);
    char c = 0x00;
    Direction d = RIGHT;

    initscr();

    board.Draw();
    while(board.gameOver())
    {
        usleep(board.Time());
        c = getch();
        switch(c){
            case 'w':
                d != DOWN ? d = UP: d = d;
                break;
            case 's':
                d != UP ? d = DOWN: d = d;
                break;
            case 'a':    
                d != RIGHT ? d = LEFT: d = d;
                break;
            case 'd':    
                   d != LEFT ? d = RIGHT: d = d;
                break;
        }
        board.Move(d);
        clear();
        board.Draw();
        refresh();
    }

    board.printGameOver();

    endwin();

    return 0;
}