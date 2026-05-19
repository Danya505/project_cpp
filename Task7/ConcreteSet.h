#ifndef CONCRETE_SET_H
#define CONCRETE_SET_H

#include "Set.h"
#include "SetImplementation.h"
#include "ArraySet.h"
#include "BinaryTreeSet.h"
#include <algorithm>

template <typename Object>
class ConcreteSet : public Set<Object>
{
private:
    SetImplementation<Object> *impl;

    void switchImplementation()
    {
        if (impl->shouldSwitchToBinaryTree() && dynamic_cast<ArraySetImpl<Object> *>(impl))
        {
            SetImplementation<Object> *newImpl = new BinaryTreeSetImpl<Object>();

            const Object *elements = impl->getElements();
            for (int i = 0; i < impl->size(); i++)
            {
                newImpl->insert(elements[i]);
            }

            delete impl;
            impl = newImpl;
        }

        else if (impl->shouldSwitchToArray() && dynamic_cast<BinaryTreeSetImpl<Object> *>(impl))
        {
            SetImplementation<Object> *newImpl = new ArraySetImpl<Object>();

            const Object *elements = impl->getElements();
            for (int i = 0; i < impl->size(); i++)
            {
                newImpl->insert(elements[i]);
            }

            delete impl;
            impl = newImpl;
        }
    }

public:
    ConcreteSet()
    {
        impl = new ArraySetImpl<Object>();
    }

    explicit ConcreteSet(SetImplementation<Object> *initialImpl) : impl(initialImpl) {}

    ConcreteSet(const ConcreteSet &other)
    {
        impl = other.impl->clone();
    }

    ~ConcreteSet()
    {
        delete impl;
    }

    void Add(const Object &obj) override
    {
        impl->insert(obj);
        switchImplementation();
    }

    void Delete(const Object &obj) override
    {
        impl->remove(obj);
        switchImplementation();
    }

    bool In(const Object &obj) const override
    {
        return impl->contains(obj);
    }

    int GetSize() const override
    {
        return impl->size();
    }

    Set<Object> *Unification(const Set<Object> &other) const override
    {
        const ConcreteSet<Object> *otherConcrete = dynamic_cast<const ConcreteSet<Object> *>(&other);
        if (!otherConcrete)
            return nullptr;

        SetImplementation<Object> *newImpl = impl->clone();

        const Object *otherElements = otherConcrete->impl->getElements();
        for (int i = 0; i < otherConcrete->impl->size(); i++)
        {
            newImpl->insert(otherElements[i]);
        }

        ConcreteSet<Object> *result = new ConcreteSet<Object>(newImpl);
        return result;
    }

    Set<Object> *Intersection(const Set<Object> &other) const override
    {
        const ConcreteSet<Object> *otherConcrete = dynamic_cast<const ConcreteSet<Object> *>(&other);
        if (!otherConcrete)
            return nullptr;

        SetImplementation<Object> *newImpl = new ArraySetImpl<Object>();

        const Object *myElements = impl->getElements();
        for (int i = 0; i < impl->size(); i++)
        {
            if (otherConcrete->In(myElements[i]))
            {
                newImpl->insert(myElements[i]);
            }
        }

        ConcreteSet<Object> *result = new ConcreteSet<Object>(newImpl);
        return result;
    }
};

#endif