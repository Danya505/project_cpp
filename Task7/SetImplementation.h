#ifndef SET_IMPLEMENTATION_H
#define SET_IMPLEMENTATION_H

template <typename Object>
class SetImplementation
{
public:
    virtual ~SetImplementation() {}

    virtual void insert(const Object &obj) = 0;
    virtual void remove(const Object &obj) = 0;
    virtual bool contains(const Object &obj) const = 0;
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual SetImplementation<Object> *clone() const = 0;
    virtual const Object *getElements() const = 0;
    virtual bool shouldSwitchToBinaryTree() const = 0; // исправлено
    virtual bool shouldSwitchToArray() const = 0;
};

#endif