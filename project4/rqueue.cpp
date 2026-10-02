// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;


int RQueue::findSize(Node* node){
  if (!node) return 0;
  return 1 + findSize(node->_left) + findSize(node->_right);
}

RQueue::RQueue(prifn_t priFn)
{
  _heap = nullptr;
  _size = 0;
  priority = priFn;

}

RQueue::~RQueue()
{
  clear();
}

void RQueue::clear() {
  clear(_heap);
}

void RQueue::clear(Node*& node){
  if (!node) return;
  clear(node->_left);
  clear(node->_right);
  delete node;
  node = nullptr;
}

RQueue::RQueue(const RQueue& rhs)
{
  _heap = copy(rhs._heap);
}

Node* RQueue::copy(const Node* node){
  if (!node) return nullptr;
  Node* newNode = new Node(node->getStudent());
  newNode->_left = copy(node->_left);
  newNode->_right = copy(node->_right);
  return newNode;
}

RQueue& RQueue::operator=(const RQueue& rhs)
{
  if (this == &rhs) return *this;

  clear();
  _heap = copy(rhs._heap);

  return *this;
}

void RQueue::insertStudent(const Student& input) {
  // Created a new RQueue with one node containing the input student.
  RQueue q(this->priority);
  Node* n = new Node(input);
  q._heap = n;

  // Merge the two trees
  mergeWithQueue(q);
}

Student RQueue::getNextStudent() {
  if (!_heap) throw domain_error("Cannot get next student: heap is empty");

  Student s = _heap->getStudent();

  Node* temp = _heap;

  RQueue p2(this->priority);
  p2._heap = _heap->_right;
  _heap = _heap->_left;
  
  mergeWithQueue(p2);

  delete temp;
  return s;
}

void RQueue::mergeWithQueue(RQueue& rhs) {
  if (this == &rhs) return;

  if (this->priority != rhs.priority) throw domain_error("Priorities do not match");

  _heap = merge(_heap, rhs._heap);

  rhs._heap = nullptr; // This line is important.
  rhs._size = 0;

  _size = findSize(_heap);
}

Node* RQueue::merge(Node* p1, Node* p2){
  if (!p1) return p2;
  if (!p2) return p1;

  // Ensure p1 contains the 'higher' priority student, or the one with the smallest priority.
  if (priority(p1->getStudent()) > priority(p2->getStudent())){
    Node* temp = p1;
    p1 = p2;
    p2 = temp;
  }

  // Swap the children of p1.
  {
    Node* temp = p1->_left;
    p1->_left = p1->_right;
    p1->_right = temp;
  }

  // Recursively set p1's left child equal to the merge of itself and p2.
  p1->_left = merge(p1->_left, p2);

  return p1;
}

int RQueue::numStudents() const{
  return _size;
}

void RQueue::printStudentQueue() const {
  printHelper(_heap);
}

void RQueue::printHelper(Node* node) const{
  if (!node) return;

  cout << *node << endl;

  printHelper(node->_left);
  printHelper(node->_right);
}

prifn_t RQueue::getPriorityFn() const {
  return priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  if (priority == priFn) return;

  int s = _size;

  priority = priFn;
  // _size = findSize(_heap); should be unnecessary.
  Student* students = new Student[s];

  {  
    int i = 0;
    buildArray(_heap, students, i);
  }

  clear();

  for (int i = 0; i < s; i++){
    insertStudent(students[i]);
  }

  // sortArray(students, s);

  // int index = 1;
  // _heap = buildTree(students, s, index);

  delete[] students;
  
}

void RQueue::buildArray(Node* node, Student* students, int& i){
  if (!node) return;

  students[i++] = node->getStudent();
  buildArray(node->_left, students, i);
  buildArray(node->_right, students, i);
}

// void RQueue::sortArray(Student* students, int size){
//   for (int i = 1; i < size; ++i) {
//     Student key = students[i];
    
//     int j = i - 1;

//     while (j >= 0 && priority(students[j]) > priority(key)) {
//       students[j + 1] = students[j];
//       --j;
//     }

//     students[j + 1] = key;
//   }
// }

// Node* RQueue::buildTree(Student* students, int size, int index){
//   if (index > size){
//     return nullptr;
//   }
//   Node* newNode = new Node(students[index - 1]);

//   newNode->_left = buildTree(students, size, index * 2);
//   newNode->_right = buildTree(students, size, index * 2 + 1);

//   return newNode;
// }

// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->_left);
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}