#ifndef LESS_THEN_COMPARABLE_H
#define LESS_THEN_COMPARABLE_H

template <typename T>
class less_then_comparable
{
public:
    bool operator==(const T &other) const
    {
        T const &self = static_cast<const T &>(*this);
        return !(self < other) && !(other < self);
    }

    bool operator>(const T &other) const
    {
        T const &self = static_cast<const T &>(*this);
        return other < self;
    }

    bool operator<=(const T &other) const
    {
        T const &self = static_cast<const T &>(*this);
        return !(other < self);
    }

    bool operator>=(const T &other) const
    {
        T const &self = static_cast<const T &>(*this);
        return !(self < other);
    }

    bool operator!=(const T &other) const
    {
        return !(*this == other);
    }
};

#endif