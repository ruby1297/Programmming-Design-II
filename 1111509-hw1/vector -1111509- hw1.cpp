#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
	myFirst = new value_type[count]();
    myLast = myEnd = myFirst + count;
	for (size_type i = 0; i < count; ++i){
		myFirst[i] = 0;
	}

}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    size_type size = static_cast<size_type>(right.myLast - right.myFirst);
    myFirst = new value_type[size]();
    myEnd = myLast = myFirst + size;
    for (size_type i = 0; i < size; i++) {
        myFirst[i] = right.myFirst[i];
    }
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert(const_iterator where, const value_type& val)
{
    if (where >= myFirst && where <= myLast)
    {
        size_type originalSize = size();
        size_type originalCapacity = capacity();

        size_type index = static_cast<size_type>(where - myFirst);

        if (originalSize == originalCapacity){
            size_type newCapacity;
            if (originalCapacity <= 1)
                newCapacity = originalCapacity + 1;
            else
                newCapacity = originalCapacity * 3 / 2;

            pointer newFirst = new value_type[newCapacity];
            pointer newLast = newFirst + originalSize + 1;

            for (size_type i = 0; i < index; i++) {
                newFirst[i] = myFirst[i];
            }

            newFirst[index] = val;

            for (size_type i = index; i < originalSize; i++) {
                newFirst[i + 1] = myFirst[i];
            }

            delete[] myFirst;
            myFirst = newFirst;
            myLast = newLast;
            myEnd = newFirst + newCapacity;
            
        }
        else
        {
            for (size_type i = originalSize; i > index; i--) {
                myFirst[i] = myFirst[i - 1];
            }

            myFirst[where - myFirst] = val;

            myLast++;
        }
        return iterator(myFirst + index);
    }

    else
        return nullptr;
}



// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign(const vector& right)
{
    if (this != &right)
    {
        size_type rightSize = right.myLast - right.myFirst;

        if (rightSize > capacity())
        {

            size_type newCapacity = capacity() * 3 / 2;
            if (newCapacity < rightSize)
                newCapacity = rightSize;
            

            pointer newFirst = new value_type[newCapacity]();

            for (size_type i = 0; i < rightSize; i++)
            {
                newFirst[i] = right.myFirst[i];
            }

            delete[] myFirst;

            myFirst = newFirst;
            myEnd = myFirst + newCapacity;
        }
        else
        for (size_type i = 0; i < rightSize; i++)
        {
            myFirst[i] = right.myFirst[i];
        }

        myLast = myFirst + rightSize;
    }

    return *this;
}


// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase( const_iterator where )
{
    if (where >= myFirst && where < myLast){

        size_type index = where - myFirst;

        for (size_type i = index; i < size() - 1; i++) {
            myFirst[i] = myFirst[i + 1];
        }

        myLast--;

        // Return an iterator pointing to the element after the erased one
        return iterator(where);
    }
    else
        return nullptr;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty()
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return static_cast< size_type >( myEnd - myFirst );
}