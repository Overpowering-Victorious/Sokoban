#include<bits/stdc++.h>
#include<unistd.h>
#include "working.h"
#include "Map.h"
using namespace std;


#define MAP_WIDTH 15
#define MAP_HEIGHT 10
#define PLAYER_POSITION pos_y * MAP_WIDTH + pos_x


// this is basic MAP without any dynamic location
// should change in future for different MAPs at different times
// first implementation so using basic MAP

// 1D map --->  2D map mein change karna hai


char** MAP;

bool check_deadlock( int row , int col ){
    bool check = false;
    if( MAP[row-1][col] == '#' ){
        if( MAP[row][col-1] == '#' || MAP[row][col+1] == '#' ) check = true;
    }
    if( MAP[row+1][col] == '#' ){
        if( MAP[row][col-1] == '#' || MAP[row][col+1] == '#' ) check = true;
    }
    return check;
}

pair<int,int> dest_squares[10];

int GetDestinationSquare(){
    // returns no of locations were blocks are to be placed
    // checks if the location is filled(by O) or not (by x) and returns total no of such locations

    int count=0;

    for(int row = 0; row < MAP_HEIGHT; row++){
        for(int col = 0; col < MAP_WIDTH; col++){
            if(MAP[row][col] == 'x' || MAP[row][col] == 'O'){
                dest_squares[count].first = row;
                dest_squares[count++].second = col;
            }
        }
    }

    return count ;
}

void GetPosition(int &pos_x, int &pos_y)
{
    for(int row = 0; row < MAP_HEIGHT; row++)                           // loop ower MAP rows
    {
        for(int col = 0; col < MAP_WIDTH; col++)                        // loop ower MAP columns
        {
            
            if(MAP[row][col] == '@')                                        // if current cell on the MAP contains player
            {
                pos_x = row;                                           // store player's x coordinate
                pos_y = col;                                           // store player's y coordinate
            }
        }
    }
}

bool MoveCharacter(int &pos_x, int &pos_y, char x)
{
    bool deadlock = false;
    if(x=='w' && MAP[pos_x-1][pos_y]!='#')
    {
        if(((MAP[pos_x-1][pos_y] == 'B') || (MAP[pos_x-1][pos_y] == 'O')) )
             {
                MAP[pos_x][pos_y]=' ';
                pos_x-=1;

                if(MAP[pos_x-1][pos_y]==' '){
                    MAP[pos_x-1][pos_y]='B';
                    deadlock = check_deadlock( pos_x-1 , pos_y );
                }
                else if(MAP[pos_x-1][pos_y]=='x')
                    MAP[pos_x-1][pos_y]='O';
                
                else
                    pos_x+=1;
                MAP[pos_x][pos_y]='@';
             }
             else
             {
                MAP[pos_x][pos_y]=' ';
                pos_x-=1;
                MAP[pos_x][pos_y]='@';
             }
    }

    else if(x=='s' && MAP[pos_x+1][pos_y]!='#')
    {
        if(((MAP[pos_x+1][pos_y] == 'B') ||                   // if player hits the box
            (MAP[pos_x+1][pos_y] == 'O')))
             {
                MAP[pos_x][pos_y]=' ';
                pos_x+=1;

                if(MAP[pos_x+1][pos_y]==' '){
                    MAP[pos_x+1][pos_y]='B';
                    deadlock = check_deadlock( pos_x+1 , pos_y );
                }
                else if(MAP[pos_x+1][pos_y]=='x')
                    MAP[pos_x+1][pos_y]='O';
                
                else
                    pos_x-=1;
                MAP[pos_x][pos_y]='@';
             }
             else
             {
                MAP[pos_x][pos_y]=' ';
                pos_x+=1;
                MAP[pos_x][pos_y]='@';
             }
    }

    else if(x=='a' && MAP[pos_x][pos_y-1]!='#')
    {
        if(((MAP[pos_x][pos_y-1] == 'B') ||                   // if player hits the box
            (MAP[pos_x][pos_y-1] == 'O')))
             {
                MAP[pos_x][pos_y]=' ';
                pos_y-=1;

                if(MAP[pos_x][pos_y-1]==' '){
                    MAP[pos_x][pos_y-1]='B';
                    deadlock = check_deadlock( pos_x , pos_y-1 );
                }
                else if(MAP[pos_x][pos_y-1]=='x')
                    MAP[pos_x][pos_y-1]='O';
                
                else
                    pos_y+=1;
                MAP[pos_x][pos_y]='@';
             }
             else
             {
                MAP[pos_x][pos_y]=' ';
                pos_y-=1;
                MAP[pos_x][pos_y]='@';
             }
    }
    else if(x=='d' && MAP[pos_x][pos_y+1]!='#')
    {
        if(((MAP[pos_x][pos_y+1] == 'B') ||                   // if player hits the box
            (MAP[pos_x][pos_y+1] == 'O')))
             {
                MAP[pos_x][pos_y]=' ';
                pos_y+=1;

                if(MAP[pos_x][pos_y+1]==' '){
                    MAP[pos_x][pos_y+1]='B';
                    deadlock = check_deadlock( pos_x , pos_y+1 );
                }
                else if(MAP[pos_x][pos_y+1]=='x')
                    MAP[pos_x][pos_y+1]='O';
                
                else
                    pos_y-=1;
                MAP[pos_x][pos_y]='@';
             }
             else
             {
                MAP[pos_x][pos_y]=' ';
                pos_y+=1;
                MAP[pos_x][pos_y]='@';
             }
    }
    return deadlock;
}


