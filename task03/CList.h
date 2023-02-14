#ifndef CLIST_H
#define CLIST_H

#include <memory>

template <typename T>
class CList
{
    struct SNode {
        T data;
        T *next = nullptr;
    };

public:
    CList() noexcept = default;
    CList(const CList &other) 
        : m_size(other.m_size)
    {
        auto ptr = other.m_head;
        while (ptr) {
            /*auto node = new SNode{};

            if (ptr->next) {
                
            }

            ptr = ptr->next;*/
        }
    }

    std::size_t size() const noexcept { 
        return m_size;
    }

    const T &at(std::size_t idx) const {
        if (idx >= size())
            throw std::out_of_range("");

        SNode *ptr = m_head;
        for (std::size_t i = 1; i < idx; ++i) {
            ptr = ptr->next;
        }

        return *ptr;
    }

    bool empty() const noexcept {
        return m_size == 0;
    }

    void clear() noexcept {
        if (!empty()) {
            SNode *ptr = m_head;
            while (ptr) {
                auto ptrNext = ptr->next;
                delete ptr;
                ptr = ptrNext;
            }

            m_size = 0;
        }
    }

private:
    void crateNewNode(const T &val) noexcept {
        auto node = new SNode{};
        node->data = val;
        node->next = nullptr;

        
    }

    SNode *m_head = nullptr;
    std::size_t m_size = 0;
};

#endif // CLIST_H