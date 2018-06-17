//#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//clear the screen
void clear(void)
{
	system("cls");
}

//stores all the values at various positions
int box_values[4][4] = { 0 };

//introduction to game
void intro(void);
//displays value present at a particular position
void DisplayValue(int, int);
//displays all the values present in a row with the help of above function
void DisplayRow(int);
//displays the whole box with help of above two functions
void DisplayBox(void);
//to scan the user entry and then send entries accordingly into MechanismChange()
int UserEntry(void);
//changes the values of the sent entries. It also changes values present in the `box_values[][]`
int MechanismChange(int&, int&, int&, int&);
//checks for all the possible entries to find any entry where change in values is possible
int EndCheck(void);
//change the values of the sent entries to check. It doesnt change values present in the `box_values[][]`
int MechanismEndCheck(int, int, int, int);
//generate a 2 or 4 at a position whose value is 0
int GenerateRandom(void);
//-----------------------
void GamePlay(void);

int main() {
	char wait;
	srand((unsigned int)time(NULL));
	
	intro();
	GamePlay();

	scanf_s(" %c", &wait, 1);
	return 0;
}

void intro(void) {
	FILE *file_pointer;
	int ch;
	char wait;

	fopen_s(&file_pointer, "here.txt", "r");
	if (file_pointer == NULL) {
		printf("file opening error!");
		scanf_s(" %c", &wait, 1);
		exit(-1);
	}

	while ((ch = getc(file_pointer)) != EOF) {
		printf("%c", (char)ch);
	}

	fclose(file_pointer);
	printf("\n\ndevoloped by Cherubim :^). Enter any key to start : ");
	scanf_s(" %c", &wait, 1);
}

void DisplayValue(int row_no, int col_no) {
	if (box_values[row_no][col_no] != 0)
	{
		printf("%5d", box_values[row_no][col_no]);
	}
	else
	{
		printf("     ");
	}
}

void DisplayRow(int row_no) {
	for (int col_no = 0; col_no < 4; col_no++)
	{
		printf("|");
		DisplayValue(row_no, col_no);
	}
	printf("|\n\n");
}

void DisplayBox(void) {
	printf("\t2048 v.1.0\n");
	printf("-----------------------------------\n\n");
	printf("w -> move up\n");
	printf("a -> move left\n");
	printf("s -> move down\n");
	printf("d -> move right\n");
	printf("x -> exit\n\n");

	for (int row_no = 0; row_no < 4; row_no++)
	{
		printf("-------------------------\n\n");
		DisplayRow(row_no);
	}
	printf("-------------------------\n\n");
}

int UserEntry(void) {
	char selection;
	int is_change_present = 0;

	printf("\nenter your selection ( w, a, s, d ) : ");
	selection = _getch();

	if (selection == 'w')
	{
		for (int index = 0; index < 4; index++)
		{
			is_change_present += MechanismChange(box_values[0][index], box_values[1][index], box_values[2][index], box_values[3][index]);
		}
	}
	else if (selection == 'a')
	{
		for (int index = 0; index < 4; index++)
		{
			is_change_present += MechanismChange(box_values[index][0], box_values[index][1], box_values[index][2], box_values[index][3]);
		}
	}
	else if (selection == 's')
	{
		for (int index = 0; index < 4; index++)
		{
			is_change_present += MechanismChange(box_values[3][index], box_values[2][index], box_values[1][index], box_values[0][index]);
		}
	}
	else if (selection == 'd')
	{
		for (int index = 0; index < 4; index++)
		{
			is_change_present += MechanismChange(box_values[index][3], box_values[index][2], box_values[index][1], box_values[index][0]);
		}
	}
	else if (selection == 'x')
	{
		exit(0);
	}
	else
	{
		char wait;
		clear();
		printf("invalid entry! use only w, a, s, d\n\n");
		scanf_s(" %c", &wait, 1);

		return 0;
	}

	if (is_change_present == 0)
	{
		return 0;
	}

	return 1;
}

