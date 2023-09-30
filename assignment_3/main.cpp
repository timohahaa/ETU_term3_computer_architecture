#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

// egavga.bgi
// 640x480
// 
// var 5 -> f(x) = cos^3(x/2) + sqrt(x)
//
// lets do a little bit of hardcoding, shall we? :)
// NOTE: hardcoding is bad, but writing good code is not the purpose of this assignment :)
// 
// the interval for the graph is 3pi/2 - 15pi
// lets do 0 - 15pi, cause it looks nicer 
// lets make it that 502 px = 16pi (less than 640px, for the looks)
// so 31,375px = pi
// or 1px = 0,1000
// thats the step for our function calculation
// function max in [0, 16pi] is about 6.865
// lets do 10, cause it looks nicer
// so 400px = 10 (less than 480px, for the looks)
// or 1 px = 1/40 = 0,0250
// thats our step for Y
// lets compute the (0,0) of our graph
// (640 - 502)/2 = 69px to skip from top left corner RIGHT
// (480 - 400)/2 = 40px to skip from the botton left corner UP

const double STEP_X = 0.1000;
const double STEP_Y = 0.0250;
const int SKIP_X = 68; // cause indexing starts from 0
const int SKIP_Y = 39; // cause indexing starts from 0
const int GRAPH_WIDTH = 502;
const int GRAPH_HEIGHT = 400;
// point (0,0) on the graph
const int ZERO_X = 68;
const int ZERO_Y = 439;
// division values
const int DV_Y = 40;
const double DV_X = 31.375;
// function max on the interval
const double maxX = 37.8079;
const double maxY = 7.144;


char* markNumber(int num)
{
    return "8";
}

double functionResult(double x)
{
    double halfX = x / 2;
    double cosine = cos(halfX);
    double toPow3 = cosine * cosine * cosine;
    double sqroot = sqrt(x);
    return toPow3 + sqroot;
}

int main()
{
    clrscr();
    // init graphics
    int graph_driver;
    int graph_mode;
    int graph_error_code;
    graph_driver = DETECT;
    initgraph(&graph_driver, &graph_mode, "C:\\Turboc3\\BGI");
    graph_error_code = graphresult( ); 
    if(graph_error_code != grOk)
    {
        cputs("error while initting graphics\n\r");
        cprintf("error code is: %d\n\r", graph_error_code);
    }
    /*
    int mX = getmaxx(); // should always be 639 in my dos emulator
    int mY = getmaxy(); // should always be 239 in my dos emulator
    */
    // draw the axis
    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    // oX
    line(ZERO_X, ZERO_Y, ZERO_X + GRAPH_WIDTH, ZERO_Y);
    // oY
    line(ZERO_X, ZERO_Y, ZERO_X, ZERO_Y - GRAPH_HEIGHT); // minus cause (0,0) of the window is at the top left
    // mark the axis
    // oY
    for(int i = 0; i <= GRAPH_HEIGHT / DV_Y; i++)
    {
        // grid line
        setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
        line(ZERO_X, ZERO_Y - i * DV_Y, ZERO_X + GRAPH_WIDTH, ZERO_Y - i * DV_Y);
        // division value ticks
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(ZERO_X - 5, ZERO_Y - i * DV_Y, ZERO_X + 5, ZERO_Y - i * DV_Y);
        // magic numbers are basicaly me fiddeling with ofsets
        char* numStr;
        itoa(i, numStr, 10);
        outtextxy(ZERO_X - 20, ZERO_Y - i * DV_Y - 5, numStr);
    }
    // oX
    settextstyle(DEFAULT_FONT, 1, 0);
    for(int j = 0; j <= (int)(GRAPH_WIDTH / DV_X); j++)
    {
        // grid line
        setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
        line(ZERO_X + (int)(j * DV_X), ZERO_Y, ZERO_X + (int)(j * DV_X), ZERO_Y - GRAPH_HEIGHT);
        // division value ticks
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(ZERO_X + (int)(j * DV_X), ZERO_Y - 5, ZERO_X + (int)(j * DV_X), ZERO_Y + 5);
        // magic numbers are basicaly me fiddeling with ofsets
        char numStr[10] = {0};
        itoa(j, numStr, 10);
        char* res = strcat(numStr, "PI");
        outtextxy(ZERO_X + (int)(j * DV_X), ZERO_Y + 5, res);
    }
    // mark the interval = [3pi/2, 15pi]
    // 47px = 3pi/2
    // 470px = 15pi
    setcolor(LIGHTBLUE);
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    line(47 + SKIP_X, ZERO_Y, 47 + SKIP_X, ZERO_Y - GRAPH_HEIGHT);
    line(470 + SKIP_X, ZERO_Y, 470 + SKIP_X, ZERO_Y - GRAPH_HEIGHT);
    
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    // for loop thru 502 pixels
    double x = 0;
    for(int xPix = 0; xPix < GRAPH_WIDTH; xPix++)
    {
        double y = functionResult(x);
        // basicaly how many STEP_Y fit into result - to map result to pixel coordinate
        int yPix = GRAPH_HEIGHT - (int)ceil(y / STEP_Y);
        putpixel(xPix + SKIP_X, yPix + SKIP_Y, WHITE);
        x += STEP_X;
    }
    
    // function max on the interval
    int xM = (int)floor(maxX / STEP_X) + ZERO_X;
    int yM = GRAPH_HEIGHT - (int)ceil(maxY / STEP_Y) + SKIP_Y;
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    pieslice(xM, yM, 0, 359, 2);
    
    // function max as a text
    // all of the magic numbers were hand picked 
    setviewport(300, 300, 500, 350, 1);
    settextstyle(DEFAULT_FONT, 0, 0);
    setcolor(GREEN);
    rectangle(0, 0, 199, 49);
    char text1[1024];
    sprintf(text1, "Max is at x = %f", maxX);
    char text2[1024];
    sprintf(text2, "With value y = %f", maxY);
    outtextxy(10, 10, text1);
    outtextxy(10, 25, text2);
    getch();
    return 0;
}