#ifndef TYPELIST_DETAIL_H
#define TYPELIST_DETAIL_H

#include <type_traits>

namespace typelist_detail
{

    template <size_t Index, typename... Types>
    struct type_at_helper;

    template <typename First, typename... Rest>
    struct type_at_helper<0, First, Rest...>
    {
        using type = First;
    };

    template <size_t Index, typename First, typename... Rest>
    struct type_at_helper<Index, First, Rest...>
    {
        using type = typename type_at_helper<Index - 1, Rest...>::type;
    };

}

#endif