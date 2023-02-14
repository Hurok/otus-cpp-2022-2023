#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <assert.h>
#include <exception>

template <typename T>
class CLinkedList
{
    struct SNode {
        ~SNode() {
            if (value)
                delete value;
        }

        T *value = nullptr;
        SNode *next = nullptr;
    };

public:
    template <typename TValue>
    struct SIterator : public std::iterator<std::input_iterator_tag, T>
    {
        friend class CLinkedList;
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
            m_data = m_data->next;
            return *this;
        }

        typename SIterator::reference operator * () const noexcept {
            assert(m_data);
            assert(m_data->value);

            return *m_data->value;
        }

    private:
        SIterator(SNode *data)
            : m_data(data)
        { }

        SNode *m_data = nullptr;
    };

    typedef SIterator<T> iterator;
    typedef SIterator<const T> const_iterator;

    iterator begin() noexcept {
        return iterator{ head() };
    }

    iterator end() noexcept {
        return iterator{ nullptr };
    }

    const_iterator cbegin() const noexcept {
        return const_iterator{ head() };
    }

    const_iterator cend() const noexcept {
        return const_iterator{ nullptr };
    }

    CLinkedList() = default;
    ~CLinkedList() {
        clear();
    }

    void clear() noexcept {
        auto ptr = head();
        while (ptr) {
            auto temp = ptr->next;
            delete ptr;
            ptr = temp;
        }

        m_size = 0;
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    std::size_t size() const noexcept {
        return m_size;
    }

    const T &at(std::size_t idx) const {
        if (idx >= size() || idx < 0)
            throw std::out_of_range(std::to_string(idx) + std::string(" out of range list ") + std::to_string(size()) + std::string(" size"));

        auto ptr = head();
        assert(ptr);
        for (std::size_t i = 0; i < idx; ++i) {
            ptr = ptr->next;
        }

        assert(ptr->value);
        return *ptr->value;
    }

    void push_back(const T &val) noexcept {
        createNode(val);
    }

private:
    void createNode(const T &val) noexcept {
        auto ptr = tail();
        if (!ptr) {
            ptr = new SNode{};
            m_head = ptr;
        } else {
            ptr->next = new SNode{};
            ptr = ptr->next;
        }

        ptr->value = new T{};
        *ptr->value = val;
        m_size++;
    }

    SNode *tail() const noexcept {
        auto ptr = head();
        while (ptr && ptr->value && ptr->next && ptr->next->value) {
            ptr = ptr->next;
        }

        return ptr;
    }

    SNode *tailWithReserved() const noexcept {
        auto ptr = tail();
        while (ptr && ptr->next) {
            ptr = ptr->next;
        }

        return ptr;
    }

    SNode *head() const noexcept {
        return m_head;
    }

    SNode *m_head = nullptr;
    std::size_t m_size = 0;
};

#endif // CLINKEDLIST_H
