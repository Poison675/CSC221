/**
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"
#include <stdexcept>

/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {
    clear();
    _root = nullptr;
}

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */ 
void UTree::loadData(string infile, bool append) {
    std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];

    /* Check to make sure the file was opened */
    if(!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
    if(!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
    while(std::getline(instream, line)) {
        std::stringstream buffer(line);

        /* Quick check to make sure each line is formatted correctly */
        int delimCount = 0;
        for(unsigned int c = 0; c < buffer.str().length(); c++) if(buffer.str()[c] == delim) delimCount++;
        if(delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes - 
         * Each line always has 5 sections of data */
        for(int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
}

/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree. 
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 */
bool UTree::insert(Account newAcct) {
    bool inserted = (insert(newAcct, _root));

    // Update height and rebalance are recursive functions that will be called at the end of 
    // every insert or delete task in my program. They check imbalances and update height from 
    // the bottom up and make sure the entire tree is still in order without unnecessary 
    // repeated calls or convoluded logic.
    updateHeight(_root);
    rebalance(_root);
    return inserted;
}

/*
  Finds the right position for the new account name to occupy. If it reaches a nullptr, 
  creates a new UNode with a new account DTree, then inserts the account. If it finds a 
  UNode with the same username, it inserts the account into the corresponding DTree. 
  param "node" is taken in as a reference so that it can change whatever pointers necessary when 
  dynamically adding a new node. Returns true if the account successfully inserted, false 
  otherwise.
*/
bool UTree::insert(Account newAcct, UNode*& node){
    bool flag;
    string uname1 = newAcct.getUsername();
    string uname2 = (node) ? node->_dtree->getUsername() : "";
    int result = uname1.compare(uname2);

    if (node == nullptr) {
        node = new UNode();
        flag = node->_dtree->insert(newAcct);
    }
    else if (result == 0){
        //If the username is equal to...
        flag = node->_dtree->insert(newAcct);
    }
    else{
        if (result > 0){
            //If the username is greater than...
            flag = insert(newAcct, node->_right);
        }
        else{ 
            //If the username is less than...
            flag = insert(newAcct, node->_left);
        }
    }

    return flag;
}

/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed) {
    bool rem = removeUser(username, disc, removed, _root);

    // Update height and rebalance are recursive functions that will be called at the end of 
    // every insert or delete task in my program. They check imbalances and update height from 
    // the bottom up and make sure the entire tree is still in order without unnecessary 
    // repeated calls or convoluded logic.
    updateHeight(_root);
    rebalance(_root);
    return rem;
}

bool UTree::removeUser(string uname, int disc, DNode*& removed, UNode*& node){
    bool flag = false;

    // This is a recursive function that breaks when it hits a node. If it reaches 
    // the bottom of the tree, it has failed to find the right UNode with the 
    // username, and so will return false.
    if (!node){
        removed = nullptr;
        return false;
    }
    else if (uname == node->_dtree->getUsername()){
        flag = node->_dtree->remove(disc, removed);
        //Checks if the UNode now contains an empty tree, if so, deletes the node.
        if (node->_dtree->getNumUsers() == 0){
            // removeUNode takes in as a reference the pointer to the node in question, 
            // replaces it with a value such that it doesnt break the tree, then deletes
            // the node.
            removeUNode(node);
        }
    }
    else{
        if (uname > node->_dtree->getUsername()){
            flag = removeUser(uname, disc, removed, node->_right);
        }
        else{
            flag = removeUser(uname, disc, removed, node->_left);
        }
    }

    return flag;
}

void UTree::removeUNode(UNode*& node){
    if (!node) { // Insurance
        return;
    } 
    if (node->_left){
        // Instead of the terrible majesty of the algorithm the instructions suggested, 
        // this moves the unode on the right most side of its left subtree to the root
        // and deletes the UNode that was in the root.
        UNode* left = node->_left;
        UNode* right = node->_right;
        delete node;
        node = recurseRight(left);
        node->_left = left;
        node->_right = right;
    }
    else{
        // Or, replaces deleted node with its right child.
        UNode* tempPtr = node->_right;
        delete node;
        node = tempPtr;
    }
}

UNode* UTree::recurseRight(UNode*& node){
    // Finds right most node of the tree, takes it out of the tree and returns the pointer 
    // to it.
    if (!node->_right){
        UNode* unode = node;
        node = node->_left;
        return unode;
    }
    else recurseRight(node->_right);
}

/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username) {
    return retrieve(username, _root);
}

UNode* UTree::retrieve(string username, UNode*& node){
    if (node == nullptr) return nullptr;

    else if (username == node->getUsername()){
        return node;
    }
    else{
        if (username > node->getUsername()){
            return retrieve(username, node->_right);
        }
        else{
            return retrieve(username, node->_left);
        }
    }
}

/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc) {
    return retrieve(username, _root)->_dtree->retrieve(disc);
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {
    return retrieve(username, _root)->_dtree->getNumUsers();
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear() {
    clear(_root);
    _root = nullptr;
}

void UTree::clear(UNode* node){
    //Takes in a node and recursively deletes all of the data of the 
    //child nodes and then deletes itself
    if (!node) return;

    clear(node->_left);
    node->_left = nullptr;
    clear(node->_right);
    node->_right = nullptr;

    delete node;
}

/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const {
    //Prints in order.
    printUsers(_root);
}

void UTree::printUsers(UNode* node) const{
    if (!node) return;
    printUsers(node->_left);
    node->_dtree->printAccounts();
    printUsers(node->_right);
}

/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {
    // By my decision, is recursive. This accomplishes the task of making the 
    // program easy to understand, if not perfectly efficient, as update height 
    // and rebalance only need to be called after insertion and deletion have finished.
    if (!node) return;

    updateHeight(node->_left);
    updateHeight(node->_right);

    if (node->_left || node->_right) {
        // These ensure the height of a leaf node is set to 0, not 1.
        int lHeight = (node->_left) ? node->_left->getHeight() : 0;
        int rHeight = (node->_right) ? node->_right->getHeight() : 0;

        node->_height = (lHeight > rHeight) ? lHeight + 1 : rHeight + 1;
    }
    else{
        node->_height = 0;
    }
}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node) {
    // Mostly a useless function in my opinion, since rebalance does the same check 
    // that this does so calling it on any given node isnt useful. Regardless, the 
    // height of negative one is given to nullptr children to ensure the correct 
    // imbalance conditions can be met.
    int lHeight = (node->_left) ? node->_left->getHeight() : -1;
    int rHeight = (node->_right) ? node->_right->getHeight() : -1;

    if (lHeight > rHeight + 1){
        return true;
    }
    else if (rHeight > lHeight + 1){
        return true;
    }
    return false;
}

/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */
void UTree::rebalance(UNode*& node) {
    // Recursive by my design...
    if (!node) return;
    if (node->_left) rebalance(node->_left);
    if (node->_right) rebalance(node->_right);

    int lHeight = (node->_left) ? node->_left->getHeight() : -1;
    int rHeight = (node->_right) ? node->_right->getHeight() : -1;

    if (lHeight > rHeight + 1){
        // 2 Cases...
        if (!node->_left->_left){
            // Double left-right rotation
            UNode* temp1 = node->_left;
            UNode* temp2 = node;
            node = node->_left->_right;

            node->_left = temp1;
            node->_left->_right = nullptr;

            node->_right = temp2;
            node->_right->_left = nullptr;
        }
        else{
            // Left rotation
            UNode* temp = node->_left;
            node->_left = node->_left->_right;
            temp->_right = node;
            node = temp;
        }
    }
    else if (rHeight > lHeight + 1 ){
        // 2 Cases...
        if (!node->_right->_right){
            // Double right-left rotation
            UNode* temp1 = node->_right;
            UNode* temp2 = node;
            node = node->_right->_left;

            node->_right = temp1;
            node->_right->_left = nullptr;

            node->_left = temp2;
            node->_left->_right = nullptr;
        }
        else{
            // Right rotation
            UNode* temp = node->_right;
            node->_right = node->_right->_left;
            temp->_left = node;
            node = temp;
        }        
    }

    // Sort of inefficient, given its recursive, but oh well...
    updateHeight(node);
}


// bool UTree::checkOrder(UNode* node){
//     if (!node) return true;
//     int result;
//     if (node->_left) {
//         result = node->getUsername().compare(node->_left->getUsername());
//         if (!(result > 0)) return false;
//     }
//     if (node->_right) {
//         result = node->getUsername().compare(node->_right->getUsername());
//         if (!(result < 0)) return false;
//     }

//     return checkOrder(node->_left) && checkOrder(node->_right);
// }