#include <iostream>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Thing {
public:
    int id;
    Thing(int id);
};

Thing::Thing(int id) {
    this->id = id;
}

// return true if thing a is less than thing b
bool compareThingsById(const Thing& a, const Thing& b) {
    return a.id < b.id;
}

bool isSorted(const vector<Thing>& values, function<bool(const Thing& a, const Thing& b)> comp) {
    unsigned int aNum = 0;
    for (unsigned int i = 0; i < values.size(); i++) {
        if (comp(values[i], values[i+1])) {
            aNum++;
        }
    }
    if (aNum == values.size()) {
        return true;
    }
    else {
        return false;
    }
}

void mergeSort(vector<Thing>& values, function<bool(const Thing& a, const Thing& b)> comp) {
    if (values.size() == 1 || values.size() == 0) {
        return;
    }

    // split into two halves
    vector<Thing> a;
    vector<Thing> b;
    for (unsigned int i = 0; i < values.size(); i++) {
        if (i < values.size()/2) {
            a.push_back(values[i]);
        }
        else if (i < values.size()){
            b.push_back(values[i]);
        }
    }

    // sort each half
    mergeSort(a, comp);
    mergeSort(b,comp);

    // merge the two halves back into the original values vector
    vector<Thing> retVec;
    unsigned int ai = 0;
    unsigned int bi = 0;

    // Initial attempt...
    /*if (a.size() >= b.size()) {
        for (int i = 0; i < a.size(); i++) {
            if (comp(a[i],b[i]) || (comp(a[i],b[i]) == comp(b[i],a[i]))) {
                if (ai + 1 == a.size()) {
                    for (int i = bi; i < b.size(); i++) {
                        retVec.push_back(b[i]);
                    }
                    values = retVec;
                    return;
                }
                retVec.push_back(a[ai]);
                ai++;
            }
            else {
                if (bi + 1 == b.size()) {
                    for (int i = ai; i < a.size(); i++) {
                        retVec.push_back(a[i]);
                    }
                    values = retVec;
                    return;
                }
                retVec.push_back(b[bi]);
                bi++;
            }
        }
    }
    else {
        for (int i = 0; i < b.size(); i++) {
            if (comp(a[i],b[i]) || (comp(a[i],b[i]) == comp(b[i],a[i]))) {
                if (ai + 1 == a.size()) {
                    for (int i = bi; i < b.size(); i++) {
                        retVec.push_back(b[i]);
                    }
                    printVector(values);
                    values = retVec;
                    return;
                }
                retVec.push_back(a[ai]);
                ai++;
            }
            else {
                if (bi + 1 == b.size()) {
                    for (int i = ai; i < a.size(); i++) {
                        retVec.push_back(a[i]);
                    }
                    values = retVec;
                    return;
                }
                retVec.push_back(b[bi]);
                bi++;
            }
        }
    }*/

    while(true) {
        if (comp(a[ai], b[bi])) {
            retVec.push_back(a[ai]);
            ai++;
        } else if (comp(b[bi], a[ai])) {
            retVec.push_back(b[bi]);
            bi++;
        } else {
            retVec.push_back(a[ai]);
            ai++;
        }

        if (ai == a.size()) {
            for (unsigned int i = bi; i < b.size(); i++) {
                retVec.push_back(b[i]);
            }
            break;
        } else if (bi == b.size()) {
            for (unsigned int i = ai; i < a.size(); i++) {
                retVec.push_back(a[i]);
            }
            break;
        }
    }
    values = retVec;
    return;
}

void printVector(vector<Thing> vec) {
    cout << "{ ";
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec[i].id;
        if (i + 1 != vec.size()) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

/*
// one option we won't use this time:
bool operator<(const Thing& a, const Thing& b) {
    return a.id < b.id;
 }
*/

TEST(SortThing, sortThree) {
    vector<Thing> v{ 3, 1, 2 };
    ASSERT_TRUE(isSorted(v, compareThingsById));
}

TEST(SortTest, isEmptyVectorSorted) {
    vector<Thing> v;
    ASSERT_TRUE(isSorted(v, compareThingsById));
}

TEST(SortTest, isSingleValueVectorSorted) {
    vector<Thing> v = { 1 };
    ASSERT_TRUE(isSorted(v, compareThingsById));
}

TEST(SortTest, isSortedVectorSorted) {
    vector<Thing> v = { 1,3,5,5,9,100 };
    ASSERT_TRUE(isSorted(v, compareThingsById));
}

TEST(SortTest, isUnsortedVectorSorted) {
    vector<Thing> v = { 1,3,5,1,9,100 };
    ASSERT_FALSE(isSorted(v, compareThingsById));
}

int main() {//int argc, char **argv) {
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

    vector<Thing> test = {2, 7, 2, -1, 69, 420, 1};
    mergeSort(test, compareThingsById);
    printVector(test);
}
