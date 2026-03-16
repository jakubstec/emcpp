#include <iostream>
#include <algorithm>
#include "MyString.h"
using namespace std;

class String
{
    using string = emcpp::MyString;
    shared_ptr<string> sptr;
    //    using string = std::string;

    /// Store a pointer to dynamically allocated string!

public:
    String();                          /// creates an empty string
    String(const char *str);           /// copy C-string
    String(const String &);            /// no copy
    String operator=(const String &s); /// no copy - czemu nie String& operator=(...)?
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch);
    /// no copy
    char get(int index) const;
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b);
    friend std::ostream &operator<<(std::ostream &out, String s);
};

String::String() : sptr(make_shared<string>()) {}

String::String(const char *str) : sptr(make_shared<string>(str)) {}

String::String(const String &s) : sptr(s.sptr) {}

String String::operator=(const String &s)
{
    if (this != &s)
    {
        this->sptr = s.sptr;
    }
    return *this;
}

void String::set(int index, char ch)
{
    if (index < 0 && index > sptr->size())
        return;

    if (sptr.use_count() > 1)
    {
        sptr = make_shared<string>(*sptr);
    }

    (*sptr)[index] = ch;
}

char String::get(int index) const
{
    if (index < 0 && index > sptr->size())
        return '\0';
    return (*sptr)[index];
}

String operator+(String a, String b)
{
    if (a.sptr->empty())
        return b;
    if (b.sptr->empty())
        return a;
    String new_str;
    new_str.sptr = make_shared<emcpp::MyString>((*a.sptr + *b.sptr).c_str());
    return new_str;
}

std::ostream &operator<<(std::ostream &out, String s)
{
    out << *s.sptr;
    return out;
}