#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

using namespace engine;

void Boot()
{
    log::Boot();
}

int main()
{
    Boot();

    engineLog.info("The engine is working !");


    return 0;
}
