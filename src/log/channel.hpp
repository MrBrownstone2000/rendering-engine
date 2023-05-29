#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <memory>
#include <vector>

namespace engine::log
{
    struct Entry;
    class IDriver;
    class IPolicy;

    class IChannel
    {
        public:
            virtual ~IChannel() = default;
            virtual void Submit(Entry& entry) = 0;
            virtual void Attach(std::shared_ptr<IDriver> driver) = 0;
            virtual void Attach(std::unique_ptr<IPolicy> policy) = 0;
    };

    class Channel : public IChannel
    {
        public:
            Channel(std::vector<std::shared_ptr<IDriver>> drivers = {}); 
            ~Channel();

            void Submit(Entry& entry) override;
            void Attach(std::shared_ptr<IDriver> driver) override;
            void Attach(std::unique_ptr<IPolicy> policy) override;
        
        private:
            std::vector<std::shared_ptr<IDriver>> m_drivers;
            std::vector<std::unique_ptr<IPolicy>> m_policies;
    };
}

#endif
