#include <iostream>
#include <vector>
#pragma once

//defining class for LinkedList and respective Nodes
template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node();
        Node(T data);
    };

    //construction/destruction
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();

    //behaviors
    void PrintForward();
    void PrintReverse();
    void PrintForwardRecursive(Node* node_pointer);
    void PrintReverseRecursive(Node* node_pointer);

    //accessors
    int NodeCount();
    void FindAll(std::vector<Node*>& vect, T& searchVal); //check return type
    typename LinkedList<T>::Node* Find(const T& data) const;
    typename LinkedList<T>::Node* GetNode(const int index);
    typename LinkedList<T>::Node* GetNode(const int index) const;
    typename LinkedList<T>::Node* Head();
    typename LinkedList<T>::Node* Tail();

    //insertions
    void AddHead(const T& addVal);
    void AddTail(const T& tailVal);
    void AddNodesHead(const T array[], const int& size);
    void AddNodesTail(const T array[], const int& size);
    void InsertAfter(Node* ptr, T data);
    void InsertBefore(Node* ptr, T data);
    void InsertAt(T data, int index);

    //removals
    bool RemoveHead();
    bool RemoveTail();
    int Remove(T data);
    bool RemoveAt(int index);
    void Clear();

    //operators
    T operator[](const int index);
    LinkedList operator=(const LinkedList& other);
    bool operator==(const LinkedList& other);

private:
    Node* head;
    Node* tail;
    int current_size = 0;
};

//default constructor
template <typename T>
LinkedList<T>::LinkedList() {
    //creates a headptr.
    head = nullptr;
    tail = nullptr;
}

//copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head, tail = nullptr;
    int counter = 0;
    Node* otherIterator = other.head;
    //iterate through nodes until size matches
    while (counter != other.current_size) {
        AddTail(otherIterator->data);
        otherIterator = otherIterator->next;
        counter++;
    }
}

//default node constructor
template <typename T>
LinkedList<T>::Node::Node() {
    next = nullptr;
    prev = nullptr;
}

//parametrized node constructor
template <typename T>
LinkedList<T>::Node::Node(T data) {
    this->data = data;
    next = nullptr;
    prev = nullptr;
}

//destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    Node* deallocator = head;
    while (deallocator != nullptr) {
        Node* temp = deallocator->next;
        delete deallocator;
        deallocator = temp;
    }
}

//PrintForward
template <typename T>
void LinkedList<T>::PrintForward() {
    Node* iterator = head;
    while (iterator != nullptr) {
        std::cout << iterator->data << std::endl;
        iterator = iterator->next;
    }
}

//PrintReverse
template <typename T>
void LinkedList<T>::PrintReverse() {
    T arr[current_size];
    Node* iterator = head;
    int counter = 0;
    while (iterator != nullptr) {
        arr[counter] = iterator->data;
        counter++;
        iterator = iterator->next;
    }
    for (int i = current_size-1; i >= 0; i--) {
        std::cout << arr[i] << std::endl;
    }
    //iterate through all nodes backwards and print values
}

//PrintForwardRecursive
template <typename T>
void LinkedList<T>::PrintForwardRecursive(Node* node_pointer) {
    Node* iterator = head;
    while (iterator != nullptr) {
        if (node_pointer == iterator) {
            std::cout << iterator->data << std::endl;
            PrintForwardRecursive(node_pointer->next);
        }
        iterator = iterator->next;
    }
}

//PrintReverseRecursive
template <typename T>
void LinkedList<T>::PrintReverseRecursive(Node* node_pointer) {
    Node* iterator = head;
    while (iterator != nullptr) {
        if (node_pointer == iterator) {
            std::cout << iterator->data << std::endl;
            PrintReverseRecursive(node_pointer->prev);
        }
        iterator = iterator->next;
    }
}

//NodeCount
template <typename T>
int LinkedList<T>::NodeCount() {
    return current_size;
}

