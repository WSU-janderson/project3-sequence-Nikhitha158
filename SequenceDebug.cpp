#include <iostream>
#include <string>
#include <cassert>
#include "Sequence.h"

using namespace std;

// ============================================================================
// Helper function to check test results
// ============================================================================
void check(bool condition, const string& testName) {
    if (condition) {
        cout << "PASS: " << testName << endl;
    } else {
        cout << "FAIL: " << testName << endl;
    }
}

// ============================================================================
// TEST 1: Create and Print
// Creates a sequence, fills some values, and checks printing.
// ============================================================================
void testCreateAndPrint() {
    cout << "\n[TEST] Create and Print" << endl;
    Sequence s(4);
    s[0] = "A";
    s[1] = "B";
    s[2] = "C";
    s[3] = "D";
    cout << "Sequence: " << s << endl;
    check(s.size() == 4, "Size should be 4");
}

// ============================================================================
// TEST 2: Independent Sequences
// Creates two separate sequences and ensures they are independent.
// ============================================================================
void testIndependentSequences() {
    cout << "\n[TEST] Independent Sequences" << endl;
    Sequence s1(3);
    Sequence s2(3);
    s1[0] = "A"; s1[1] = "B"; s1[2] = "C";
    s2[0] = "X"; s2[1] = "Y"; s2[2] = "Z";
    cout << "s1: " << s1 << ", s2: " << s2 << endl;
    check(s1[0] == "A" && s2[0] == "X", "Sequences store values separately");
}

// ============================================================================
// TEST 3: push_back
// Adds items to the end of the list.
// ============================================================================
void testPushBack() {
    cout << "\n[TEST] push_back" << endl;
    Sequence s;
    s.push_back("A");
    s.push_back("B");
    s.push_back("C");
    cout << "Sequence: " << s << endl;
    check(s.size() == 3, "Size after push_back");
}

// ============================================================================
// TEST 4: pop_back
// Removes items from the end.
// ============================================================================
void testPopBack() {
    cout << "\n[TEST] pop_back" << endl;
    Sequence s;
    s.push_back("A");
    s.push_back("B");
    s.push_back("C");
    s.pop_back();
    cout << "Sequence after pop: " << s << endl;
    check(s.size() == 2, "Size after pop_back");
}

// ============================================================================
// TEST 5: insert
// Inserts items at specific positions.
// ============================================================================
void testInsert() {
    cout << "\n[TEST] insert" << endl;
    Sequence s;
    s.push_back("A");
    s.push_back("C");
    s.insert(1, "B"); // Insert between A and C
    cout << "Sequence: " << s << endl;
    check(s[1] == "B", "Insert in middle works");
}

// ============================================================================
// TEST 6: erase
// Removes items from the list.
// ============================================================================
void testErase() {
    cout << "\n[TEST] erase" << endl;
    Sequence s;
    s.push_back("A");
    s.push_back("B");
    s.push_back("C");
    s.erase(1); // remove B
    cout << "Sequence: " << s << endl;
    check(s[1] == "C", "Erase middle element");
}

// ============================================================================
// TEST 7: front and back
// Tests access to first and last items.
// ============================================================================
void testFrontBack() {
    cout << "\n[TEST] front() and back()" << endl;
    Sequence s;
    s.push_back("A");
    s.push_back("B");
    s.push_back("C");
    cout << "Front: " << s.front() << ", Back: " << s.back() << endl;
    check(s.front() == "A" && s.back() == "C", "Front and back access");
}

// ============================================================================
// TEST 8: clear, empty, and size
// Clears all items and checks size/empty.
// ============================================================================
void testClearEmptySize() {
    cout << "\n[TEST] clear(), empty(), and size()" << endl;
    Sequence s;
    s.push_back("A");
    s.push_back("B");
    s.clear();
    cout << "After clear: " << s << endl;
    check(s.empty(), "Sequence should be empty after clear");
    check(s.size() == 0, "Size should be 0 after clear");
}

// ============================================================================
// TEST 9: assignment operator
// Copies one sequence into another.
// ============================================================================
void testAssignment() {
    cout << "\n[TEST] Assignment operator" << endl;
    Sequence s1;
    s1.push_back("A");
    s1.push_back("B");

    Sequence s2;
    s2 = s1;
    s2[0] = "X";

    cout << "Original: " << s1 << ", Copy: " << s2 << endl;
    check(s1[0] == "A", "Original unchanged after assignment");
}

// ============================================================================
// TEST 10: copy constructor
// Creates a new sequence as a copy of another.
// ============================================================================
void testCopyConstructor() {
    cout << "\n[TEST] Copy constructor" << endl;
    Sequence s1;
    s1.push_back("A");
    s1.push_back("B");

    Sequence s2(s1);
    s2[0] = "X";

    cout << "Original: " << s1 << ", Copy: " << s2 << endl;
    check(s1[0] == "A", "Copy constructor makes independent copy");
}

// ============================================================================
// TEST 11: Trailing comma fix
// Makes sure printing doesn’t show an extra comma.
// ============================================================================
void testOutputFormat() {
    cout << "\n[TEST] Output format (no trailing comma)" << endl;
    Sequence s(3);
    s[0] = "A";
    s[1] = "B";
    // s[2] left empty on purpose
    cout << "Sequence: " << s << endl;
    cout << "(Expected: <A, B>)" << endl;
}

// ============================================================================
// MAIN FUNCTION
// Runs all tests in order and prints a summary.
// ============================================================================
int main() {
    cout << "SIMPLE SEQUENCE DEBUG TESTS" << endl;

    testCreateAndPrint();
    testIndependentSequences();
    testPushBack();
    testPopBack();
    testInsert();
    testErase();
    testFrontBack();
    testClearEmptySize();
    testAssignment();
    testCopyConstructor();
    testOutputFormat();

    cout << "\n All tests finished!" << endl;
    return 0;
}
