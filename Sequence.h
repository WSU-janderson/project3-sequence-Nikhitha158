#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <memory>      // For managing the memory
#include <string>      // For using text strings like "hello world"
#include <stdexcept>   // For error handling and throwing exceptions


// SequenceNode - A single item in our linked list
class SequenceNode {
public:
    // The actual data stored in this node
    std::string item;

     /* Pointer to the next node in the list
       Uses unique_ptr so it automatically deletes the next node when this node is deleted */
    std::unique_ptr<SequenceNode> next;

     /* Pointer to the previous node in the list
    Uses raw pointer because previous node already owns this one */
    SequenceNode* prev;

    // Default constructor - creates an empty node
    SequenceNode() : item(""), next(nullptr), prev(nullptr) {}

    // Constructor with value - creates a node with specific data
    SequenceNode(const std::string& value) : item(value), next(nullptr), prev(nullptr) {}

    /* Disable copying to prevent accidentally creating duplicate nodes
    This helps avoid memory management issues */
    SequenceNode(const SequenceNode&) = delete;
    SequenceNode& operator=(const SequenceNode&) = delete;
};

// ============================================================================
// Sequence - A doubly linked list
// ============================================================================
class Sequence {
private:
    // Pointer to the first node in the list
    std::unique_ptr<SequenceNode> head;

    // Pointer to the last node in the list
    SequenceNode* tail;

    // Count of how many items are currently in the list
    size_t numElts;

    // Helper function to find a node at a specific position
    SequenceNode* getNode(size_t position) const;

public:
    // CONSTRUCTORS AND DESTRUCTOR

    // Create a new Sequence - can be empty or with a specific number of empty slots
    Sequence(size_t sz = 0);

    // Copy constructor - makes a complete duplicate of another Sequence
    Sequence(const Sequence& s);

    // Destructor - automatically cleans up all memory when Sequence is destroyed
    ~Sequence();

    // Assignment operator - makes this Sequence a copy of another one
    Sequence& operator=(const Sequence& s);


    // ELEMENT ACCESS

    // Get or change an element at a specific position, like array[index]
    std::string& operator[](size_t position);

    // MODIFIERS - Functions that change the Sequence


    // Add a new item to the end of the Sequence
    void push_back(std::string item);

    // Remove the last item from the Sequence
    void pop_back();

    // Insert a new item at a specific position
    void insert(size_t position, std::string item);

    // Remove all items from the Sequence
    void clear();

    // Remove one item at a specific position
    void erase(size_t position);

    // Remove multiple items starting from a specific position
    void erase(size_t position, size_t count);


    // ACCESSORS - Functions that look at but don't change the Sequence


    // Get the first item in the Sequence
    std::string front() const;

    // Get the last item in the Sequence
    std::string back() const;

    // Check if the Sequence is empty (has no items)
    bool empty() const;

    // Get the number of items in the Sequence
    size_t size() const;


    // OUTPUT


    // Print the Sequence to the screen
    friend std::ostream& operator<<(std::ostream& os, const Sequence& s);
};

#endif
