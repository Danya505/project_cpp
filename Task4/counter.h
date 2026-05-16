#ifndef COUNTER_H
#define COUNTER_H

template <typename T>
class counter
{
public:
    counter()
    {
        ++created;
        ++alive;
    }

    counter(const counter &)
    {
        ++created;
        ++alive;
    }

    ~counter()
    {
        --alive;
    }

    static int howManyAlive()
    {
        return alive;
    }

    static int howManyCreated()
    {
        return created;
    }

private:
    static int created;
    static int alive;
};

template <typename T>
int counter<T>::created(0);

template <typename T>
int counter<T>::alive(0);

#endif