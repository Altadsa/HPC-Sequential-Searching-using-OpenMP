#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>

#define MAX_TESTS 20
#define PRODUCT_COUNT 5
#define PRODUUCT_BASE 2

int totalPatterns;
long textLength;
long patternLength;


struct TextPatternSize
{
    long textLength;
    long patternLength;
};

struct TextPatternSize patterns[20];

void readCombinations(FILE *file, long product)
{
    int result;

    while ((result = fscanf(file, "%ld,%ld", 
                            &textLength,
                            &patternLength)) != EOF)
    {
        patterns[totalPatterns].textLength = textLength;
        patterns[totalPatterns].patternLength = patternLength;
        totalPatterns++;

        //debug only
        long calcProduct = textLength*patternLength;
        printf("Calculated Product: %ld, Required Product: %ld\n", calcProduct, product);
        if (calcProduct != product)
        {
            printf("readCombinations: Calculated product doesn't equal actual product.\n");
        }

        printf("Text Length: %ld, Pattern Length: %ld, Product: %ld\n",
                textLength, 
                patternLength,
                textLength*patternLength);

    }
    
}

int readData(int productNumber)
{
    FILE *file;
    char fileName[50];

#ifdef DOS
    sprintf (fileName, "text_patterns\\ten_%d.txt", productNumber);
#else
    sprintf (fileName, "text_patterns/ten_%d.txt", productNumber);
#endif

    file = fopen(fileName, "r");
    if (file == NULL)
    {
        return 0;
    }

    readCombinations(file, pow(10,productNumber));

    fclose(file);

    printf("Loaded Combinations for 10^%d\n", productNumber);
    return 1;

}

void create_directories()
{
    struct stat st = {0};
    char path[50];
    int i;
    for (i = 0; i < MAX_TESTS; i++) 
    {
        
        sprintf(path, "./inputs/test%d/", i);
        if (stat(path, &st) == -1) 
        {
            mkdir(path, 0700);
        }
    }



}

int main()
{

    totalPatterns = 0;

    create_directories();

    int productNumber = 1;
    while (readData(productNumber*PRODUUCT_BASE))
    {
        productNumber++;
    }

    FILE *fp;
    char testDir[50];
    char fileName[50];

    int i;
    long j;

    for (i = 0; i < totalPatterns; i++)
    {
        textLength = patterns[i].textLength;
        patternLength = patterns[i].patternLength;

#ifdef DOS
        sprintf (testDir, "..\\data\\test%d\\", i);
#else
        sprintf (testDir, "../data/test%d/", i);
#endif

        fp = fopen(strcat(testDir, "pattern.txt"), "w+");
        for (j = 0; j < patternLength - 1; j++)
        {
            fputc('A',fp);
        }
        fputc('B',fp);
        fclose(fp);

        sprintf(testDir, "../data/test%d/", i);
        fp = fopen(strcat(testDir, "text.txt"), "w+");
        for (j = 0; j < textLength - 1; j++)
        {
            fputc('A',fp);
        }
        fputc('B',fp);
        fclose(fp);


    }
    


    
}