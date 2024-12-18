#ifndef __ASSERT_HPP__
#define __ASSERT_HPP__

#include "macros.hpp"
#include "exception.hpp"

#include <sstream>
#include <string>

namespace engine
{
    M_DEF_EXCEPTION(FailedAssertion);

    class Assertion
    {
        public:
            enum class Consequence
            {
                Log,
                Terminate,
                Exception,
            };

            Assertion(std::string expr, const char* file, const char* function, int line,
                      Consequence consequence = Consequence::Terminate);
            ~Assertion();
            Assertion& msg(std::string msg);

            template <typename T>
            Assertion& watchValue(T&& val, const char* name)
            {
                m_oss << "    " << name << " => " << std::forward<T>(val) << "\n";
                return *this;
            }

            [[noreturn]] void ex();

        private:
            const char* m_file;
            const char* m_function;
            int m_line;
            Consequence m_consequence;
            std::stringstream m_oss;
    };
}

#ifndef M_USE_ASSERT
    #ifdef NDEBUG
        #define M_USE_ASSERT false
    #else
        #define M_USE_ASSERT true
    #endif
#endif

#define Assert(expr) (!M_USE_ASSERT || bool(expr))? void(0) : (void)engine::Assertion(M_STR(expr), __FILE__, __FUNCTION__, __LINE__)
#define Check(expr) (bool(expr))? void(0) : (void)engine::Assertion(M_STR(expr), __FILE__, __FUNCTION__, __LINE__, \
        (M_USE_ASSERT ? engine::Assertion::Consequence::Terminate : \
         engine::Assertion::Consequence::Log))

#endif
