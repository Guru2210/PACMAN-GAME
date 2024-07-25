// PACMAN GAME  
// GROUP 30
// 19/ENG/028
// 19/ENG/037
// 19/ENG/083
// 19/ENG/102

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>


using namespace std;

const int MAXROWS = 18;
const int MAXCOLUMNS = 32;

//Start position of pacman [10][1]
int PacmanI = 10, PacmanJ = 1;
//Start postion of Enemy [14][14]
int EnemyI = 14, EnemyJ = 14;
int i = 0, j = 0;
char key = 127;

char Map[MAXROWS][MAXCOLUMNS] =
{
"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
"O              P              O",
"O       oooooooooooooooooo    O",
"O   OOOOOOOOO   OOO    OOOOOOOO",
"O   O  ooooooooooooooooO   oo O",
"O   OOOO O  O oooooooooO    o O",
"O   O   PO  O OOOO  O  O    o O",
"O   OOOOOO  OOOP    OOOO    o O",
"O            OOOO  O        o O",
"OOOOOOO   OO  oooo  OOO ooooo O",
"OX        OOOOOO  OOOOO   OOOOO",
"O ooooooooOooooooooooooooooo  O",
"OOOO   OOOOOO   OOOO    OOOOOOO",
"O ooooooooo OooooooOoooooo    O",
"O           O      O         PO",
"O  OOOOOOOOOOOOOOOOOOOOoooooo O",
"O                             O",
"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
};



void Moving_Pacman();
void Setting_Enemy();
void GotoXY(int column, int line);
bool Enemymoveup();
bool Enemymovedown();
bool Enemymoveleft();
bool Enemymoveright();

int lives = 3;
clock_t startTime = 0, endTime = 0;
bool SuperPellet = false;
bool Pellet = false; int Points = 0;



int main()
{
	{
	HANDLE  hConsole;
	int k = 5;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);

	cout << "              ###" << endl;
	cout << "          ##########" << endl;
	cout << "       ####### _########" << endl;
	cout << "    ##########|_|#########" << endl;
	cout << "  ####################         #######     #          ####    ##     ##        #       ##      #" << endl;
	cout << " #################             #      #   # #       #      #  # #   # #       # #      # #     #" << endl;
	cout << "###############                #      #  #   #     #          #  # #  #      #   #     #  #    #" << endl;
	cout << "#############                  #######  #######    #          #   #   #     #######    #   #   #" << endl;
	cout << "###############                #       #       #   #          #       #    #       #   #    #  #" << endl;
	cout << " #################             #      #         #   #      #  #       #   #         #  #     # #" << endl;
	cout << "  ####################         #     #           #    ####    #       #  #           # #      ##" << endl;
	cout << "    #######################" << endl;
	cout << "       #################" << endl;
	cout << "          ###########" << endl;
	cout << "              ###" << endl;

	cout << endl;
	cout<<"\t\t\tINSTRUCTIONS"<<endl;
	cout<<"-> Pacman is X"<<endl;
	cout<<"-> Enemy is W"<<endl;
	cout<<"-> o is pellet and P is Power pellet "<<endl;
	cout<<"-> Your score will increase by 1 point,If you eat one pellet"<<endl;
	cout<<"-> Your Score will icrease by 10 points, If you eat one Power pellet"<<endl;
	cout<<"-> Your enemy will move in opposite direction, If you eat a power pellet "<<endl;
	cout<<"-> The game is over when you touch Enemy"<< endl;
	system("pause");
	char key = 0;
	system("mode 120, 30");
	int pills = 30;
	bool stopCounting = false;


	while(true)
	{
		//for setting the Start position
		GotoXY(0, 0);
		Setting_Enemy();
		//start column
		for (i = 0; i < 18; i++)
		{
			//start row
			for (j = 0; j < 32; j++)
			{
				//coloring walls
				if (Map[i][j] == 'O')
				{
					k = 1;
					SetConsoleTextAttribute(hConsole, k);
				}
				//coloring pacman
				else if (Map[i][j] == 'X' )
				{
					k = 14;
					SetConsoleTextAttribute(hConsole, k);
				}
				//colouring blank
				else if (Map[i][j] == ' ')
				{
					k = 0;
					SetConsoleTextAttribute(hConsole, k);
				}
				//coloing ghost
				else if (Map[i][j] == 'W')
				{
					if (SuperPellet)
					{
						k = 7;
						SetConsoleTextAttribute(hConsole, k);
					}
					else
					{
						k = 4;
						SetConsoleTextAttribute(hConsole, k);
					}
				}
				//coloring pill
				else if (Map[i][j] == 'o')
				{
					k = 15;
					SetConsoleTextAttribute(hConsole, k);
				}
				//coloring power pill
				else if (Map[i][j] == 'P')
				{
					k = 14;
					SetConsoleTextAttribute(hConsole, k);
				}

				cout << Map[i][j];
				if (j == 31)
					cout << endl;

				if (j == 31 && i == 17)
					stopCounting = true;
			}
		}
		Moving_Pacman();
		//Color
		k = 15;
		SetConsoleTextAttribute(hConsole, k);

		cout << "lives remaining " << lives << endl;
		endTime = clock();
		int elapsed = int((endTime - startTime) / CLOCKS_PER_SEC);
		//getting elapsed time

		if (elapsed > 10)
		{
			SuperPellet = false;
			elapsed = 0;
		}
		if (lives == 0)
		{
			system("cls");
			SetConsoleTextAttribute(hConsole, 5);
			cout << "\n\n\n\n";
			cout << "    ######             #        ##           ##  #########            #####      #           #  #########  #######" << endl;
			cout << " #          #         # #       # #         # #  #                 #         #    #         #   #          #       #" << endl;
			cout << "#                    #   #      #  #       #  #  #                #           #    #       #    #          #       #" << endl;
			cout << "#        ######     #######     #   #     #   #  #########        #           #     #     #     #########  #######" << endl;
			cout << "#           # #    #       #    #    #   #    #  #                #           #      #   #      #          #  #" << endl;
			cout << " #         #  #   #         #   #     # #     #  #                 #         #        # #       #          #    #" << endl;
			cout << "    ######    #  #           #  #      #      #  #########            #####            #        #########  #      #" << endl << endl << endl;
			cout << "Your Score = " << Points << endl;
			system("pause");
			return 0;
		}
	} 
	}
	return 0;
};

