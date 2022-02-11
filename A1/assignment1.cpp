#include <stdio.h>
#include <iostream>
using namespace std;

#define ARRSIZE 50
int datastore[ARRSIZE] = {};


// Four variables for the newstore function.

// dataAllocation tells us how much space is left in datastore
// newstoreIncrement is the returned value of newstore
static int dataAllocation = ARRSIZE;
static int newstoreIncrement = 0;


// sizesIncrements helps us keep track of how many stores we have
// sizes stores the sizes of various mini-stores in datastores plus all the space prior to it
// ex. sizes[0] holds size N of the first store and sizes[1] holds the size of the second store plus the size of thh first store
//     the reason for holding the sum of the current store size and all the previous ones is to prevent having to go through 
//     all indices to get the actual position of the Mth store. I only need to subtract sizes[M] 
//     from sizes[M-1] to know the size and use sizes[M-1] to know where the store M starts.
static int sizesIncrement = 0;
static int sizes[ARRSIZE];



int newstore(int ssize)
{
    if (dataAllocation - ssize >= 0) 
    {
        dataAllocation -= ssize;
        
        //at the return value of sizes we put how big the mini-store is
        //then we increment sizesIncrement by 1
        if (newstoreIncrement==0) sizes[sizesIncrement] = ssize;
        else sizes[sizesIncrement] = ssize + sizes[sizesIncrement-1];
        sizesIncrement++;

        newstoreIncrement++;
        return newstoreIncrement-1;
    }
    else return -1;
}


int add_element_to_store(int id, int val, int idx=-1)
{
    
    int realIDStart;
    if (id!=0) realIDStart = sizes[id-1];
    else realIDStart = 0;

    int realSize;
    if (id!=0) realSize = sizes[id]-sizes[id-1];
    else realSize = sizes[id];

    // sizes[id] has the size of the id-th mini-store plus all previous store sizes so 
    // the end of the id-th store is size of the id-th store minus 1.
    if (idx==-1)
    {
        for (int a=realIDStart;a<sizes[id];a++)
        {
            if (datastore[a]==0) 
            {
                datastore[a]=val;
                return 0;
            }
        }
    }
    else 
    {

        int realIndex;
        if (id!=0) realIndex = sizes[id-1]+idx;
        else realIndex = idx;

        // What's the range of indices possible? max is sizes[id]-1 and min can't logically go below the relative 0 index
        // This is a result of how i organized my variables to work and is explained above.
        // Anyway, if it's out of range then return -1;
        if (realIndex>sizes[id]-1) return -1;
        else
        {

            // Since we're looking at the first array no reference to other variables is neccesary (yet).
            if (id==0) datastore[idx] = val;

            // As explained in the variable declarations above, sizes[id-1] holds the first position of the id-th mini-store.
            else datastore[sizes[id-1]+idx] = val;

        }
    }
    
    return 0;
}





int main()
{
    int s1 = newstore(3); // create new empty data store of size 3
    int s2 = newstore(5); // create new empty data store of size 5

    //printf("%d-%d\n",s1,s2);

    if (s1 != -1)
    {
        //THE PROBLEM IS THAT I DECIDED TO SAY IF(IDX==-1) THEN PUT IT AT LAST SPOT INSTEAD OF APPEND TO END
        add_element_to_store(s1, 13);
        add_element_to_store(s1, 15);
        add_element_to_store(s1, 21);
        add_element_to_store(s1, 42); // this should return -1
    }
    
    for (int i=0;i<50;i++)
    {
        printf("%d-",datastore[i]);
    }

    return 0;
}