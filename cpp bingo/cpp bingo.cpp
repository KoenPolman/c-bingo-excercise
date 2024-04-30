#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <random>
int GenerateRandomNumber1tm99()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 99);
	return dis(gen);
}

int CollectUserInput()
{
	std::string userInput;
	std::cin >> userInput;
	int userInputInt = std::stoi(userInput);
	return userInputInt;
}

class Cell {
public:
	int value;
	bool coloured = false;
	bool rolled = false;
};

class Table {
public:
	int size = 5;
	Cell cell[5][5];
	bool numbersOnTable[100];

	void GenerateNewGrid()
	{
		for (int z = 0; z < 100; z++)
		{
			numbersOnTable[z] = false;
		}
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				int randomInt = 100;
				//this do-while loop should enshure: no double numbers in the grid, yet it does not
				do
				{
					randomInt = GenerateRandomNumber1tm99();
					if (!numbersOnTable[randomInt])
					{
						numbersOnTable[randomInt] = true;
					}
				} while (!numbersOnTable[randomInt]);
				cell[x][y].value = randomInt;
				cell[x][y].coloured = false;
				cell[x][y].rolled = false;
			}
		}
	}
	void DrawGrid(int lastRolledNum)
	{
		std::cout << "\n\t(1)\t(2)\t(3)\t(4)\t(5)\n\n";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int x = 0; x < size; x++)
		{
			std::cout << "(" << x + 1 << ")";
			for (int y = 0; y < size; y++)
			{
				if (cell[x][y].value == lastRolledNum)
				{
					cell[x][y].rolled = true;
				}
				if (cell[x][y].coloured)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				}
				if (cell[x][y].rolled && !cell[x][y].coloured)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				}
				std::cout << "\t" << cell[x][y].value;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			std::cout << "\n\n";
		}
		std::cout << "\t----------------------------------\n\t0: quit\n\t1: roll again\n\t2: select\n\t3: start over\n\t----------------------------------\n\n";
	}
	bool HorizontalCheck()
	{
		int winCount = 0;
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				if (cell[x][y].coloured && cell[x][y].rolled)
				{
					winCount++;
				}
			}
			if (winCount == size)
			{
				return true;
			}
			winCount = 0;
		}
		return false;
	}
	bool VerticalCheck()
	{
		int winCount = 0;
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				if (cell[y][x].coloured && cell[y][x].rolled)
				{
					winCount++;
				}
			}
			if (winCount == size)
			{
				return true;
			}
			winCount = 0;
		}
		return false;
	}
	bool PositiveDiagonalCheck()
	{
		if (cell[0][4].rolled && cell[1][3].rolled && cell[2][2].rolled && cell[3][1].rolled && cell[4][0].rolled)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool NegativeDiagonalCheck()
	{
		if (cell[0][0].rolled && cell[1][1].rolled && cell[2][2].rolled && cell[3][3].rolled && cell[4][4].rolled)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool WinChecker()
	{
		if (HorizontalCheck() || VerticalCheck() || PositiveDiagonalCheck() || NegativeDiagonalCheck())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void StampNumberOff()
	{
		int x = 0;
		bool validInputEnterd;
		std::cout << "you are now selecting the horizontal index of the square to stamp off (not 0-indexed)\n";
		do
		{
			validInputEnterd = true;
			switch (CollectUserInput())
			{ //i know this is a bad way of doing this
			case 1:
				x = 0;
				break;

			case 2:
				x = 1;
				break;

			case 3:
				x = 2;
				break;

			case 4:
				x = 3;
				break;

			case 5:
				x = 4;
				break;

			default:
				std::cout << "please enter a valid command";
				validInputEnterd = false;
				break;
			}
		} while (!validInputEnterd);

		std::cout << "you ar now selecting the vertical index of the square to stamp off (not 0-indexed)\n";
		int y = 0;
		do
		{
			validInputEnterd = true;
			switch (CollectUserInput())
			{ //read comment at line 191
			case 1:
				y = 0;
				break;

			case 2:
				y = 1;
				break;

			case 3:
				y = 2;
				break;

			case 4:
				y = 3;
				break;

			case 5:
				y = 4;
				break;

			default:
				std::cout << "please enter a valid command";
				validInputEnterd = false;
				break;
			}
		} while (!validInputEnterd);

		cell[y][x].coloured = true;
	}
};

Table table;

void Play()
{
	if (table.WinChecker())
	{
		std::cout << "\n\tYOU WON (epic)\n";
	}
	table.GenerateNewGrid();
	bool quit = false;
	int rolledNum = 0;
	while (!quit)
	{
		if (!rolledNum == 0)
		{
			std::cout << "\n\t" << rolledNum << " was just rolled\n";
		}
		table.DrawGrid(rolledNum);
		switch (CollectUserInput())
		{
		case 0:
			quit = true;
			break;

		case 1:
			rolledNum = GenerateRandomNumber1tm99();
			break;

		case 2:
			table.StampNumberOff();
			break;

		case 3:
			table.GenerateNewGrid();
			rolledNum = 0;
			break;

		default:
			std::cout << "please enter a valid command";
			break;
		}
		system("cls");
	}
}
int main()
{
	Play();
	return 0;
}