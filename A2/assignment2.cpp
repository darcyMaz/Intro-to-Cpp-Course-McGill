#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

static int datastoreLength = 0;

class node
{
    int id;
    int ssize;
    int* store_data;
    node* next = nullptr;
    //static node *nullNode; // = new node(0);


    public:
        //node* next;


        /**
         * @brief Construct a new node object
         * 
         * @param pSsize
         */
        node(int pSsize)
        {
            id = datastoreLength;
            ssize = pSsize;
            store_data = new int[ssize]; //to get next one do *(store_data + 1)
            for (int i=0;i<ssize;i++)
            {
                store_data[i] = 0;
            }
        }

        ~node()
        {
            delete [] store_data;
        }

        void setNext(node* pNode)
        {
            next = pNode;
        }
        node* getNext()
        {
            //if (next == nullptr) return ;
            return next;
        }

        int getSize()
        {
            return ssize;
        }

        int getId()
        {
            return id;
        }

        int setId(int pId)
        {
            id = pId;
        }

        /**
         * @brief
         * 
         * @param data to insert into store_data
         * @return int 0 on success, -1 on failure out of range or out of space for idx=-1.
         */
        int insertData(int data, int index)
        {
            if (index == -1) 
            {
                //Loop through the data_store until we hit a 0 and append the data there.
                for (int i=0;i<ssize;i++)
                {
                    if ( *(store_data + i)==0 ) 
                    {
                       *(store_data + i) = data;
                       //store_data[i] = data; 
                       return 0;
                    } 
                }
                return -1;
            }
            else if (index >= ssize) return -1;
            else 
            {
                *(store_data + index) = data;
                //store_data[index] = data; 
            }
        }

        int getData(int index)
        {
            return *(store_data + index);
            //return store_data[index];
        }

        void deleteDataByIndex(int index)
        {
            store_data[index] = 0;
        }

        void deleteDataByValue(int value)
        {
            for (int i=0;i<ssize;i++)
            {
                if (store_data[i]==value) {store_data[i] = 0; break;}
            }
        }

        int checkForValue(int value)
        {
            for (int i=0;i<ssize;i++)
            {
                if (store_data[i]==value) { return 0;}
            }
            return 1;
        }

        /**
         * @brief Tells you if there is another node after this one.
         * 
         * @return int 0 if next is not null 1 if next is null
         */
        int hasNext()
        {
            // If next exists return 0.
            if (next != nullptr) return 0;
            else return 1;
        }

        void setAllData(int newSize)
        {
            ssize = newSize;
            int* newArray = new int[newSize];

            for (int i=0;i<ssize;i++)
            {
                newArray[i] = store_data[i];
            }

            delete [] store_data;
            store_data = newArray;

        }

};

static node* nullNode;

class dataList
{
    node* head;
    node* tail;

    public:
        
        dataList(node* pHead)
        {

            head = pHead;
            tail = pHead;

            head->setNext(nullNode);

        }
        node getHead()
        {
            return *head;
        }
        void addNode(node* pNode)
        {
            tail->setNext(pNode);
            pNode->setNext(nullNode);
            tail = pNode;
        }
        void deleteNode(int index)
        {
            node prior = *head;

            if (index>=datastoreLength) return;

            if (index==0)
            {
                head = prior.getNext();
                prior.setNext(nullNode);

                datastoreLength--;

                node temp = *head;
                for (int i=0;i<datastoreLength;i++)
                {
                    temp.setId(temp.getId()-1);
                    temp = *temp.getNext();
                }

                
                return;
            }

            for (int i=0;i!=index-1;i++)
            {
                prior = *prior.getNext();
            }
            node toDelete = *prior.getNext();
            node *postDelete = toDelete.getNext();

            prior.setNext(postDelete);
            toDelete.setNext(nullNode);

            datastoreLength--;

            for (int i=0;i<datastoreLength;i++)
            {
                postDelete->setId(postDelete->getId()-1);
                postDelete = postDelete->getNext();
            }

            return ;
        }
};

