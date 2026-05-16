#include <iostream>
#include <cassert>
#include "counter.h"
#include "less_then_comparable.h"

class Number : public less_then_comparable<Number>, public counter<Number>
{
public:
    Number(int value) : m_value{value} {}

    int value() const { return m_value; }

    bool operator<(const Number &other) const
    {
        return m_value < other.m_value;
    }

private:
    int m_value;
};

int main()
{
    Number one{1};
    Number two{2};
    Number three{3};
    Number four{4};

    assert(one >= one);
    assert(one <= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);
    assert(one != two);
    assert(three >= two);
    assert(four > three);
    assert(one <= three);

    assert(!(one > two));
    assert(!(two < one));
    assert(!(three == four));
    assert(!(two != two));

    std::cout << "All assertions passed successfully!\n";
    std::cout << "Number objects created: " << counter<Number>::howManyCreated() << std::endl;
    std::cout << "Number objects alive: " << counter<Number>::howManyAlive() << std::endl;

    {
        Number five{5};
        Number six{6};
        assert(counter<Number>::howManyAlive() == 6);
        std::cout << "Inside block - alive: " << counter<Number>::howManyAlive() << std::endl;
    }

    assert(counter<Number>::howManyAlive() == 4);

    std::cout << "Final total created objects: " << counter<Number>::howManyCreated() << std::endl;
    std::cout << "All tests passed!\n";

    return 0;
}