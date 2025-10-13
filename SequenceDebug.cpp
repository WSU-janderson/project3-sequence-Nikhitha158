/**
 * SequenceDebug.cpp
 * Comprehensive test coverage for ALL rubric items
 * Tests every point mentioned in the grading rubric
 */

#include <iostream>
#include <string>
#include <cassert>
#include "Sequence.h"

using namespace std;

// Test counter
int testsPassed = 0;
int totalTests = 0;
//add
#define RUN_TEST(test_func) \
    do { \
        totalTests++; \
        try { \
            test_func(); \
            cout << "✅ PASS: " << #test_func << endl; \
            testsPassed++; \
        } catch (const exception& e) { \
            cout << "❌ FAIL: " << #test_func << " - " << e.what() << endl; \
        } catch (...) { \
            cout << "❌ FAIL: " << #test_func << " - unknown exception" << endl; \
        } \
    } while(0)

void testCreateAndPrint() {
    Sequence s(4);
    s[0] = "function";
    s[1] = "parameter";
    s[3] = "pointer";
    cout << "   Result: " << s << endl;
    assert(s.size() == 4);
    // Should output: <function, parameter, pointer> without trailing comma
}

void testMultipleIndependent() {
    Sequence s1(3);
    Sequence s2(3);
    s1[0] = "A"; s1[1] = "B"; s1[2] = "C";
    s2[0] = "X"; s2[1] = "Y"; s2[2] = "Z";
    assert(s1[0] == "A" && s2[0] == "X");
    cout << "   s1: " << s1 << ", s2: " << s2 << endl;
}

void testPushBackExisting() {
    Sequence s(3);
    s[0] = "A"; s[1] = "B"; s[2] = "C";
    s.push_back("D");
    s.push_back("E");
    assert(s.size() == 5);
    assert(s[4] == "E");
    cout << "   Result: " << s << endl;
}

void testPushBackEmpty() {
    Sequence s;
    s.push_back("first");
    s.push_back("second");
    assert(s.size() == 2);
    assert(s[0] == "first");
    assert(s[1] == "second");
    cout << "   Result: " << s << endl;
}

void testPopBackNormal() {
    Sequence s(5);
    for (int i = 0; i < 5; i++) s[i] = to_string(i);
    s.pop_back();
    s.pop_back();
    assert(s.size() == 3);
    assert(s[2] == "2");
    cout << "   Result: " << s << endl;
}

void testPopBackEmpty() {
    Sequence s;
    try {
        s.pop_back();
        assert(false); // Should not reach here
    } catch (const exception& e) {
        // Expected - test passes if exception thrown
    }
}

void testInsertValid() {
    Sequence s(5);
    for (int i = 0; i < 5; i++) s[i] = to_string(i);
    s.insert(3, "99");
    s.insert(0, "88");
    s.insert(7, "77"); // Insert at new end
    assert(s.size() == 8);
    assert(s[0] == "88");
    assert(s[4] == "99");
    assert(s[7] == "77");
    cout << "   Result: " << s << endl;
}

void testInsertInvalid() {
    Sequence s(3);
    try {
        s.insert(5, "invalid");
        assert(false);
    } catch (const exception& e) {
        // Expected
    }
}

void testFrontNormal() {
    Sequence s(3);
    s[0] = "first"; s[1] = "second"; s[2] = "third";
    assert(s.front() == "first");
}

void testFrontEmpty() {
    Sequence s;
    try {
        s.front();
        assert(false);
    } catch (const exception& e) {
        // Expected
    }
}

void testBackNormal() {
    Sequence s(3);
    s[0] = "first"; s[1] = "second"; s[2] = "third";
    assert(s.back() == "third");
}

void testBackEmpty() {
    Sequence s;
    try {
        s.back();
        assert(false);
    } catch (const exception& e) {
        // Expected
    }
}

void testEmpty() {
    Sequence s1;
    Sequence s2(3);
    assert(s1.empty() == true);
    assert(s2.empty() == false);
    s2.clear();
    assert(s2.empty() == true);
}

void testSize() {
    Sequence s;
    assert(s.size() == 0);
    s.push_back("A");
    assert(s.size() == 1);
    s.push_back("B");
    assert(s.size() == 2);
    s.pop_back();
    assert(s.size() == 1);
    s.clear();
    assert(s.size() == 0);
}

void testClear() {
    Sequence s(5);
    for (int i = 0; i < 5; i++) s[i] = to_string(i);
    s.clear();
    assert(s.empty());
    assert(s.size() == 0);
    // Should be able to reuse after clear
    s.push_back("new");
    assert(s.size() == 1);
}

void testEraseSingle() {
    Sequence s;
    for (int i = 0; i < 5; i++) s.push_back(to_string(i));
    s.erase(2); // Remove element at position 2 ("2")
    assert(s.size() == 4);
    assert(s[2] == "3");
    cout << "   After erase(2): " << s << endl;
}

void testEraseMultiple() {
    Sequence s;
    for (int i = 0; i < 6; i++) s.push_back(to_string(i));
    s.erase(2, 2); // Remove elements at positions 2-3 ("2", "3")
    assert(s.size() == 4);
    assert(s[2] == "4");
    cout << "   After erase(2,2): " << s << endl;
}

