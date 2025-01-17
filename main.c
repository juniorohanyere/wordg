#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "validate.h"

/**
 * main - entry point
 *
 * Description: a word game program
 *
 * Return: always return 0
*/

int main(void)
{
	int flag, i;
	size_t *n = malloc(sizeof(size_t) * 1024);
	char *str = NULL;
	char *row[] = {"ABCDE", "FGHIJ", "KLMNO", "PQRST", "UVWXY", "Z", NULL};
	char *col[] = {"AFKPUZ", "BGLQV", "CHMRW", "DINSX", "EJOTY", NULL};
	data_t data;

	printf("----------------(Word Game)----------------\n");
	printf("Magically Determines the Word in Your Mind\n");
	printf("-------------------------------------------\n");
	printf("\tCTRL+D or CTRL+C to exit\n\n");

	while (1)
	{
		do {
			printf("How many letters does the word contain?: ");

			flag = getline(&str, n, stdin);
			if (flag == -1)
			{
				free(str);
				exit(EXIT_SUCCESS);
			}

			str[strlen(str) -1] = '\0';

		} while (isnumber(str) == 0);

		i = atoi(str);

		data.row = malloc(sizeof(char) * (i + 1));
		data.col = malloc(sizeof(char) * (i + 1));

		strcpy(data.row, "");
		strcpy(data.col, "");

		flag = get_pos(row, data.row, i, 1);
		if (flag == -1)
			return (0);

		printf("Nice, so we go again!\n\n");

		flag = get_pos(col, data.col, i, 1);
		if (flag == -1)
			return (0);

		printf("Your Word is: %s\n", get_result(data, row, col));
		printf("\n");
	}

	return (0);
}

/**
 * pos - determines the string to append to a given number
 *
 * @num: the given number
 *
 * Description: the string to append may be either 'st' as in '1st', 'nd' as in
 *		'2nd', or 'rd' as in '3rd'
 *
 * Return: return either 'st', 'nd', or 'rd'
*/

char *pos(int num)
{
	int i, j, k;
	char *str = malloc(sizeof(char) * 1024);
	static char *s[] = {"st", "nd", "rd", NULL};

	snprintf(str, 1024, "%d", num);
	i = atoi(str);

	if (i == 11 || i == 12 || i == 13)
	{
		str = "th";

		return (str);
	}

	for (j = 0, k = 1; s[j] != NULL; j++, k++)
	{
		if (i == k)
			return (s[j]);
	}

	if (strlen(str) > 1 && str[strlen(str) - 2] == '1')
	{
			str = "th";

			return (str);
	}
	else
	{
		i = atoi(&str[strlen(str) - 1]);
		for (j = 0, k = 1; s[j] != NULL; j++, k++)
		{
			if (i == k)
				return (s[j]);
		}
	}

	str = "th";

	return (str);
}

/**
 * get_pos - gets the numeral position of letters by row and column and stores
 *	     them into a string
 *
 * @array: double pointer to a char array of letters
 * @str: char pointer to store the position of the letters
 * @num: the total number of letters the expected word contains
 *
 * Return: return -1 if end of file condition is encountered
*/

int get_pos(char **array, char *str, int num, int pstn)
{
	int i, j, flag;
	char *buffer = NULL, *s = NULL;
	size_t *n = malloc(sizeof(size_t) * 1024);

	for (i = pstn; i <= num; i++)
	{
		for (j = 0; array[j] != NULL; j++)
		{
			printf("Is the %d%s letter here? [%s]: ", i, pos(i),
				array[j]);

			flag = getline(&buffer, n, stdin);
			if (flag == -1)
			{
				free(str);

				return (-1);
			}

			buffer[strlen(buffer) - 1] = '\0';
			if (strcmp(buffer, "y") == 0 || strcmp(buffer, "yes"
				) == 0)
			{
				s = malloc(sizeof(char) * 2);

				snprintf(s, 2, "%d", j);
				strcat(str, s);

				free(s);

				break;
			}
			else if (strcmp(buffer, "n") == 0 || strcmp(buffer,
				"no") == 0)
			{
				/* pass */
			}
			else
			{
				printf("Invalid input\n");
				j -= 1;
			}
		}

		printf("\n");

		if (array[j] == NULL)
		{
			printf("something must be wrong, ");
			printf("please try agian carefully\n\n");

			/* repeat again (recursion) */
			get_pos(array, str, i, i);
		}
	}

	return (0);
}

/**
 * get_result - get the string obtained from cross-refrencing positions of
 *		letters from row and column (see get_pos function)
 *
 * data: data structure for row and column
 * row: array containing a list of grouped letters
 * col: array containing a list of grouped letters
 *
 * Description: the obtained string is the word to determine
 * Return: return the obtained string
*/

char *get_result(data_t data, char **row, char **col)
{
	int i, r, c;
	char *str = NULL, *result = malloc(sizeof(char) * 1024);

	strcpy(result, "");

	for (i = 0; data.row[i] != '\0'; i++)
	{
		str = malloc(sizeof(char) * 2);

		snprintf(str, 2, "%c", data.row[i]);
		r = atoi(str);

		snprintf(str, 2, "%c", data.col[i]);
		c = atoi(str);

		snprintf(str, 2, "%c", row[r][c]);
		strcat(result, str);

	}

	return (result);
}
