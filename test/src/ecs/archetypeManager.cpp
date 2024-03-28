#include "UnitTests/asserts.hpp"
#include "UnitTests/test.hpp"

#include "Engine/ecs/ecs.hpp"

using namespace engine;

namespace
{
    struct TestComponent
    {
        int i;
        double d;
        char c;

        bool operator==(const TestComponent& rhs) const
        {
            return i == rhs.i && d == rhs.d && c == rhs.c;
        }
    };

    std::stringstream& operator<< (std::stringstream& ss, const TestComponent& rhs)
    {
        ss << "(" << rhs.i << ", ";
        ss << rhs.d << ", ";
        ss << rhs.c << ")";
        return ss;
    }
}

TEST_MODULE(ECS_ArchetypeManager)
{
    TEST(TODO)
    {
        throw 1;
    }
}
