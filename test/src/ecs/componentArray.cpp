#include "testCore/asserts.hpp"
#include "testCore/test.hpp"

#include "engine/ecs/ecs.hpp"

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

TEST_MODULE(ECS_ComponentArray)
{
    TEST(PushBack_Get_Data)
    {
        ecs::ComponentArray array;

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        array.push_back(c1);

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        array.push_back(c2);
        
        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        array.push_back(c3);

        TestComponent c4;
        c4.i = 4;
        c4.d = 40.1;
        c4.c = 'd';

        array.push_back(c4);

        test::expect_eq(array.at<TestComponent>(0), c1);
        test::expect_eq(array.at<TestComponent>(1), c2);
        test::expect_eq(array.at<TestComponent>(2), c3);
        test::expect_eq(array.at<TestComponent>(3), c4);
    }

    TEST(SetBack_Get_Data)
    {
        ecs::ComponentArray array;
        array.setup(sizeof(TestComponent));

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c1);

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c2);
        
        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c3);

        TestComponent c4;
        c4.i = 4;
        c4.d = 40.1;
        c4.c = 'd';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c4);

        test::expect_eq(array.at<TestComponent>(0), c1);
        test::expect_eq(array.at<TestComponent>(1), c2);
        test::expect_eq(array.at<TestComponent>(2), c3);
        test::expect_eq(array.at<TestComponent>(3), c4);
    }

    TEST(ModifyData)
    {
        ecs::ComponentArray array;

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        array.push_back(c1);

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c2);
        
        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        array.push_back(c3);

        TestComponent c4;
        c4.i = 4;
        c4.d = 40.1;
        c4.c = 'd';

        array.push_back(c4);

        test::expect_eq(array.at<TestComponent>(0), c1);
        test::expect_eq(array.at<TestComponent>(1), c2);
        test::expect_eq(array.at<TestComponent>(2), c3);
        test::expect_eq(array.at<TestComponent>(3), c4);

        array.at<TestComponent>(2) = c1;
        test::expect_eq(array.at<TestComponent>(2), c1);
    }

    TEST(ResizeArray)
    {
        ecs::ComponentArray array(1);

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        array.push_back(c1);

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c2);

        array.push_back(c3);

        test::expect_eq(array.at<TestComponent>(0), c1);
        test::expect_eq(array.at<TestComponent>(1), c2);
        test::expect_eq(array.at<TestComponent>(2), c3);
    }

    TEST(EraseLastElt)
    {
        ecs::ComponentArray array;

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        array.push_back(c1);

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c2);
        
        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        array.push_back(c3);

        TestComponent c4;
        c4.i = 4;
        c4.d = 40.1;
        c4.c = 'd';

        array.push_back(c4);

        array.erase(3);

        test::expect_eq(array.at<TestComponent>(0), c1);
        test::expect_eq(array.at<TestComponent>(1), c2);
        test::expect_eq(array.at<TestComponent>(2), c3);
        test::expect_eq(array.size(), 3ul);
    }

    TEST(EraseElt)
    {
        ecs::ComponentArray array;

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        array.push_back(c1);

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        array.insertEmpty();
        array.set_back(sizeof(TestComponent), &c2);
        
        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        array.push_back(c3);

        TestComponent c4;
        c4.i = 4;
        c4.d = 40.1;
        c4.c = 'd';

        array.push_back(c4);

        array.erase(0);

        test::expect_eq(array.at<TestComponent>(0), c2);
        test::expect_eq(array.at<TestComponent>(1), c3);
        test::expect_eq(array.at<TestComponent>(2), c4);
        test::expect_eq(array.size(), 3ul);
    }

    TEST(BigData)
    {
        constexpr u64 nb_elts = (1 << 16) - 1;
        ecs::ComponentArray array;

        TestComponent c1;
        c1.i = 1;
        c1.d = 10.1;
        c1.c = 'a';

        TestComponent c2;
        c2.i = 2;
        c2.d = 20.1;
        c2.c = 'b';

        TestComponent c3;
        c3.i = 3;
        c3.d = 30.1;
        c3.c = 'c';

        for (u64 i = 0; i < nb_elts; i += 3)
        {
            array.push_back(c1);
            array.push_back(c2);
            array.push_back(c3);
        }

        for (u64 i = 0; i < nb_elts; i += 3)
        {
            test::expect_eq(array.at<TestComponent>(i), c1);
            test::expect_eq(array.at<TestComponent>(i + 1), c2);
            test::expect_eq(array.at<TestComponent>(i + 2), c3);
        }
    }

    // TEST(WrongType)
    // {
    //     ecs::ComponentArray array;

    //     TestComponent c1;
    //     c1.i = 1;
    //     c1.d = 10.1;
    //     c1.c = 'a';

    //     array.push_back(c1);

    //     array.push_back(1);
    // }
}
