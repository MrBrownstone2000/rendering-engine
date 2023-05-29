#include "channel.hpp"

#include "driver.hpp"
#include "policy.hpp"

namespace engine::log
{
    Channel::Channel(std::vector<std::shared_ptr<IDriver>> drivers)
        : m_drivers(drivers)
    {
    }

    Channel::~Channel()
    {
    }

    void Channel::Submit(Entry& entry) 
    {
        for (auto& p : m_policies)
            if (!p->TransformFilter(entry))
                return;

        for (auto& d : m_drivers)
            d->Submit(entry);
    }

    void Channel::Attach(std::shared_ptr<IDriver> driver) 
    {
        m_drivers.push_back(std::move(driver));
    }

    void Channel::Attach(std::unique_ptr<IPolicy> policy)
    {
        m_policies.push_back(std::move(policy));
    }
}
