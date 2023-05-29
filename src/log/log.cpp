#include "log.hpp"

#include "../ioc/singleton.hpp"
#include "../ioc/container.hpp"
#include "../log/channel.hpp"
#include "../log/driver.hpp"
#include "../log/severityLevelPolicy.hpp"
#include "../log/linuxDebugDriver.hpp"
#include "log/fileDriver.hpp"
#include "log/level.hpp"
#include "log/textFormatter.hpp"

namespace engine::log
{
    IChannel* GetDefaultChannel()
    {
        static std::shared_ptr<IChannel> channelCache = ioc::Sing().Resolve<IChannel>();
        return channelCache.get();
    }

    void Boot()
    {
        // Init container
        ioc::Get().Register<log::IChannel>([] {
            std::vector<std::shared_ptr<IDriver>> drivers {
                ioc::Get().Resolve<log::IDebugDriver>(),
                ioc::Get().Resolve<log::IFileDriver>()
            };
            auto chan = std::make_shared<log::Channel>(std::move(drivers));
            chan->Attach(ioc::Get().Resolve<log::ISeverityLevelPolicy>());
            return chan;
        });

        ioc::Get().Register<log::IDebugDriver>([] {
            return std::make_shared<log::LinuxDebugDriver>( ioc::Get().Resolve<log::ITextFormatter>() );
        });

        ioc::Get().Register<log::IFileDriver>([] {
            return std::make_shared<log::FileDriver>( "logs/log.txt", ioc::Get().Resolve<log::ITextFormatter>() );
        });

        ioc::Get().Register<log::ITextFormatter>([] {
            return std::make_shared<log::TextFormatter>();
        });

        ioc::Get().Register<log::ISeverityLevelPolicy>([] {
            return std::make_shared<log::SeverityLevelPolicy>(log::Level::Error);
        });

        // Init singleton
        ioc::Sing().RegisterPassThru<log::IChannel>();
    }
}
