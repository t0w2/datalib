#include "../libs/structures.h"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

// Main routine
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Testing array creation
TEST(own_array, constructor)
{
    // Tony added a comment from prilepski-patch-1.
    own_array<int> myarray;
    ASSERT_TRUE(0 == myarray.getSize());
}

// TEsting element addition
TEST(own_array, addElement)
{
    // Tony added a comment from prilepski-patch-2.
    own_array<int> myarray;
    long size = myarray.getSize();
    ASSERT_TRUE(0 == size) << "Array size is not 0 after creation";

    myarray.addElement(-1, 1);
    myarray.addElement(-1, 2);
    myarray.addElement(-1, 3);
    ASSERT_TRUE(3 == myarray.getSize()) << "Array size is not 3 after creation";

    int element;

    myarray.getElement(0, element);
    ASSERT_TRUE(1 == element) << "First element is not 1";
    myarray.getElement(1, element);
    ASSERT_TRUE(2 == element) << "First element is not 2";
    myarray.getElement(2, element);
    ASSERT_TRUE(3 == element) << "First element is not 3";

    myarray.addElement(0, 0);
    myarray.getElement(0, element);
    ASSERT_TRUE(0 == element) << "First element is no 0";

    myarray.addElement(2, 5);
    myarray.getElement(2, element);
    ASSERT_TRUE(5 == element) << "Element at position 2 is not 5";

    myarray.clear();
    ASSERT_TRUE(0 == myarray.getSize()) << "Array is not empty after removeElemenet";

    // adding to the tail of empty array
    myarray.addElement(-1, -1);
    myarray.getElement(0, element);
    ASSERT_TRUE(-1 == element) << "First element is not -1";
    myarray.clear();

    // adding to the non-zero position of empty array
    myarray.addElement(5, 5);
    myarray.getElement(5, element);
    ASSERT_TRUE(5 == element) << "Element at position 5 is not 5 it is " << element;
    myarray.clear();

}

// remove element tests
TEST(own_array, removeElement)
{
    // Tony added comment from prilepski-patch-3
    own_array<int> myarray;

    ASSERT_TRUE(0 == myarray.removeElement(0));
    ASSERT_TRUE(0 == myarray.removeElement(-1));
    ASSERT_TRUE(0 == myarray.removeElement(-10));
    ASSERT_TRUE(0 == myarray.removeElement(10));

    myarray.addElement(-1, 1);
    ASSERT_TRUE(-1 == myarray.removeElement(-2)) << "Error removing negative index";
    ASSERT_TRUE(-1 == myarray.removeElement(10)) << "Error removing poditive index > size";

    ASSERT_TRUE(0 == myarray.removeElement(0)) << "Error removing the only index from elget> size";

    unsigned int numElements = 10;
    for (unsigned int i = 0; i < numElements; i++)
        myarray.addElement(-1, i);

    ASSERT_TRUE(numElements == myarray.getSize()) << "Array size is not 10 after creation";

    ASSERT_TRUE(-1 == myarray.removeElement(myarray.getSize())) << "Error removing element beyong array size";

    ASSERT_TRUE(--numElements == myarray.removeElement(4)) << "Removing element 4 resulted in unexpected size";
    ASSERT_TRUE(--numElements == myarray.removeElement(0)) << "Removing first element resulted in unexpected size";
    ASSERT_TRUE(--numElements == myarray.removeElement(-1)) << "Removing tail element resulted in unexpected size";

    long size = myarray.getSize();
    ASSERT_TRUE(--numElements == myarray.removeElement(size - 1)) << "Removing tail element resulted in unexpected size";



//    ASSERT_TRUE(2 == myarray.removeElement(-1)) << "Removing tail element resulted in unexpected size";
}

TEST(own_array, clear)
{
    own_array<int> myarray;

    myarray.clear();
    ASSERT_TRUE(0 == myarray.getSize()) << "Array size is not 0 after cleaning an empty array";

    myarray.addElement(0, 1);
    ASSERT_TRUE(1 == myarray.getSize()) << "Array size is not 1 after adding 1 element";

    myarray.clear();
    ASSERT_TRUE(0 == myarray.getSize()) << "Array size is not 0 after cleaning non empty array";
}


TEST(own_array, getElement)
{
    own_array<int> myarray;
    int element;

    ASSERT_TRUE(-1 == myarray.getElement(0, element)) << "Unexpected result from empty array";
    ASSERT_TRUE(-1 == myarray.getElement(-1, element)) << "Unexpected result quering element -1 from empty array";
    ASSERT_TRUE(-1 == myarray.getElement(5, element)) << "Unexpected result quering element 5 from empty array";

    myarray.addElement(0, 1);
    ASSERT_TRUE(1 == myarray.getSize()) << "Array size is not 1 after adding 1 element";

    ASSERT_TRUE(-1 == myarray.getElement(-1, element)) << "Unexpected result querring element -1 from non-empty array";
    ASSERT_TRUE(-1 == myarray.getElement(5, element)) << "Unexpected result querring element 5 from 1 element array";
}

// Testing array operations at scale
TEST(own_array, dataConsistency)
{
    own_array<long> myarray;
    std::vector<long> myvector;
    std::vector<long>::iterator it;

    // operations:
    // 0 - insert
    // 1 - delete
    // 2 - clear

    unsigned long numCycles = 10000000;

    myvector.push_back(0);
    myarray.addElement(-1, 0);

    long position = 0;
    for (unsigned long i = 0; i < numCycles; i++){
        if (0 == myvector.size())
            position = 0;
        else
            position = (rand() % myvector.size() - 1);

        if (-1 == position )
            it = myvector.end() - 1;
        else{
            it = myvector.begin();
            it += position;
        }

        switch (rand() % 3){
            case 0:
                myvector.insert(it, i);
                myarray.addElement(position, i);
                break;
            case 1:
                if (myvector.size() > 0){
                    myvector.erase(it);
                    myarray.removeElement(position);
                }
                break;
            case 2:
                myvector.clear();
                myarray.clear();
                break;
        }
    }

    ASSERT_TRUE(myvector.size() == myarray.getSize()) << "Array sizes do not match";
    for (unsigned long i; i < myvector.size(); i++){
        long element;
        myarray.getElement(i, element);
        ASSERT_TRUE(myvector[i] == element) << "Element " << i << " do not match between arrays";
    }
}

/*
TEST(own_hash, constructor)
{
    //own_hash<int>* myhash = new own_hash<int>;
    own_hash<int> myhash;
    ASSERT_TRUE(true);
}
*/