//FindAll
template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& vect, T& searchVal) {
    Node* iterator = head;
    while (iterator != nullptr) {
        if (iterator->data == searchVal) {
            vect.push_back(iterator);
        }
        iterator = iterator->next;
    }
}

//Find
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
    Node* iterator = head;
    while (iterator != nullptr) {
        if (iterator->data == data) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return nullptr;
}

//GetNode
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(const int index) {
    Node* iterator = head;
    int loop_index = 0;
    if (index >= current_size || index < 0) {
        throw std::out_of_range("index out of range!");
    }
    else {
        while (iterator != nullptr && loop_index <= index) {
            if (loop_index == index) {
                return iterator;
            }
            loop_index++;
            iterator = iterator->next;
        }
    }
}

//non-const
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(const int index) const {
    Node* iterator = head;
    int loop_index = 0;
    if (index >= current_size || index < 0) {
        throw std::out_of_range("index out of range!");
    }
    else {
        while (iterator != nullptr && loop_index <= index) {
            if (loop_index == index) {
                return iterator;
            }
            loop_index++;
            iterator = iterator->next;
        }
    }
}

//getHead
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

//getTail
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    //assigns temporary Node to head
    Node* tailChecker = head;
    //iterates through nodes until end reached
    while (tailChecker != nullptr) {
        //returns the temporary pointer once "next" is nullptr
        if (tailChecker->next == nullptr) {
            return tailChecker;
        }
        tailChecker = tailChecker->next;
    }
}

//AddHead
template <typename T>
void LinkedList<T>::AddHead(const T& addVal) {
    if (current_size == 0) {
        head = new Node(addVal);
    }
    else {
        if (tail == nullptr) {
            //new node created
            Node* newNode = new Node(addVal);
            //assigning new node to head
            newNode->next = head;
            head->prev = newNode;
            head = tail;
            newNode->prev = nullptr;
            //declaring that new node is now head
            head = newNode;
        }
        else {
            //new node created
            Node* newNode = new Node(addVal);
            //assigning new node to head
            newNode->next = head;
            head->prev = newNode;
            newNode->prev = nullptr;
            //declaring that new node is now head
            head = newNode;
        }

    }
    current_size++;
}

//AddTail
template <typename T>
void LinkedList<T>::AddTail(const T& tailVal) {
    if (current_size == 0) {
        head = new Node(tailVal);
    }
    else {
        //new node created
        Node* newNode = new Node(tailVal);
        //temporary pointer
        Node* temporaryNode = head;
        while (temporaryNode != nullptr) {
            if (temporaryNode->next == nullptr) {
                temporaryNode->next = newNode;
                newNode->prev = temporaryNode;
                newNode->next = nullptr;
                tail = newNode;
                break;
            }
            temporaryNode = temporaryNode->next;
        }
    }
    current_size++;
}

//AddNodesHead
template <typename T>
void LinkedList<T>::AddNodesHead(const T array[], const int& size) {
    for (int i = size-1; i >= 0; i--) {
        AddHead(array[i]);
    }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T array[], const int& size) {
    for (int i = 0; i < size; i++) {
        AddTail(array[i]);
    }
}

//InsertAfter
template <typename T>
void LinkedList<T>::InsertAfter(Node* ptr, T data) {
    Node* iterator = head;
    while (iterator != nullptr) {
        if (iterator == ptr) {
            Node* newNode = new Node(data);
            newNode->next = iterator->next;
            iterator->next = newNode;
            newNode->prev = iterator;
            break;
        }
        iterator = iterator->next;
    }
}

//InsertBefore
template <typename T>
void LinkedList<T>::InsertBefore(Node* ptr, T data) {
    Node* iterator = head;
    while (iterator != nullptr) {
        if (iterator == ptr) {
            Node* newNode = new Node(data);
            iterator->prev->next = newNode;
            iterator->prev = newNode;
            newNode->next = iterator;
            newNode->prev = iterator->prev;
            break;
        }
        iterator = iterator->next;
    }
}

