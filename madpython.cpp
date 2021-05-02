/*
*  python game, for implementation with linux libraries (ncurses)
*
*/

#include <cstdlib>
#include <ctime>
#include <vector>
#include <ncurses.h>

const int WIDTH = 20;
const int HEIGHT = 50;

const int IMGPYTHON = 64; 	//symbol representations for actors
const int IMGFRUIT = 42;
const int IMGSQUIRREL = 97;
const int IMGWALL = 88;
const int IMGSPACE = 46;

const int FRUITCOUNT = 8;    // max possible amount of fruits on the screen
const int SQUIRRELCOUNT = 0;
const int STARTINGPYTHON = 5;	// starting length of the python
const float STARTINGSPEED = 1;

using namespace std;

// python tail elements
class Pythbit
{
	public: 
		float positionx;
		float positiony;
		int CheckCollision(float actorx, float actory);
		Pythbit(float x, float y)
		{
			positionx = x;
			positiony = y;
		}
};

// edible objects
class Fruit
{
	public:
		float positionx;
		float positiony;
		int pointvalue = 5;
		int CheckCollision(float actorx, float actory);
		Fruit(float x, float y)
		{
			positionx = x;
			positiony = y;
		}
};
int Fruit::CheckCollision(float actorx, float actory)
{
	if ((abs(actorx - positionx) < 1) && (abs(actory - positiony) < 1))
		return 1;
	else
		return 0;
}

// moving snake head object
class Snake
{
	public:
		float positionx;
		float positiony;
		float velocity;
		float fullness = STARTINGPYTHON;		// spent to grow the tail
		float odometer = 0.0;						//remembering the distance covered
		int direction[2] = {0,1};
		vector<Pythbit> tail;
		void Move();
		void Eat(int amount);
		
		Snake(float px, float py, float vel)
		{
			positionx = px;
			positiony = py;
			velocity = vel;
		}
};
void Snake::Move()		
{
	positionx = positionx + direction[0] * velocity;
	positiony = positiony + direction[1] * velocity;

	//tail growth and displacement
	odometer += velocity;
	if (odometer >=1)
	{
		odometer--;
		if (fullness > 0.0)
		{
			fullness--;
			tail.insert(tail.begin(), Pythbit(positionx, positiony));
			
		}
		else   //in case of hunger, reusing last element as the snake moves
		{
			(tail.end()-1)->positionx = positionx;
			(tail.end()-1)->positiony = positiony;
			Pythbit tempbit = *(tail.end()-1);
			tail.pop_back();
			tail.emplace(tail.begin(), tempbit);
		}
	}
}
void Snake::Eat(int amount)
{
	fullness += amount;
}

