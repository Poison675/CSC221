#include "dtree.h"
#include "utree.h"
#include <random>
#include <stdexcept>
#include <fstream>

using namespace std;


#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);
    bool testBasicUTreeInsert(UTree& utree);
    bool testBasicUTreeRemove(UTree& utree);

};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}

bool Tester::testBasicDTreeRemove(DTree& dtree) {
    bool allRemoved = true;
    int numDiscriminators = 3;
    int discriminators[] = {8319, 2987, 1691};
    DNode* removed = nullptr;

    for(int i = 0; i < numDiscriminators; i++) {
        if(!dtree.remove(discriminators[i], removed)) {
            cout << "Deletion on node " << discriminators[i] << " did not return true" << endl;
        }
        delete removed;
    }

    cout << "Dumping the tree after 3 deletions time" << endl;
    dtree.dump();
    cout << endl;

    cout << "Inserting 1 element to cause an imbalance and to clear vacant nodes" << endl;
    Account bigAcct = Account("", 9999, 0, "", "");
    dtree.insert(bigAcct);
    return allRemoved;
}

bool Tester::testBasicUTreeInsert(UTree& utree){
    ifstream file("accounts.csv");

    if (!file.is_open()){
        throw runtime_error("Could not open file.");
    }

    bool allinserted = true;

    for (int i = 0; i < 2; i++){
        string line;
        if (!getline(file, line)) return false;

        int index = line.find(',');
        string username = line.substr(0,index);
        line = line.substr(index + 1);

        index = line.find(',');
        int disc = stoi(line.substr(0,index));
        line = line.substr(index + 1);

        index = line.find(',');
        bool nitro = bool(stoi(line.substr(0,index)));
        line = line.substr(index + 1);

        index = line.find(',');
        string badge = line.substr(0,index);
        line = line.substr(index + 1);

        index = line.find(',');
        string status = line.substr(0,index);
        line = line.substr(index + 1);

        Account nAct(username, disc, nitro, badge, status);
        if (!utree.insert(nAct)){
            cout << endl << "Insertion with account " << nAct << " did not return true" << endl << endl;
            allinserted = false;
        }
    }

    return allinserted;
}

bool Tester::testBasicUTreeRemove(UTree& utree){
    bool removed = true;
    DNode* dnode;

    if (!utree.removeUser("Capstan", 604, dnode)){
        cout << "Removing user returned false" << endl;
        removed = false;

        if (!dnode) {
            cout << "Failed to get DNode" << endl;
            removed = false;
        }
    }
    delete dnode;

    if (!utree.removeUser("Cinnamon", 5319, dnode)){
        cout << "Removing user returned false" << endl;
        removed = false;

        if (!dnode) {
            cout << "Failed to get DNode" << endl;
            removed = false;
        }
    }
    delete dnode;

    // if (!utree.removeUser("Capstan", 4962, dnode)){
    //     cout << "Removing user returned false" << endl;
    //     removed = false;

    //     if (!dnode) {
    //         cout << "Failed to get DNode" << endl;
    //         removed = false;
    //     }
    // }
    // delete dnode;


    return removed;
}

int main() {
    Tester tester;

    /* Basic dtree tests */
    // DTree dtree;

    // cout << "Testing DTree insertion...";
    // if(tester.testBasicDTreeInsert(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "Resulting DTree:" << endl;
    // dtree.dump();
    // cout << endl;

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "Resulting DTree:" << endl;
    // dtree.dump();
    // cout << endl;

    UTree utree;

    cout << "Testing UTree insertion...";
    if(tester.testBasicUTreeInsert(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting UTree:" << endl;
    utree.dump();
    cout << endl;   

    // cout << "Testing UTree balance..." << endl;
    // if (utree.checkOrder()){
    //     cout << "test passed" << endl;
    // } else{
    //     cout << "test failed" << endl;
    // }

    cout << "Testing UTree removal...";
    if(tester.testBasicUTreeRemove(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting UTree:" << endl;
    utree.dump();
    cout << endl;

    // cout << "Testing UTree balance..." << endl;
    // if (utree.checkOrder()){
    //     cout << "test passed" << endl;
    // } else{
    //     cout << "test failed" << endl;
    // }

    return 0;
}
