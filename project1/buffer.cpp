#include "buffer.h"

Buffer::Buffer(int capacity){
    // **************************************
    // Implement the alternative constructor
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // **************************************
    if (capacity < 1) m_capacity = 0;
    else m_capacity = capacity;
    //The instructions say not to allocate memory for 0 size arrays, 
    //this is handled automatically by the array class;
    m_buffer = new int[m_capacity](); 
    m_count = 0;
    m_start = 0;

    //This indicates that the list is empty. 
    m_end = -1;
}

void Buffer::clear(){
    // ***********************************
    // Implement clear() function
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // ***********************************
    if (m_buffer == nullptr) return;
    delete[] m_buffer; 
    m_buffer = nullptr;
    m_capacity = 0;
    m_count = 0;
    m_start = 0;
    m_end = -1;  
}

Buffer::~Buffer(){
    clear();
}

int Buffer::count(){return m_count;}

int Buffer::capacity(){return m_capacity;}

bool Buffer::full(){
    // **************************
    // Implement full() function
    // **************************
    return m_count == m_capacity;
}

bool Buffer::empty(){
    // **************************
    // Implement empty() function
    // **************************
    return m_count == 0;
}

void Buffer::enqueue(int data){
    // ********************************
    // Implement enqueue(...) function
    // ********************************
    if (full()) {
        // string error = "Array full:\n\t";
        // error.append("Tried to add: ");
        // error.append(to_string(data));
        // error.append("\n\tm_start = " + to_string(m_start) + "\n");
        // error.append("\tm_end = " + to_string(m_end) + "\n");
        // error.append("\tm_capacity = " + to_string(m_capacity) + "\n");
        // throw overflow_error(error);
        // print();
        throw overflow_error("Array full");
    }
    else{
        //Adds items to the buffer using modular arithmatic
        m_buffer[(m_end + 1) % m_capacity] = data;
        m_end = (m_end + 1) % m_capacity;
        m_count++;
    }
}

int Buffer::dequeue(){
    // *****************************
    // Implement dequeue() function
    // *****************************
    if (empty()){
        // this->print();
        throw underflow_error("Array is empty");
    }
    int val = m_buffer[m_start];
    m_start = (m_start + 1) % m_capacity;
    m_count--;
    if (m_count == 0){
        //If the buffer becomes empty, reset the start and the end values
        //Its the best way I thought of to keep track of if the array is empty
        m_start = 0;
        m_end = -1;
    }
    return val;
}

Buffer::Buffer(const Buffer & rhs) : m_capacity(rhs.m_capacity), 
                                     m_count(rhs.m_count), m_start(rhs.m_start), 
                                     m_end(rhs.m_end){
    // *******************************
    // Implement the copy constructor
    // *******************************
    m_buffer = new int[m_capacity]();
    for (int i = 0; i < m_capacity; i++){
        m_buffer[i] = rhs.m_buffer[i];
    }

}

const Buffer& Buffer::operator=(const Buffer & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************
    if (this == &rhs) return *this;

    clear();

    m_capacity = rhs.m_capacity; 
    m_count = rhs.m_count;
    m_start = rhs.m_start; 
    m_end = rhs.m_end;
    m_buffer = new int[m_capacity]();
    for (int i = 0; i < m_capacity; i++){
        m_buffer[i] = rhs.m_buffer[i];
    }

    return *this;
}

void Buffer::dump(){
    int start = m_start;
    //int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}

void Buffer::print(){
    string out;
    out.append("\tm_start = " + to_string(m_start) + "\n");
    out.append("\tm_end = " + to_string(m_end) + "\n");
    out.append("\tm_count = " + to_string(m_count) + "\n");
    out.append("\tm_capacity = " + to_string(m_capacity) + "\n");
    cout << out << endl;
}