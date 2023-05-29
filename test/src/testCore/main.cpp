#include "testCore/runner.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/channel.hpp"
#include "engine/log/linuxDebugDriver.hpp"
#include "engine/log/textFormatter.hpp"
#include "engine/log/entryBuilder.hpp"
#include "engine/log/severityLevelPolicy.hpp"

using namespace engine;
#define engineLog log::EntryBuilder(__FILE__, __FUNCTION__, __LINE__)

int main()
{
    std::unique_ptr<log::IChannel> chan = std::make_unique<log::Channel>(
            std::vector<std::shared_ptr<log::IDriver>> {
                std::make_shared<log::LinuxDebugDriver>(std::make_unique<log::TextFormatter>())
            });
    chan->Attach(std::make_unique<log::SeverityLevelPolicy>(log::Level::Error));

    engineLog.chan(chan.get()).fatal("Oh No!");
    engineLog.chan(chan.get()).warn("warning");
    engineLog.chan(chan.get()).error("Error !");

    if (test::Run())
        return 0;
    return 1;
}
