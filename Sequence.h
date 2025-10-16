#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <memory>                   // Provides smart pointers
#include <string>                   // Provides std::string class
#include <stdexcept>                // Provides exception classes (runtime_error, out_of_range)
// SequenceNode - Node of a doubly-linked list using shared/weak pointers

class SequenceNode {
public:
    std::string item;                               // Data value stored in this node
    std::shared_ptr<SequenceNode> next;             // Shared pointer to next node
    std::weak_ptr<SequenceNode> prev;               // Weak pointer to previous node

    SequenceNode() : item(""), next(nullptr), prev() {}                  // Default constructor initializes empty node
    SequenceNode(const std::string& value) : item(value), next(nullptr), prev() {} // Constructor initializes with value
};
// Sequence - Doubly linked list supporting random access and dynamic operations

class Sequence {
private:
    std::shared_ptr<SequenceNode> head;             // Pointer to first node
    std::weak_ptr<SequenceNode> tail;               // Pointer to last node
    size_t numElts;                                 // Tracks number of elements in list

    std::shared_ptr<SequenceNode> getNode(size_t position) const; // Returns pointer to node at index

public:
    // Constructors / Destructor
    Sequence(size_t sz = 0);                        // Creates list with given number of empty nodes
    Sequence(const Sequence& s);                    // Copy constructor creates deep copy of another Sequence
    ~Sequence();                                    // Destructor releases all resources
    Sequence& operator=(const Sequence& s);         // Assignment operator performs deep copy

    // Element access
    std::string& operator[](size_t position);       // Provides read/write access to element at index

    // Modifiers
    void push_back(std::string item);               // Adds new element to end of list
    void pop_back();                                // Removes last element from list
    void insert(size_t position, std::string item); // Inserts element at given index
    void clear();                                   // Removes all elements from list
    void erase(size_t position);                    // Removes single element at index
    void erase(size_t position, size_t count);      // Removes multiple elements starting at index

    // Accessors
    std::string front() const;                      // Returns first element (throws if empty)
    std::string back() const;                       // Returns last element (throws if empty)
    bool empty() const;                             // Checks if list contains no elements
    size_t size() const;                            // Returns current number of elements

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Sequence& s); // Prints formatted list to output stream
};

#endif // SEQUENCE_H
