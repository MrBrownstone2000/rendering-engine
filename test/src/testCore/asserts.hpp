#ifndef __ASSERTS_HPP__
#define __ASSERTS_HPP__

#include <exception>
#include <functional>
#include <string>
#include <sstream>

#define STR(a) #a

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

    template <typename T, typename U>
    void expect_eq(T&& a, U&& b)
    {
        if (a != b){
            std::stringstream ss;
            ss << STR(a) << " == " << STR(b) << std::endl;
            ss << "values are: " << a;
            ss << " and " << b;
            throw test::assert_failed(ss.str());
        }
    }

    template <typename T, typename U>
    void expect_neq(T&& a, U&& b)
    {
        if (a == b){
            std::stringstream ss;
            ss << STR(a) << " != " << STR(b) << std::endl;
            ss << "values are: " << a;
            ss << " and " << b;
            throw test::assert_failed(ss.str());
        }
    }

    template <typename T, typename U>
    void expect_lteq(T&& a, U&& b)
    {
        if (a > b){
            std::stringstream ss;
            ss << STR(a) << " <= " << STR(b) << std::endl;
            ss << "values are: " << a;
            ss << " and " << b;
            throw test::assert_failed(ss.str());
        }
    }

    template <typename T, typename U>
    void expect_gteq(T&& a, U&& b)
    {
        if (a < b){
            std::stringstream ss;
            ss << STR(a) << " >= " << STR(b) << std::endl;
            ss << "values are: " << a;
            ss << " and " << b;
            throw test::assert_failed(ss.str());
        }
    }

    template <typename T, typename U>
    void expect_lt(T&& a, U&& b)
    {
        if (a >= b){
            std::stringstream ss;
            ss << STR(a) << " < " << STR(b) << std::endl;
            ss << "values are: " << a;
            ss << " and " << b;
            throw test::assert_failed(ss.str());
        }
    }

    template <typename T, typename U>
    void expect_gt(T&& a, U&& b)
    {
        if (a <= b){
            std::stringstream ss;
            ss << STR(a) << " > " << STR(b) << std::endl;
            ss << "values are: " << a;
            ss << " and " << b;
            throw test::assert_failed(ss.str());
        }
    }

    template <typename T>
    void expect(T expr)
    {
        if (!expr){
            std::stringstream ss;
            ss << "expression is not true";
            throw test::assert_failed(ss.str());
        }
    }

    template <typename E>
    void expect_exception(std::function<void()> function)
    {
        bool caught = false;
        try {
            function();
        } catch(const E& e) {
            caught = true;
        }
        if (!caught) {
            std::stringstream ss;
            ss << "Did not catch exception ";
            ss << typeid(E).name();
            throw test::assert_failed(ss.str());
        }
    }
}


#endif
