// results will be freed
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOTAL_ALPHA 26

/**
 * get_reg : function that determines the size of the 5 strings
 *           If possible the message will be evenly split between the five strings; 
 *           If not possible, parts 1, 2, 3, 4 will be longer and part 5 shorter. 
 *           The fifth part can have length equal to the other ones or shorter. 
 *           If there are many options of how to split, choose the option where the 
 *           fifth part has the longest length, provided that the previous conditions 
 *           are fulfilled. If the last part is the empty string don't put this empty 
 *           string in the resulting array.
 */

void get_reg(int *reg, int *l, int *lg)
{
	int rem = *lg % 5;
	int div = *lg / 5;
	*reg = div;
	*l = div;
	if(rem == 4)
	{
		(*reg)++;
	}
	else if(rem > 0)
	{
		while(rem < 4)
		{
			rem++;
			(*l)--;
		}
		(*reg)++;
	}
}

/**
 *  encode: this is a variation on the ceasar cypher.
 *  encode takes a string and uses the shift which is the given ofset for the code then encodes
 *  the string into an array of 4 or 5 strings depending on the length of theinput string.
 *  For example:
 *  input string: char* u = "I should have known that you would have a perfect answer for me!!!";
 *   output char* sol[5] = {"ijJ tipvme ibw","f lopxo uibu z","pv xpvme ibwf ","b qfsgfdu botx","fs gps nf!!!"};
 */
char** encode(char* strng, int shift, int* lg)
{
	int i, j, k, len, end_array, end_string, regular, last;
	char **strng1;
	i = j = k = 0;
	len = (strlen(strng) + 2);
	get_reg(&regular, &last, &len);

	if(last > 0)
		strng1 = malloc( 5 * sizeof(char*));
	else
		strng1 = malloc( 4 * sizeof(char*));

	if(last > 0)
	{
		end_array = 5;
		*lg = 5;
	}
	else
	{
		end_array = 4;
		*lg = 4;
	}
	for(i = 0; i < end_array; ++i)
	{
		if (i < 4)
		{
			end_string = regular;
			strng[i] = malloc( regular * sizeof(char) + 1);
		}
		else
		{
			end_string = last;
			strng[i] = malloc( last * sizeof(char) + 1);
		}

		for(j= 0; j < end_string; ++j)
		{
			if (i == 0 && j == 0)
			{
				strng1[i][j] = tolower(strng[0]);
			}
			else if( i == 0 && j == 1)
			{
				strng1[i][j] = (((tolower(strng[0]) - 'a') + shift) % TOTAL_ALPHA) + 'a';
			}
			else
			{
				if(isupper(strng[k]))
					strng1[i][j] = (((strng[k] - 'A') + shift) % TOTAL_ALPHA) + 'A';
				else if(islower(strng[i]))
					strng1[i][j] = (((strng[k] - 'a') + shift) % TOTAL_ALPHA) + 'a';
				else
					strng1[i][j] = strng[k];
			}
			if(i != 0 || j > 1)
				k++;
		}
		strng1[i][j] = '\0';
	}
	return strng1;
}
