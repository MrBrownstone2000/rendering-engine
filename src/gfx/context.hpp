#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

namespace engine
{
    class IRenderingContext
    {
        public:
            virtual ~IRenderingContext() = default;
            virtual void swapBuffers() = 0;
            virtual void* getNativeContext() = 0;
    };
}

#endif
