#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

namespace engine::renderer
{
    class IContext
    {
        public:
            virtual void SwapBuffers() = 0;
    };
}

#endif
