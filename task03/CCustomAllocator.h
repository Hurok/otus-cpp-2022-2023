#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>

template <typename T, typename Allocator = std::allocator<T> >
class CCustomAllocator
{
public:
    using value_type = T;

    CCustomAllocator() = default;
    ~CCustomAllocator() = default;

    template <typename U>
    struct rebind {
        using other = CCustomAllocator<U>;
    };

    T *allocate (std::size_t count) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;

        auto ptr = std::malloc(sizeof(T) * count);
        if (!ptr)
            throw std::bad_alloc();

        return reinterpret_cast<T *>(ptr);
    }

    void deallocate (T *ptr, std::size_t count) {
        (void)count;
        std::free(ptr);

        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    template <typename U, typename... Args>
    void construct(U *ptr, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;

        new (ptr) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U *ptr) {
       std::cout <<  __PRETTY_FUNCTION__ << std::endl;

        ptr->~U();
    }
};

#endif // CUSTOMALLOCATOR_H
