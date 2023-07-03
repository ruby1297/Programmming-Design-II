#include <iostream>
using std::cout;
using std::exit;

//#include <algorithm>
//using std::max;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;
   
   if (myRes < 16)
   {
       //copy ptr to buf
       std::copy(ptr, ptr + mySize, bx.buf);
       bx.buf[mySize] = '\0';
   }
   else
   {
       //copy ptr to buf
       bx.ptr = new char[myRes + 1];
       std::copy(ptr, ptr + mySize, bx.ptr);
       bx.ptr[mySize] = '\0';
   }

}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   if( count > 15 )
   {
      myRes = ( mySize / 16 ) * 16 + 15;
	  bx.ptr = new char[myRes + 1];
   }

   for (size_type i = 0; i < mySize; i++)
	   myPtr()[i] = ch;
   
   myPtr()[mySize] = '\0';

}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = right.mySize;
   myRes = ( mySize / 16 ) * 16 + 15;
   if (myRes > 15) {
       bx.ptr = new char[myRes + 1];

	   //memcpy是複製記憶體 copy是複製值 strcpy只能複製字串 
	   memcpy(bx.ptr, right.myPtr(), mySize);//copy right.myPtr() to bx.ptr
       bx.ptr[mySize] = '\0';
   }
   else {
	   memcpy(bx.buf, right.myPtr(), mySize); //copy right.myPtr() to bx.buf
	   bx.buf[mySize] = '\0';
   }
   
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}


string& string::assign(const string& right)
{
    if (this != &right)
    {
        if (right.mySize > myRes)
        {
            myRes = myRes * 3 / 2;
            if (myRes < (right.mySize / 16) * 16 + 15)
                myRes = (right.mySize / 16) * 16 + 15;

            if (myRes > 15) {
                pointer newptr = new value_type[myRes + 1]();
                memcpy(newptr, right.myPtr(), right.mySize);
                //delete[] myPtr();
                bx.ptr = newptr;
            }
            else
                memcpy(bx.buf, right.myPtr(), right.mySize);

        }
        else
            memcpy(myPtr(), right.myPtr(), right.mySize);

        mySize = right.mySize;
        myPtr()[mySize] = value_type();
    }
    return *this;
}

string::iterator string::insert(const_iterator where, const char ch)
{
    if (where >= myPtr() && where <= myPtr() + mySize)
    {
        size_type index = where - myPtr();
        if (mySize == myRes)
        {
            size_type newMyRes;
            if (myRes == 15 || myRes == 31)
                newMyRes = myRes + 16;
            else
                newMyRes = myRes * 3 / 2;

            char* temp = new char[newMyRes + 1];

            memcpy(temp, myPtr(), index);
            temp[index] = ch;
            memcpy(temp + index + 1, myPtr() + index, mySize - index);
            temp[++mySize] = '\0';

            if (myRes > 15)
                delete[] bx.ptr;
            bx.ptr = temp;
            myRes = newMyRes;
        }
        else
        {
            for (size_type i = mySize; i > index; i--)
                myPtr()[i] = myPtr()[i - 1];
            myPtr()[index] = ch;
            mySize++;
        }

        return iterator(myPtr() + index);
    }
    else
        return iterator(nullptr);
}



string::iterator string::erase(const_iterator where)
{
    if (where >= myPtr() && where < myPtr() + mySize)
    {
        
        size_type index = where - myPtr();

        if (myRes < 16) 
			/*for (size_type i = index; i < mySize; i++)
				myPtr()[i] = myPtr()[i + 1];*/
			memcpy(myPtr() + index, myPtr() + index + 1, mySize - index);
        
        else {
			pointer newptr = new value_type[myRes]();
			memcpy(newptr, myPtr(), index);
			memcpy(newptr + index, myPtr() + index + 1, mySize - index - 1);
			delete[] bx.ptr;
			bx.ptr = newptr;
        }
		mySize--;
        
        return iterator(myPtr() + index);
    }
    else
    {
        return iterator(nullptr);
    }
}


void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}