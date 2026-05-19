#ifndef ARRAY_SET_IMPL_H
#define ARRAY_SET_IMPL_H

#include "SetImplementation.h"
#include <vector>
#include <algorithm>

template <typename Object>
class ArraySetImpl : public SetImplementation<Object>
{
private:
    std::vector<Object> data;
    static const int MAX_ARRAY_SIZE = 100;

public:
    ArraySetImpl() {}

    ArraySetImpl(const ArraySetImpl &other) : data(other.data) {}

    void insert(const Object &obj) override
    {
        if (contains(obj))
            return;
        data.push_back(obj);
    }

    void remove(const Object &obj) override
    {
        auto it = std::find(data.begin(), data.end(), obj);
        if (it != data.end())
        {
            data.erase(it);
        }
    }

    bool contains(const Object &obj) const override
    {
        return std::find(data.begin(), data.end(), obj) != data.end();
    }

    int size() const override
    {
        return data.size();
    }

    bool isEmpty() const override
    {
        return data.empty();
    }

    void clear() override
    {
        data.clear();
    }

    SetImplementation<Object> *clone() const override
    {
        return new ArraySetImpl<Object>(*this);
    }

    const Object *getElements() const override
    {
        return data.data();
    }

    bool shouldSwitchToBinaryTree() const override
    {
        return size() > MAX_ARRAY_SIZE;
    }

    bool shouldSwitchToArray() const override
    {
        return false;
    }
};

#endif