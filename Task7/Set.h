#ifndef SET_H
#define SET_H

template <typename Object>
class Set
{
public:
    virtual ~Set() {}

    virtual void Add(const Object &obj) = 0;
    virtual void Delete(const Object &obj) = 0;
    virtual bool In(const Object &obj) const = 0;
    virtual Set<Object> *Unification(const Set<Object> &other) const = 0;
    virtual Set<Object> *Intersection(const Set<Object> &other) const = 0;
    virtual int GetSize() const = 0;
};

#endif