// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
    : myData()
{
}

string::string(const value_type* const ptr, const size_type count)
    : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;
    if (myData.myRes > 15)
        myData.bx.ptr = new char[myData.myRes + 1];

    std::copy(ptr, ptr + myData.mySize, myData.myPtr());
    myData.myPtr()[myData.mySize] = '\0';

}

string::string(const size_type count, const value_type ch)
    : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16 * 16 + 15);

    if (count >= 16)
        myData.bx.ptr = new char[myData.myRes + 1];

    std::fill_n(myData.myPtr(), count, ch);
    myData.myPtr()[myData.mySize] = '\0';


}

string::string(const string& right)
    : myData()
{
    myData.mySize = right.myData.mySize;
    myData.myRes = (myData.mySize / 16 * 16 + 15);
    if (myData.myRes > 15) {
        myData.bx.ptr = new char[myData.myRes + 1];
    }
    memcpy(myData.myPtr(), right.myData.myPtr(), myData.mySize);
    myData.myPtr()[myData.mySize] = '\0';

}

string::~string()
{
    if (myData.myRes > 15)
        delete[] myData.bx.ptr;
}


string& string::operator=(const string& right)
{
    if (this != &right)
    {
        if (right.myData.mySize > myData.myRes)
        {
            if (myData.myRes > 15)
                delete[] myData.bx.ptr;
            myData.myRes = myData.myRes * 3 / 2;
            if (myData.myRes < (right.myData.mySize / 16) * 16 + 15)
                myData.myRes = (right.myData.mySize / 16) * 16 + 15;

            myData.bx.ptr = new char[myData.myRes];
        }
        for (size_t i = 0; i < right.myData.mySize; i++)
            myData.myPtr()[i] = right.myData.myPtr()[i];

        myData.mySize = right.myData.mySize;
        myData.myPtr()[myData.mySize] = value_type();
    }

    return *this;
}

string& string::operator=(const value_type* const ptr)
{
    size_t count = strlen(ptr);
    if (count > 0)
    {
        if (count > myData.myRes)
        {
            if (myData.myRes > 15)
                delete[] myData.bx.ptr;

            myData.myRes = myData.myRes * 3 / 2;
            if (myData.myRes < (count / 16) * 16 + 15)
                myData.myRes = (count / 16) * 16 + 15;

            myData.bx.ptr = new value_type[myData.myRes]();


        }
        for (size_t i = 0; i < count; i++)
            myData.myPtr()[i] = ptr[i];

        myData.mySize = count;
        myData.myPtr()[myData.mySize] = value_type();
    }

    return *this;
}


string& string::erase(size_t off, size_t count)
{
    if (off < myData.mySize)
    {
        for (size_type i = off; i < myData.mySize - count; i++)
            myData.myPtr()[i] = myData.myPtr()[i + count];

        myData.mySize -= count;

    }

    return *this;
}


void string::clear()
{
    myData.mySize = 0;
    myData.myPtr()[0] = value_type();
}

string::iterator string::begin()
{
    return iterator(myData.myPtr());
}

string::const_iterator string::begin() const
{
    return const_iterator(myData.myPtr());
}

string::iterator string::end()
{
    return iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::const_iterator string::end() const
{
    return const_iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::reference string::operator[](size_type off)
{
    // check for off out-of-range error
    if (off > myData.mySize)
    {
        cout << "\nstring subscript out of range\n";
        system("pause");
        exit(1); // terminate program; off out of range
    }

    return myData.myPtr()[off]; // returns copy of this element
}

string::const_reference string::operator[](size_type off) const
{
    // check for off out-of-range error
    if (off > myData.mySize)
    {
        cout << "\nstring subscript out of range\n";
        system("pause");
        exit(1); // terminate program; off out of range
    }

    return myData.myPtr()[off]; // returns copy of this element
}

string::const_pointer string::data() const
{
    return myData.myPtr();
}

string::size_type string::size() const
{
    return myData.mySize;
}

string::size_type string::find(value_type ch, size_type off) const
{
    while (off < myData.mySize)
    {
        if (myData.myPtr()[off] == ch)
            return off;
        off++;
    }

    return string::npos;
}

string::size_type string::find(const value_type* ptr, size_type off) const
{
    size_t count = strlen(ptr);

    while (off < myData.mySize)
    {
        if (memcmp(myData.myPtr() + off, ptr, count) == 0)
            return off;
        off++;
    }

    return string::npos;
}

string string::substr(size_type off, size_type count) const
{
    if (count > myData.mySize - off)
        count = myData.mySize - off;

    string temp(count, char());
    if (off < myData.mySize) {
        for (size_type i = 0; i < count; i++)
            temp.myData.myPtr()[i] = myData.myPtr()[off + i];

    }

    return temp;
}


// compare [ 0, size() ) with right for equality
bool string::equal(const string& right) const
{
    if (size() != right.size())
        return false;

    for (int i = size() - 1; i >= 0; i--) {
        if (myData.myPtr()[i] != right.myData.myPtr()[i]) {
            return false;
        }
    }
    return true;


}

bool operator==(const string& left, const string& right)
{
    return left.equal(right);
    //   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=(const string& left, const string& right)
{
    return !left.equal(right);
}

ostream& operator<<(ostream& ostr, string& str)
{
    for (size_t i = 0; i < str.size(); i++)
        ostr << str.data()[i];

    return ostr; // enables cout << x << y;
}