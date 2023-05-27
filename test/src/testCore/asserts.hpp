#ifndef __ASSERTS_HPP__
#define __ASSERTS_HPP__

#include <exception>

namespace test
{
    class assert_failed : public std::exception
    {
        
    };
}

#endif
