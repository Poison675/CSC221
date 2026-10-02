#include "dtree.h"
#include <random>
#include <stdexcept>


#define NUMACCTS 10
#define RANDDISC (distAcct(rng))
int discs[10] = {1531, 2238, 2700, 3123, 4721, 5857, 5918, 5997, 7515, 7810};

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);

};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;

    for(int i = 0; i < NUMACCTS; i++) {
        int disc = discs[i];
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
        // dtree.dump();
        // cout << endl;
    }
    return allInserted;
}


bool Tester::testBasicDTreeRemove(DTree& dtree) {
    bool allRemoved = true;
    int numDiscriminators = 3;
    int discriminators[] = {5857, 2238, 5997};
    DNode* removed = nullptr;

    for(int i = 0; i < numDiscriminators; i++) {
        if(!dtree.remove(discriminators[i], removed)) {
            cout << "Deletion on node " << discriminators[i] << " did not return true" << endl;
        }
    }

    cout << "Dumping the tree after 3 deletions time" << endl;
    dtree.dump();
    cout << endl << endl;

    cout << "Inserting 1 element to cause an imbalance and to clear vacant nodes" << endl;
    Account bigAcct = Account("", 9999, 0, "", "");
    dtree.insert(bigAcct);

    return allRemoved;
}



int main() {
    Tester tester;
    // cout << "Tester created" << endl;

    /* Basic dtree tests */
    DTree dtree;
    // cout << "DTree created" << endl;

    cout << "Testing DTree insertion...";
    if(tester.testBasicDTreeInsert(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;

    cout << "\n\nTesting DTree deletion...";
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;


    return 0;
}
