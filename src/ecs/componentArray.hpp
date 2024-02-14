#ifndef __COMPONENTARRAY_HPP__
#define __COMPONENTARRAY_HPP__

#include <cstddef>
#include <cstdlib>

#include "../engine.hpp"
#include "../util/assert.hpp"
#include "../util/types.hpp"

namespace engine::ecs
{
    // Array of Components Data.
    // Uses type erasure to store the data
    class ComponentArray
    {
    public:
        ComponentArray(size_t initialSize = 1024)
            : m_data(nullptr), m_size(0), m_maxSize(initialSize), m_elementSize(0)
        {
        }

        ~ComponentArray()
        {
            if (m_data)
                free(m_data);
        }

        size_t getElementSize()
        {
            return m_elementSize;
        }

        template<class T>
        T& at(size_t i)
        {
            Check(m_data);
            Check(m_elementSize == sizeof(T));
            Check(i < m_size);
            return ((T*) m_data)[i];
        }

        template<class T>
        const T& at(size_t i) const
        {
            Check(m_data);
            Check(m_elementSize == sizeof(T));
            Check(i < m_size);
            return ((T*) m_data)[i];
        }

        void* get(size_t i)
        {
            Check(m_data);
            Check(i < m_size);
            return m_data + m_elementSize * i;
        }

        void set_back(size_t size, const void* data)
        {
            Check(m_data);
            Check(m_elementSize);
            memcpy(m_data + (m_size - 1) * m_elementSize, data, size);
        }

        void insertEmpty(size_t n = 1)
        {
            Check(m_data);
            Check(n);

            m_size += n;

            if (m_size >= m_maxSize)
            {
                size_t newSize = m_maxSize;
                while(newSize < m_size)
                    newSize *= 2;

                char* new_array = (char*) malloc(newSize * m_elementSize);
                memcpy(new_array, m_data, m_maxSize * m_elementSize);
                m_maxSize = newSize;
                free(m_data);
                m_data = new_array;
            }
        }

        void erase(size_t i)
        {
            Check(m_data);
            Check(i < m_size);
            m_size--;
            if (m_size - i > 1)
            {
                void* elt = m_data + m_elementSize * i;
                void* nextElt = (char*) elt + m_elementSize;
                memmove(elt, nextElt, (m_size - i) * m_elementSize);
            }
        }

        size_t size() const
        {
            return m_size;
        }

        void setup(size_t elementSize)
        {
            m_data = (char*) malloc(m_maxSize * elementSize);
            m_elementSize = elementSize;
        }

    private:
        char* m_data;
        u64 m_size;
        u64 m_maxSize;
        u64 m_elementSize;
    };
}

#endif