// Interactable object of varying sizes
class Prop
{
	public:
		float positionx;
		float positiony;
		float width;
		float height;
		int fatal = 1;
		int CheckCollision(float actorx, float actory);
		Prop(float posx, float posy, float w, float h)
		{
			positionx = posx;
			positiony = posy;
			width = w;
			height = h;
		}
};
int Prop::CheckCollision(float actorx, float actory)
{
	if ((abs(actorx - positionx)< width/2) && (abs(actory - positiony) < height/2))
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////

int main(int argc, char ** argv)
{
//ncurses settings
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);  //getch won't hold the algorythm hostage
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

	srand(static_cast<unsigned int>(time(0)));  //randomization seed


//field setup
	char Level[WIDTH][HEIGHT];
	for (int i = 0; i<WIDTH; i++)
		for (int j = 0; j<HEIGHT; j++)
			Level[i][j] = IMGSPACE;

//game parameters, populating object lists
	Snake Player(10.0, 10.0, STARTINGSPEED);
	float worldx = WIDTH;
	float worldy = HEIGHT;

	vector<Prop> propset;
	propset.push_back(Prop (0.0, worldy/2, 1.0,  worldy));
	propset.push_back(Prop (worldx-1, worldy/2, 1.0,  worldy));
	propset.push_back(Prop (worldx/2, 0.0, worldx,  1.0));
	propset.push_back(Prop (worldx/2, worldy-1, worldx,  1.0));
	//propset.push_back(Prop (5.0,15.0,3.0,4.0));

	vector<Fruit> fruits;
	for(int i=0; i<FRUITCOUNT; i++)
	{
		fruits.push_back(Fruit(1+rand()%(WIDTH-2), 1+rand()%(HEIGHT-2)));
	}
	
	int score = 0;
	int gamestate = 1; 
	int newchar = 0;  //player input stored here
	
	float oldtime = 0;

	enum difficulty {EASY, NORMAL, HARD, MAD}; //not used atm
	difficulty thisdifficulty = NORMAL;

// main game loop
	 do
	 {
		// float deltatime = clock() - oldtime;
		// double fps = (1.0/deltatime) * 1000;
		// oldtime = clock();

		clear();

		//field render
		attron(COLOR_PAIR(2));
		for (int i = 0; i<WIDTH; i++)
			for (int j = 0; j<HEIGHT; j++)
			{
				mvaddch(i,j, Level[i][j]);
			}

	//if alive...
		if (gamestate == 1)  
		{
			switch(newchar) // python changing directions depending on key input
			{
				case 119:
					Player.direction[0] = -1;	
					Player.direction[1] = 0;	
					break;
				case 115:
					Player.direction[0] = 1;	
					Player.direction[1] = 0;	
					break;
				case 97:
					Player.direction[0] = 0;	
					Player.direction[1] = -1;	
					break;
				case 100:
					Player.direction[0] = 0;	
					Player.direction[1] = 1;	
					break;
			}

			Player.Move();  

			attron(COLOR_PAIR(3));
			for (int i = 0; i<propset.size(); i++)
			{
				//wall render
				for (int j = -propset[i].width/2; j < propset[i].width/2; j++)
					for (int k = -propset[i].height/2; k < propset[i].height/2; k++)
						mvaddch(propset[i].positionx + j, propset[i].positiony + k, IMGWALL);

				//collision check
				if (propset[i].CheckCollision(Player.positionx, Player.positiony) == 1)
					gamestate = 0;
			}

			attron(COLOR_PAIR(4));
			for (int i =0; i<fruits.size(); i++)
			{
				//fruit render
				mvaddch(fruits[i].positionx, fruits[i].positiony, IMGFRUIT);	

				//fruit collision check
				if(fruits[i].CheckCollision(Player.positionx, Player.positiony) == 1)
				{
					Player.Eat(2);
					fruits.erase(fruits.begin()+i);
				}
			}
			attroff(COLOR_PAIR(4));			

			//player display
			attron(COLOR_PAIR(1));
			for (int i=0; i<Player.tail.size(); i++)
			{
				mvaddch(Player.tail[i].positionx, Player.tail[i].positiony, IMGFRUIT);
			}
			mvaddch(Player.positionx, Player.positiony, IMGPYTHON);
			attroff(COLOR_PAIR(1));
		}
	//...otherwise dead
		else
		{
			attron(COLOR_PAIR(1));
			mvprintw(WIDTH/2, 11, "G A M E  O V E R");
			mvprintw(WIDTH/2+1, 10, "press r to restart");
			attroff(COLOR_PAIR(1));

			// game reset
			if (newchar == 114) 
			{
				gamestate = 1;
				Player.positionx = 10.0;
				Player.positiony = 10.0;
				Player.fullness = STARTINGPYTHON;
				Player.odometer = 0.0;
				while (Player.tail.size()>0)
					Player.tail.clear();
					
				fruits.clear();
				for(int i=0; i<FRUITCOUNT; i++)
				{
					fruits.push_back(Fruit(1+rand()%(WIDTH-2), 1+rand()%(HEIGHT-2)));
				}
			}
		}

		mvaddch(WIDTH+2,0, 32); //resetting printing head below the game screen
		newchar = getch();

		//some arbitrary UI for now	
		printw("tails to grow: %f   fruits left: %i", Player.fullness, fruits.size());
		refresh();

		napms(150);  //crude deltatime substitute
		} while (newchar != 27);  
	
	refresh();
	endwin();	//releasing memory from ncurses 
	return 0;
}