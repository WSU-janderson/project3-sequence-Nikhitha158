
#include "Sequence.h"

// ============================================================================
// Helper: get node at index (throws on invalid)
// ============================================================================
SequenceNode* Sequence::getNode(size_t position) const {
    if (position >= numElts)
        throw std::out_of_range("Invalid index");

    SequenceNode* current = head.get();
    for (size_t i = 0; i < position; ++i) {
        current = current->next.get();
    }
    return current;
}

// ============================================================================
// Constructors / Destructor / Assignment
// ============================================================================
Sequence::Sequence(size_t sz) : head(nullptr), tail(nullptr), numElts(0) {
    for (size_t i = 0; i < sz; ++i)
        push_back(""); // initialize with empty strings
}

Sequence::Sequence(const Sequence& s) : head(nullptr), tail(nullptr), numElts(0) {
    SequenceNode* node = s.head.get();
    while (node) {
        push_back(node->item);
        node = node->next.get();
    }
}

Sequence::~Sequence() {
    clear();
}

Sequence& Sequence::operator=(const Sequence& s) {
    if (this != &s) {
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
// Element access
// ============================================================================
std::string& Sequence::operator[](size_t position) {
    return getNode(position)->item;
}

// ============================================================================
// Modifiers
// ============================================================================
void Sequence::push_back(std::string item) {
    auto newNode = std::make_unique<SequenceNode>(item);
    SequenceNode* newNodePtr = newNode.get();

    if (!head) {
        // Empty list
        head = std::move(newNode);
        tail = newNodePtr;
    } else {
        // Non-empty list
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = newNodePtr;
    }
    ++numElts;
}

void Sequence::pop_back() {
    if (empty())
        throw std::runtime_error("Cannot pop_back from empty sequence");

    if (head.get() == tail) {
        // Only one element in list
        head.reset();
        tail = nullptr;
    } else {
        // Multiple elements
        SequenceNode* newTail = tail->prev;
        newTail->next.reset();  // This deletes the tail node
        tail = newTail;
    }
    --numElts;
}

void Sequence::insert(size_t position, std::string item) {
    if (position > numElts)
        throw std::out_of_range("Invalid index for insert");

    if (position == numElts) {
        // Insert at end
        push_back(item);
        return;
    }

    auto newNode = std::make_unique<SequenceNode>(item);
    SequenceNode* newNodePtr = newNode.get();

    if (position == 0) {
        // Insert at beginning
        newNode->next = std::move(head);
        if (newNode->next) {
            newNode->next->prev = newNodePtr;
        }
        head = std::move(newNode);
        if (!tail) tail = newNodePtr;  // List was empty
    } else {
        // Insert in middle
        SequenceNode* current = getNode(position);
        SequenceNode* prevNode = current->prev;

        newNode->prev = prevNode;
        newNode->next = std::move(prevNode->next);
        newNode->next->prev = newNodePtr;
        prevNode->next = std::move(newNode);
    }
    ++numElts;
}

void Sequence::clear() {
    head.reset();
    tail = nullptr;
    numElts = 0;
}

void Sequence::erase(size_t position) {
    erase(position, 1);
}

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
                // Middle node - connect prev to next
                toDelete->next->prev = toDelete->prev;
                toDelete->prev->next = std::move(toDelete->next);
            } else {
                // Last node
                toDelete->prev->next.reset();
                tail = toDelete->prev;
            }
        } else {
            // First node
            if (toDelete->next) {
                // First of multiple nodes
                toDelete->next->prev = nullptr;
                head = std::move(toDelete->next);
            } else {
                // Only node
                head.reset();
                tail = nullptr;
            }
        }

        ++deleted;
        --numElts;
    }
}

// ============================================================================
// Accessors
// ============================================================================
std::string Sequence::front() const {
    if (empty())
        throw std::runtime_error("Sequence is empty");
    return head->item;
}

std::string Sequence::back() const {
    if (empty())
        throw std::runtime_error("Sequence is empty");
    return tail->item;
}

bool Sequence::empty() const {
    return numElts == 0;
}

size_t Sequence::size() const {
    return numElts;
}

// ============================================================================
// Output operator - FIXED to handle empty strings properly
// ============================================================================
std::ostream& operator<<(std::ostream& os, const Sequence& s) {
    os << "<";
    SequenceNode* current = s.head.get();
    bool first = true;

    while (current) {
        // Only print non-empty items to avoid trailing commas
        if (!current->item.empty()) {
            if (!first) os << ", ";
            os << current->item;
            first = false;
        }
        current = current->next.get();
    }
    os << ">";
    return os;
}
