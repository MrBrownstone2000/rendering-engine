#ifndef __ASSERTS_HPP__
#define __ASSERTS_HPP__

#include <exception>
#include <string>
#include <sstream>

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

#define expect_eq(a, b)                             \
if (a != b){                                        \
    std::stringstream ss;                           \
    ss << #a << " == " << #b << std::endl;          \
    ss << "values are: " << a;                      \
    ss << " and " << b;                             \
    throw test::assert_failed(ss.str());            \
}

#define expect_neq(a, b)                            \
if (a == b){                                        \
    std::stringstream ss;                           \
    ss << #a << " != " << #b << std::endl;          \
    ss << "values are: " << a;                      \
    ss << " and " << b;                             \
    throw test::assert_failed(ss.str());            \
}

#define expect_lteq(a, b)                           \
if (a > b){                                         \
    std::stringstream ss;                           \
    ss << #a << " <= " << #b << std::endl;          \
    ss << "values are: " << a;                      \
    ss << " and " << b;                             \
    throw test::assert_failed(ss.str());            \
}

#define expect_gteq(a, b)                           \
if (a < b){                                         \
    std::stringstream ss;                           \
    ss << #a << " >= " << #b << std::endl;          \
    ss << "values are: " << a;                      \
    ss << " and " << b;                             \
    throw test::assert_failed(ss.str());            \
}

#define expect_lt(a, b)                             \
if (a >= b){                                        \
    std::stringstream ss;                           \
    ss << #a << " < " << #b << std::endl;           \
    ss << "values are: " << a;                      \
    ss << " and " << b;                             \
    throw test::assert_failed(ss.str());            \
}

#define expect_gt(a, b)                             \
if (a <= b){                                        \
    std::stringstream ss;                           \
    ss << #a << " > " << #b << std::endl;           \
    ss << "values are: " << a;                      \
    ss << " and " << b;                             \
    throw test::assert_failed(ss.str());            \
}

#define expect(expr)                                \
if (!(expr)){                                       \
    std::stringstream ss;                           \
    ss << #expr << " is not true";                  \
    throw test::assert_failed(ss.str());            \
}

#define expect_exception(exception, code)           \
    bool caught = false;                            \
    try {                                           \
        code;                                       \
    } catch(const exception& e) {                   \
        caught = true;                              \
    }                                               \
    if (!caught) {                                  \
        std::stringstream ss;                       \
        ss << "Did not catch exception ";           \
        ss << #exception;                           \
        throw test::assert_failed(ss.str());        \
    }

#endif
