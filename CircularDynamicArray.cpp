#include <iostream>
#include <signal.h>
#include <bits/stdc++.h> 

using namespace std;

template <class elmtype>
class CircularDynamicArray
{
    public:
        //Empty constructor
        CircularDynamicArray()
        {
            this->data = new elmtype[2];

            head = 0;
            tail = 0;

            size = 0;
            capacity_arr = 2;
        }

        //Set size constructor
        CircularDynamicArray(int s)
        {
            this->data = new elmtype[s];

            size = s;
            capacity_arr = s;

            head = 0;
            tail = s - 1;
        }

        //Destructor
        ~CircularDynamicArray()
        {
            //Not sure whether to use free, or delete.
            //Used both, and since no conflicts arose, kept
            //free(data);
            //delete(data);
            delete[] data;

            size = 0;
            capacity_arr = 0;
        }

        //Overloading [] operators
        elmtype& operator[](int i)
        {
            if(i > (size - 1))
            {
                cout << "Out of bounds refrence : " << i << endl;
                //return error;
            }

            return this->data[(head + i) % capacity_arr];
        }

        elmtype at(int i)
        {
            if(i > (size - 1))
            {
                cout << "Out of bounds refrence : " << i << endl;
                //return error;
            }

            return this->data[(head + i) % capacity_arr];
        }

        //Overloading = operator
        //Primarily to avoid = setting the data pointers as the same
        CircularDynamicArray& operator=(CircularDynamicArray& other)
        {
            if(this != &other)
            {
                this->data = new elmtype[other.capacity()];
                capacity_arr = other.capacity();
                size = other.length();

                for(int i = 0; i < size; i++)
                {
                    this->data[i] = other[i];
                }
            }

            return *this;
        }

        //Add to end of circular array
        void addEnd(elmtype v)
        {
            if(capacity_arr == size)
            {
                resize(true);
            }

            this->data[(head + (size)) % capacity_arr] = v;
            size++;

            tail++;
            if(tail > (capacity_arr - 1))
            {
                tail = 0;
            }
        }

        //Add to front of circular array
        void addFront(elmtype v)
        {
            if(capacity_arr == size)
            {
                resize(true);
            }

            head--;
            if(abs(head) != head)
            {
                head = capacity_arr - 1;
            }

            this->data[(head) % capacity_arr] = v;
            size++;
        }

        //Delete from end of circular array
        void delEnd()
        {
            if(size <= capacity_arr / 4)
            {
                resize(false);
            }

            tail--;
            if(abs(tail) != tail)
            {
                tail = capacity_arr - 1;
            }

            size--;
        }
        
        //Delete from front of circular array
        void delFront()
        {
            if(size <= capacity_arr / 4)
            {
                resize(false);
            }

            size--;

            head++;
            if(head > (capacity_arr - 1))
            {
                head = 0;
            }
        }

        int length()
        {
            return size;
        }
        int capacity()
        {
            return capacity_arr;
        }
        void clear()
        {
            this = new CircularDynamicArray();
        }


    private:
        int size;
        int capacity_arr;

        int head;
        int tail;

        //elmtype error = NULL;//-2147483627;

        elmtype* data;

        //This is a function only used by operations that have order O(N) complexity, as this needs to be masked
        int resize(bool grow)
        {
            //printf("RESIZING");
            if(grow)
            {
                //printf(" UP\n");
                elmtype* data_resized = new elmtype[capacity_arr * 2];

                for(int i = 0; i < size; i++)
                {
                    data_resized[i] = this->data[(head + i) % capacity_arr];
                }

                capacity_arr *= 2;

                //free(data);
                delete[] data;
                this->data = data_resized;
                head = 0;
                tail = size - 1;

                return size;
            }
            else
            {
                //printf(" DOWN\n");
                elmtype* data_resized = new elmtype[capacity_arr / 2];

                for(int i = 0; i < size; i++)
                {
                    data_resized[i] = this->data[(head + i) % capacity_arr];
                }

                capacity_arr /= 2;

                //free(data);
                delete[] data;
                this->data = data_resized;
                head = 0;
                tail = size - 1;

                return size; 
            }
            
        }

        //Similar to resize, not sure if I should delete or not
        void reorder()
        {
            elmtype* reordered = new elmtype[capacity_arr];

                for(int i = 0; i < size; i++)
                {
                    reordered[i] = this->data[(head + i) % capacity_arr];
                }

            //delete(data);
            delete[] data;
            this->data = reordered;
            head = 0;
            tail = size - 1;
        }


        void printArray(elmtype A[], int size) 
        { 
            for (int i=0; i < size; i++)
            {
                cout << A[i] << " ";
            }

            printf(" \n"); 
        } 
};

