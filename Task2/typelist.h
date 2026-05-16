#ifndef TYPELIST_H
#define TYPELIST_H

#include "typelist_detail.h"

namespace typelist
{
    template <typename... Types>
    struct TypeList
    {
        static constexpr size_t size = sizeof...(Types);
    };

    template <typename... Ts, typename... Us>
    constexpr bool operator==(TypeList<Ts...>, TypeList<Us...>)
    {
        return false;
    }

    template <typename... Ts>
    constexpr bool operator==(TypeList<Ts...>, TypeList<Ts...>)
    {
        return true;
    }

    template <typename... Ts, typename... Us>
    constexpr bool operator!=(TypeList<Ts...> a, TypeList<Us...> b)
    {
        return !(a == b);
    }

    template <size_t Index, typename... Types>
    constexpr auto type_at(TypeList<Types...>)
    {
        static_assert(Index < sizeof...(Types), "Index out of bounds");
        using T = typename typelist_detail::type_at_helper<Index, Types...>::type;
        return T{};
    }

    template <typename... Types>
    constexpr size_t size(TypeList<Types...>)
    {
        return sizeof...(Types);
    }

    template <typename T, typename... Types>
    constexpr bool contains(TypeList<Types...>)
    {
        return (std::is_same_v<T, Types> || ...);
    }

    template <typename T, typename... Types>
    constexpr int index_of(TypeList<Types...>)
    {
        int result = -1;
        int idx = 0;
        ((std::is_same_v<T, Types> ? (result = idx, 0) : (++idx, 0)), ...);
        return result;
    }

    template <typename T, typename... Ts>
    constexpr auto push_front(TypeList<Ts...>)
    {
        return TypeList<T, Ts...>{};
    }

    template <typename T, typename... Ts>
    constexpr auto push_back(TypeList<Ts...>)
    {
        return TypeList<Ts..., T>{};
    }

    template <typename T, typename... Ts>
    constexpr auto pop_front(TypeList<T, Ts...>)
    {
        return TypeList<Ts...>{};
    }

    template <size_t Index, typename List>
    using type_at_t = decltype(type_at<Index>(List{}));

    template <typename List>
    inline constexpr size_t size_v = size(List{});

    template <typename T, typename List>
    inline constexpr bool contains_v = contains<T>(List{});

    template <typename T, typename List>
    inline constexpr int index_of_v = index_of<T>(List{});

    template <typename List, typename T>
    using push_front_t = decltype(push_front<T>(List{}));

    template <typename List, typename T>
    using push_back_t = decltype(push_back<T>(List{}));

    template <typename List>
    using pop_front_t = decltype(pop_front(List{}));

}

#endif