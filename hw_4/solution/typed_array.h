#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;

    // Setters
    void set(int index, ElementType value);

    // =================================================================
    // hw4
    // =================================================================
    // push
    void push(const ElementType& value);

    // pop
    ElementType pop();

    // push_front
    void push_front(const ElementType& value);

    // pop_front
    ElementType pop_front();

    // concat
    TypedArray concat(const TypedArray& other) const;
    void push_back(const ElementType& value);

    // reverse
    TypedArray& reverse();

    //operator+
    TypedArray operator+(const TypedArray& other) const;

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;
    origin = capacity / 2;
    end = origin;
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    }
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

//TODO:
// =================================================================
// hw4
// =================================================================

// push
template <typename ElementType>
void TypedArray<ElementType>::push(const ElementType& value) {
    // Extend buffer if necessary
    while (out_of_buffer(end)) {
        extend_buffer();
    }

    // Insert element at the end
    buffer[end] = value;
    end++;
}

// pop
template <typename ElementType>
ElementType TypedArray<ElementType>::pop() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }

    // Decrease end index and return the element
    end--;
    return buffer[end];
}

// push front
template <typename ElementType>
void TypedArray<ElementType>::push_front(const ElementType& value) {
    // Extend buffer if necessary
    while (out_of_buffer(origin - 1)) {
        extend_buffer();
    }

    // Insert element at the front
    origin--;
    buffer[origin] = value;

}

// pop front
template <typename ElementType>
ElementType TypedArray<ElementType>::pop_front() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }

    // Get the front element and move all elements one position to the left
    ElementType result = buffer[origin];
    origin++;

    return result;
}

// concat helper
template <typename ElementType>
void TypedArray<ElementType>::push_back(const ElementType& value) {
    // If the array is full, extend the buffer
    while (out_of_buffer(end)) {
        extend_buffer();
    }
    // Add the new element at the end
    buffer[end] = value;
    end++;
}

// concat
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray& other) const {
    TypedArray<ElementType> result;

    for (int i = 0; i < size(); i++) {
        result.push_back(this->safe_get(i));
    }
    for (int i = 0; i < other.size(); i++) {
        result.push_back(other.safe_get(i));
    }

    return result;
}

// reverse
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::reverse() {
    int left = origin;
    int right = end - 1;

    // Swap elements from both ends until the middle is reached
    while (left < right) {
        ElementType temp = buffer[left];
        buffer[left] = buffer[right];
        buffer[right] = temp;

        left++;
        right--;
    }

    return *this;
}

// operator+
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType>& other) const {
    TypedArray<ElementType> result;

    // Copy the elements of the current array
    for (int i = 0; i < this->size(); ++i) {
        result.set(i, this->safe_get(i));
    }

    // Copy the elements of the other array
    for (int i = 0; i < other.size(); ++i) {
        result.set(this->size() + i, other.safe_get(i));
    }

    return result;
}


// ============================================================================

// ============================================================================
// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}

#endif