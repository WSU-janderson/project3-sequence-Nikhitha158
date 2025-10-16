/* Name : Nikhitha Palakurla
Project Name and Description : Sequence Project
construct a Sequence class that supports random access like an array, but also
allows dynamic insertion and removal of new elements */

#include "Sequence.h"

//get node at a specific index (throws exception if index is invalid)
SequenceNode* Sequence::getNode(size_t position) const {
    if (position >= numElts)
        throw std::out_of_range("Invalid index");

    // Start from the head and move forward 'position' times
    SequenceNode* current = head.get();
    for (size_t i = 0; i < position; ++i) {
        current = current->next.get();
    }
    return current;
}

// ============================================================================
// Constructors / Destructor / Assignment
// ============================================================================

// Default + sized constructor
// Creates an empty list, then fills it with 'sz' empty string nodes
Sequence::Sequence(size_t sz) : head(nullptr), tail(nullptr), numElts(0) {
    for (size_t i = 0; i < sz; ++i)
        push_back(""); // Adds empty strings
}

// Copy constructor: makes a deep copy of another Sequence
Sequence::Sequence(const Sequence& s) : head(nullptr), tail(nullptr), numElts(0) {
    SequenceNode* node = s.head.get();
    while (node) {
        push_back(node->item);
        node = node->next.get();
    }
}

// Destructor: automatically clears all nodes
Sequence::~Sequence() {
    clear();
}

// Assignment operator: clears current list and copies another Sequence
Sequence& Sequence::operator=(const Sequence& s) {
    if (this != &s) {  // Avoid self-assignment
        clear();
        SequenceNode* node = s.head.get();
        while (node) {
            push_back(node->item);
            node = node->next.get();
        }
    }
    return *this;
}

// ============================================================================
// Element Access
// ============================================================================

// Returns a reference to the item at the given index
std::string& Sequence::operator[](size_t position) {
    return getNode(position)->item;
}

// ============================================================================
// Modifiers (functions that change the list)
// ============================================================================

// Adds a new node to the end of the list
void Sequence::push_back(std::string item) {
    auto newNode = std::make_unique<SequenceNode>(item);
    SequenceNode* newNodePtr = newNode.get();

    if (!head) {
        // Case 1: list is empty
        head = std::move(newNode);
        tail = newNodePtr;
    } else {
        // Case 2: list already has elements
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = newNodePtr;
    }
    ++numElts;
}

// Removes the last node in the list
void Sequence::pop_back() {
    if (empty())
        throw std::runtime_error("Cannot pop_back from empty sequence");

    if (head.get() == tail) {
        // Case 1: only one element
        head.reset();
        tail = nullptr;
    } else {
        // Case 2: more than one element
        SequenceNode* newTail = tail->prev;
        newTail->next.reset();  // Deletes the last node
        tail = newTail;
    }
    --numElts;
}

// Inserts a new node at a specific position
void Sequence::insert(size_t position, std::string item) {
    if (position > numElts)
        throw std::out_of_range("Invalid index for insert");

    if (position == numElts) {
        // Insert at the end of the list
        push_back(item);
        return;
    }

    auto newNode = std::make_unique<SequenceNode>(item);
    SequenceNode* newNodePtr = newNode.get();

    if (position == 0) {
        // Case 1: insert at beginning
        newNode->next = std::move(head);
        if (newNode->next) {
            newNode->next->prev = newNodePtr;
        }
        head = std::move(newNode);
        if (!tail) tail = newNodePtr;  // List was empty before
    } else {
        // Case 2: insert in middle
        SequenceNode* current = getNode(position);
        SequenceNode* prevNode = current->prev;

        newNode->prev = prevNode;
        newNode->next = std::move(prevNode->next);
        newNode->next->prev = newNodePtr;
        prevNode->next = std::move(newNode);
    }
    ++numElts;
}

// Removes all elements from the list
void Sequence::clear() {
    head.reset();
    tail = nullptr;
    numElts = 0;
}

// Erase a single element at a given position
void Sequence::erase(size_t position) {
    erase(position, 1);  // Delegate to the multi-element erase
}

// Erase 'count' elements starting at 'position'
void Sequence::erase(size_t position, size_t count) {
    if (position >= numElts)
        throw std::out_of_range("Invalid erase position");
    if (count == 0)
        return;
    if (position + count > numElts)
        throw std::out_of_range("Invalid erase range");

    size_t deleted = 0;
    while (deleted < count) {
        SequenceNode* toDelete = getNode(position);

        if (toDelete->prev) {
            // Not the first node
            if (toDelete->next) {
                // Middle node — link prev and next
                toDelete->next->prev = toDelete->prev;
                toDelete->prev->next = std::move(toDelete->next);
            } else {
                // Last node — update tail
                toDelete->prev->next.reset();
                tail = toDelete->prev;
            }
        } else {
            // First node
            if (toDelete->next) {
                // Update head to next node
                toDelete->next->prev = nullptr;
                head = std::move(toDelete->next);
            } else {
                // Only node in list
                head.reset();
                tail = nullptr;
            }
        }

        ++deleted;
        --numElts;
    }
}

// ============================================================================
// Accessors (functions that only read data)
// ============================================================================

// Returns the first item in the sequence
std::string Sequence::front() const {
    if (empty())
        throw std::runtime_error("Sequence is empty");
    return head->item;
}

// Returns the last item in the sequence
std::string Sequence::back() const {
    if (empty())
        throw std::runtime_error("Sequence is empty");
    return tail->item;
}

// Checks if the list has zero elements
bool Sequence::empty() const {
    return numElts == 0;
}

// Returns how many elements are in the list
size_t Sequence::size() const {
    return numElts;
}

// ============================================================================
// Output operator - prints the Sequence like <A, B, C>
// ============================================================================

std::ostream& operator<<(std::ostream& os, const Sequence& s) {
    os << "<";
    SequenceNode* current = s.head.get();
    bool first = true; // Used to avoid a leading comma

    while (current) {
        if (!current->item.empty()) {  // Skip empty strings
            if (!first) os << ", ";
            os << current->item;
            first = false;
        }
        current = current->next.get();
    }
    os << ">";
    return os;
}
