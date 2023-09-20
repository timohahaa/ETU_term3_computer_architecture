#include <dos.h>
#include <conio.h>

const char* PHRASE = "Hello, world!";
const char* NL = "\n\r";
const int X1 = 10;
const int Y1 = 8;
const int X2 = 70;
const int Y2 = 18;
const int S = 2;
const int TIME = 700;
const int TEXT_COLOR_MASK = 15; // 0b00001111
const int BG_COLOR_MASK = 112; // 0b01110000
const int BLINK_MASK = 128; // 0b10000000

void printNewLines(int count)
{
    for(int i = 0; i < count; i++)
    {
	cputs(NL);
    }
}

int main()
{
    clrscr();
    window(X1, Y1, X2, Y2);
    for(int i = 0; i < 256; i++)
    {
            delay(TIME);
	    insline();
            textattr(i);
            int textColor = i & TEXT_COLOR_MASK;
            int bgColor = i & BG_COLOR_MASK;
            int blink = i & BLINK_MASK;
	    cputs(PHRASE);
            cprintf(" %d text: %c, bg: %c, blink: %d\n\r", i,  textColor, bgColor, blink);
	    printNewLines(S);
    }
    cputs(PHRASE);
    getch();
    return 0;
}