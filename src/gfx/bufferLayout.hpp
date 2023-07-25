#ifndef __BUFFERLAYOUT_HPP__
#define __BUFFERLAYOUT_HPP__

#include <string>
#include <vector>

#include "../log/log.hpp"
#include "../util/types.hpp"

namespace engine::renderer
{
    enum class ShaderDataType
    {
        float2,
        float3,
        float4,
    };

    struct BufferElement
    {
        ShaderDataType m_type;
        std::string m_name;
        uint32_t m_size;
        uint32_t m_offset;
        bool m_normalized;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

        uint32_t getCount() const;
        uint32_t getGLBaseType() const;
        inline bool isNormalized() const { return m_normalized; };
    };

    class BufferLayout
    {
        public:
            BufferLayout() = default;
            BufferLayout(const std::initializer_list<BufferElement>& elts);

            inline const std::vector<BufferElement>& getElements() const { return m_elements; } 
            inline uint32_t getStride() const { return m_stride; }

            inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
            inline std::vector<BufferElement>::iterator end() { return m_elements.end(); }
            inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
            inline std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

        private:
            std::vector<BufferElement> m_elements;
            uint32_t m_stride;
    };
}

#endif
