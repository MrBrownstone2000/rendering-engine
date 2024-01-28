#include "testCore/runner.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"
#include "engine/util/assert.hpp"

using namespace engine;

void Boot()
{
    log::Boot();

    // ioc::Get().Register<log::ISeverityLevelPolicy>([] {
    //     return std::make_shared<log::SeverityLevelPolicy>(log::Level::None);
    // });
}

int main()
{
    Boot();

    if (test::Run())
        return 0;
    return 1;
}
