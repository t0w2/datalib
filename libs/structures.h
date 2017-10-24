#include <stdlib.h>
#include <iostream>
#include <cassert>

template <class T>
class own_array
{
  public:
    own_array();
    ~own_array();

    long addElement(long position, T element);
    long removeElement(long position);
    unsigned long getSize();
    long getElement(long position, T& element);
    long clear(); // clear array. Keep pointer, but make array empty.
  private:
    T* arrayStructure;
    unsigned long size;
};

template <class T>
own_array<T>::own_array(){
    arrayStructure = NULL;
    size = 0;
}

template <class T>
own_array<T>::~own_array(){
    if (arrayStructure)
        clear();
}

template <class T>
unsigned long own_array<T>::getSize(){
    return size;
}

template <class T>
long own_array<T>::addElement(long position, T element)
{
    switch (position)
    {
    case -1: // add to the tail
        if (0 == size)
            arrayStructure = new T[1];
        else
            arrayStructure = (T *)realloc(arrayStructure, (size + 1) * sizeof(T));
        size++;
        arrayStructure[size - 1] = element;
        break;
    case 0: // add to the head
        if (0 == size)
            arrayStructure = new T[1];
        else
            arrayStructure = (T *)realloc(arrayStructure, (size + 1) * sizeof(T));
        size++;
        arrayStructure[0] = element;
        break;
    default: // adding in the middle of array
        if (0 != size)
        {
            arrayStructure = (T *)realloc(arrayStructure, (size + 1) * sizeof(T));

            // move elements to the right of position by one step
            for (unsigned long i = size; i > (unsigned long) position; i--)
                arrayStructure[i] = arrayStructure[i - 1];

            arrayStructure[position] = element;
            size++;
        }
        else
        {
            assert(NULL == arrayStructure);
            // empty array. Just allocate space
//            if (arrayStructure)
  //              delete[] arrayStructure;

            arrayStructure = new T[position + 1];
            arrayStructure[position] = element;
            size = position + 1;
        }
    }
    return size;
}

template <class T>
long own_array<T>::removeElement(long position){
    if (size <= 0){// Empry Array. nothing to do
        return 0;
    }

    if (position >= (long) size || position < -1)
      return -1; // position is out of bound

    if (1 == size){ 
        //single element & we already know position >=0 and < size
        // Simply delete whole array
        return clear();
    }

    // more than 1 element in the array
    if (-1 == position || position == (long) (size - 1)){ // delete tail element
        arrayStructure = (T*) realloc(arrayStructure, (size - 1) * sizeof(T));
        size--;
        return size;
    }
    else{
        long copyFrom = 0;
        // set position to copy into:
        // 0 - if first element being removed
        // position - if element in the middle is being replaced
        if (0 != position)
            copyFrom = position;

        for (unsigned long i = copyFrom; i < (size - 1); ++i)
            arrayStructure[i] = arrayStructure[i + 1];
        
        arrayStructure = (T*) realloc(arrayStructure, (size -1) * sizeof(T));
        
        return --size;
    }
}

template <class T>
long own_array<T>::getElement(long position, T& element){
  if (0 == size || 
      position < 0 || 
      position >= (long) size)
    return -1;

  element = arrayStructure[position];

  return position;
}


template <class T>
long own_array<T>::clear(){
    if (arrayStructure){
        delete []  arrayStructure;
        arrayStructure = nullptr;
    }
    size = 0;
    return 0;
}