//InsertAt
template <typename T>
void LinkedList<T>::InsertAt(T data, int index) {
    Node* iterator = head;
    int counter = 0;
    if (index > current_size+1) {
        throw std::runtime_error("error");
    }
    while (counter != index) {
        counter++;
        iterator = iterator->next;
    }
    if (index == 0) {
        AddHead(data);
    }
    else {
        InsertBefore(iterator, data);
        current_size++;
    }
    if (index == current_size-1) {
        AddTail(data);
        current_size--;
    }
}


//RemoveHead
template <typename T>
bool LinkedList<T>::RemoveHead() {
    Node* iterator = head;
    if (current_size > 0) {
        head = head->next;
        delete iterator;
        current_size--;
        return true;
    }
}

//RemoveTail
template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (current_size == 1) {
        delete tail;
        tail = nullptr;
        head = nullptr;
        current_size = 0;
        return true;
    }
    if (current_size > 0) {
        Node* tempTail = tail;
        tempTail->prev->next = nullptr;
        tail = tail->prev;
        delete tempTail;
        current_size--;
        return true;
    }
}

//Remove
template <typename T>
int LinkedList<T>::Remove(T data) {
    Node* iterator = head;
    int count = 0;
    while (iterator != nullptr) {
        if (iterator->data == data) {
            Node* beforeNode = iterator->prev;
            beforeNode->next = iterator->next;
            iterator->next->prev = beforeNode;
            delete iterator;
            current_size--;
            iterator = beforeNode->next;
            count++;
        }
        iterator = iterator->next;
    }
    return count;
}

//RemoveAt function removes a node at a particular location and returns a bool indicating success/failure
template <typename T>
bool LinkedList<T>::RemoveAt(int index) {
    Node* iterator = head;
    int counter = 0;
    if (index > current_size) {
        return false;
    }
    if (index == 0) {
        RemoveHead();
        return true;
    }
    if (index == counter) {
        RemoveTail();
        return true;
    }
    while (iterator != nullptr) {
        if (counter == index) {
            Node* beforeNode = iterator->prev;
            beforeNode->next = iterator->next;
            iterator->next->prev = beforeNode;
            delete iterator;
            current_size--;
            iterator = beforeNode->next;
            return true;
        }
        counter++;
        iterator = iterator->next;
    }
}

//Clear
template <typename T>
void LinkedList<T>::Clear() {
    Node* deallocator = head;
    while (deallocator != nullptr) {
        Node* temp = deallocator->next;
        delete deallocator;
        current_size--;
        deallocator = temp;
    }
    head = nullptr;
    tail = nullptr;
    current_size = 0;
}

//[] operator
template <typename T>
T LinkedList<T>::operator[](const int index) {
    Node* iterator = head;
    int loop_index = 0;
    if (index >= current_size || index < 0) {
        throw std::out_of_range("index out of range!");
    }
    else {
        while (iterator != nullptr && loop_index <= index) {
            if (loop_index == index) {
                return iterator->data;
            }
            loop_index++;
            iterator = iterator->next;
        }
    }
}

//= operator
template <typename T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList& other) {
    //deallocate previous data
    Node* deallocator = head;
    while (deallocator != nullptr) {
        Node* temp = deallocator->next;
        delete deallocator;
        deallocator = temp;
    }
    //assign new values to "this" and return
    head, tail = nullptr;
    current_size = 0;
    int counter = 0;
    Node* otherIterator = other.head;
    while (counter != other.current_size) {
        AddTail(otherIterator->data);
        otherIterator = otherIterator->next;
        counter++;
    }
    return *this;
}

//== operator
template <typename T>
bool LinkedList<T>::operator==(const LinkedList& other) {
    int original_size = other.current_size;
    int counter = 0;
    Node* iterator = other.head;
    Node* og_iterator = head;
    while (iterator != nullptr) {
        if (og_iterator->data == iterator->data) {
            counter++;
        }
        iterator = iterator->next;
        og_iterator = og_iterator->next;
    }
    if (counter == original_size) {
        return true;
    }
}
