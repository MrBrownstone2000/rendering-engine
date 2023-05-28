#include "channel.hpp"

#include "driver.hpp"

namespace engine::log
{
    Channel::Channel(std::vector<std::shared_ptr<IDriver>> drivers)
        : m_drivers(drivers)
    {
    }

    void Channel::Submit(Entry& entry) 
    {
        for (auto& d : m_drivers)
            d->Submit(entry);
    }

    void Channel::Attach(std::shared_ptr<IDriver> driver) 
    {
        m_drivers.push_back(std::move(driver));
    }
}
