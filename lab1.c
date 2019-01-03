/*
*
*lab1
*
*Created by Indra Bhurtel on 9/13/18.
*Copyright © 2018 Indra Bhurtel. All rights reserved.
*
*Name:Indra Bhurtel
*I am senior at UTA. My major is software Engineering.
*UTA ID NO:1001542825
*
*lab 1 assignment
*
*Professor Bob Weems
*I am writing this program  to take a sequence of integer values and remove duplicate occurrences
*and Output the number of unique values followed by the values
*
*Code compilation in Omega as follows:
    gcc lab1.c
    ./a.out
*/

#include <stdio.h>
#include <stdlib.h>

/*
* struct to store the value with the index
*/
struct NumIndexPair
{
    int index;
    int value;
};

typedef struct NumIndexPair Pair;

/*
* the comparison function to be provided to qsort
* for sorting by value
* item1: first element to compare,
* item2: second element to compare
* returns the comparison status
*/
int pairComparatorByValue (const void * item1, const void * item2)
{
    Pair* ap = (Pair*)item1;	// obtain first struct item
    Pair* bp = (Pair*)item2;	// obtain second struct item

    // if value of two items is same, sort by index
    if (ap->value == bp->value)
    {
        return (ap->index - bp->index);
    }
    else
        return (ap->value - bp->value);
}

/*
* the comparison function to be provided to qsort
* for sorting by index
* item1: first element to compare,
* item2: second element to compare
* returns the comparison status
*/
int pairComparatorByIndex(const void * item1, const void * item2)
{
    Pair* ap = (Pair*)item1;	// obtain first struct item
    Pair* bp = (Pair*)item2;	// obtain second struct item

    return (ap->index - bp->index);
}

/* array of struct to store upto 100 elements.*/
Pair items[100];

/*
* function to print the array of pairs as desired,
* takes the string for particular phase and count of elements
* phaseStr: string to be displayed as per the phase,
* numItems: the count of elements to print.
*/
void printPairs(char* phaseStr, int numItems)
{
    int i = 0;
    printf("\n%s\n\n", phaseStr);
    for (i = 0; i < numItems; i++)
    {
        printf("%d:  %d  %d\n", i, items[i].value, items[i].index);
    }
}

/*
* function to remove extras from the sorted array.
* numItems: the current count of elements as the input.
* returns the updated count of elements
*/
int removeExtras(int numItems)
{
    int newCount = 0;	// new count of elements
    int i;

    // if there are no or only 1 element, no need to run the loop.
    if (numItems == 0 || numItems == 1)
        return numItems;

    /*
    * run the loop over next to last element,
    * check if the previous element is same as current element,
    * if yes, move to next element else set the element as next element
    * in the modified array with newCount.
    */
    newCount++;		// first element is always new.
    for (i = 1; i < numItems; i++)
    {
        // if this element is not same as previous.
        if (items[i].value != items[i - 1].value)
        {
            // assign as next element in the modified array.
            items[newCount].index = items[i].index;
            items[newCount].value = items[i].value;
            newCount++;
        }
    }

    // return the updated count of unique elements.
    return newCount;
}

/*
 * main function
 */
int main(int argc, char** argv)
{

    int numItems, i;
    printf("Input:\n\n");
    scanf("%d", &numItems);	// read the count of numbers.

    // loop to read the specfied count of numbers.
    for (i = 0; i < numItems; i++)
    {
        int item;
        scanf("%d", &item);
        // store the number in the struct array.
        items[i].index = i;
        items[i].value = item;
    }

    // print phase a.
    printPairs("a. Array of pairs", numItems);
    // sort the numbers based on value.
    qsort(items, numItems, sizeof(Pair), pairComparatorByValue);
    // print phase b.
    printPairs("b. After sorting", numItems);
    // remove extras. get updated count
    numItems = removeExtras(numItems);
    // print phase c.
    printPairs("c. Remove extras", numItems);
    // sort based on index.
    qsort(items, numItems, sizeof(Pair), pairComparatorByIndex);
    // print phase d.
    printPairs("d. After sorting", numItems);
    // print output.
    printf("\nOutput:\n\n%d\n", numItems);
    for (i = 0; i < numItems; i++)
    {
        printf("%d\n", items[i].value);
    }

    return (EXIT_SUCCESS);
}
