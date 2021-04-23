#include <iostream>
#include <conio.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Point
{
	bool gameover;
	int width;
	int height;
	int x, y, fruit_X, fruit_Y, score;
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir = STOP;
	int tail_X[100], tail_Y[100];
	int nTail;
public:
	bool get_gameover()
	{
		return gameover;
	}

	const eDirection get_dir()const
	{
		return dir;
	}
	eDirection get_dir()
	{
		return dir;
	}

	Point(bool gameover = 0, int width = 20, int height = 20, eDirection dir = STOP, int score = 0)//Setup
	{
		x = width / 2 - 2;
		y = height / 2 - 2;
		fruit_X = rand() % width;
		fruit_Y = rand() % width;

		this->score = score;
		this->gameover = gameover;
		this->width = width;
		this->height = height;
		this->dir = dir;
		cout << "Constructor" << endl;
	}
	~Point()
	{
		cout << "Destructor" << endl;
	}

	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
		{
			cout << "#";
		}
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j == 0)
				{
					cout << "#";
				}
				if (i == y && j == x)
				{
					cout << "0";
				}
				else if (i == fruit_Y && j == fruit_X)
				{
					cout << "F";
				}
				else
				{
					for (int k = 0; k < nTail; k++)
					{
						if (tail_X[k] == j && tail_Y[k] == i)
						{
							cout << "o";
						}
					}
					cout << " ";
				}
			}
			cout << "#" << endl;
		}

		for (int i = 0; i < width + 2; i++)
		{
			cout << "#";
		}
		cout << endl;
		cout << "Score : " << score << endl;
	}
	void Input()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case'a':
				dir = LEFT;
				break;
			case'd':
				dir = RIGHT;
				break;

			case'w':
				dir = UP;
				break;

			case's':
				dir = DOWN;
				break;
			case' ':
				dir = STOP;
				break;
			case'x':
				gameover = true;
				break;
			}
		}	
	}

	void Logic()
	{
		int prev_X = tail_X[0];
		int prev_Y = tail_Y[0];
		int prev2X, prev2Y;
		for (int i = 0; i < nTail; i++)
		{
			prev2X = tail_X[i];
			prev2Y = tail_Y[i];
			tail_X[i] = prev_X;
			tail_Y[i] = prev_Y;
			prev_X = prev2X;
			prev_Y = prev2Y;
		}
		switch (dir)
		{
		case STOP:
			;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		}
		if (x > width || y > height || x < 0 || y < 0)
		{
			gameover = true;
		}
		if (x == fruit_X && y == fruit_Y)
		{
			score += 10;
			fruit_X = rand() % width;
			fruit_Y = rand() % width;
			nTail++;
		}
	}
};

int main()
{
	Point A;
	cout << A.get_dir() << endl;
	while (!A.get_gameover())
	{
		A.Draw();
		A.Input();
		A.Logic();
	}

	return 0;
}