#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

namespace engine::renderer
{
    class IContext
    {
        public:
            virtual ~IContext() = default;
            virtual void swapBuffers() = 0;
            virtual void* getNativeContext() = 0;
    };
}

#endif
