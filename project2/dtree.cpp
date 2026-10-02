/**
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */

#include "dtree.h"
#include <stdexcept>

/**
 * Destructor, deletes all dynamic memory.
 */
DTree::~DTree() {
    clear();    
    _root = nullptr;
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */
DTree& DTree::operator=(const DTree& rhs) {
    if (this == &rhs) return *this;
    clear();
    _root = copy(rhs._root);
    return *this;
}

/**
 * Dynamically allocates a new DNode in the tree. 
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */
bool DTree::insert(Account newAcct) {
    if (retrieve(newAcct.getDiscriminator())) return false;
    bool flag = insert(_root, newAcct);

    if (checkImbalance(_root)){
        rebalance(_root);
    }

    return flag;
}

/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::remove(int disc, DNode*& removed) {
    removed = retrieve(disc);
    if (!removed) return false;
    remove(_root, disc); //Calls a recursive helper function
    return true;
}

/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::retrieve(int disc) {
    return retrieve(disc, _root);
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::clear() {
    //Calls the recursive function "clear".
    if (_root){
        clear(_root);
    }
    _root = nullptr;
}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const {
    printAccounts(_root);
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if(node == nullptr) return;

    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {
    return getNumUsers(_root);
}

/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 */
void DTree::updateSize(DNode* node) {
    node->_size = 1 + (node->_left ? node->_left->_size : 0) + 
                      (node->_right ? node->_right->_size : 0);
}


/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node) {
    node->_numVacant = (node->_left ? node->_left->_numVacant : 0) + 
                       (node->_right ? node->_right->_numVacant : 0);
    if (node->isVacant()) node->_numVacant++;
}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
bool DTree::checkImbalance(DNode* node) {
    if (!node) return false;

    float leftSize = (node->_left) ? node->_left->getSize() : 0;
    float rightSize = (node->_right) ? node->_right->getSize() : 0;

    if (leftSize < 4 && rightSize < 4){
        return false;
    }
    else if (leftSize * 1.5 <= rightSize ||
             rightSize * 1.5 <= leftSize){
        // cout << "Rebalancing! Left = " << leftSize << ", Right = " << rightSize << ", disc = " << node->getDiscriminator() << endl;
        return true;
    }
    else{
        return checkImbalance(node->_left) || checkImbalance(node->_right);
    }

}

//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
void DTree::rebalance(DNode*& node) {
    // cout << endl << "Prebalance: " << endl;
    // dump();

    int size = node->getSize() - node->getNumVacant();
    Account* array = new Account[size];
    int index = 0;
    convertToArray(node, array, index);
    clear(node);
    
    node = fromArrayToTree(array, 0, size - 1);

    delete[] array;

    // cout << endl << "Postbalance: " << endl;
    // dump();
    // cout << endl << endl;
}

// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
//DNode* DTree::rebalance(DNode*& node) {
    
//}
//----------------

/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
 */
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() << 
            "\n\tDiscriminator: " << acct.getDiscriminator() <<
            "\n\tNitro: " << acct.hasNitro() << 
            "\n\tBadge: " << acct.getBadge() << 
            "\n\tStatus: " << acct.getStatus();
    return sout;
}

void DTree::clear(DNode* node){
    //Takes in a node and recursively deletes all of the data of the 
    //child nodes and then deletes itself
    if (node == nullptr) return;

    clear(node->_left);
    node->_left = nullptr;
    clear(node->_right);
    node->_right = nullptr;

    delete node;
}

DNode* DTree::copy(const DNode* node){
    if (node == nullptr) return nullptr;

    DNode* newNode = new DNode(node->_account);
    newNode->_size = node->getSize();
    newNode->_numVacant = node->getNumVacant();
    newNode->_vacant = node->isVacant();
    newNode->_left = copy(node->_left);
    newNode->_right = copy(node->_right);
    return newNode;
}

bool DTree::insert(DNode*& node, Account account){
    //For the simple case of being handed an empty root node, this is added to prevent
    //a segmentation fault:
    if (!node){
        _root = new DNode(account);
        updateSize(_root);
        return true;
    }
    // If discriminator is smaller than the current nodes', check if it can be inserted
    // to the left. If it cant, recursively insert on the left node. If it can, insert 
    // and then update size.
    if (account.getDiscriminator() < node->getDiscriminator()){
        if (node->_left == nullptr){
            //return case
            node->_left = new DNode(account);
            updateSize(node);
            
            return true;
        }
        else {
            //recursive case
            bool inserted = insert(node->_left, account);
            if (inserted){
                //MUST BE INCLUDED IN EVERY RECURSIVE CALL
                updateNumVacant(node); 
                updateSize(node);
                return inserted;
            }
        }
    }

    // Granted the bootstrap function ensures that "insert" is only called when the 
    // account is not found in any non-vacant nodes, If the current nodes' descriminator
    // is equal to the account's, then it inserts it, decrements the number of vacant
    // cells, sets vacant in that cell to false, then returns true for successful 
    // insertion.
    else if (account.getDiscriminator() == node->getDiscriminator()){
        //node should be 'vacant'
        //return case
        node->_account = account;
        node->_numVacant--;
        node->_vacant = false;
        //size should stay the same
        return true;
    }

    // Similar to the less-than case, if the account's discriminator is greater than the 
    // current nodes', check and insert if it can be inserted in an empty branch, 
    // otherwise recursively insert the account on the right node.
    else { //if the discriminator is greater than the nodes'
        if (node->_right == nullptr){
            //return case
            node->_right = new DNode(account);
            updateSize(node);
            return true;
        }
        else {
            //recursive case
            bool inserted = insert(node->_right, account);
            if (inserted){
                //MUST BE INCLUDED IN EVERY RECURSIVE CALL
                updateNumVacant(node); 
                updateSize(node);
                return inserted;
            }
        }
    }
    return true;
}

void DTree::remove(DNode* node, int disc){
    if (node == nullptr) return;

    if (node->getDiscriminator() == disc){
        node->_vacant = true;
        node->_numVacant++;
        return;
    }
    else if (node->getDiscriminator() > disc){
        remove(node->_left, disc);
        updateNumVacant(node);
        updateSize(node);
    }
    else{ //disc is greater than the nodes'
        remove(node->_right, disc);
        updateNumVacant(node);
        updateSize(node);
    }
}

DNode* DTree::retrieve(int disc, DNode* node){
    if (node == nullptr) return nullptr;

    if (node->getDiscriminator() == disc){
        return node;
    }
    else if (node->getDiscriminator() > disc){
        return retrieve(disc, node->_left);
    }
    else {
        return retrieve(disc, node->_right);
    }
}

void DTree::printAccounts( DNode* node) const{
    if (!node) return;
    if (!node->isVacant()){
        cout << node->_account << endl;
    }
    printAccounts(node->_left);
    printAccounts(node->_right);
}


int DTree::getNumUsers(DNode* node) const {
    return getNumUsers(node->_left) + getNumUsers(node->_right) + 1;
}

void DTree::convertToArray(DNode* node, Account array[], int& index){
    if (!node) return;
    convertToArray(node->_left, array, index);
    if (!node->isVacant()) array[index++] = node->_account;
    convertToArray(node->_right, array, index);
}

DNode* DTree::fromArrayToTree(Account array[], int lower, int upper){
    if (lower > upper) return nullptr;

    int middle = ((upper - lower) / 2) + lower;
    DNode* root = new DNode(array[middle]);
    root->_left = fromArrayToTree(array, lower, middle - 1);
    root->_right = fromArrayToTree(array, middle + 1, upper);

    updateSize(root);
    
    return root;
}
