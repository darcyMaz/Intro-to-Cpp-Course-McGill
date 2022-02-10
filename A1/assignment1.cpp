#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARRSIZE 50
int datastore[ARRSIZE] = {};

// Two variables for the newstore function.
//  dataAllocation tells us how much space is left in datastore
//  newstoreIncrement is the returned value of newstore
static int dataAllocation = ARRSIZE;
static int newstoreIncrement = 0;

int newstore(int ssize)
{
    if (dataAllocation - ssize >= 0) 
    {
        dataAllocation -= ssize; 
        newstoreIncrement++;
        return newstoreIncrement-1;
    }
    else return -1;
}





int main()
{

    return 0;
}