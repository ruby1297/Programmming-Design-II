// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

const int maxSize = 200;

#include <cstddef>

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
      myLast(),
      myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   vector()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count )
      : myData()
   {
      if( count != 0 )
      {
         myData.myFirst = new value_type[ count ]();
         myData.myLast = myData.myFirst + count;
         myData.myEnd = myData.myFirst + count;
      }
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right )
      : myData()
   {
       myData.myFirst = new value_type[right.size()];
       myData.myLast = myData.myEnd = myData.myFirst + right.size();

       for (int i = 0; i < right.size(); i++) {
           myData.myFirst[i] = right.myData.myFirst[i];
       }
   }

   // Vector destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   // The vector is extended by inserting a new element before the element
   // at the specified position, effectively increasing the container size by one.
   // This causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   // Relocates all the elements that were after "where" to their new positions.
   iterator insert( const_iterator where, const value_type &val )
   {
      if( where >= myData.myFirst && where <= myData.myLast )
      {
         size_type index = where - myData.myFirst;
         size_type originalSize = size();
         size_type originalCapacity = capacity();
         if( originalSize == originalCapacity )
         {
            size_type newCapacity;
            if( originalCapacity <= 1 )
               newCapacity = originalCapacity + 1;
            else
               newCapacity = originalCapacity * 3 / 2;
            pointer newFirst = myData.myFirst;
            myData.myFirst = new value_type[newCapacity]();

            for (size_type i = 0; i < index; i++)
                myData.myFirst[i] = newFirst[i];

            myData.myFirst[index] = val;

            for (size_type i = index; i < originalSize; i++)
                myData.myFirst[i + 1] = newFirst[i];

            myData.myLast = myData.myFirst + originalSize + 1;
            myData.myEnd = myData.myFirst + newCapacity;

            delete[] newFirst;


         }
         else
         {
             for (size_type i = originalSize; i > index; i--)
                 myData.myFirst[i] = myData.myFirst[i - 1];

             myData.myFirst[index] = val;
             myData.myLast++;


         }
		 return (myData.myFirst + index);
      }
      else
         return nullptr;
   }

   // overloaded assignment operator
   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   vector& operator=( const vector &right )
   {
       if (this != &right) // avoid self-assignment
       {
           size_type rightSize = right.size();
           if (rightSize > capacity())
           {
               if (size() > 0)
                   delete[] myData.myFirst;

               size_type newCapacity = capacity() * 3 / 2;
               if (newCapacity < rightSize)
                   newCapacity = rightSize;

               myData.myFirst = new value_type[newCapacity]();
               myData.myEnd = myData.myFirst + newCapacity;
           }
           
           myData.myLast = myData.myFirst + rightSize;

           for (size_type i = 0; i < rightSize; i++) {
               myData.myFirst[i] = right.myData.myFirst[i];
           }


       }

       return *this; // enables x = y = z, for example
   }

   // Removes from the vector a single element (where).
   // This effectively reduces the container size by one, which is destroyed.
   // Relocates all the elements after the element erased to their new positions.
   iterator erase( const_iterator where )
   {
      if( where >= myData.myFirst && where < myData.myLast )
      {
          size_type index = where - myData.myFirst;
          for (size_t i = index; i < size() - 1; i++)
              myData.myFirst[i] = myData.myFirst[i + 1];

          myData.myLast--;

          return  iterator(where);

      }
      else
         return nullptr;
   }

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   iterator end()
   {
      return myData.myLast;
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   // Returns a const_iterator pointing to the first element in the container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator cbegin() const
   {
      return begin();
   }

   // Returns a const_iterator pointing to the past-the-end element in the container.
   // If the container is empty, this function returns the same as vector::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const
   {
      return end();
   }

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& front()
   {
      return *myData.myFirst;
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& front() const
   {
      return *myData.myFirst;
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right )
{
        if (left.size() != right.size())
            return false;

    if (right.size() == 0)
        return true;

    for (size_t i = 0; i < right.size(); i++)
        if (left.begin()[i] != right.begin()[i])
            return false;

    return true;

}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( const vector< Ty > &left, const vector< Ty > &right )
{
   return !( left == right );
}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   // constructor; construct a zero HugeInteger with size n
   HugeInteger( unsigned int n = 0 )
      : integer( ( n == 0 ) ? 1 : n )
   {
   }

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy )
      : integer( integerToCopy.integer )
   {
   }

   // destructor; destroys the HugeInteger
   ~HugeInteger()
   {
   }

   // overloaded assignment operator;
   // return avoids: ( a1 = a2 ) = a3
   const HugeInteger& operator=( const HugeInteger &right )
   {
      if( &right != this ) // avoid self-assignment
         integer = right.integer;

      return *this; // enables x = y = z, for example
   }

   // function that tests if two HugeIntegers are equal
   bool operator==( const HugeInteger &right )
   {
      return ( integer == right.integer );
   } // end function operator==

   // function that tests if one HugeInteger is less than another
   bool operator<( HugeInteger &right )
   {
       if (integer.size() < right.integer.size())
           return true;
       if (integer.size() > right.integer.size())
           return false;
       for (int i = right.integer.size() - 1; i >= 0; i--) { 
           if (integer.begin()[i] < right.integer.begin()[i])
               return true;
           if (integer.begin()[i] > right.integer.begin()[i])  
               return false;  
       }

       return false;

   } // end function operator<

   // function that tests if one HugeInteger is less than or equal to another
   bool operator<=( HugeInteger &right )
   {
      return ( *this == right || *this < right );
   }

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 )
   {
      HugeInteger zero;
      if( *this == op2 )
         return zero;

      HugeInteger difference( *this );
      
      size_type op1Size = integer.size();
      size_type op2Size = op2.integer.size();

      typename T::iterator it1 = integer.begin();
	  //typename T::iterator it2 = op2.integer.begin(); 為什麼這樣寫會錯誤
      auto it2 = op2.integer.begin();
      auto it3 = difference.integer.begin();
      
      int* temp = new int[difference.integer.size()]();

      
	  for (int i = 0; i < op2Size; i++) 
          temp[i] = it1[i]-it2[i];

      for (int i = op2Size; i < op1Size; i++) 
          temp[i] = it1[i];
          
      for (int i = 0; i < difference.integer.size(); i++) {
		  if (temp[i] < 0)
		  {
			  temp[i] += 10;
			  temp[i + 1]--;
		  }
          it3[i] = temp[i];
      }
          
      while (difference.integer.back() == 0 && !difference.isZero())
          difference.integer.erase(difference.integer.end() - 1);

      if( difference.leadingZero() )
         cout << "difference has a leading zero!\n";

      return difference;
   }

   // subtraction assignment operator; HugeInteger -= HugeInteger
   void operator-=( HugeInteger &op2 )
   {
      *this = *this - op2;
   }

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger &op2 )
   {
      HugeInteger zero;
      if( isZero() || op2.isZero() )
         return zero;

      HugeInteger product( integer.size() + op2.integer.size() );
      
      size_type op1Size = integer.size();
      size_type op2Size = op2.integer.size();
      size_type productSize = op1Size + op2Size;

      typename T::iterator it1 = integer.begin();
      typename T::iterator it2 = op2.integer.begin();
      typename T::iterator it3 = product.integer.begin();

      for (size_type i = 0; i < op2Size; i++) {
          for (size_type j = 0; j < op1Size; j++) {
              *(it3 + i + j) += *(it1 + j) * *(it2 + i);
          }
      }

      for (it3 = product.integer.begin(); it3 != product.integer.end() - 1; ++it3) {
          if (*it3 > 9) {
              *(it3 + 1) += (*it3 / 10);
              *it3 %= 10;
          }
      }

      while (product.integer.back() == 0 && !product.isZero()) {
		  product.integer.erase(product.integer.end() - 1);
      }



      if( product.leadingZero() )
         cout << "product has a leading zero!\n";

      return product;
   }

   // multiplication assignment operator; HugeInteger *= HugeInteger
   void operator*=( HugeInteger &op2 )
   {
      *this = *this * op2;
   }

   // division operator; HugeInteger / HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator/( HugeInteger &op2 )
   {
      HugeInteger zero;
      if( *this < op2 )
         return zero;
      
      size_type op1Size = integer.size();
      size_type op2Size = op2.integer.size();
      size_type n = op1Size - op2Size;
      HugeInteger buffer(op1Size);

      for (int i = 0; i < op2Size; i++) {
          buffer.integer.begin()[i + (op1Size - op2Size)] = op2.integer.begin()[i];
      }
      size_type quotientSize = n;
      if (*this < buffer) { 
          buffer.divideByTen();
      }
      else {
          quotientSize++;
      }

      HugeInteger quotient(quotientSize);
      HugeInteger remainder = *this;

      for (int k = quotientSize - 1; k >= 0; k--) {
          while (buffer <= remainder) {
              remainder -= buffer;
              quotient.integer.begin()[k]++;
              if (remainder.integer.begin()[remainder.integer.size() - 1] <= 0) {
                  break;
              }
          }
          buffer.divideByTen();
      }



      return quotient;
   } // end function operator/

   // modulus operator; HugeInteger % HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator%( HugeInteger &op2 )
   {
      return *this - ( ( *this / op2 ) * op2 );
   }

   // overloaded prefix increment operator 
   HugeInteger& operator++()
   {
      helpIncrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix increment operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator++( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpIncrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // overloaded prefix decrement operator 
   HugeInteger& operator--()
   {
      helpDecrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix decrement operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator--( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpDecrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // convert an integer into a HugeInteger
   void convert( const value_type &number )
   {
      integer.erase( integer.end() - 1 );
      for( value_type i = number; i > 0; i /= 10 )
         integer.insert( integer.end(), i % 10 );
   }

   // compute base raised to the power of expon
   void power( HugeInteger &base, const value_type &expon )
   {
      *integer.begin() = 1;
      for( value_type i = 0; i < expon; ++i )
      {
         *this *= base;
         if( integer.size() > maxSize - base.integer.size() )
            break;
      }
   }

   size_type size()
   {
      return integer.size();
   }

   // return true if and only if all digits are zero
   bool isZero()
   {
      typename T::iterator it = integer.begin();
      for( ; it != integer.end(); ++it )
         if( *it != 0 )
            return false;

      return true;
   }

   // return true if and only if the leftmost digit is zero
   bool leadingZero()
   {
      return ( integer.size() > 1 && integer.back() == 0 );
   }

private:
   T integer;

   // function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
   void divideByTen()
   {
      typename T::iterator it = integer.begin() + 1;
      for( ; it != integer.end(); ++it )
         *( it - 1 ) = *it;
      integer.erase( integer.end() - 1 );
   }

   // function to help increment the integer
   void helpIncrement()
   {
      typename T::iterator it = integer.begin();
      ( *it )++;
      typename T::iterator it2 = it;
      for( ++it2; it2 != integer.end(); ++it, ++it2 )
         if( *it == 10 )
         {
            *it = 0;
            ( *it2 )++;
         }

      if( ( *it ) == 10 )
      {
         *it = 0;
         integer.insert( integer.end(), 1 );
      }
   }

   // function to help decrement the integer
   void helpDecrement()
   {
      typename T::iterator it = integer.begin();
      for( ; *it == 0; ++it )
         *it = 9;

      ( *it )--;

      if( !isZero() && integer.back() == 0 )
         integer.erase( integer.end() - 1 );
   }
}; // end class HugeInteger


// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}


template< typename T1, typename T2 >
void solution2( T2 t, T2 a, T2 b )
{
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInteger< T1 > base;
         base.convert( t ); // put all digits of t into base

         HugeInteger< T1 > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< T1 > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               HugeInteger< T1 > quotient = dividend / divisor;
               HugeInteger< T1 > remainder = dividend % divisor;

               if( quotient.leadingZero() )
                  cout << "quotient has a leading zero!\n";

               if( remainder.leadingZero() )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && remainder.isZero() )
                  cout << quotient << endl;
               else
                  cout << "is not an integer with less than 100 digits.\n";
            }
         }
      }
   }
}

template< typename T >
void solution1()
{
   T t = T(), a = T(), b = T();
   solution2< vector< T > >( t, a, b );
}

int main()
{
   // execute the following 6 instructions one by one, each of them should get an AC
   solution1< int >();
  // solution1< unsigned int >();
//   solution1< long int >();
//   solution1< unsigned long int >();
//   solution1< long long int >();
//   solution1< unsigned long long int >();

   system( "pause" );
}