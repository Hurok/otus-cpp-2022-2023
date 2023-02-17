#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <array>

template <typename T, std::size_t AreaSizeBytes = 128, std::size_t MaxAreasCount = 128>
class CCustomAllocator
{
    struct SArea {
        void *data;
        void *begin;
        std::size_t leftBytes;

        SArea()
            : data(std::malloc(AreaSizeBytes)),
              begin(data),
              leftBytes(AreaSizeBytes)
        { }

        ~SArea() {
            std::free(data);
        }
    };

public:
    using value_type = T;
    ~CCustomAllocator() {
        for (std::size_t i = 0; i < MaxAreasCount && m_areas[i]; ++i) {
            delete m_areas[i];
        }
    }

    template <typename U, std::size_t UAreaSize = AreaSizeBytes>
    struct rebind {
        using other = CCustomAllocator<U, UAreaSize>;
    };

    T *allocate (std::size_t count) {
        std::size_t countBytes = sizeof(T) * count;
        if (countBytes > AreaSizeBytes)
            throw std::bad_alloc();

        auto area = getArea(countBytes);
        if (!area)
            throw std::bad_alloc();

        auto ptr = area->begin;
        if (!ptr)
            throw std::bad_alloc();

        area->begin += countBytes;
        area->leftBytes -= countBytes;
        return reinterpret_cast<T *>(ptr);
    }

    void deallocate (T *ptr, std::size_t count) {
        (void)ptr;
        (void)count;


    }

private:
    SArea *getArea(std::size_t needBytes) {
        SArea *res = nullptr;
        for (std::size_t i = 0; i < MaxAreasCount; ++i) {
            if (m_areas[i]) {
                auto ref = m_areas[i];
                if (ref->leftBytes >= needBytes) {
                    res = m_areas[i];
                    std::cout << "found area " << i << ", need bytes " << needBytes << ", area size " << AreaSizeBytes << ", left bytes " << ref->leftBytes << std::endl;
                    break;
                }
            } else if (!m_areas[i]) {
                m_areas[i] = new SArea{};
                std::cout << "create new area " << i << ", need bytes " << needBytes << ", area size " << AreaSizeBytes << std::endl;
                res = m_areas[i];
                break;
            }
        }

        return res;
    }

    SArea *m_areas[MaxAreasCount] = { nullptr };
};

#endif // CUSTOMALLOCATOR_H
