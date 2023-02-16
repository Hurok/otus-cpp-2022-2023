#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <assert.h>
#include <exception>
#include <memory>

template <typename T, typename Allocator = std::allocator<T>, int ExtendElemCount = 8 >
class CLinkedVector
{
public:
    template <typename TValue>
    struct SIterator
    {
        using iterator_category = std::input_iterator_tag;
        using value_type = TValue;
        using reference = TValue &;

        friend class CLinkedVector;
        SIterator() = default;
        SIterator(const SIterator &other)
            : m_data(other.m_data)
        { }
        ~SIterator() = default;

        bool operator != (const SIterator &other) const noexcept {
            return m_data != other.m_data;
        }

        bool operator == (const SIterator &other) const noexcept {
            return m_data == other.m_data;
        }

        SIterator &operator ++ () {
            m_data = m_data + 1;
            return *this;
        }

        typename SIterator::reference operator * () const noexcept {
            return *m_data;
        }

    private:
        SIterator(TValue *data)
            : m_data(data)
        { }

        TValue *m_data = nullptr;
    };

    typedef SIterator<T> iterator;
    typedef SIterator<const T> const_iterator;

    iterator begin() noexcept {
        return iterator{ m_data };
    }

    iterator end() noexcept {
        return iterator{ nullptr };
    }

    const_iterator cbegin() const noexcept {
        return const_iterator{ m_data };
    }

    const_iterator cend() const noexcept {
        return const_iterator{ nullptr };
    }

    CLinkedVector() = default;
    ~CLinkedVector() {
        clear();
    }

    void clear() noexcept {
        if (!empty()) {
            for (std::size_t i; i < capacity(); ++i) {
                m_alloc.destroy(&m_data[i]);
            }

            m_alloc.deallocate(m_data, capacity());
            m_capacity = 0;
            m_size = 0;
        }
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    std::size_t size() const noexcept {
        return m_size;
    }

    const T &at(std::size_t idx) const {
        if (idx >= size() || idx < 0)
            throw std::out_of_range();

        return *m_data[idx];
    }

    std::size_t capacity() const noexcept {
        return m_capacity;
    }

    void shrink_to_fit() noexcept {
        if (capacity() > 0) {
            auto buffer = m_alloc.allocate(size());

            for (std::size_t i; i < size(); ++i) {
                m_alloc.construct(buffer[i]);
                buffer[i] = m_data[i];

                m_alloc.destroy(&m_data[i]);
            }
            m_alloc.dealocate(m_data);

            m_data = buffer;
            m_capacity = size();
        }
    }

    void push_back(const T &val) noexcept {
        if (size() >= capacity()) {
            reserve(ExtendElemCount);
        }

        m_data[size()] = val;
        m_size++;
    }

    void reserve(std::size_t count) noexcept {
        m_capacity += count;
//        reserveNodes(count);
    }

private:
    T *m_data = nullptr;
    Allocator m_alloc;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

#endif // CLINKEDLIST_H
