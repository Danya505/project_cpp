#include <iostream>
#include <type_traits>
#include "typelist.h"
#include "typelist_detail.h"

struct A
{
};
struct B
{
};
struct C
{
};
struct D
{
};
struct E
{
};

int main()
{
    using namespace typelist;

    using List1 = TypeList<A, B, C>;
    using List2 = TypeList<A, B, C>;
    using List3 = TypeList<A, B, D>;
    using Empty = TypeList<>;

    static_assert(List1{} == List2{}, "Same lists");
    static_assert(List1{} != List3{}, "Different lists");

    static_assert(size(List1{}) == 3);
    static_assert(size_v<List1> == 3);
    static_assert(size(Empty{}) == 0);

    static_assert(std::is_same_v<decltype(type_at<0>(List1{})), A>);
    static_assert(std::is_same_v<decltype(type_at<1>(List1{})), B>);
    static_assert(std::is_same_v<decltype(type_at<2>(List1{})), C>);
    static_assert(std::is_same_v<type_at_t<0, List1>, A>);
    static_assert(std::is_same_v<type_at_t<1, List1>, B>);
    static_assert(std::is_same_v<type_at_t<2, List1>, C>);

    static_assert(contains<A>(List1{}));
    static_assert(contains<B>(List1{}));
    static_assert(contains<C>(List1{}));
    static_assert(!contains<D>(List1{}));
    static_assert(contains_v<A, List1>);
    static_assert(!contains_v<D, List1>);

    static_assert(index_of<A>(List1{}) == 0);
    static_assert(index_of<B>(List1{}) == 1);
    static_assert(index_of<C>(List1{}) == 2);
    static_assert(index_of_v<B, List1> == 1);

    static_assert(push_front<A>(TypeList<B, C>{}) == TypeList<A, B, C>{});
    using PushedFront = push_front_t<List1, D>;
    static_assert(std::is_same_v<PushedFront, TypeList<D, A, B, C>>);

    static_assert(push_back<D>(List1{}) == TypeList<A, B, C, D>{});
    using PushedBack = push_back_t<List1, D>;
    static_assert(std::is_same_v<PushedBack, TypeList<A, B, C, D>>);

    static_assert(pop_front(List1{}) == TypeList<B, C>{});
    using Popped = pop_front_t<List1>;
    static_assert(std::is_same_v<Popped, TypeList<B, C>>);

    static_assert(pop_front(push_front<D>(List1{})) == List1{});
    static_assert(push_front<D>(pop_front(List1{})) == TypeList<D, B, C>{});

    static_assert(push_front<A>(Empty{}) == TypeList<A>{});
    static_assert(push_back<A>(Empty{}) == TypeList<A>{});
    static_assert(pop_front(TypeList<A>{}) == TypeList<>{});

    using BigList = TypeList<int, double, char, float, long, short, A, B, C, D, E>;
    static_assert(size(BigList{}) == 11);

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}