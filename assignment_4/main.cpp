#include <conio.h>
#include <dos.h>

// window params for my varinat
const int X1 = 10;
const int Y1 = 8;
const int X2 = 70;
const int Y2 = 18;
const int WINDOW_WIDTH = 60;
const int WINDOW_HEIGHT = 10;
// scan-codes for the control keys
const char F4 = 0x3E;
const char F5 = 0x3F;
const char F6 = 0x40;
const char F7 = 0x41;
// other scan-codes
const char ENTER = 0x1C;
// other
const int DELAY = 300;

struct Key
{
    char scan_code;
    char ascii_code;
};

// cool ._.
Key getKey()
{
    char sc, ac;
    _asm{
        MOV AH, 0
        INT 0x16
        MOV ac, AL
        MOV sc, AH
    }
    Key ret = {sc, ac};
    return ret;
}

int main()
{
    clrscr();
    cputs("to exit the programm, press enter");
    //draw a rectangle arroung the window
    window(X1-1, Y1-1, X2+1, Y2+1);
    int i = 0;
    for(i = 1; i <= X2-X1+2; i++) cputs("#");
    gotoxy(1, Y2-Y1+2);
    for(i = 1; i <= X2-X1+2; i++) cputs("#");
    gotoxy(1,1);
    for(i = 1; i <= Y2-Y1+2; i++)
    {
        gotoxy(1,i);
        cputs("#");
        gotoxy(X2-X1+2, i);
        cputs("#");
    }
    window(X1, Y1, X2, Y2);
    textcolor(RED);
    // start with F7, so the symbol goes right
    Key key = {F7, 0};
    // coordinates of a 
    int x = 1, y = 1;
    gotoxy(x, y);
    cputs("*");
    while(key.scan_code != ENTER)
    {
        delay(DELAY);
        if(kbhit())
        {
            key = getKey();
        }
        // put " " on top of a previous "*" position
        gotoxy(x, y);
        cputs(" ");
        switch(key.scan_code)
        {
            case F4: // go left
            {
                x--;
                if(x < 1)
                {
                    x = WINDOW_WIDTH;
                }
            }
            break;
            case F5: // go down
            {
                // cause top-left corner is (0,0)
                y++;
                if(y > WINDOW_HEIGHT)
                {
                    y = 1;
                }
            }
            break;
            case F6: // go up
            {
                y--;
                if(y < 1)
                {
                    y = WINDOW_HEIGHT;
                }
            }
            break;
            case F7: // go right
            {
                x++;
                if(x > WINDOW_WIDTH)
                {
                    x = 1;
                }
            }
            break;
            default:
            // do nothing
            break;
        }
        // now put the "*" char
        gotoxy(x, y);
        cputs("*");
    }
    return 0;
}