// void MoveCharacter(int pos_x, int pos_y, int offset)
// {
//     if(MAP[PLAYER_POSITION + offset] != '#')                            // if player doesn't hit the wall
//     {
//         if(((MAP[PLAYER_POSITION + offset] == 'B') ||                   // if player hits the box
//             (MAP[PLAYER_POSITION + offset] == 'O')) &&                  // or the box on 'x' cell
//             (MAP[PLAYER_POSITION + offset * 2] != '#' ||                // and box doesn't hit a wall
//              MAP[PLAYER_POSITION + offset * 2] != 'B' ||                // or another box
//              MAP[PLAYER_POSITION + offset * 2] != 'O'))                 // or box on 'x' cell
//         {
//             MAP[PLAYER_POSITION] = ' ';                                 // clear previous player's position
//             pos_x += offset;                                            // update player's coordinate

//             if(MAP[PLAYER_POSITION + offset] == ' ')                    // if the square next to the box is empty
//                 MAP[PLAYER_POSITION + offset] = 'B';                    // push the box

//             else if(MAP[PLAYER_POSITION + offset] == 'x')               // if the square next to the box is 'x'  
//                 MAP[PLAYER_POSITION + offset] = 'O';                    // mark the box is on it's place

//             else
//             {
//                 MAP[PLAYER_POSITION - offset] = '@';                    // if box hits the wall or another box
//                 return;                                                 // don't push it any further
//             }

//             MAP[PLAYER_POSITION] = '@';                                 // draw the player in the new position
//         }

//         else                                                            // if the square next to the player is empty                                                        
//         {
//             MAP[PLAYER_POSITION] = ' ';                                 // clear previous player position
//             pos_x += offset;                                            // update player's coordinate
//             MAP[PLAYER_POSITION] = '@';                                 // draw the player in the new position
//         }
//     }   
// } 


int main()
{
    
    int key;
    int pos_x, pos_y;
    int dest_count;

    
    MAP = __MAP__();

    int dest_num = GetDestinationSquare();
    cout<<dest_num<<endl;
    PrintMap(MAP);
    GetPosition(pos_x,pos_y);


    while(true)
    {
        char x=getch();

        bool deadlock_check = MoveCharacter(pos_x,pos_y,x);

        dest_count = 0;

        for(int i=0;i<10;i++){
            if(MAP[dest_squares[i].first][dest_squares[i].second] == 'O') dest_count++;

            if(MAP[dest_squares[i].first][dest_squares[i].second] == ' ')
                MAP[dest_squares[i].first][dest_squares[i].second] = 'x';
        }
        
        PrintMap(MAP);
        if( deadlock_check ){
            cout<<"YOU HAVE PUT ONE BOX IN DEADLOCK :( \n";
            cout<<"TRY AGAIN...\n";
            break;
        }
        if(dest_num == dest_count)
        {
            cout<<"YOU WIN";
            getch();
            break;
        }
        if(x == 65)
            exit(0);
    }

    // for(int i=0;i<10;i++){
    //     for(int j=0;j<14;j++)
    //         cout<<MAP[i][j];
    //     cout<<endl;
    // }
    // while(true){
    //     char x = getch();
    //     // cout<<x;
    //     int center_x = SCREEN_WIDTH /2 - MAP_WIDTH/2;
    //     int center_y = SCREEN_HEIGHT /2 - MAP_HEIGHT/2;
        
        
    //     GetPosition(&pos_x, &pos_y);
        
    //     switch(x){

    //         case 'w': MoveCharacter(pos_x, pos_y, -MAP_WIDTH-1); break;
    //         case 's': MoveCharacter(pos_x, pos_y, MAP_WIDTH+1); break;
    //         case 'a': MoveCharacter(pos_x, pos_y, - 1); break;
    //         case 'd': MoveCharacter(pos_x, pos_y, 1); break;
    //     }

    //     dest_count = 0;

    //     for(int i=0;i<10;i++){
    //         if(MAP[dest_squares[i]] == 'O') dest_count++;

    //         if(MAP[dest_squares[i]] == ' ')
    //             MAP[dest_squares[i]] = 'x';
    //     }
        
    //     PrintMap(MAP);

    //     if(dest_num == dest_count)
    //     {
    //         cout<<"YOU WIN";
    //         getch();
    //         break;
    //     }

    //     if(x == 65){
    //         exit(0);
    //     }
    // }

    cout<<"Exiting...";

    
    // system("clear");

    return 0;
}