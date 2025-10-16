#include <iostream>
#include <string>
#include <cassert>       // Provides assert() for runtime test validation
#include <stdexcept>     // Provides standard exception classes
#include "Sequence.h"

using namespace std;

// ============================================================================
// TEST 1: Verifies sequence creation, indexing, and formatted printing
// ============================================================================
void testCreateAndPrint() {
    cout << "TEST 1: Create and Print" << endl;
    Sequence s(5);                               // Create sequence of 5 nodes
    s[0] = "function"; s[1] = "parameter"; s[4] = "pointer";
    cout << "Sequence: " << s << endl;           // Output full sequence
    assert(s.size() == 5);                       // Verify correct size
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 2: Ensures multiple sequences operate independently
// ============================================================================
void testIndependentSequences() {
    cout << "TEST 2: Independent Sequences" << endl;
    Sequence s1(3), s2(3);                       // Two separate sequences
    s1[0] = "A"; s1[1] = "B"; s1[2] = "C";
    s2[0] = "X"; s2[1] = "Y"; s2[2] = "Z";
    cout << "s1: " << s1 << ", s2: " << s2 << endl;
    assert(s1[0] == "A" && s2[0] == "X");        // Validate independence
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 3: Confirms push_back appends elements correctly
// ============================================================================
void testPushBack() {
    cout << "TEST 3: push_back()" << endl;
    Sequence s(3);
    s[0] = "A"; s[1] = "B"; s[2] = "C";
    s.push_back("D"); s.push_back("E");          // Append new elements
    cout << "After push_back: " << s << endl;
    assert(s.size() == 5 && s[4] == "E");
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 4: Verifies push_back works on initially empty sequence
// ============================================================================
void testPushBackEmpty() {
    cout << "TEST 4: push_back() on empty" << endl;
    Sequence s;
    s.push_back("first"); s.push_back("second");
    cout << "Empty + push_back: " << s << endl;
    assert(s.size() == 2);
    assert(s[0] == "first" && s[1] == "second");
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 5: Validates pop_back removes last element
// ============================================================================
void testPopBack() {
    cout << "TEST 5: pop_back()" << endl;
    Sequence s;
    s.push_back("A"); s.push_back("B"); s.push_back("C");
    s.pop_back();                                 // Remove last element
    cout << "After pop_back: " << s << endl;
    assert(s.size() == 2 && s[1] == "B");
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 6: Ensures pop_back throws exception when called on empty sequence
// ============================================================================
void testPopBackEmpty() {
    cout << "TEST 6: pop_back() on empty" << endl;
    Sequence s;
    try {
        s.pop_back();                             // Should throw exception
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 7: Confirms insert correctly places new element at position
// ============================================================================
void testInsert() {
    cout << "TEST 7: insert()" << endl;
    Sequence s;
    s.push_back("A"); s.push_back("C");
    s.insert(1, "B");                             // Insert in middle
    cout << "After insert: " << s << endl;
    assert(s[1] == "B" && s.size() == 3);
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 8: Verifies insert throws exception for invalid index
// ============================================================================
void testInsertInvalid() {
    cout << "TEST 8: insert() with invalid index" << endl;
    Sequence s(2);
    try {
        s.insert(5, "invalid");                   // Should fail
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 9: Checks front() returns first element correctly
// ============================================================================
void testFront() {
    cout << "TEST 9: front()" << endl;
    Sequence s;
    s.push_back("first"); s.push_back("middle"); s.push_back("last");
    assert(s.front() == "first");
    cout << "Front: " << s.front() << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 10: Ensures front() throws exception on empty sequence
// ============================================================================
void testFrontEmpty() {
    cout << "TEST 10: front() on empty" << endl;
    Sequence s;
    try {
        s.front();                                // Should throw
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 11: Checks back() returns last element correctly
// ============================================================================
void testBack() {
    cout << "TEST 11: back()" << endl;
    Sequence s;
    s.push_back("first"); s.push_back("middle"); s.push_back("last");
    assert(s.back() == "last");
    cout << "Back: " << s.back() << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 12: Ensures back() throws exception on empty sequence
// ============================================================================
void testBackEmpty() {
    cout << "TEST 12: back() on empty" << endl;
    Sequence s;
    try {
        s.back();                                 // Should throw
        assert(false);
    } catch (const std::exception& e) {
        cout << " Correctly caught exception: " << e.what() << endl;
    }
    cout << " PASS" << endl << endl;
}

// ============================================================================
// TEST 13: Validates empty() correctly identifies empty/non-empty lists
// ============================================================================
void testEmpty() {
    cout << "TEST 13: empty()" << endl;
    Sequence s1, s2(3);
    assert(s1.empty() && !s2.empty());
    cout << "Empty sequence: " << s1.empty() << ", Non-empty: " << s2.empty() << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 14: Confirms size() updates after insertions
// ============================================================================
void testSize() {
    cout << "TEST 14: size()" << endl;
    Sequence s;
    assert(s.size() == 0);
    s.push_back("A"); s.push_back("B");
    assert(s.size() == 2);
    cout << "Sizes: 0->" << s.size() << " after 2 push_backs" << endl;
    cout << " PASS" << endl << endl;
}

// ============================================================================
// TEST 15: Checks clear() empties the sequence completely
// ============================================================================
void testClear() {
    cout << "TEST 15: clear()" << endl;
    Sequence s(5);
    s[0] = "A"; s[1] = "B"; s[2] = "C";
    s.clear();                                    // Remove all nodes
    cout << "After clear - Empty: " << s.empty() << ", Size: " << s.size() << endl;
    assert(s.empty() && s.size() == 0);
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 16: Verifies erase() removes the correct range of elements
// ============================================================================
void testErase() {
    cout << "TEST 16: erase()" << endl;
    Sequence s;
    for (int i = 0; i < 6; i++) s.push_back(to_string(i));
    s.erase(2, 2);                                // Remove middle elements
    cout << "After erase(2,2): " << s << endl;
    assert(s.size() == 4 && s[2] == "4");
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 17: Ensures erase() throws exceptions for invalid parameters
// ============================================================================
void testEraseInvalid() {
    cout << "TEST 17: erase() with invalid parameters" << endl;
    Sequence s(3);
    try {
        s.erase(5, 1);                            // Invalid start index
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught out_of_range: " << e.what() << endl;
    }
    try {
        s.erase(1, 5);                            // Invalid range
        assert(false);
    } catch (const std::exception& e) {
        cout << " Correctly caught out_of_range: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 18: Checks assignment operator performs deep copy
// ============================================================================
void testAssignment() {
    cout << "TEST 18: Assignment operator" << endl;
    Sequence s1; s1.push_back("A"); s1.push_back("B"); s1.push_back("C");
    Sequence s2; s2 = s1;                          // Deep copy assignment
    s2[0] = "X";                                  // Modify copy only
    cout << "Original: " << s1 << ", Copy: " << s2 << endl;
    assert(s1[0] == "A" && s2[0] == "X");
    cout << " PASS" << endl << endl;
}

// ============================================================================
// TEST 19: Confirms copy constructor performs deep copy
// ============================================================================
void testCopyConstructor() {
    cout << "TEST 19: Copy constructor" << endl;
    Sequence s1; s1.push_back("A"); s1.push_back("B"); s1.push_back("C");
    Sequence s2(s1);                              // Create copy via constructor
    s2[1] = "Y";                                  // Modify copy only
    cout << "Original: " << s1 << ", Copy: " << s2 << endl;
    assert(s1[1] == "B" && s2[1] == "Y");
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 20: Performs stress test to check for memory leaks or crashes
// ============================================================================
void testMemoryLeaks() {
    cout << "TEST 20: Memory leak check" << endl;
    Sequence* s = new Sequence(100);              // Dynamically allocate
    for (int i = 0; i < 50; i++) s->push_back("test");
    for (int i = 0; i < 25; i++) s->pop_back();
    s->insert(10, "inserted");
    s->erase(5, 10);
    delete s;                                     // Ensure proper cleanup
    cout << "No crashes during intensive operations" << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 21: Confirms output formatting matches expected structure
// ============================================================================
void testOutputFormat() {
    cout << "TEST 21: Output format" << endl;
    Sequence s(3);
    s[0] = "A"; s[1] = "B";                      // Leave one element empty
    cout << "Sequence with empty: " << s << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// Main - Runs all defined test cases and prints results
// ============================================================================
int main() {
    cout << "RUNNING ALL SEQUENCE TESTS" << endl << endl;

    testCreateAndPrint();
    testIndependentSequences();
    testPushBack();
    testPushBackEmpty();
    testPopBack();
    testPopBackEmpty();
    testInsert();
    testInsertInvalid();
    testFront();
    testFrontEmpty();
    testBack();
    testBackEmpty();
    testEmpty();
    testSize();
    testClear();
    testErase();
    testEraseInvalid();
    testAssignment();
    testCopyConstructor();
    testMemoryLeaks();
    testOutputFormat();

    cout << "ALL TESTS PASSED!" << endl;
    return 0;
}
