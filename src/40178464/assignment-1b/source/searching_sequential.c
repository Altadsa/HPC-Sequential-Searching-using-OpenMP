
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

char *textData;
int textLength;

char *patternData;
int patternLength;

clock_t c0, c1;
time_t t0, t1;

void outOfMemory()
{
	fprintf (stderr, "Out of memory\n");
	exit (0);
}

void readFromFile (FILE *f, char **data, int *length)
{
	int ch;
	int allocatedLength;
	char *result;
	int resultLength = 0;

	allocatedLength = 0;
	result = NULL;

	

	ch = fgetc (f);
	while (ch >= 0)
	{
		resultLength++;
		if (resultLength > allocatedLength)
		{
			allocatedLength += 10000;
			result = (char *) realloc (result, sizeof(char)*allocatedLength);
			if (result == NULL)
				outOfMemory();
		}
		result[resultLength-1] = ch;
		ch = fgetc(f);
	}
	*data = result;
	*length = resultLength;
}

int readData (int testNumber)
{
	FILE *f;
	char fileName[1000];
#ifdef DOS
        sprintf (fileName, "inputs\\test%d\\text.txt", testNumber);
#else
	sprintf (fileName, "inputs/test%d/text.txt", testNumber);
#endif
	f = fopen (fileName, "r");
	if (f == NULL)
		return 0;
	readFromFile (f, &textData, &textLength);
	fclose (f);
#ifdef DOS
        sprintf (fileName, "inputs\\test%d\\pattern.txt", testNumber);
#else
	sprintf (fileName, "inputs/test%d/pattern.txt", testNumber);
#endif
	f = fopen (fileName, "r");
	if (f == NULL)
		return 0;
	readFromFile (f, &patternData, &patternLength);
	fclose (f);

	printf ("Read test number %d\n", testNumber);

	return 1;

}



int hostMatch(long *comparisons)
{
	int i,j,k, lastI;
	
	i=0;
	j=0;
	k=0;
	lastI = textLength-patternLength;
        *comparisons=0;

	while (i<=lastI && j<patternLength)
	{
                (*comparisons)++;
		if (textData[k] == patternData[j])
		{
			k++;
			j++;
		}
		else
		{
			i++;
			k=i;
			j=0;
		}
	}

	if (j == patternLength)
	{
	    printf("\nPattern found, stopping search. Searched up to index %i out of maximum of %i indexes.\n\n", i, lastI);
        return i;
    }
	else
		return -1;
}
void processData()
{
	unsigned int result;
        long comparisons;

	printf ("Text length = %d\n", textLength);
	printf ("Pattern length = %d\n", patternLength);

	result = hostMatch(&comparisons);
	if (result == -1)
		printf ("Pattern not found\n");
	else
		printf ("Pattern found at position %d\n", result);
        printf ("# comparisons = %ld\n", comparisons);

}

long getNanos(void)
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void runTest(int testNumber)
{

    readData(testNumber);
    long timeStart, timeEnd;

    timeStart = getNanos();
    processData();
    timeEnd = getNanos();

    long elapsedNsec = (timeEnd - timeStart);

    printf("\nTest %d elapsed wall clock time = %ld\n", testNumber, (long)(elapsedNsec / 1.0e9));
    printf("Test %d elapsed CPU time = %.09f\n\n", testNumber, (double)elapsedNsec / 1.0e9);

}

void readDefault()
{
    int testNumber = 0;

    while (readData (testNumber))
    {
        runTest(testNumber);
        testNumber++;
    }
}

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("\nRead Default - not enough arguments.\n");
        readDefault();
    }
    else
    {
        int testNumber = atoi(argv[1]);
        runTest(testNumber);
    }
}