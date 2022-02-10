#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <ncurses.h>

using namespace std;

#define PLAYERCOUNT 2       // use arguments to alter player count and winning line length

int fieldsize;
int WINLENGTH = 3;
enum tictacs{_ = '_', X = 'X', O = 'O', A = 'A', Z = '@'};
enum gamestate{inprogress, victory, draw, abandoned};
struct player
{
    bool cpucontrolled;
    tictacs symbol;
    int color;
};
struct game
{
    tictacs** gamefield = nullptr;
    player* Players;
    gamestate Gamestate = inprogress;
    int turncount = 0;
    int turnorder;
};
struct cursor
{
    int x = 0;
    int y = 0;
    cursor(int newx, int newy)
    {
        x = newx;
        y = newy;
    }
};
struct cpumemory
{
    int dirx;
    int diry;
    int threat;
    cpumemory(int dx, int dy, int thr)
    {
        dirx = dx;
        diry = dy;
        threat = thr;
    }
};
cursor Cursor(0,0);

////////////////////////////////////////////////////////////////  Functions //////////////////////////////////////////////////////////////////////////

///=============================== fancy randomizer
int32_t getRandomNum(int32_t min, int32_t max)
{
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

///=============================== returns current player's color
int getPlayerColor(const game &gam)                     
{
    return COLOR_PAIR(gam.Players[gam.turnorder].color);
}

///=============================== field drawing accounting for spaces
void fielddisplay(game &gam, int size)                
{
    int clr;

    for (size_t j = 0; j < size; j++)              
    {
        for (size_t i = 0; i < size; i++)              
        {
            if (gam.gamefield[i][j] == _)
                clr = 1;
            else
                clr = 2;

            attron(COLOR_PAIR(clr));
            mvprintw(2*j,2*i,"%c",gam.gamefield[i][j]);
            attroff(COLOR_PAIR(clr));
        }
    }
	
}

///=============================== making a few players robots, considering total amount of players
void robotify(game &gam, int cpunumber)                     
{
    if (cpunumber > PLAYERCOUNT)
        cpunumber = PLAYERCOUNT;
    for(int i = 0; i < cpunumber; i++)
        gam.Players[i].cpucontrolled = true;

}

///=============================== constrained cursor displacement within field borders
void cursormove(int y, int x, cursor &cur)
{
    cur.x += x;
    cur.y += y;
    if (cur.x < 0)
        cur.x = 0;
    else if (cur.x > fieldsize-1)
        cur.x = fieldsize-1;
    if (cur.y < 0)
        cur.y = 0;
    else if (cur.y > fieldsize-1)
        cur.y = fieldsize-1;        
}

///=============================== checking if cell is available to move into
bool iscellfree(game &gam, int x, int y)           
{
    if (gam.gamefield[x][y] == _)
        return 1;
    else return 0;
}

///=============================== Sets a new token of current player in the cell
void makemove(game &gam, int x, int y)              
{
    gam.gamefield[x][y] = gam.Players[gam.turnorder].symbol;
}

///=============================== Turn rotation with player count in mind
void nextturn(game &gam)
{
    gam.turncount++;
    gam.turnorder += 1;
    if (gam.turnorder >= PLAYERCOUNT)
        gam.turnorder = 0;
}

void Previousturn(game &gam)
{
    gam.turncount--;
    gam.turnorder -= 1;
    if (gam.turnorder < 0)
        gam.turnorder = PLAYERCOUNT-1;
}

///=============================== Checks if 1d position is within a field
int oob(int coord)                 
{
    if ((coord < 0) || (coord > fieldsize-1))
        return 1;
    else 
        return 0;
}

///=============================== Returns length of same symbol line in certain direction, recursively
int verifycell(game &gam, int dirx, int diry, int winstreak, tictacs psymb)               
{
    
    if (oob(Cursor.x+dirx+dirx*winstreak) || oob(Cursor.y+diry+diry*winstreak))
        return winstreak;    

    if (gam.gamefield[Cursor.x+dirx+dirx*winstreak][Cursor.y+diry+diry*winstreak] == psymb)
        {
        if (winstreak+1 == WINLENGTH)
            return winstreak;
        else
            return verifycell(gam, dirx, diry, winstreak+1, psymb);
        }
    else
        return winstreak;
}

///=============================== Does verifycell in all directions from the last placed token, in hopes to find length further than one in winning conditions
void checkvictory(game &gam, tictacs psymb)                    
{
    //vertical, horizontal and 2 diag checks
    //recursive search returns winstreak in case of interruption
    // combine values of both directions + its own cell to figure out if required length is achieved
    if (((verifycell(gam,0,-1,0,psymb) + verifycell(gam,0,1,0,psymb) +1) >= WINLENGTH) ||
        ((verifycell(gam,-1,0,0,psymb) + verifycell(gam,1,0,0,psymb) +1) >= WINLENGTH) ||
        ((verifycell(gam,1,-1,0,psymb) + verifycell(gam,-1,1,0,psymb)+1) >= WINLENGTH) ||
        ((verifycell(gam,1,1,0,psymb) + verifycell(gam,-1,-1,0,psymb)+1) >= WINLENGTH))
        gam.Gamestate = victory;
}

///=============================== awfully looking method to pick a random neighbor that is viable and not occupied
cursor getfreeneighbor(const game &gam, cursor pos)        
{
    vector<cursor> candidates;
    if (pos.x+1 < fieldsize)
        if (gam.gamefield[pos.x+1][pos.y] == _)
            candidates.push_back(cursor(pos.x+1, pos.y));
    if (pos.x-1 >= 0)
        if (gam.gamefield[pos.x-1][pos.y] == _)
            candidates.push_back(cursor(pos.x-1, pos.y));

    if (pos.y+1 < fieldsize)
        if (gam.gamefield[pos.x][pos.y+1] == _)
            candidates.push_back(cursor(pos.x, pos.y+1));
    if (pos.y-1 >= 0)
        if (gam.gamefield[pos.x][pos.y-1] == _)
            candidates.push_back(cursor(pos.x, pos.y-1));

    if ((pos.y+1 < fieldsize)&&(pos.x+1 < fieldsize))
        if(gam.gamefield[pos.x+1][pos.y+1] == _)
            candidates.push_back(cursor(pos.x+1, pos.y+1));

    if ((pos.y+1 < fieldsize)&&(pos.x-1 >= 0))
        if(gam.gamefield[pos.x-1][pos.y+1] == _)
            candidates.push_back(cursor(pos.x-1, pos.y+1));

    if ((pos.y-1 >= 0)&&(pos.x + 1 < fieldsize))
        if(gam.gamefield[pos.x+1][pos.y-1] == _)
            candidates.push_back(cursor(pos.x+1, pos.y-1));
        
    if ((pos.y-1 >= 0)&&(pos.x-1 >= 0))
        if(gam.gamefield[pos.x-1][pos.y-1] == _)
            candidates.push_back(cursor(pos.x-1, pos.y-1));

    if (candidates.empty())                 // couldnt pick anything
        return cursor(-1,-1);
    else                                    // hands back one of the opportunities
    {   
        int temp = getRandomNum(0,candidates.size()-1);
        return cursor(candidates.at(temp).x,candidates.at(temp).y);
    }
}

///=============================== Collection of cpu behaviors that essentially places a cursor in viable place, to put a token properly
void cpudecision(game &gam, player cpu)                     
{
    int mood;
    int selection;
    vector<cursor> memoryset;
    vector<cpumemory> potentialrows;

    if (gam.turncount < PLAYERCOUNT)                             // random selection at first
    {
        Cursor.x = getRandomNum(0,fieldsize-1);
        Cursor.y = getRandomNum(0,fieldsize-1);
    }
    else
    {
        mood = getRandomNum(1,99)/50;
        

        switch (mood)               // computer decides to be...
        {
        case 0:                                     //...completely random
            for(int i = 0; i<fieldsize; i++)
                for(int j = 0; j<fieldsize; j++)
                    if (gam.gamefield[i][j] == _)
                        memoryset.push_back(cursor(i,j));

            selection = getRandomNum(0,memoryset.size()-1);
            Cursor.x = memoryset[selection].x;
            Cursor.y = memoryset[selection].y;
            break;

        case 1:                                      //...a blind asshole

            for(int i = 0; i<fieldsize; i++)
                for(int j = 0; j<fieldsize; j++)
                    if ((gam.gamefield[i][j] != cpu.symbol) && (gam.gamefield[i][j] != _))
                        memoryset.push_back(cursor(i,j));           //collecting every opponents' symbol

            do                                  //assuming theres space to make moves (it has to be), randomly place a symbol around opponents symbol
            {
                selection = getRandomNum(0,memoryset.size()-1);

                cursor newpick = getfreeneighbor(gam, memoryset[selection]);       //collection neighbors for one of the found opponents moves
        
                if (newpick.x == -1)
                    memoryset.erase(memoryset.begin()+selection);
                else
                {
                    Cursor.x = newpick.x;
                    Cursor.y = newpick.y;
                    memoryset.clear();
                }
            }
            while (!memoryset.empty());
            break;
        
        default:
            mvprintw(0, 2*fieldsize+3,"computer is screaming instead of making a move");
            refresh();
            napms(1000);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
///////////// ncurses routine
initscr();          
keypad(stdscr, TRUE);
start_color();
init_pair(1, COLOR_RED, COLOR_BLACK);
init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
init_pair(3, COLOR_YELLOW, COLOR_BLACK);
init_pair(5, COLOR_YELLOW, COLOR_YELLOW);

////////////////////////////////////////////////////////////////////////////// game init
int capture;                // immediate key capture
char longcap[3];            // sensible input capture

game Game;
Game.Players = new player[PLAYERCOUNT];
Game.Players[0].cpucontrolled = false;
Game.Players[0].symbol = X;
Game.Players[0].color = 2;
Game.Players[1].cpucontrolled = false;
Game.Players[1].symbol = Z;
Game.Players[1].color = 3;
Game.turnorder = getRandomNum(0,PLAYERCOUNT-1);       //player order

////////////////////////////////////////////////////////////////////////////// user settings
clear();
mvprintw(0,0,"input field size: ");
getstr(longcap);
sscanf(longcap,"%d", &fieldsize);               // reasonable field constrainments
if (fieldsize < 2) 
    fieldsize = 2;
if (fieldsize > 15)
    fieldsize = 15;
if (fieldsize < WINLENGTH)                      // correcting victory conditions if you for some reason wanted to play 2x2
    WINLENGTH = fieldsize;

int cpunumber;                                          // setting up cpu amount
mvprintw(0,0, "how man AI players? ");
getstr(longcap);
sscanf(longcap, "%d", &cpunumber);
robotify(Game, cpunumber);

noecho();
nodelay(stdscr, TRUE);                                  //shutting down input demanding RETURN key
refresh();

Game.gamefield = new tictacs* [fieldsize];               //initializing the field
for (size_t i = 0; i < fieldsize; i++)              
    Game.gamefield[i] = new tictacs[fieldsize];
for (size_t i = 0; i < fieldsize; i++)                  
    for (size_t j = 0; j < fieldsize; j++)
        Game.gamefield[i][j] = _;


////////////////////////////////////////////////////////////////////////////////// game loop
do
{
    clear();

/// TURN DECISION    
    if (Game.Players[Game.turnorder].cpucontrolled)
    {
        mvprintw(2*fieldsize+4,0,"computer is thinking...");
        cpudecision(Game, Game.Players[Game.turnorder]);
        makemove(Game, Cursor.x, Cursor.y);
        checkvictory(Game, Game.Players[Game.turnorder].symbol);
        nextturn(Game);
    }
    else
        switch(capture)
        {
            case KEY_LEFT:
                cursormove(0,-1, Cursor);
                break;
            case KEY_RIGHT:
                cursormove(0,1, Cursor);
                break;
            case KEY_UP:
                cursormove(-1,0, Cursor);
                break;
            case KEY_DOWN:
                cursormove(1,0, Cursor);
                break;
            case 100:
                if (iscellfree(Game, Cursor.x, Cursor.y))
                {
                    mvprintw(2*fieldsize+4,0,"new symbol placed");
                    makemove(Game, Cursor.x, Cursor.y);
                    checkvictory(Game, Game.Players[Game.turnorder].symbol);
                    nextturn(Game);
                }
                else
                    mvprintw(2*fieldsize+4,0,"this cell is taken");
                napms(100);
                break;
            case 113:
                Game.Gamestate = abandoned;
                break;
            default:
                mvaddch(2*fieldsize+5, 0, -1);
                refresh();
                break;
        }

    if (Game.turncount >= (fieldsize*fieldsize)&&(Game.Gamestate != victory))                    // useless to continue if theres no space to move into
        Game.Gamestate = draw;

/// DRAWING PHASE
    fielddisplay(Game, fieldsize);
    attron(getPlayerColor(Game));
    mvprintw(2*fieldsize+2, 0, "player %c move", Game.Players[Game.turnorder].symbol);     //player colored UI
    attroff(getPlayerColor(Game));
    mvprintw(2*fieldsize+2, 20, "| Turn: %d", Game.turncount);
    
    attron(COLOR_PAIR(5));
    mvaddch(2*Cursor.y, 2*Cursor.x, 88);    //cursor
    attroff(COLOR_PAIR(5));

    mvaddch(2*fieldsize+7,0,-1);        // cursor reset
    refresh();
    napms(150);

    capture = getch();
    // //if x.y turns and still not victory, draw
} while (Game.Gamestate == inprogress);

////////////// GAME WAS OVER, CHECKING NEW GAMESTATE

switch (Game.Gamestate)         // case for game outcomes
{
case 1:
    Previousturn(Game);
    mvprintw(2*fieldsize+5, 0, "this is a victory");
    mvprintw(2*fieldsize+6, 0, "player %c won", Game.Players[Game.turnorder].symbol);
    break;
case 2:
    mvprintw(2*fieldsize+5, 0, "this is a draw");
    break;
case 3:
    mvprintw(2*fieldsize+5, 0, "game was abandoned");
    break;

default:
    break;
}
mvprintw(2*Cursor.y, 2*Cursor.x, "%c", Game.gamefield[Cursor.x][Cursor.y]);  //cursor overdraw, to see the last token placed
mvprintw(2*fieldsize+7,0,"");

refresh();
nodelay(stdscr, FALSE);                                  //shutting down ncurses key listening gimmick to hang up the screen until user input
getch();

for (int i = 0; i < fieldsize; i++)                     // freeing whatever dynamically created entities
{
    delete[] Game.gamefield[i];
}
delete[] Game.gamefield;
Game.gamefield = nullptr;                               
delete[] Game.Players;
Game.Players = nullptr;

    endwin();                                           // closing ncurses
    return 0;
}