//In order to get a node from the datastore I have to define the node "node temp = (datastore + wtvr);" then i can do temp.getWtvr();
static dataList* datastore; //the first node of datastore remains not created yet. *(datastore + 0) is the first node +1 is the second etc.
//static node tail;



int newstore(int ssize)
{
    // First one is id=0
    //node newNode(ssize);
    node *newNode = new node(ssize);

    //cout << "after first initi" << endl;

    if (datastoreLength==0) //True if no nodes yet in datastore (length was updates inside of the constructor so we subtract one).
    {
        
        nullNode = new node(0);
        nullNode->setId(-1);

        

        datastore = new dataList(newNode);

    }
    else
    {
        //cout << "got to else" << endl;
        //node *tempNode = (datastore + (datastoreLength-2));
        //tempNode->next = newNode;
        datastore->addNode(newNode);
    }
    
    datastoreLength++;

    return datastoreLength - 1;
}

int add_element_to_store(int id, int val, int idx=-1)
{
    node temp = datastore->getHead(); // = *(datastore + id);
    int i=0;

    for (;i!=id && i<datastoreLength;i++)
    {
        temp = *temp.getNext();
    }
    if (i==datastoreLength) return 1;
    else return temp.insertData(val,idx);
}

int print_debug()
{

    if (datastoreLength==0) 
    {
        cout << "Number of total used store elements: 0" << endl << endl;
        cout << "#######################################" << endl << endl;
        return 0;
    }

    string toPrint = "";
    int totalUsedSpace = 0;

    node temp = datastore->getHead();
    int lengthCounter = 0;

    for (int j=0;j<datastoreLength;j++)
    {

        toPrint += "\n\n";
        toPrint += "store: " + std::to_string(temp.getId()) + "\n\n";

        int emptyCounter = 0;
        for (int i=0;i<temp.getSize();i++)
        {
            int tempData = temp.getData(i);

            if (tempData==0) emptyCounter++; 
            else totalUsedSpace++;
            toPrint += to_string(tempData) + " ";
        }
        cout << endl;

        lengthCounter++;

        temp = *temp.getNext();
    } 
    
    cout << "Number of total used store elements (not counting empty slots): " << totalUsedSpace << endl << endl;
    cout << "#######################################";
    cout << toPrint << endl << endl << "#######################################" << endl;

    return 0;
}


void delete_element_from_store_by_value(int id, int val)
{
    node temp = datastore->getHead(); // = *(datastore + id);
    int i=0;
    
    for (;i!=id && i<datastoreLength;i++)
    {
        temp = *temp.getNext();
    }
    if (i==datastoreLength) return ;
    else temp.deleteDataByValue(val);
}


void delete_element_from_store_by_index(int id, int idx)
{
    node temp = datastore->getHead(); // = *(datastore + id);
    int i=0;
    
    for (;i!=id && i<datastoreLength;i++)
    {
        temp = *temp.getNext();
    }
    if (i==datastoreLength) return ;
    else temp.deleteDataByIndex(idx);
}

void which_stores_have_element(int val)
{
    string toPrint = "";
    int existsBool = 1;

    node temp = datastore->getHead();

    for (int j=0;j<datastoreLength;j++)
    {
        if (temp.checkForValue(val)==0)  //CHECK THIS FUNCTION
        {
            existsBool = 0;
            toPrint += to_string(j);
            toPrint += ", ";
        }
        temp = *temp.getNext();
    }
    

    if (existsBool) cout << "Element " << to_string(val) << " is not available in any store." << endl;
    else
    { 
        cout << "Element " << to_string(val) << " is in store IDs: ";
        cout << toPrint << endl << endl;
    }
}


void delete_store(int id)
{
    datastore->deleteNode(id);
}

int resize_store(int id, int newsize)
{
    node temp = datastore->getHead();
    int i=0;
    
    for (;i!=id && i<datastoreLength;i++)
    {
        temp = *temp.getNext();
    }
    if (i==datastoreLength) return 1;

    temp.setAllData(newsize);

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

    which_stores_have_element(15); // these no worky
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