bool Enemymoveup()
{
	char Enemynextup = Map[EnemyI - 1][EnemyJ];
	//Checking for wall
	if (Enemynextup != 'O')
	{
		//Checking for pills
		if (Enemynextup == 'o')
		{
			//Putting the pill back
			Map[EnemyI - 1][EnemyJ] = 'W';

			Map[EnemyI][EnemyJ] = Enemynextup;
			EnemyI--;
		}
		else
		{
			Pellet = false;
			Map[EnemyI][EnemyJ] = 'o';
			Map[EnemyI - 1][EnemyJ] = 'W';
			EnemyI--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemymovedown()
{

	char Enemynextdown = Map[EnemyI + 1][EnemyJ];
	if (Enemynextdown != 'O')
	{
		if (Enemynextdown == 'o')
		{
			Map[EnemyI + 1][EnemyJ] = 'W';
			Map[EnemyI][EnemyJ] = Enemynextdown;
			EnemyI++;
		}
		else
		{
			Map[EnemyI][EnemyJ] = 'o';
			Map[EnemyI + 1][EnemyJ] = 'W';
			EnemyI++;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemymoveleft()
{
	char Enemynextleft = Map[EnemyI][EnemyJ - 1];
	if (Enemynextleft != 'O')
	{
		if (Enemynextleft == 'o')
		{
			Map[EnemyI][EnemyJ - 1] = 'W';
			Map[EnemyI][EnemyJ] = Enemynextleft;
			EnemyJ--;
		}
		else
		{
			Map[EnemyI][EnemyJ] = 'o';
			Map[EnemyI][EnemyJ - 1] = 'W';
			EnemyJ--;
		}
		return true;
	}
	else
	{
		return false;
	}

}

bool Enemymoveright()
{
	char Enemynextright = Map[EnemyI][EnemyJ + 1];
	if (Enemynextright != 'O')
	{

		if (Enemynextright == 'o')
		{
			Map[EnemyI][EnemyJ + 1] = 'W';
			Map[EnemyI][EnemyJ] = Enemynextright;

			EnemyJ++;
		}
		else
		{
			Map[EnemyI][EnemyJ] = 'o';
			Map[EnemyI][EnemyJ + 1] = 'W';
			EnemyJ++;
		}
		return true;
	}
	else
	{
		return false;
	}

}

void Setting_Enemy()
{
	if (SuperPellet)
	{
		//Moving enemy up
		if (PacmanI > EnemyI)
		{
			//if wall found
			if (!Enemymoveup())
			{
				//find node path 
			}
		}

		//Moving enemy down
		else if (PacmanI < EnemyI)
		{
			if (!Enemymovedown())
			{

			}
		}

		//Moving enemy left
		if (PacmanJ > EnemyJ)
		{
			if (!Enemymoveleft())
			{

			}
		}

		//Moving enemy right
		else if (PacmanJ < EnemyJ)
		{
			if (!Enemymoveright())
			{

			}
		}
	}
	else
	{


		//Moving enemy up 
		if (PacmanI < EnemyI)
		{

			//if wall found
			if (!Enemymoveup())
			{

			}
		}

		//Moving enemy down
		else if (PacmanI > EnemyI)
		{
			if (!Enemymovedown())
			{

			}
		}

		//Moving enemy left
		if (PacmanJ < EnemyJ)
		{
			if (!Enemymoveleft())
			{

			}
		}

		//Ghost is moving right
		else if (PacmanJ > EnemyJ)
		{
			if (!Enemymoveright())
			{

			}
		}
	}

	//If enemy caught the pacman 
	if (PacmanJ == EnemyJ && PacmanI == EnemyI && SuperPellet)
	{
		Map[EnemyI][EnemyJ] = 'X';
		EnemyI = 14;
		EnemyJ = 14;
		Map[14][14] = 'W';
	}
	//Resetting the postion of pacman and Enemy
	else if (PacmanJ == EnemyJ && PacmanI == EnemyI)
	{
		lives--;
		Map[PacmanI][PacmanJ] = ' ';
		Map[EnemyI][EnemyJ] = ' ';
		PacmanI = 10;
		PacmanJ = 1;
		EnemyI = 14;
		EnemyJ = 14;
		Map[10][1] = 'X';
		Map[14][14] = 'W';
	}
}

void Moving_Pacman()
{
	key = _getch();

	if (key == 72) //Moving the pacman up
	{
		if (Map[PacmanI - 1][PacmanJ] != 'O')
		{
			if (Map[PacmanI - 1][PacmanJ] == 'o')
			{
				Points++;
			}
			if (Map[PacmanI - 1][PacmanJ] == 'P')
			{
				startTime = clock();
				SuperPellet = true;
				Points = Points + 10;

			}
			Map[PacmanI][PacmanJ] = ' ';
			Map[PacmanI - 1][PacmanJ] = 'X';
			PacmanI--;
		}
	}
	else if (key == 75) //Moving the pacman left
	{
		if (Map[PacmanI][PacmanJ - 1] != 'O')
		{
			if (Map[PacmanI][PacmanJ - 1] == 'o')
			{
				Points++;
			}
			if (Map[PacmanI][PacmanJ - 1] == 'P')
			{
				startTime = clock();
				SuperPellet = true;
				Points = Points + 10;

			}
			Map[PacmanI][PacmanJ] = ' ';
			Map[PacmanI][PacmanJ - 1] = 'X';
			PacmanJ--;
		}
	}
	else if (key == 77) //Moving the pacman right
	{
		if (Map[PacmanI][PacmanJ + 1] != 'O')
		{
			if (Map[PacmanI][PacmanJ + 1] == 'o')
			{
				Points++;
			}
			if (Map[PacmanI][PacmanJ + 1] == 'P')
			{
				startTime = clock();
				SuperPellet = true;
				Points = Points + 10;

			}
			Map[PacmanI][PacmanJ] = ' ';
			Map[PacmanI][PacmanJ + 1] = 'X';
			PacmanJ++;
		}
	}
	else if (key == 80) //moving the pacman down
	{
		if (Map[PacmanI + 1][PacmanJ] != 'O')
		{
			if (Map[PacmanI + 1][PacmanJ] == 'o')
			{
				Points++;
			}
			if (Map[PacmanI + 1][PacmanJ] == 'P')
			{
				startTime = clock();
				SuperPellet = true;
				Points = Points + 10;

			}
			Map[PacmanI][PacmanJ] = ' ';
			Map[PacmanI + 1][PacmanJ] = 'X';
			PacmanI++;
		}
	}
}

void GotoXY(int column, int line)
{
	// creating a coodinate structure
	COORD coord;
	coord.X = column;
	coord.Y = line;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!SetConsoleCursorPosition(hConsole, coord))
	{
		
	}
}

