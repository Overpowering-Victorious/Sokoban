#include<bits/stdc++.h>
using namespace std;
#define MAP_WIDTH 15
#define MAP_HEIGHT 10
#define SCREEN_SIZE SCREEN_WIDTH * SCREEN_HEIGHT

// char screen[SCREEN_SIZE];

// including files for windows system
#ifdef WIN32 

#include <windows.h>
#include <stdlib.h>
#include <cstdlib>

HANDLE console;
CONSOLE_CURSOR_INFO cursor;
COORD coord;
DWORD chars_to_write = 0;

#endif

#ifdef unix

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

#endif


void InitScreen()
{
    // print directly to screen buffer
    #ifdef WIN32
    console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);    
    //cursor.dwSize = 100;
    cursor.bVisible = FALSE;    
    coord.X = 0;
    coord.Y = 0;
    SetConsoleActiveScreenBuffer(console);
    SetConsoleCursorInfo(console, &cursor);        
    #endif

    // use ANSI VT100 escape sequences hide cursor and clear screen 
    #ifdef unix
    cout<<endl;
    #endif
}

void RefreshScreen()
{
    // might not be needed on windows natively, needed on wine though
    // for(int scr_cell = 0; scr_cell < SCREEN_SIZE; scr_cell++)
    //     if(!screen[scr_cell]) screen[scr_cell] = ' ';

    // // update screen buffer
    // #ifdef WIN32
    // // screen[SCREEN_SIZE - 1] = 0;
	// WriteConsoleOutputCharacter(console, screen, SCREEN_WIDTH * SCREEN_HEIGHT, coord, &chars_to_write);
    // #endif

    #ifdef WIN32
    system("cls");
    cout<<endl;
    #endif

    // print screen buffer to stdout at coordinates 0, 0
    #ifdef unix
    // printf("\x1b[0;0H%s", screen);
    system("clear");
    cout<<endl;
    #endif
}




void PrintMap(char** MAP)
{
    RefreshScreen(); 
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH-1; col++)
        {
            cout<<MAP[row][col];
        }

        cout<<endl;
    }



} 



#ifdef WIN32

int getch()
{
    DWORD mode, chars_to_read;
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
        
    GetConsoleMode(console, &mode);
    SetConsoleMode(console, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    int key = 0;
    ReadConsole(console, &key, 1, &chars_to_read, NULL);
    SetConsoleMode(console, mode);
    
    return key;
}

#endif


#ifdef unix

int getch()
{
    struct termios oldattr, newattr;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    int key = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

    return key;   
}

#endif