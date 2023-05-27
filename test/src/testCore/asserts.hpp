#ifndef __ASSERTS_HPP__
#define __ASSERTS_HPP__

#include <exception>
#include <string>

namespace test
{
    class assert_failed : public std::exception
    {
    public:
        assert_failed() = default;
        assert_failed(const std::string& msg) : msg(msg) {}

        const char* what() const noexcept override
        {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}

#endif
