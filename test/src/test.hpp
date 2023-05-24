#ifndef __TEST_HPP__
#define __TEST_HPP__

class Test
{
    public:
        virtual bool init() = 0;
        virtual void run() = 0;
        virtual void shutdown() = 0;
};

#endif
