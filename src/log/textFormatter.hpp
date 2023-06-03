#ifndef __TEXTFORMATTER_HPP__
#define __TEXTFORMATTER_HPP__

#include <string>

namespace engine::log
{
    class Entry;

    class ITextFormatter
    {
        public:
            virtual ~ITextFormatter() = default;
            virtual std::string Format(const Entry&) const = 0;
    };

    class TextFormatter : public ITextFormatter
    {
        public:
            std::string Format(const Entry&) const override;
        private:
            std::string c_fatal =  "\033[1;38;5;196m";
            std::string c_error = "\033[38;5;196m";
            std::string c_warn = "\033[38;5;202m";
            std::string c_info = "\033[38;5;77m";
            std::string c_debug = "\033[38;5;12m";
            std::string c_normal = "\033[0m";
    };
}

#endif
