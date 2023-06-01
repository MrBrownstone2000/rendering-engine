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
    };
}

#endif