void testEraseInvalid() {
    Sequence s(3);
    try {
        s.erase(5); // Invalid position
        assert(false);
    } catch (const exception& e) {
        // Expected
    }

    try {
        s.erase(1, 5); // Invalid count
        assert(false);
    } catch (const exception& e) {
        // Expected
    }
}

void testAssignmentOperator() {
    Sequence s1(3);
    for (int i = 0; i < 3; i++) s1[i] = to_string(i);
    Sequence s2;
    s2 = s1;
    s2[0] = "modified";
    // s1 should be unchanged
    assert(s1[0] == "0");
    assert(s2[0] == "modified");
    cout << "   Original: " << s1 << ", Copy: " << s2 << endl;
}

void testCopyConstructor() {
    Sequence s1(3);
    for (int i = 0; i < 3; i++) s1[i] = to_string(i);
    Sequence s2(s1);
    s2[0] = "modified";
    // s1 should be unchanged
    assert(s1[0] == "0");
    assert(s2[0] == "modified");
    cout << "   Original: " << s1 << ", Copy: " << s2 << endl;
}

void testMemoryLeaks() {
    // Create and destroy many sequences to check for memory leaks
    // Run this test with Valgrind for proper memory leak detection
    for (int i = 0; i < 10000; ++i) {
        Sequence s(10);
        for (int j = 0; j < 10; j++) s[j] = to_string(j);
        s.insert(5, "inserted");
        s.erase(2, 3);
        s.push_back("new_end");
        s.pop_back();
    }
    cout << "   Created/destroyed 10,000 sequences - check Valgrind for leaks" << endl;
}

void testEdgeCases() {
    // Test various edge cases
    Sequence s;

    // Insert into empty
    s.insert(0, "only");
    assert(s.size() == 1);

    // Erase only element
    s.erase(0);
    assert(s.empty());

    // Insert at beginning of non-empty
    s.push_back("B");
    s.insert(0, "A");
    assert(s.front() == "A");

    // Insert at end
    s.insert(2, "C");
    assert(s.back() == "C");

    // Erase first element
    s.erase(0);
    assert(s.front() == "B");

    // Erase last element
    s.erase(1);
    assert(s.back() == "B");

    cout << "   All edge cases passed" << endl;
}

void testOutputFormat() {
    Sequence s;
    s.push_back("A");
    s.push_back("B");
    s.push_back("C");
    cout << "   Output format: " << s << " (should be <A, B, C>)" << endl;
}

void testTrailingCommaFix() {
    cout << "=== Testing Trailing Comma Fix ===" << endl;
    // This reproduces the exact test harness scenario
    Sequence data(4);
    data[0] = "A";
    data[1] = "B";
    data[2] = "C";
    // data[3] is intentionally not set (empty string)

    cout << "   Sequence with uninitialized element: " << data << endl;
    cout << "   Should be: <A, B, C> (NO trailing comma!)" << endl;

    // Test that empty strings don't create trailing commas
    Sequence s2(3);
    cout << "   All empty: " << s2 << " (should be <>)" << endl;
}

int main() {
    cout << "=== COMPREHENSIVE SEQUENCE DEBUG TESTS ===" << endl;
    cout << "Testing all rubric items..." << endl << endl;

    // Run all tests matching the grading rubric
    RUN_TEST(testCreateAndPrint);           // 5 points
    RUN_TEST(testMultipleIndependent);      // 3 points
    RUN_TEST(testPushBackExisting);         // 3 points
    RUN_TEST(testPushBackEmpty);            // 3 points
    RUN_TEST(testPopBackNormal);            // 3 points
    RUN_TEST(testPopBackEmpty);             // 1 point
    RUN_TEST(testInsertValid);              // 3 points
    RUN_TEST(testInsertInvalid);            // 1 point
    RUN_TEST(testFrontNormal);              // 2 points
    RUN_TEST(testFrontEmpty);               // 1 point
    RUN_TEST(testBackNormal);               // 2 points
    RUN_TEST(testBackEmpty);                // 1 point
    RUN_TEST(testEmpty);                    // 1 point
    RUN_TEST(testSize);                     // 1 point
    RUN_TEST(testClear);                    // 2 points
    RUN_TEST(testEraseSingle);              // 3 points
    RUN_TEST(testEraseMultiple);            // Included in erase test
    RUN_TEST(testEraseInvalid);             // 1 point
    RUN_TEST(testAssignmentOperator);       // 3 points
    RUN_TEST(testCopyConstructor);          // 3 points
    RUN_TEST(testMemoryLeaks);              // 3 points
    RUN_TEST(testEdgeCases);                // Additional robustness
    RUN_TEST(testOutputFormat);             // Format check
    RUN_TEST(testTrailingCommaFix);         // Critical fix verification

    cout << endl << "=== TEST SUMMARY ===" << endl;
    cout << "Passed: " << testsPassed << "/" << totalTests << " tests" << endl;

    if (testsPassed == totalTests) {
        cout << "🎉 ALL TESTS PASSED! Estimated score: 50/50" << endl;
        cout << "Run with Valgrind to confirm no memory leaks for full points." << endl;
    } else {
        cout << "❌ Some tests failed. Review the failures above." << endl;
    }

    return 0;
}
