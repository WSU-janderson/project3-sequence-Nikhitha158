#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

// ============================================================================
// SequenceNode  --  doubly linked node using smart pointers
// ============================================================================
class SequenceNode {
public:
    std::string item;
    std::shared_ptr<SequenceNode> next;
    std::weak_ptr<SequenceNode> prev;

    SequenceNode() : item(""), next(nullptr), prev() {}
    SequenceNode(const std::string& value) : item(value), next(nullptr), prev() {}
};

// ============================================================================
// Sequence  --  doubly linked list with random access via traversal
// ============================================================================
class Sequence {
private:
    std::shared_ptr<SequenceNode> head;
    std::weak_ptr<SequenceNode> tail;
    size_t numElts;

    std::shared_ptr<SequenceNode> getNode(size_t position) const;

public:
    // Constructors / Destructor
    Sequence(size_t sz = 0);
    Sequence(const Sequence& s);
    ~Sequence();
    Sequence& operator=(const Sequence& s);

    // Element access
    std::string& operator[](size_t position);

    // Modifiers
    void push_back(std::string item);
    void pop_back();
    void insert(size_t position, std::string item);
    void clear();
    void erase(size_t position);
    void erase(size_t position, size_t count);

    // Accessors
    std::string front() const;
    std::string back() const;
    bool empty() const;
    size_t size() const;

    // Sort by memory location (for grading spec)
    std::weak_ptr<SequenceNode> sortByMemoryLocation(bool ascending = true);

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Sequence& s);
};

#endif
