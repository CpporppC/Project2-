/*		Project 2
Taking in a password and checking
against a list of common passwords

This improved version cuts out unneeded
functions, includes better memory
managemant and changes c-casts to static casts.
*/

#include <cstdio>
#include <cstring>

#include <algorithm>

const int ptrsz = sizeof(char*);
int sortfunc(const char* str1, const char* str2);

int main()
{
	char test[12];
	char** best = static_cast<char**>(malloc(ptrsz));
	printf("Give me a password:\n");
	scanf("%11s", test);
	printf("You provided a password of %s\n", test);
	printf("The most similar passwords to %s are:\n", test);

	int count = static_cast<int>(strlen(test));
	const int tsize = count;

	FILE * file = fopen("common_passwords.txt", "r");
	if (!file) { perror("Error");}

	int matches = 0;
	int loc = 0;
	int chr;

	int best_size = 0;
	fpos_t start;
	fgetpos(file, &start);

	while ((chr = fgetc(file)) != EOF)
	{
		if (chr == 10)
		{

			int current = (loc > tsize ? loc : tsize) - matches;
			if (current <= count)
			{
				if (current < count)
				{
					for (int count1 = 0; count1 < best_size; count1++)
					{
						free(best[count1]);
						if (count1 == best_size - 1) free(best);
					}
					char** best = static_cast<char**>(malloc(ptrsz));
					count = current;
					best_size = 0;
				}
				fsetpos(file, &start);

				char* word = static_cast<char*>(malloc(loc + 1));

				fread(word, 1, loc + 1, file);
				word[loc] = 0;
				best = static_cast<char**>(realloc(best, (best_size + 1) * ptrsz));
				best[best_size] = word;

				best_size = best_size + 1;

				if (!(count)) { break; }
			}

			loc = 0;
			matches = 0;
			fgetpos(file, &start);
		}
		else
		{

			if ((loc < tsize) && (test[loc] == chr)) { matches = matches + 1; }
			loc = loc + 1;
		}

	}

	fclose(file);

	std::stable_sort(&best[0], &best[best_size], sortfunc);
	for (int count3 = 0; count3 < best_size; count3++)
	{
		printf("%s, ", best[count3]);
		free(best[count3]);
	}

	printf("\nAll of which are %d character(s) different.\n", count);

	free(best);

	return 0;
}


int sortfunc(const char* str1, const char* str2)
{
	if (strncmp((str1), (str2), 4) < 0) return 1;
	return 0;
}
