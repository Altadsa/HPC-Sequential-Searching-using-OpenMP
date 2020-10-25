
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>


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



int hostMatch(long *comparisons, int thread_count)
{
	int i,j,k, lastI;
	
	i=0;
	j=0;
	k=0;
	lastI = textLength-patternLength;
        *comparisons=0;

	long localComparisons = 0;

	int patternLoc = -1;
	int breakSearch = 0; // used to stop comparing text-patterns and move to next text character.

	#pragma omp parallel for reduction(+: localComparisons) \
	shared(patternLoc) private(j,k) firstprivate(breakSearch) \
	num_threads(thread_count) schedule(runtime)
	for (i = 0; i <= lastI; i++)
	{
			k = i;
			j = 0;
			while (j < patternLength && breakSearch == 0)
			{
				localComparisons++;
				if (textData[k] == patternData[j])
				{
					k++;
					j++;
				}
				else
				{
                    breakSearch = 1;
				}
			}

			// condition can only be true once assuming only one occurrence of pattern in text.
			if (j == patternLength && patternLoc == -1)
			{
                patternLoc = i;
			}
			else
			{
				breakSearch = 0;
			}
	}
	(*comparisons) = localComparisons;
    return patternLoc; // returns -1 if not found.
	
}

void processData(int thread_count)
{
	unsigned int result;
        long comparisons;

	printf ("Text length = %d\n", textLength);
	printf ("Pattern length = %d\n", patternLength);

	result = hostMatch(&comparisons, thread_count);
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

void runTest(int testNumber, int minThreads, int maxThreads)
{
    printf("\nMax threads available = %d\n", omp_get_max_threads());
    printf("\nProcessors available = %d\n\n", omp_get_num_procs());

    // initialise array of different thread numbers

    int numThreadSizes = 0;
    int threads = minThreads;
    for (threads; threads < (maxThreads + 1); threads=threads*2)
    {
        numThreadSizes++;
    }

    int threadSizes[numThreadSizes];
    threads = minThreads;
    int index = 0;
    for (index; index < numThreadSizes; index++)
    {
        threadSizes[index] = threads;
        threads = threads * 2;
    }

    // run test for different threads

    int threadIdx = 0;

    readData(testNumber);

    for (threadIdx; threadIdx < numThreadSizes; threadIdx++)
    {
        int threadCount = threadSizes[threadIdx];
        printf("\n\nRunning Test %d using %d threads\n", testNumber, threadCount);
        long timeStart, timeEnd;

        timeStart = getNanos();
        processData(threadCount);
        timeEnd = getNanos();

        long elapsedNsec = (timeEnd - timeStart);

        printf("\nTest %d elapsed wall clock time = %ld\n", testNumber, (long)(elapsedNsec / 1.0e9));
        printf("Test %d elapsed CPU time = %.09f\n\n", testNumber, (double)elapsedNsec / 1.0e9);
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("\nRead Default - not enough arguments.\n");
    }
    else
    {
        int testNumber = atoi(argv[1]);
        int minThreads = atoi(argv[2]);
        int maxThreads = atoi(argv[3]);
        runTest(testNumber,minThreads, maxThreads);
    }
}

