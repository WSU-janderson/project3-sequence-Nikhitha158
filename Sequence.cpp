/* Name : Nikhitha Palakurla
Project Name and Description : Sequence Project
construct a Sequence class that supports random access like an array, but also
allows dynamic insertion and removal of new elements */

#include "Sequence.h"  // Include class and node definitions

// ============================================================================
// getNode - returns pointer to node at a given position
// ============================================================================
std::shared_ptr<SequenceNode> Sequence::getNode(size_t position) const {
    if (position >= numElts)                        // Validate index bounds
        throw std::out_of_range("Invalid index");   // Throw if out of range

    auto current = head;                            // Start from head node
    for (size_t i = 0; i < position; ++i)           // Traverse forward to target node
        current = current->next;
    return current;                                 // Return located node
}

// ============================================================================
// Constructors / Destructor / Assignment
// ============================================================================
Sequence::Sequence(size_t sz) : head(nullptr), tail(), numElts(0) {
    for (size_t i = 0; i < sz; ++i)                 // Create sz empty nodes if requested
        push_back("");
}

Sequence::Sequence(const Sequence& s) : head(nullptr), tail(), numElts(0) {
    auto node = s.head;                             // Start copying from source head
    while (node) {                                  // Deep-copy each node
        push_back(node->item);
        node = node->next;
    }
}

Sequence::~Sequence() {
    clear();                                        // Release all nodes on destruction
}

Sequence& Sequence::operator=(const Sequence& s) {
    if (this != &s) {                               // Avoid self-assignment
        clear();                                    // Clear existing nodes
        auto node = s.head;                         // Copy from source sequence
        while (node) {
            push_back(node->item);
            node = node->next;
        }
    }
    return *this;                                   // Enable assignment chaining
}

// ============================================================================
// Element Access
// ============================================================================
std::string& Sequence::operator[](size_t position) {
    return getNode(position)->item;                 // Return reference to element at index
}

// ============================================================================
// Modifiers
// ============================================================================
void Sequence::push_back(std::string item) {
    auto newNode = std::make_shared<SequenceNode>(item); // Create new node for item

    if (!head) {                                   // If list is empty
        head = newNode;                            // New node becomes head
        tail = newNode;                            // And also the tail
    } else {
        auto tailPtr = tail.lock();                // Get strong ref to current tail
        tailPtr->next = newNode;                   // Link new node after tail
        newNode->prev = tailPtr;                   // Set back link to old tail
        tail = newNode;                            // Update tail pointer
    }
    ++numElts;                                     // Increment element count
}

void Sequence::pop_back() {
    if (empty())                                   // Prevent pop on empty list
        throw std::runtime_error("Cannot pop_back from empty sequence");

    auto tailPtr = tail.lock();                    // Get strong reference to tail

    if (head == tailPtr) {                         // If only one element remains
        head.reset();                              // Remove head
        tail.reset();                              // Remove tail
    } else {
        auto prevNode = tailPtr->prev.lock();      // Get previous node
        if (prevNode) prevNode->next.reset();      // Detach last node
        tail = prevNode;                           // Move tail backward
    }
    --numElts;                                     // Decrease element count
}

void Sequence::insert(size_t position, std::string item) {
    if (position > numElts)                        // Validate insert index
        throw std::out_of_range("Invalid index for insert");

    if (position == numElts) {                     // Append if at end
        push_back(item);
        return;
    }

    auto newNode = std::make_shared<SequenceNode>(item); // Create node to insert

    if (position == 0) {                           // Insert at beginning
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (numElts == 0) tail = newNode;          // Update tail if list was empty
    } else {
        auto current = getNode(position);          // Get node currently at position
        auto prevNode = current->prev.lock();      // Get previous node

        newNode->next = current;                   // Link new node before current
        newNode->prev = prevNode;                  // Link back to previous
        if (prevNode) prevNode->next = newNode;    // Update previous node’s next
        current->prev = newNode;                   // Update current node’s prev
    }
    ++numElts;                                     // Update count
}

void Sequence::clear() {
    head.reset();                                  // Release head chain
    tail.reset();                                  // Release tail reference
    numElts = 0;                                   // Reset count
}

void Sequence::erase(size_t position) {
    erase(position, 1);                            // Delegate to range erase
}

void Sequence::erase(size_t position, size_t count) {
    if (position >= numElts)                       // Validate starting index
        throw std::out_of_range("Invalid erase position");
    if (count == 0)                                // Nothing to remove
        return;
    if (position + count > numElts)                // Ensure range is valid
        throw std::out_of_range("Invalid erase range");

    for (size_t i = 0; i < count; ++i) {           // Remove requested nodes
        auto toDelete = getNode(position);         // Locate node to remove
        auto prevNode = toDelete->prev.lock();     // Access previous node
        auto nextNode = toDelete->next;            // Access next node

        if (prevNode)
            prevNode->next = nextNode;             // Skip over deleted node
        else
            head = nextNode;                       // Update head if first removed

        if (nextNode)
            nextNode->prev = prevNode;             // Reconnect backward link
        else
            tail = prevNode;                       // Update tail if last removed

        --numElts;                                 // Decrement size counter
    }
}

// ============================================================================
// Accessors
// ============================================================================
std::string Sequence::front() const {
    if (empty()) throw std::runtime_error("Sequence is empty"); // Check nonempty
    return head->item;                           // Return first element
}

std::string Sequence::back() const {
    if (empty()) throw std::runtime_error("Sequence is empty"); // Check nonempty
    auto tailPtr = tail.lock();                  // Obtain strong ref to tail
    return tailPtr->item;                        // Return last element
}

bool Sequence::empty() const {
    return numElts == 0;                         // True if no elements
}

size_t Sequence::size() const {
    return numElts;                              // Return number of elements
}

// Output operator - prints formatted contents of sequence

std::ostream& operator<<(std::ostream& os, const Sequence& s) {
    os << "<";                                   // Begin list formatting
    auto current = s.head; // Start at first node
    bool first = true;                           // Track comma placement

    while (current) {                            // Traverse all nodes
        if (!current->item.empty()) {            // Skip empty strings
            if (!first) os << ", ";              // Add comma after first element
            os << current->item;                 // Output current item
            first = false;                       // Mark first printed
        }
        current = current->next;                 // Move to next node
    }

    os << ">";                                   // Close list formatting
    return os;                                   // Return output stream
}
