/* Simple pattern generation
 *
 * Written by Alain Espinosa <alainesp at gmail.com> in 2014.
 * No copyright is claimed, and the software is hereby placed in the public domain.
 * In case this attempt to disclaim copyright and place the software
 * in the public domain is deemed null and void, then the software is
 * Copyright (c) 2014 Alain Espinosa
 * and it is hereby released to the general public under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 *
 * (This is a heavily cut-down "BSD license".)
 */

#include <string.h>
#include <math.h>
#include <stdio.h>

#define LEN(x) (sizeof(x)/sizeof(x[0]))

int main()
{
	char* numbers[] = 
	{
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
		"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety",
		"hundred", "thousand", "million", "billion"
	};

	FILE* file = fopen("patterns.txt", "w");

	// Write the pattern two consecutive number_in_letter
	for(int i = 0; i < LEN(numbers); i++)
		for(int j = 0; j < LEN(numbers); j++)
			fprintf(file, "%s%s\n", numbers[i], numbers[j]);
	
	// Write the pattern word "Number" followed by 3 digits
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			for(int k = 0; k < 10; k++)
				fprintf(file, "Number%i%i%i\n", i, j, k);

	// Word we want to permute
	char* words[] =
	{
		"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday",
		"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december",
		"jan", "feb", "mar", "apr", "jun", "jul", "aug", "sep", "oct","nov", "dec",
		"autumn", "winter", "summer", "spring",
		"whitehat", "blackhat", "lasvegas", "vegas", "korelogic", "defcon", "hello", "facebook"
	};
	char generate_word[32];

	// Generate permutation of words
	for(int i = 0; i < LEN(words); i++)
	{
		int len = strlen(words[i]);

		// Change case everywhere
		int total_change_case = pow(2., len);
		for(int num_gen = 0; num_gen < total_change_case; num_gen++)
		{
			int tmp_num_gen = num_gen;

			for(int pos = 0; pos < len; pos++, tmp_num_gen >>= 1)
				generate_word[pos] = words[i][pos] - ((tmp_num_gen & 1) ? 32 : 0);
			generate_word[len] = 0;

			fprintf(file, "%s\n", generate_word);

			// Prefix and append char
			for(int add_char = 32; add_char < 127; add_char++)
			{
				fprintf(file, "%c%s\n", add_char, generate_word);
				fprintf(file, "%s%c\n", generate_word, add_char);

				// Prefix and append other char
				for(int add_char1 = 32; add_char1 < 127; add_char1++)
				{
					fprintf(file, "%c%c%s\n", add_char, add_char1, generate_word);
					fprintf(file, "%s%c%c\n", generate_word, add_char, add_char1);

					// Prefix and append at the same time
					fprintf(file, "%c%s%c\n", add_char, generate_word, add_char1);
				}
			}
		}
	}

	fclose(file);

	return 0;
}

