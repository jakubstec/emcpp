#pragma once
#include <iostream>
#include <memory>
#include "Box.h"

using namespace std;

class Container
{
    // Exercise 2: Use smart pointer.
    // done
    unique_ptr<Box> pbox;

public:
    static bool verbose;
    Container(int content) : pbox(make_unique<Box>(content))
    {
        if (verbose)
            cout << "Creating Container" << endl;
    }
    Container(const Container &container) : pbox(make_unique<Box>(*container.pbox))
    {
        if (verbose)
            cout << "Creating copy of Container\n";
    }
    Container &operator=(const Container &container)
    {
        if (this != &container)
        {
            if (verbose)
                cout << "Copying Container\n";
            pbox = make_unique<Box>(*container.pbox);
        }
        return *this;
    }
    ~Container()
    {
        if (verbose)
            cout << "Destroying Container \n";
        pbox.reset();
    }

    // moves semantics!
    Container(Container &&container) : pbox(move(container.pbox))
    {
        if (verbose)
            cout << "Move constructor\n";
    }

    Container &operator=(Container &&container)
    {
        if (this != &container)
        {
            if (verbose)
                cout << "Destroying Container \n";
            pbox = move(container.pbox);
        }
        return *this;
    }

    friend Container operator+(const Container &p1, const Container &p2);
    friend std::ostream &operator<<(std::ostream &out, const Container &p)
    {
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container &p1, const Container &p2)
{
    Container suma(p1.pbox->getContent() + p2.pbox->getContent());
    return suma;
}
