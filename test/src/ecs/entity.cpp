#include "testCore/asserts.hpp"
#include "testCore/test.hpp"

#include "engine/ecs/ecs.hpp"

#include <vector>

using namespace engine;

namespace
{
    struct TestComponent1
    {
        int i;
        double d;
        char c;

        bool operator==(const TestComponent1& rhs) const
        {
            return i == rhs.i && d == rhs.d && c == rhs.c;
        }
    };

    std::stringstream& operator<< (std::stringstream& ss, const TestComponent1& rhs)
    {
        ss << "(" << rhs.i << ", ";
        ss << rhs.d << ", ";
        ss << rhs.c << ")";
        return ss;
    }

    struct TestComponent2
    {
        double x, y, z;

        bool operator==(const TestComponent2& rhs) const
        {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }
    };

    std::stringstream& operator<< (std::stringstream& ss, const TestComponent2& rhs)
    {
        ss << "(" << rhs.x << ", ";
        ss << rhs.y << ", ";
        ss << rhs.z << ")";
        return ss;
    }
}

TEST_MODULE(ECS_Entity)
{
    TEST(AddComponent)
    {
        ecs::World::clear();

        ecs::Entity e(0,0);
        TestComponent1 c1Start = {1, 2., 'a'};
        TestComponent2 c2Start = {1., 2., 3.};

        e.add<TestComponent1>(c1Start);

        test::expect(e.hasComponent<TestComponent1>());
        test::expect(!e.hasComponent<TestComponent2>());
        test::expect_eq(c1Start, e.get<TestComponent1>());

        e.add<TestComponent2>(c2Start);

        test::expect(e.hasComponent<TestComponent1>());
        test::expect(e.hasComponent<TestComponent2>());
        test::expect_eq(c2Start, e.get<TestComponent2>());
        test::expect_eq(c1Start, e.get<TestComponent1>());
    }

    TEST(RemoveComponent)
    {
        ecs::World::clear();

        ecs::Entity e(0,0);
        TestComponent1 c1Start = {1, 2., 'a'};
        TestComponent2 c2Start = {1., 2., 3.};

        e.add<TestComponent1>(c1Start);

        test::expect_eq(c1Start, e.get<TestComponent1>());

        e.add<TestComponent2>(c2Start);

        test::expect_eq(c2Start, e.get<TestComponent2>());
        test::expect_eq(c1Start, e.get<TestComponent1>());

        e.remove<TestComponent1>();
        test::expect_eq(c2Start, e.get<TestComponent2>());

        test::expect_exception<ecs::BadComponent>([&]()
        {
            e.get<TestComponent1>(); 
        });
    }

    TEST(ManyEntities)
    {
        ecs::World::clear();

        std::vector<ecs::Entity> e;
        TestComponent1 c1Special = {1, 2., 'a'};
        TestComponent2 c2Special = {1., 2., 3.};
        TestComponent1 c1Rand = {4, -18., 'i'};
        TestComponent2 c2Rand = {13., 19., -35.};

        for (int i = 0; i < 666; ++i)
        {
            e.push_back(ecs::Entity(i, 0));
            if (i == 439)
            {
                e[i].add(c1Special);
                e[i].add(c2Special);
            }
            else
            {
                e[i].add(c1Rand);
                e[i].add(c2Rand);
            }
        }

        for (int i = 0; i < 666; ++i)
        {
            if (i == 439)
            {
                test::expect_eq(c1Special, e[i].get<TestComponent1>());
                test::expect_eq(c2Special, e[i].get<TestComponent2>());
            }
            else
            {
                test::expect_eq(c1Rand, e[i].get<TestComponent1>());
                test::expect_eq(c2Rand, e[i].get<TestComponent2>());
            }
        }

        for (int i = 0; i < 666; ++i)
            e[i].remove();

    }
}

