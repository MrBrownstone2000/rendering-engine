#include "pch.hpp"
#include "bufferLayout.hpp"

#include <GL/glew.h>

namespace engine
{
    // ==================== ShaderDataType ==================== 
    static uint32_t shaderDataTypeCount(BufferLayout::ShaderDataType type)
    {
        switch (type)
        {
            case BufferLayout::ShaderDataType::float2: return 2;
            case BufferLayout::ShaderDataType::float3: return 3;
            case BufferLayout::ShaderDataType::float4: return 4;
        }
        engineLog.error("Unknown data type");
        return 0;
    }

    static uint32_t shaderDataType_GLBaseType(BufferLayout::ShaderDataType type)
    {
        switch (type)
        {
            case BufferLayout::ShaderDataType::float2: return GL_FLOAT;
            case BufferLayout::ShaderDataType::float3: return GL_FLOAT;
            case BufferLayout::ShaderDataType::float4: return GL_FLOAT;
        }
        engineLog.error("Unknown data type");
        return 0;
    }

    static uint32_t shaderDataTypeSize(BufferLayout::ShaderDataType type)
    {
        switch (type)
        {
            case BufferLayout::ShaderDataType::float2: return 4 * 2;
            case BufferLayout::ShaderDataType::float3: return 4 * 3;
            case BufferLayout::ShaderDataType::float4: return 4 * 4;
        }

        engineLog.error("Unknown data type");
        return 0;
    }

    // ==================== BufferElement ==================== 
    BufferLayout::BufferElement::BufferElement(BufferLayout::ShaderDataType type, const std::string& name, bool normalized)
        : m_type(type), m_name(name), m_size(shaderDataTypeSize(type)),
        m_offset(0), m_normalized(normalized)
    {}

    uint32_t BufferLayout::BufferElement::getCount() const { return shaderDataTypeCount(m_type); }
    uint32_t BufferLayout::BufferElement::getGLBaseType() const { return shaderDataType_GLBaseType(m_type); }

    // ==================== BufferLayout ==================== 
    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elts)
        : m_elements(elts)
    {
        // Calculate offset and stride
        uint32_t offset = 0;
        for (BufferElement& elt : m_elements)
        {
            elt.m_offset = offset;
            offset += elt.m_size;
        }
        m_stride = offset;
    }
}
