#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include "vertexArray.hpp"

#include <memory>

namespace engine::renderer
{
    void clear();
    void setClearColor(float r, float g, float b, float a = 1);

    void drawIndexed(const std::shared_ptr<VertexArray>& vao);
}

#endif
