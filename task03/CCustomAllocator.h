#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <array>

/*!
 * \brief Туповатый аллокатор, который не умеет перераспределять аллоцированные ранее арены. Освобождение конкретного элемента не предполагается - время жизни арен совпадает с временем жизни аллокатора.
 * \param T - тип данных.
 * \param AreaSizeBytes - размер одной арены в байтах. При превышении будет сгенерировано исключение std::bad_allocate.
 * \param MaxAreasCount - максимальное количество создаваемы арен размером AreaSizeBytes. При превышении будет сгенерировано исключение std::bad_allocate.
 */
template <typename T, std::size_t AreaSizeBytes = 128, std::size_t MaxAreasCount = 128>
class CCustomAllocator
{
    /*!
     * \brief Аллоцируемая область памяти с фиксированным размером. Удаление отдельных элементов не предусмотрено.
     */
    struct SArea {
        /// Память.
        void *data;
        /// Адрес начала неиспользуемой памяти.
        void *begin;
        /// Количество оставшихся байт в текущей арене.
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

        // Поиск или создание арены для получения блока памяти
        auto area = getArea(countBytes);
        if (!area)
            throw std::bad_alloc();

        // Получение адреса доступной свободной памяти на арене
        auto ptr = area->begin;
        if (!ptr)
            throw std::bad_alloc();

        // Пересчет счетчиков арены (приведение к uint8_t для отключения ворнинга)
        auto ptrBytes = reinterpret_cast<uint8_t *>(area->begin);
        ptrBytes += countBytes;
        area->leftBytes -= countBytes;

        return reinterpret_cast<T *>(ptr);
    }

    void deallocate (T *ptr, std::size_t count) {
        // Реализация не нужна, потому что аллокатор не предусматривает удаление отдельных элементов. Вся память высвобождается при разрушении аллокатора
        (void)ptr;
        (void)count;
    }

private:
    /*!
     * \brief Поиск допустимой арены или создание новой.
     * \param needBytes - требуемое количество байт для аллоцирования.
     * \return Возвращается указатель на найденную арену или nullptr, если не удалось ничего найти.
     */
    SArea *getArea(std::size_t needBytes) noexcept {
        SArea *res = nullptr;
        for (std::size_t i = 0; i < MaxAreasCount; ++i) {
            if (m_areas[i]) {
                auto ref = m_areas[i];
                if (ref->leftBytes >= needBytes) {
                    res = m_areas[i];

                    break;
                }
            } else if (!m_areas[i]) {
                m_areas[i] = new SArea{};
                res = m_areas[i];

                break;
            }
        }

        return res;
    }

    SArea *m_areas[MaxAreasCount] = { nullptr };
};

#endif // CUSTOMALLOCATOR_H
