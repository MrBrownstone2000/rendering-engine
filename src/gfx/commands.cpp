#include "pch.hpp"
#include "commands.hpp"

#include <GL/glew.h>

namespace engine::renderer
{
    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
        
    void setClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void drawIndexed(const std::shared_ptr<VertexArray>& vao)
    {
        glDrawElements(GL_TRIANGLES, vao->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}
