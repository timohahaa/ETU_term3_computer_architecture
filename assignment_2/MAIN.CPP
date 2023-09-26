#include <dos.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>

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


const char* numToColor(int color, int rus) 
{
    switch(color)
    {
        case 0:
        {
            if(rus)
            {
                return "CHERNIY";
            }
            return "BLACK";
        }
        break;
        case 1:
        {
            if(rus)
            {
                return "SINIY";
            }
            return "BLUE";
        }
        break;
        case 2:
        {
            if(rus)
            {
                return "ZELENIY";
            }
            return "GREEN";
        }
        break;
        case 3:
        {
            if(rus)
            {
                return "SINE-ZELENIY";
            }
            return "CYAN";
        }
        break;
        case 4:
        {
            if(rus)
            {
                return "KRASNIY";
            }
            return "RED";
        }
        break;
        case 5:
        {
            if(rus)
            {
                return "KRASNO-SINIY";
            }
            return "MAGENTA";
        }
        break;
        case 6:
        {
            if(rus)
            {
                return "KORICHNEVIY";
            }
            return "BROWN";
        }
        break;
        case 7:
        {
            if(rus)
            {
                return "SVETLO-SERIY";
            }
            return "LIGHTGRAY";
        }
        break;
        case 8:
        {
            if(rus)
            {
                return "TEMNO-SERIY";
            }
            return "DARKGRAY";
        }
        break;
        case 9:
        {
            if(rus)
            {
                return "SVETLO-SINIY";
            }
            return "LIGHTBLUE";
        }
        break;
        case 10:
        {
            if(rus)
            {
                return "SVETLO-ZELENIY";
            }
            return "LIGHTGREEN";
        }
        break;
        case 11:
        {
            if(rus)
            {
                return "SVETLO-SINE-ZELENIY";
            }
            return "LIGHTCYAN";
        }
        break;
        case 12:
        {
            if(rus)
            {
                return "SVETLO-KRASNIY";
            }
            return "LIGHTRED";
        }
        break;
        case 13:
        {
            if(rus)
            {
                return "SVETLO-KRASNO-SINIY";
            }
            return "LIGHTMAGENTA";
        }
        break;
        case 14:
        {
            if(rus)
            {
                return "ZELTIY";
            }
            return "YELLOW";
        }
        break;
        case 15:
        {
            if(rus)
            {
                return "BELIY";
            }
            return "WHITE";
        }
        break;


    }
}


void printNewLines(int count)
{
    for(int i = 0; i < count; i++)
    {
	cputs(NL);
    }
}

int main()
{
    system("chcp 866");
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
            cprintf(" text: %s, bg: %s\n\r", numToColor(textColor, 1), numToColor(bgColor >> 4, 0));
	    printNewLines(S);
    }
    cputs(PHRASE);
    getch();
    return 0;
}