#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class SmartAllocator
{

    T* pointer;

    T* allocateMemory(T alloc_size)
    {
        if (alloc_size==1) throw("Size too small (less than 1).\n");

        T * foo;
        foo = new T[alloc_size];

        return foo;
    }

    public:
        SmartAllocator()
        {
            try
            {
                cout << "hi" << endl;
                pointer = allocateMemory(1);
            }
            catch (bad_alloc e)
            {
                cout << "bad_alloc" << endl;
            }
        }
        SmartAllocator(int pSize)
        {
            try
            {
                pointer = allocateMemory(pSize);
            }
            catch (bad_alloc e)
            {
                cout << "bad_alloc" << endl;
            }
            
        }
        ~SmartAllocator()
        {
            delete [] pointer;
        }

        T* getAddress()
        {
            return pointer;
        }



};


int main()
{
    SmartAllocator<int> s;

    s.getAddress();

    return 0;
}