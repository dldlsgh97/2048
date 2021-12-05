#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int nSpaces(int n) //숫자 자리수를 제외한 나머지 빈칸 개수
{
	if (n < 10)
		return 7;
	if (n < 100)
		return 6;
	if (n < 1000)
		return 5;
	if (n < 10000)
		return 4;
	return 0;
}

void printSpaces(int n) //빈칸 출력
{
	printf("%*c", n, ' ');
}

void pickColor(int n) //숫자별 색상
{
	if (n == -1)
		printf("\033[39;49m");//standard
	if (n == 0)
		printf("\033[100m"); //gray
	if (n == 2)
		printf("\033[97;41m"); //red
	if (n == 4)
		printf("\033[97;42m");//green
	if (n == 8)
		printf("\033[97;43m");//orange
	if (n == 16)
		printf("\033[97;44m");//blue
	if (n == 32)
		printf("\033[97;45m");//purple
	if (n == 64)
		printf("\033[97;46m");//light blue
	if (n == 128)
		printf("\033[30;101m");//stroin red
	if (n == 256)
		printf("\033[30;102m");//light green
	if (n == 512)
		printf("\033[30;103m");//yellow
	if (n == 1024)
		printf("\033[30;104m");//sky blue
	if (n == 2048)
		printf("\033[30;105m");//light purple
}

void print(int grid[][4]) //행렬내의 숫자와 빈칸 출력
{
	printf("\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf(" ");
			pickColor(grid[i][j]);
			if (grid[i][j] != 0)
			{
				printf("%i", grid[i][j]);
				printSpaces(nSpaces(grid[i][j]));
			}
			else
				printSpaces(8);
			pickColor(-1);
		}
		printf("\n");
	}
}

int countEmpty(int grid[][4]) //비어있는 행렬의 개수
{
	int c = 0;
	for (int i = -1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j] == 0)
				c++;
		}
	}
	return c;
}

void add(int grid[][4], int value) //랜덤한 위치에 2출력
{
	time_t ti;
	srand((unsigned)time(&ti));
	int pos  = rand() % countEmpty(grid);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j] == 0)
			{
				if (count++ == pos)
				{
					grid[i][j] = value;
					return;
				}
			}
		}
	}
}

int move(int grid[][4]) //블록 이동
{
	int score = 0;
	int moved = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = j + 1; k < 4; k++)
			{
				if (grid[i][j] != 0 && grid[i][k] != 0 && grid[i][j] != grid[i][k])
				{
					break;
				}
				if (grid[i][j] != 0 && grid[i][k] != 0 && grid[i][j] == grid[i][k])
				{
					grid[i][j] *= 2;
					grid[i][k] = 0;
					score += grid[i][j];
					moved = 1;
					break;
				}
				else if (grid[i][j] == 0 && grid[i][k] != 0)
				{
					grid[i][j] = grid[i][k];
					grid[i][k] = 0;
					moved = 1;
				}
				else if (grid[i][j] != 0 && grid[i][k] == 0 && j == 0)
				{
					if (grid[i][j + 2] != grid[i][j + 3] && grid[i][j] == grid[i][j + 2])
					{
						grid[i][j] *= 2;
						grid[i][j + 2] = 0;
						score += grid[i][j];
					}
					else if (grid[i][j + 2] == grid[i][j + 3])
					{
						grid[i][j + 2] *= 2;
						grid[i][j + 3] = 0;
						score += grid[i][j + 2];
					}
					else if (grid[i][j + 2] == 0 && grid[i][j] == grid[i][j + 3])
					{
						grid[i][j] *= 2;
						grid[i][j + 3] = 0;
						score += grid[i][j];
					}
					moved = 1;
					break;
				}
			}
		}
	}
	if (moved == 1)
		add(grid, 2);
	return score;
}

void rotate(int rotations, int grid[][4]) //행렬 회전
{
	for (int r = 0; r < rotations; r++)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = i; j < 4 - i - 1; j++)
			{
				int tmp = grid[i][j];
				grid[i][j] = grid[j][4 - i - 1];
				grid[j][4 - i - 1] = grid[4 - i - 1][4 - j - 1];
				grid[4 - i - 1][4 - j - 1] = grid[4 - j - 1][i];
				grid[4 - j - 1][i] = tmp;
			}
		}
	}
}

int Move (char c, int grid[][4], int *score) // 방향키
{
	int t = 0;
	if ( c == 'a' || c == 'A')
	{
		*score += move(grid);
	}
	else if (c == 's' || c == 'S')
	{
		rotate(3, grid);
		*score += move(grid);
		rotate(1, grid);
	}
	else if (c == 'w' || c == 'W')
	{
		rotate(1, grid);
		score += move(grid);
		rotate(3, grid);
	}
	else if (c == 'd' || c == 'D')
	{
		rotate(2, grid);
		*score += move(grid);
		rotate(2, grid);
	}
	return 0;
}

int check(int grid[][4]) //블록움직임 가능 여부 체크
{
	int moveAvailable = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j] == 2048)
				return -1;
			if (moveAvailable == 0)
			{
				if (grid[i][j] == 0)
					moveAvailable++;
				else if (i < 3 && grid[i + 1][j] == grid[i][j])
					moveAvailable++;
				else if (j < 3 && grid[i][j + 1] == grid[i][j])
					moveAvailable++;
				else if (i > 0 && grid[i - 1][j] == grid[i][j])
					moveAvailable++;
				else if (j > 0 && grid[i][j - 1] == grid[i][j])
					moveAvailable++;
			}
		}
	}
	return moveAvailable;
}

void initialize(int grid[][4]) //초기화면 출력
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			grid[i][j] = 0;
	add(grid, 2);
	add(grid, 2);
}

void menu() //메뉴 출력
{
	system("clear");
	printf(" 2048 - Game\n * Use w-a-s-d keys to move the tiles.\n * When two tiles with the same number touch, they merge into one.\n\n\t      ^\n\t      w\n\t< a       d >\n\t      s\n\t      v\n\n *Press 'Enter' key to continue.. ");
	getchar();
}


void main()
{
	menu();
	char SETTINGS_FILE[256]; 	

	int grid[4][4];
	int score = 0;
	initialize(grid);

	while (1)
	{
		system("clear");
		print(grid);
		printf("\n SCORE: %d\n ",score);

		int status = Move(getchar(), grid, &score);
		if (status == 1){
			break;
		}
		else if(status == 2){
			score = 0;
			initialize(grid);
			continue;
		}
		status = check(grid);
		if (status == -1)
		{
			system("clear");
			print(grid);
			printf("Score: %d\n You Win !\n", score);
			break;
		}
		else if (status == 0)
		{
			system("clear");
			print(grid);
			printf("Score: %d\n Game Over !\n", score);
			break;
		}
		printf("\n");
	}

}
