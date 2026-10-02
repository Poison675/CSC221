#include "bufferlist.h"
BufferList::BufferList(int minBufCapacity){
    // **************************************
    // Implement the alternative constructor
    // **************************************
    if (minBufCapacity <= 1) m_minBufCapacity = DEFAULT_MIN_CAPACITY;
    else m_minBufCapacity = minBufCapacity;

    m_listSize = 1;
    m_cursor = new Buffer(m_minBufCapacity);
    m_cursor->m_next = m_cursor;
}
BufferList::~BufferList(){
    clear();
}

void BufferList::clear(){
    // *****************************
    // Implement clear() function
    // *****************************

    if (m_cursor == nullptr) return;
    Buffer* cursor = m_cursor;
    m_cursor = m_cursor->m_next;

    while (m_cursor != cursor){
        Buffer* temp = m_cursor;
        m_cursor = m_cursor->m_next;
        temp->m_next = nullptr;
        delete temp;
        m_listSize--;
    }

    m_cursor->m_next = nullptr;
    delete m_cursor;
    m_listSize--;
    m_cursor = nullptr;
}

void BufferList::enqueue(const int& data) {
    // ****************************************************************************
    // Implement enqueue(...) function
    // we always insert at the back, that would be the cursor
    // if the current cursor is full we create a new node as cursor then we insert
    // ****************************************************************************
    try{
        m_cursor->enqueue(data);
    }

    catch (const overflow_error& e) {
        //Set the size to a maximum of MAX_FACTOR
        int size;
        if (MAX_FACTOR < (m_cursor->m_capacity) * INCREASE_FACTOR){ 
            size = MAX_FACTOR;
        }
        else {
            size = (m_cursor->m_capacity) * INCREASE_FACTOR;
        }

        //Create a new buffer and then append to the end of list using cursor
        Buffer* nextBuffer = new Buffer(size);
        m_listSize++;
        nextBuffer->m_next = m_cursor->m_next;
        m_cursor->m_next = nextBuffer;
        m_cursor = nextBuffer;

        //Retry enqueue.
        m_cursor->enqueue(data);
        nextBuffer = nullptr;
    }
}

int BufferList::dequeue() {
    // *****************************
    // Implement dequeue() function
    // *****************************
    int val;
    try{
        val = m_cursor->m_next->dequeue();
    }

    catch (const underflow_error& e){
        if (m_cursor->m_next != m_cursor){
            Buffer* temp = m_cursor->m_next;
            m_cursor->m_next = temp->m_next;
            temp->m_next = nullptr;
            delete temp;
            m_listSize--;
            val = m_cursor->m_next->dequeue();
        }
        else{
            throw underflow_error("Empty buffer list.");
        }
    }
    // A second list should by definition not be empty if the only way its
    // created is if its being added to. In this case, there is no need to 
    // retry the try block using a loop or other shenanigens.

    return val;
}

BufferList::BufferList(const BufferList & rhs){
    // *******************************
    // Implement the copy constructor
    // *******************************


    /*
    The first step to copying the buffer list is unique because the cursor
    needs to be initialized to the beginning of the list. Temporary cursor 
    is an iterator for BufferList. It will keep track of what buffer is to be 
    copied next off of the rhs BufferList.
    */
    Buffer* temp_cursor = rhs.m_cursor->m_next;
    Buffer* firstBuffer = new Buffer(*temp_cursor);
    m_cursor = firstBuffer;
    m_cursor->m_next = m_cursor;


    /*
    After the first buffer has been created and the cursor has been set,
    temporary buffer is updated to point to the next buffer from the rhs.
    The while loop will run as long as the next buffer in line to be copied 
    ISN'T the first buffer which has already been copied. For each iteration,
    a new buffer object is created. The buffer updates to point back to the 
    beginning, the previous buffer is updated to point to the next buffer,
    and then the cursor is updated to point to the most recent buffer.    
    */
    temp_cursor = temp_cursor->m_next;
    while (temp_cursor != rhs.m_cursor->m_next){
        Buffer* nextBuffer = new Buffer(*temp_cursor);
        nextBuffer->m_next = m_cursor->m_next;
        m_cursor->m_next = nextBuffer;
        m_cursor = nextBuffer;

        temp_cursor = temp_cursor->m_next;
    }

    m_listSize = rhs.m_listSize;
    m_minBufCapacity = rhs.m_minBufCapacity;
}

const BufferList & BufferList::operator=(const BufferList & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************
    //Self assignment check.
    if (this == &rhs) return *this;
    
    //The rest of this is the same as the copy constructor.
    clear();
    Buffer* temp_cursor = (rhs.m_cursor->m_next);
    Buffer* firstBuffer = new Buffer(*temp_cursor);
    m_listSize = 1;
    m_cursor = firstBuffer;
    m_cursor->m_next = m_cursor;

   temp_cursor = temp_cursor->m_next;
    while (temp_cursor != rhs.m_cursor->m_next){
        Buffer* nextBuffer = new Buffer(*temp_cursor);
        m_listSize++;
        nextBuffer->m_next = m_cursor->m_next;
        m_cursor->m_next = nextBuffer;
        m_cursor = nextBuffer;

        temp_cursor = temp_cursor->m_next;
    }

    m_minBufCapacity = rhs.m_minBufCapacity;

    //... Besides the return of course.
    return *this;
}

void BufferList::dump(){
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}