int MechanismChange(int& value_1, int& value_2, int& value_3, int& value_4) {
	int initial_values[4] = { value_1, value_2, value_3, value_4 };
	int values[4] = { value_1, value_2, value_3, value_4 };

	for (int index = 1; index < 4; index++) {
		//if the value in box is zero skip mechanism
		if (values[index] == 0)
			continue;
		else {
			//move into spaces if possible
			for (int in_index = index - 1; in_index >= 0; in_index--) {
				if (values[in_index] == 0) {
					values[in_index] = values[in_index + 1];
					values[in_index + 1] = 0;
				}
				else 
				{ 
					break; 
				}
			}
		}
	}//move all

	for (int index = 1; index < 4; index++) {
		//combine with above one if possible
		if ((index != 0) && (values[index - 1] == values[index])) {
			values[index - 1] *= 2;
			values[index] = 0;
		}
	}//change all

	for (int index = 1; index < 4; index++) {
		//if the value in box is zero skip mechanism
		if (values[index] == 0)
			continue;
		else {
			//move into spaces if possible
			for (int in_index = index - 1; in_index >= 0; in_index--)
			{
				if (values[in_index] == 0)
				{
					values[in_index] = values[in_index + 1];
					values[in_index + 1] = 0;
				}
				else
				{
					break;
				}
			}
		}
	}//move all

	if (value_1 == values[0] && value_2 == values[1] && value_3 == values[2] && value_4 == values[3])
	{
		return 0;
	}

	value_1 = values[0];
	value_2 = values[1];
	value_3 = values[2];
	value_4 = values[3];

	return 1;
}

int MechanismEndCheck(int value_1, int value_2, int value_3, int value_4) {
	int initial_values[4] = { value_1, value_2, value_3, value_4 };
	int values[4] = { value_1, value_2, value_3, value_4 };

	for (int index = 1; index < 4; index++) {
		//if the value in box is zero skip mechanism
		if (values[index] == 0)
			continue;
		else {
			//move into spaces if possible
			for (int in_index = index - 1; in_index >= 0; in_index--) {
				if (values[in_index] == 0) {
					values[in_index] = values[in_index + 1];
					values[in_index + 1] = 0;
				}
				else
				{
					break;
				}
			}
		}
	}//move all

	for (int index = 1; index < 4; index++) {
		//combine with above one if possible
		if ((index != 0) && (values[index - 1] == values[index])) {
			values[index - 1] *= 2;
			values[index] = 0;
		}
	}//change all

	for (int index = 1; index < 4; index++) {
		//if the value in box is zero skip mechanism
		if (values[index] == 0)
			continue;
		else {
			//move into spaces if possible
			for (int in_index = index - 1; in_index >= 0; in_index--)
			{
				if (values[in_index] == 0)
				{
					values[in_index] = values[in_index + 1];
					values[in_index + 1] = 0;
				}
				else
				{
					break;
				}
			}
		}
	}//move all

	if (value_1 == values[0] && value_2 == values[1] && value_3 == values[2] && value_4 == values[3])
	{
		return 0;
	}

	return 1;
}

int EndCheck() {
	int is_change_present = 0;

	for (int index = 0; index < 4; index++) {
		is_change_present += MechanismEndCheck(box_values[0][index], box_values[1][index], box_values[2][index], box_values[3][index]);
		is_change_present += MechanismEndCheck(box_values[index][0], box_values[index][1], box_values[index][2], box_values[index][3]);
		is_change_present += MechanismEndCheck(box_values[3][index], box_values[2][index], box_values[1][index], box_values[0][index]);
		is_change_present += MechanismEndCheck(box_values[index][3], box_values[index][2], box_values[index][1], box_values[index][0]);
	}

	if (is_change_present == 0) {
		return 0;
	}

	return 1;
}

int GenerateRandom(void) {
	int source[2] = { 2, 4 };
	int spaces_present[16];
	int spaces_count = 0;
	int rand_number;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (box_values[row][col] == 0)
			{
				spaces_present[spaces_count] = (10 * row) + col;
				spaces_count++;
			}
		}
	}

	if (spaces_count != 0)
	{
		rand_number = spaces_present[rand() % spaces_count];

		box_values[rand_number / 10][rand_number % 10] = source[rand() % 2];
	}

	return spaces_count;
}

void GamePlay(void) {
	char next = 'y';
	int change = 1, vacancies = 16;

	GenerateRandom();

	while (next == 'y')
	{
		clear();

		if (change == 1)
		{
			vacancies = GenerateRandom();
		}

		else
		{
			printf("\nno change!\n");

			if (EndCheck() == 0)
			{
				char wait;
				clear();
				printf("GAME OVER! :(\n\nbetter luck next time\n\n");

				scanf_s(" %c", &wait, 1);
				exit(0);
			}
		}

		DisplayBox();
		change = UserEntry();
	}
}
