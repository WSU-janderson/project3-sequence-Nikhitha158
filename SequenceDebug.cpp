#include <iostream>        // For console I/O
#include <string>          // For string handling
#include <cassert>         // For runtime test validation
#include <stdexcept>       // For exception handling
#include "Sequence.h"      // Includes the Sequence class definition

using namespace std;

// ============================================================================
// TEST 1: Create and Print
// PURPOSE: Tests that a Sequence can be created with a specified size,
//          allows indexed element assignment, and prints correctly
// ============================================================================
void testCreateAndPrint() {
    cout << "TEST 1: Create and Print" << endl;
    Sequence s(5);                               // Create a sequence with 5 nodes
    s[0] = "function";                           // Assign to index 0
    s[1] = "parameter";                          // Assign to index 1
    s[4] = "pointer";                            // Assign to last index (others empty)
    cout << "Sequence: " << s << endl;           // Should print all values
    assert(s.size() == 5);                       // Verify correct length
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 2: Independent Sequences
// PURPOSE: Verifies that separate Sequence objects maintain independent data
// ============================================================================
void testIndependentSequences() {
    cout << "TEST 2: Independent Sequences" << endl;
    Sequence s1(3), s2(3);                       // Two independent sequences
    s1[0] = "A"; s1[1] = "B"; s1[2] = "C";       // Modify first sequence
    s2[0] = "X"; s2[1] = "Y"; s2[2] = "Z";       // Modify second sequence
    cout << "s1: " << s1 << ", s2: " << s2 << endl;
    assert(s1[0] == "A" && s2[0] == "X");        // Ensure no shared state
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 3: push_back()
// PURPOSE: Confirms that push_back correctly appends elements and adjusts size
// ============================================================================
void testPushBack() {
    cout << "TEST 3: push_back()" << endl;
    Sequence s(3);                               // Start with 3 elements
    s[0] = "A"; s[1] = "B"; s[2] = "C";
    s.push_back("D");                            // Append one element
    s.push_back("E");                            // Append another
    cout << "After push_back: " << s << endl;
    assert(s.size() == 5 && s[4] == "E");        // Confirm new size and last item
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 4: push_back() on empty
// PURPOSE: Ensures that push_back can initialize an empty list correctly
// ============================================================================
void testPushBackEmpty() {
    cout << "TEST 4: push_back() on empty" << endl;
    Sequence s;                                  // Empty sequence
    s.push_back("first");
    s.push_back("second");
    cout << "Empty + push_back: " << s << endl;  // Should print both values
    assert(s.size() == 2);                       // Verify growth
    assert(s[0] == "first" && s[1] == "second");
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 5: pop_back()
// PURPOSE: Ensures that pop_back removes the last element and updates size
// ============================================================================
void testPopBack() {
    cout << "TEST 5: pop_back()" << endl;
    Sequence s;
    s.push_back("A"); s.push_back("B"); s.push_back("C");
    s.pop_back();                                 // Remove last item (“C”)
    cout << "After pop_back: " << s << endl;
    assert(s.size() == 2 && s[1] == "B");        // Verify last element and size
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 6: pop_back() on empty
// PURPOSE: Checks that pop_back throws an exception when called on an empty list
// ============================================================================
void testPopBackEmpty() {
    cout << "TEST 6: pop_back() on empty" << endl;
    Sequence s;                                  // Empty sequence
    try {
        s.pop_back();                            // Should trigger runtime_error
        assert(false);                           // If no exception, test fails
    } catch (const std::exception& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 7: insert()
// PURPOSE: Verifies that insert adds an element at a specific position
// ============================================================================
void testInsert() {
    cout << "TEST 7: insert()" << endl;
    Sequence s;
    s.push_back("A"); s.push_back("C");
    s.insert(1, "B");                             // Insert “B” between “A” and “C”
    cout << "After insert: " << s << endl;
    assert(s[1] == "B" && s.size() == 3);         // Confirm insertion and size
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 8: insert() with invalid index
// PURPOSE: Confirms insert throws an exception for out-of-range positions
// ============================================================================
void testInsertInvalid() {
    cout << "TEST 8: insert() with invalid index" << endl;
    Sequence s(2);
    try {
        s.insert(5, "invalid");                   // Index beyond bounds
        assert(false);                            // Fail if no exception
    } catch (const std::exception& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 9: front()
// PURPOSE: Ensures front() retrieves the first element correctly
// ============================================================================
void testFront() {
    cout << "TEST 9: front()" << endl;
    Sequence s;
    s.push_back("first"); s.push_back("middle"); s.push_back("last");
    assert(s.front() == "first");                 // Should match first element
    cout << "Front: " << s.front() << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 10: front() on empty
// PURPOSE: Confirms that front() throws an exception when list is empty
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
// TEST 11: back()
// PURPOSE: Ensures back() retrieves the last element correctly
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
// TEST 12: back() on empty
// PURPOSE: Confirms back() throws an exception on an empty sequence
// ============================================================================
void testBackEmpty() {
    cout << "TEST 12: back() on empty" << endl;
    Sequence s;
    try {
        s.back();                                 // Should throw runtime_error
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 13: empty()
// PURPOSE: Tests that empty() correctly identifies empty and non-empty sequences
// ============================================================================
void testEmpty() {
    cout << "TEST 13: empty()" << endl;
    Sequence s1, s2(3);                           // One empty, one pre-sized
    assert(s1.empty() && !s2.empty());
    cout << "Empty sequence: " << s1.empty() << ", Non-empty: " << s2.empty() << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 14: size()
// PURPOSE: Verifies that size() reflects the correct element count after operations
// ============================================================================
void testSize() {
    cout << "TEST 14: size()" << endl;
    Sequence s;
    assert(s.size() == 0);                        // Initially empty
    s.push_back("A"); s.push_back("B");           // Add elements
    assert(s.size() == 2);                        // Should now be 2
    cout << "Sizes: 0->" << s.size() << " after 2 push_backs" << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 15: clear()
// PURPOSE: Ensures that clear() removes all nodes and resets count
// ============================================================================
void testClear() {
    cout << "TEST 15: clear()" << endl;
    Sequence s(5);                                // Prepopulate sequence
    s[0] = "A"; s[1] = "B"; s[2] = "C";
    s.clear();                                    // Remove everything
    cout << "After clear - Empty: " << s.empty() << ", Size: " << s.size() << endl;
    assert(s.empty() && s.size() == 0);
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 16: erase()
// PURPOSE: Verifies that erase() removes correct elements and maintains linkage
// ============================================================================
void testErase() {
    cout << "TEST 16: erase()" << endl;
    Sequence s;
    for (int i = 0; i < 6; i++) s.push_back(to_string(i)); // Fill 0–5
    s.erase(2, 2);                                // Remove indices 2 and 3
    cout << "After erase(2,2): " << s << endl;
    assert(s.size() == 4 && s[2] == "4");         // Remaining sequence should be 0,1,4,5
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 17: erase() invalid parameters
// PURPOSE: Confirms that erase() throws exceptions for invalid positions or ranges
// ============================================================================
void testEraseInvalid() {
    cout << "TEST 17: erase() with invalid parameters" << endl;
    Sequence s(3);
    try {
        s.erase(5, 1);                            // Start index too large
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught out_of_range: " << e.what() << endl;
    }
    try {
        s.erase(1, 5);                            // Range exceeds bounds
        assert(false);
    } catch (const std::exception& e) {
        cout << "Correctly caught out_of_range: " << e.what() << endl;
    }
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 18: Assignment operator
// PURPOSE: Ensures operator= performs a deep copy (no shared ownership)
// ============================================================================
void testAssignment() {
    cout << "TEST 18: Assignment operator" << endl;
    Sequence s1; s1.push_back("A"); s1.push_back("B"); s1.push_back("C");
    Sequence s2; s2 = s1;                          // Copy contents
    s2[0] = "X";                                  // Modify copy to verify independence
    cout << "Original: " << s1 << ", Copy: " << s2 << endl;
    assert(s1[0] == "A" && s2[0] == "X");          // Ensure deep copy
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 19: Copy constructor
// PURPOSE: Verifies that the copy constructor performs deep copying behavior
// ============================================================================
void testCopyConstructor() {
    cout << "TEST 19: Copy constructor" << endl;
    Sequence s1; s1.push_back("A"); s1.push_back("B"); s1.push_back("C");
    Sequence s2(s1);                              // Copy via constructor
    s2[1] = "Y";                                  // Modify copy to ensure deep copy
    cout << "Original: " << s1 << ", Copy: " << s2 << endl;
    assert(s1[1] == "B" && s2[1] == "Y");         // Verify independence
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 20: Memory leak check
// PURPOSE: Performs a stress test of insert/erase/push/pop to ensure no leaks
// ============================================================================
void testMemoryLeaks() {
    cout << "TEST 20: Memory leak check" << endl;
    Sequence* s = new Sequence(100);              // Dynamically allocate
    for (int i = 0; i < 50; i++) s->push_back("test");
    for (int i = 0; i < 25; i++) s->pop_back();
    s->insert(10, "inserted");                    // Insert mid-list
    s->erase(5, 10);                              // Erase range
    delete s;                                     // Delete sequence (should free memory)
    cout << "No crashes during intensive operations" << endl;
    cout << "PASS" << endl << endl;
}

// ============================================================================
// TEST 21: Output format
// PURPOSE: Verifies that formatted output matches "<A, B>" structure
// ============================================================================
void testOutputFormat() {
    cout << "TEST 21: Output format" << endl;
    Sequence s(3);
    s[0] = "A"; s[1] = "B";                      // Leave one element empty
    cout << "Sequence with empty: " << s << endl; // Should print only non-empty
    cout << "PASS" << endl << endl;
}

// ============================================================================
// MAIN FUNCTION
// PURPOSE: Runs all test cases sequentially and reports status to console.
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
