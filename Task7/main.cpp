#include "ConcreteSet.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T>
void PrintSet(Set<T> *set, const string &name)
{
    cout << name << " size: " << set->GetSize() << endl;
}

template <typename T>
void TestBasicOperations()
{
    cout << "\n=== 1. Test Basic Operations ===" << endl;

    ConcreteSet<T> set;

    // Add elements
    for (int i = 0; i < 10; i++)
    {
        set.Add(i);
    }
    cout << "Added 0-9, size = " << set.GetSize() << " (expected 10)" << endl;

    // Add duplicate
    set.Add(5);
    cout << "Added duplicate 5, size = " << set.GetSize() << " (expected 10)" << endl;

    // Check In
    cout << "Contains 3: " << set.In(3) << " (expected 1)" << endl;
    cout << "Contains 99: " << set.In(99) << " (expected 0)" << endl;

    // Delete
    set.Delete(5);
    cout << "Deleted 5, size = " << set.GetSize() << " (expected 9)" << endl;
    cout << "Contains 5: " << set.In(5) << " (expected 0)" << endl;

    // Delete non-existent
    set.Delete(999);
    cout << "Deleted 999, size = " << set.GetSize() << " (expected 9)" << endl;
}

void TestAutoSwitch()
{
    cout << "\n=== 2. Test Auto Switch Array -> Tree ===" << endl;

    ConcreteSet<int> set;

    // Add elements until switch threshold (100+)
    for (int i = 0; i < 120; i++)
    {
        set.Add(i);
    }

    cout << "Added 120 elements, size = " << set.GetSize() << endl;

    // Проверим что все элементы на месте
    bool allFound = true;
    for (int i = 0; i < 120; i++)
    {
        if (!set.In(i))
        {
            allFound = false;
            cout << "Missing: " << i << endl;
        }
    }
    cout << "All elements present after switch: " << (allFound ? "YES" : "NO") << endl;

    // Test reverse switch (Tree -> Array)
    cout << "\n=== 3. Test Auto Switch Tree -> Array ===" << endl;

    for (int i = 0; i < 80; i++)
    {
        set.Delete(i);
    }

    cout << "Deleted first 80 elements, size = " << set.GetSize() << " (expected 40)" << endl;

    // Check remaining elements (80-119)
    bool remainingFound = true;
    for (int i = 80; i < 120; i++)
    {
        if (!set.In(i))
        {
            remainingFound = false;
            cout << "Missing: " << i << endl;
        }
    }
    cout << "Remaining elements present: " << (remainingFound ? "YES" : "NO") << endl;
}

void TestUnification()
{
    cout << "\n=== 4. Test Unification ===" << endl;

    ConcreteSet<int> set1;
    ConcreteSet<int> set2;

    // Set1: 0,2,4,6,8
    for (int i = 0; i < 10; i += 2)
    {
        set1.Add(i);
    }

    // Set2: 1,3,5,7,9
    for (int i = 1; i < 10; i += 2)
    {
        set2.Add(i);
    }

    cout << "Set1 size: " << set1.GetSize() << " (evens 0-8)" << endl;
    cout << "Set2 size: " << set2.GetSize() << " (odds 1-9)" << endl;

    Set<int> *unionSet = set1.Unification(set2);

    cout << "Union size: " << unionSet->GetSize() << " (expected 10)" << endl;

    // Check all numbers 0-9
    bool allInUnion = true;
    for (int i = 0; i < 10; i++)
    {
        if (!unionSet->In(i))
        {
            allInUnion = false;
            cout << "Union missing: " << i << endl;
        }
    }
    cout << "Union contains all 0-9: " << (allInUnion ? "YES" : "NO") << endl;

    delete unionSet;
}

void TestIntersection()
{
    cout << "\n=== 5. Test Intersection ===" << endl;

    ConcreteSet<int> set1;
    ConcreteSet<int> set2;

    // Set1: 0-9
    for (int i = 0; i < 10; i++)
    {
        set1.Add(i);
    }

    // Set2: 5-14
    for (int i = 5; i < 15; i++)
    {
        set2.Add(i);
    }

    cout << "Set1 size: " << set1.GetSize() << " (0-9)" << endl;
    cout << "Set2 size: " << set2.GetSize() << " (5-14)" << endl;

    Set<int> *intersectionSet = set1.Intersection(set2);

    cout << "Intersection size: " << intersectionSet->GetSize() << " (expected 5)" << endl;

    // Should have 5,6,7,8,9
    bool correctIntersection = true;
    for (int i = 5; i < 10; i++)
    {
        if (!intersectionSet->In(i))
        {
            correctIntersection = false;
            cout << "Intersection missing: " << i << endl;
        }
    }

    // Should NOT have others
    for (int i = 0; i < 5; i++)
    {
        if (intersectionSet->In(i))
        {
            correctIntersection = false;
            cout << "Intersection has extra: " << i << endl;
        }
    }

    cout << "Intersection correct: " << (correctIntersection ? "YES" : "NO") << endl;

    delete intersectionSet;
}

void TestStringSet()
{
    cout << "\n=== 6. Test with strings (different type) ===" << endl;

    ConcreteSet<string> set;

    set.Add("apple");
    set.Add("banana");
    set.Add("cherry");
    set.Add("apple"); // duplicate

    cout << "Size: " << set.GetSize() << " (expected 3)" << endl;
    cout << "Contains 'banana': " << set.In("banana") << " (expected 1)" << endl;
    cout << "Contains 'grape': " << set.In("grape") << " (expected 0)" << endl;

    set.Delete("banana");
    cout << "After delete 'banana', size: " << set.GetSize() << " (expected 2)" << endl;
}

void TestEdgeCases()
{
    cout << "\n=== 7. Test Edge Cases ===" << endl;

    ConcreteSet<int> emptySet;
    cout << "Empty set size: " << emptySet.GetSize() << " (expected 0)" << endl;
    cout << "Empty set contains 0: " << emptySet.In(0) << " (expected 0)" << endl;

    // Delete from empty
    emptySet.Delete(100);
    cout << "Delete from empty, size: " << emptySet.GetSize() << " (expected 0)" << endl;

    // Union with empty
    ConcreteSet<int> nonEmpty;
    for (int i = 0; i < 5; i++)
        nonEmpty.Add(i);

    Set<int> *unionWithEmpty = nonEmpty.Unification(emptySet);
    cout << "Union with empty size: " << unionWithEmpty->GetSize() << " (expected 5)" << endl;

    // Intersection with empty
    Set<int> *intersectWithEmpty = nonEmpty.Intersection(emptySet);
    cout << "Intersection with empty size: " << intersectWithEmpty->GetSize() << " (expected 0)" << endl;

    delete unionWithEmpty;
    delete intersectWithEmpty;

    // Copy constructor / clone
    ConcreteSet<int> original;
    for (int i = 0; i < 10; i++)
        original.Add(i);

    ConcreteSet<int> copy(original); // copy constructor
    cout << "Copy size: " << copy.GetSize() << " (expected 10)" << endl;

    copy.Delete(5);
    cout << "Original still has 5: " << original.In(5) << " (expected 1)" << endl;
    cout << "Copy has 5 after delete: " << copy.In(5) << " (expected 0)" << endl;
}

int main()
{
    cout << "========== BRIDGE PATTERN SET TESTS ==========" << endl;

    TestBasicOperations<int>();
    TestAutoSwitch();
    TestUnification();
    TestIntersection();
    TestStringSet();
    TestEdgeCases();

    cout << "\n========== ALL TESTS COMPLETED ==========" << endl;

    return 0;
}