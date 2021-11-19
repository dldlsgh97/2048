#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int nSpaces(int n)
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

void pickColor(int n)
{
	if (n == -1)
		printf("\033[39;49m");
	if (n == 0)
		printf("\033[100m");
	if (n == 2)
		printf("\033[97;41m");
	if (n == 4)
		printf("\033[97;42m");
	if (n == 8)
		printf("\033[97;43m");
	if (n == 16)
		printf("\033[97;44m");
	if (n == 32)
		printf("\033[97;45m");
	if (n == 64)
		printf("\033[97;46m");
	if (n == 128)
		printf("\033[30;101m");
	if (n == 256)
		printf("\033[30;102m");
	if (n == 512)
		printf("\033[30;103m");
	if (n == 1024)
		printf("\033[30;104m");
	if (n == 2048)
		printf("\033[30;105m");
}

void add(int grid[][4], int value)
{
	time_t ti;
	srand((unsigned)time(&ti));
	int pos = rand();
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

void initialize(int grid[][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			grid[i][j] = 0;
	add(grid, 2);
	add(grid, 2);
}

void printSpaces(int n)
{
	printf("%*c", n, ' ');
}

void print(int grid[][4])
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





void main()
{
	
	
	int grid[4][4];
	int score = 0;
	initialize(grid);

		print(grid);

}
