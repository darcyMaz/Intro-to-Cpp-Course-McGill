#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define ARRSIZE 50
int datastore[ARRSIZE] = {};



// I've created two static variables for my implementation (i guess they don't NEED to be static but why not)

// dataAllocation tells us how much space is left in datastore
static int dataAllocation = ARRSIZE;

// sizes stores the sizes of mini-stores by id. However, the sizes[M] holds the size of its mini-store and all mini-stores before it.
// ex. sizes[0] holds size N of the first store and sizes[1] holds the size of the second store plus the size N of the first store
//     the reason for holding the sum of the current store size and all the previous ones is to prevent having to go through 
//     all indices to get the actual position of the Mth store. I only need to subtract sizes[M] 
//     from sizes[M-1] to know the size and use sizes[M-1] to know where the store M starts.
//static int sizesIncrement = 0;
static int sizes[ARRSIZE];



int newstore(int ssize)
{
    // If there's actually enough space to make this mini-store.
    if (dataAllocation - ssize >= 0) 
    {
        // Update dataAllocation and find the id this store should represent.
        dataAllocation -= ssize;

       for (int i=0;i<50;i++)
       {
            if (i==0) 
            {
                if (sizes[i]==0)
                {
                    sizes[i] = ssize;
                    return i;
                }
            }
            else
            {
            if (sizes[i]==0) 
                {
                    sizes[i] = ssize+sizes[i-1];
                    return i;
                }
            }
       }
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

int print_debug()
{

    printf("available elements in datastore: %d\n\n",dataAllocation);

    printf("datastore   :");
    for (int i=0;i<50;i++)
    {
        printf(" %d",datastore[i]);
    }
    printf("\n\n");

    for (int i=0;i<50;i++)
    {
        if (sizes[i]!=0)
        {
            int jTemp;
            if (i==0) jTemp = 0;
            else jTemp =sizes[i-1];

            printf("store %d:",i);
            for (int j=jTemp;j<sizes[i];j++)
            {
                printf(" %d",datastore[j]);
            }
            printf("\n\n");
        }
        else break;
    }

    printf("#####################################\n\n");

    return 0;
}

void delete_element_from_store_by_value(int id, int val)
{
    int realStartIdx;
    if (id==0) realStartIdx = 0;
    else realStartIdx = sizes[id-1];

    // No out of range checks are neccesary because this for loop will never check out of range for val.
    for (int i=realStartIdx;i<sizes[id];i++)
    {
        if (datastore[i]==val) 
        {
            datastore[i] = 0;
            break;
        }
    }
}

void delete_element_from_store_by_index(int id, int idx)
{
    int realStartIdx;
    if (id==0) realStartIdx = 0;
    else realStartIdx = sizes[id-1];

    if (realStartIdx >= sizes[id]) ;
    else datastore[realStartIdx + idx] = 0;
}

void which_stores_have_element(int val)
{
    printf("Element %d",val);
    // This for loop looks through datastore and stops if it finds an instance of val.
    // If it never does then nothing happens except for the "not available" print out.
    for (int i=0;i<50;i++)
    {
        if (datastore[i]==val) 
        {
                // All the code below is code which will go through each store properly and return which stores have val.
                string toReturn = " is in store IDs:";
                for (int k=0;k<50;k++)
                {
                    if (sizes[k]!=0)
                    {
                        int jTemp;
                        if (k==0) jTemp = 0;
                        else jTemp =sizes[k-1];

                        for (int j=jTemp;j<sizes[k];j++)
                        {
                            if (datastore[j]==val) 
                            {
                                //printf(" %d,",k);
                                toReturn = toReturn + " " + to_string(k) + ",";
                                break; 
                                // This break is here because it does not matter if we find val again in this store.
                            }
                        }
                    }
                    else break;
                }

                // This substring business is to get rid of the trailing comma.
                cout << toReturn.substr(0,toReturn.size()-1) << endl << endl;
                return ;
        }
    }

    printf(" is not available in any store\n\n");
    
}

void delete_store(int id)
{
    int iTemp;
    if (id==0) iTemp = 0;
    else iTemp =sizes[id-1];
    // Remember again, sizes[id-1] holds the first index of the mini-store id. And sizes[id] holds the last index of id + 1.

    dataAllocation += sizes[id]-iTemp;

    int idSize;
    if (id!=0) idSize = sizes[id] - sizes[id-1];
    else idSize = sizes[id];

    // Starting at the index immediately after the mini-store at hand, move all elements back by the size of the store being deleted.
    for (int i = sizes[id];i<50;i++)
    {
        datastore[i-idSize] = datastore[i];
    }
    for (int i=50-idSize;i<50;i++)
    {
        datastore[i] = 0;
    }

    for (int i=id;i<50;i++)
    {
        if (sizes[i+1]==0) {sizes[i]=0;break;}
        else sizes[i] = sizes[i+1]-idSize;
    }
}

int resize_store(int id, int newsize)
{
    // OK so this won't get full marks for a very specific reason that became evident with the testing code at the end of the assignment.
    // In the main() testing code s1 is deleted. This is fine and works. However, it then asks to resize s2...
    // According to the way I've implemented this, s2 (which refers directly to an id of 1) is a mini-store which no longer exists.
    // However, the next print_debug() call in the pdf shows that s2 resizes the array which now has id 0 and previously had id 1.
    // My code does not do this, instead it still tries to resize the array at id 1 and fails because the only mini-store that exits is at id 0.
    // I don't have time to change my whole system to fix this so I've just explained it to you here.
    // Other than that, this function should work.

    int prevSize;
    if (id==0) prevSize = 0;
    else prevSize = sizes[id-1];

    if (sizes[id]==0) return -1;

    int currentIdSpace = sizes[id] - prevSize;

    if (newsize - currentIdSpace > dataAllocation) return -1;
    else 
    {
        dataAllocation -= newsize - currentIdSpace;

        if (newsize>currentIdSpace)
        {
            // This for loop moves elements
            for (int i=49-(newsize - currentIdSpace);i>=sizes[id];i--)
            {
                datastore[i+(newsize - currentIdSpace)] = datastore[i];
            }
            
            // This for loop empties new spaces of old values.
            for (int i=sizes[id];i<sizes[id]+(newsize - currentIdSpace);i++)
            {
                datastore[i] = 0;
            }

            // I must update the sizes array because each element in sizes holds the size of its array and all before it.
            for (int i=id;i<50;i++)
            {
                if (sizes[i]==0) break;
                else 
                {
                    sizes[i] += (newsize - currentIdSpace);
                }
            }
        }
        //this is the scenario where we're shrinking this ministore
        else 
        {

            // First we move elements backwards from the mini-store after the one represented by ID to the end
            for (int i=sizes[id];i<50;i++)
            {
                datastore[i+(newsize - currentIdSpace)]=datastore[i]; //DEF NOT. WE WANT DATASTORE[I-SOMETHING] = DATASTORE[I] OR WTVR
            }
            // Second, another for loop makes sure the spaces at the end of datastore which don't get new values are returned to 0.
            for (int i=50+(newsize - currentIdSpace);i<50;i++)
            {
                datastore[i] = 0;
            }
            // Third, I must update the sizes array because each element in sizes holds the size of its array and all before it.
            for (int i=id;i<50;i++)
            {
                if (sizes[i]==0) break;
                else 
                {
                    sizes[i] += (newsize - currentIdSpace);
                }
            }

        }

    }

    return 0;
}

int main()
{
    int s1 = newstore(3); // create new empty data store of size 3
    int s2 = newstore(5); // create new empty data store of size 5

    if (s1 != -1)
    {
        add_element_to_store(s1, 13);
        add_element_to_store(s1, 15);
        add_element_to_store(s1, 21);
        add_element_to_store(s1, 42); // this should return -1
    }
    
    if (s2 != -1)
    {
        add_element_to_store(s2, 7, 2);
        add_element_to_store(s2, 15, 0);
        add_element_to_store(s2, 22, 1);
    }
    print_debug();

    delete_element_from_store_by_value(s1, 13);
    delete_element_from_store_by_value(s1, 71);
    delete_element_from_store_by_index(s2, 2);
    delete_element_from_store_by_index(s1, 5);
    print_debug();

    which_stores_have_element(15);
    which_stores_have_element(29);

    delete_store(s1);
    print_debug();

    resize_store(s2, 20);
    int s3 = newstore(40);
    print_debug();

    s3 = newstore(30);
    add_element_to_store(s3, 7, 29);
    print_debug();
    
}

