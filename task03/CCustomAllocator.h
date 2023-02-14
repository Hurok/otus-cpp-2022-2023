#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>

template <typename T>
class CCustomAllocator : public std::allocator<T>
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T * const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equa;

    pointer allocate(size_type n, const void * hint = 0) {

    }

    void deallocate(pointer ptr, size_type n) {
        delete ptr;
    }
};

#endif // CUSTOMALLOCATOR_H
