#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <exception>
#include <string>

namespace engine::util
{
    class IException : public std::exception {};

    class BufferedException : public IException
    {
        public:
            BufferedException() = default;
            BufferedException(std::string msg);
            const char* what() const noexcept override;

        private:
            std::string m_msg;
            mutable std::string m_buffer;
    };
}

#define M_DEF_EXCEPTION_FROM(NewType, BaseType) class NewType : public BaseType { using Base = BaseType; public: using Base::Base; }
#define M_DEF_EXCEPTION(NewType) M_DEF_EXCEPTION_FROM(NewType, engine::util::BufferedException)

#endif
