// Silly program that randomly shuffles an array of numbers
// and checks to see if they are sorted.  The program continues
// to run until the array is sorted.

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

void populateArr(long arr[], long len);
int getLen(char* string);
int checkString(char* string);
int isSorted(long arr[], long len);
void swap(long *a, long *b);
void shuffle(long arr[],  long len);
void stupidSort(long arr[], long len);
void printArr(long arr[], long len);

int main(int argc, char* argv[])
{
    srand(time(NULL));

    long numbersLen; // Holds array length;

    // Checks number of command line arguments
    if (argc < 2)
    {
        numbersLen = 10; // Sets default array length
    }
    else if (argc == 2)
    {
        // Checks for non-numeric characters
        if (checkString(argv[1]))
        {
            printf("Numbers only, please.\n");
            return 1;
        }
        else
        {
            int num = atoi(argv[1]);
            // Checks if elements are less than 1
            if (num < 1)
            {
                printf("Enter 1 or more elements.\n");
                return 2;
            }
            else
            {
                numbersLen = num;
            }
        }
    }
    else
    {
        printf("Too many arguments.\n");
        return -1;
    }

    long numbers[numbersLen];
    populateArr(numbers, numbersLen);

    stupidSort(numbers, numbersLen);
}

// Gets a random number between 0 and MAX and assigns it
// to each element of the array
void populateArr(long arr[], long len)
{
    const long MAX = 99;

    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % MAX;
    }
}

// Gets length of string and returns it as an int
int getLen(char* string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        i++;
    }

    return i;
}

// Cycles through each character in string to see if character is a digit
// Returns 1 if non-digit character is found
// Returns 0 if all characters are digits
int checkString(char* string)
{
    int len = getLen(string);

    for (int i = 0; i < len; i++)
    {
        if (isdigit(string[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

// Checks pairs of digits in array for least to greatest in value
// If digit 1 is greater than digit 2, return 0 for out of order
// If all digits are in order least to greatest, return 1
int isSorted(long arr[], long len)
{
    // Checks for length of array, defaults to sorted if array is length of 1
    if (len > 1)
    {
        // Cycles through each pair of values, and compares
        for (int i = 1; i < len; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                return 0; // Previous value was larger than next value
            }
        }
    }

    return 1;
}

// Swaps two numbers
// Arguments: pointer to long a, pointer to long b
void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
}

// Shuffles an array
// Cycles through array len amount of times, and
// selects a random element, and switches current
// element with the random element
void shuffle(long arr[],  long len)
{
    for (int i = len - 1; i > 0; i--)
    {
        long j = rand() % (i + 1);

        swap(&arr[i], &arr[j]);
    }
}

// The main function, prints a description of what is happening
// Continuously shuffles array until the array is in order
// Prints that the array is ordered, and gives the amount of shuffles
// it took to sort array.
void stupidSort(long arr[], long len)
{
    unsigned long long tries = 0; // Holds number of shuffles

    printf("Original order: \n");
    printArr(arr, len);

    while(!(isSorted(arr, len)))
    {
        tries++; //Increase number of tries
        shuffle(arr, len);
        printf("Shuffle #%llu\n", tries);
        printArr(arr, len);
        Sleep(2000);
		system("cls");
    }

    printf("\n\nThe numbers are sorted!!!\n");
    printf("It took %llu shuffles to sort the array.\n", tries);
}

// Prints each element of array, in rows of ROW length
// Spacing and line break supports two digit numbers, currently
void printArr(long arr[], long len)
{
    const int ROW = 10;
    int cell = 1;

    printf("-----------------------------\n");

    for (int i = 0; i < len; i++)
    {
        if (cell > ROW)
        {
            cell = 1;
            printf("\n");
        }
        //Checks if number is single digit, adds preceding space if it is
        if (arr[i] > 9)
        {
            printf("%ld ", arr[i]);
        }
        else
        {
            printf(" %ld ", arr[i]);
        }
        cell++;
    }
    printf("\n-----------------------------\n");
}