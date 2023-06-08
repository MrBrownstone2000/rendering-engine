#include "engine/ioc/container.hpp"

#include "testCore/test.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>

class Base
{
    public:
        virtual int test() { return 42; }
        virtual ~Base() {}
};

class Derived : public Base
{
    public:
        int test() override { return 69; }
};

struct ParameterizedClass
{
	struct IocParams
	{
		std::string s;
	};
	ParameterizedClass(IocParams params) : s{ std::move(params.s) } {}
	std::string s;
};

struct Dependant
{
	std::shared_ptr<Base> pDependency;
	Dependant(std::shared_ptr<Base> pDependency_in) : pDependency{ std::move(pDependency_in) } {}
};

using namespace engine;

TEST_MODULE(IoC)
{
    TEST(PolymorphicResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_shared<ioc::Container>();

        pIoC->Register<Base>([] { return std::make_shared<Derived>(); });
        test::expect_eq(69, pIoC->Resolve<Base>()->test());
    }

    TEST(SimpleResolveFailure)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_shared<ioc::Container>();

        test::expect_exception<ioc::ServiceNotFound>([pIoC] { pIoC->Resolve<Base>()->test(); });
    }

    TEST(ParameterizedResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_shared<ioc::Container>();

        pIoC->Register<ParameterizedClass>([](ParameterizedClass::IocParams p){
            return std::make_shared<ParameterizedClass>(std::move(p));
        });
        test::expect_eq(pIoC->Resolve<ParameterizedClass>({"toto"})->s, "toto");
    }

    TEST(CascadedResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_shared<ioc::Container>();

        pIoC->Register<Dependant>([&] {
            return std::make_shared<Dependant>(pIoC->Resolve<Base>());
        });
        pIoC->Register<Base>([] { return std::make_shared<Base>(); });
        test::expect_eq(42, pIoC->Resolve<Dependant>()->pDependency->test());
    }

    TEST(IndependantResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();

        pIoC->Register<ParameterizedClass>([](ParameterizedClass::IocParams p){
            return std::make_shared<ParameterizedClass>(std::move(p));
        });

        auto pFirst = pIoC->Resolve<ParameterizedClass>({ .s = "first" });
        auto pSecond = pIoC->Resolve<ParameterizedClass>({ .s = "second" });

        test::expect_eq(pFirst->s, "first");
        test::expect_eq(pSecond->s, "second");

        pFirst->s = "toto";

        test::expect_eq(pFirst->s, "toto");
        test::expect_eq(pSecond->s, "second");
    }

    TEST(ReplacementInjection)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_shared<ioc::Container>();

        pIoC->Register<Dependant>([&] {
            return std::make_shared<Dependant>(pIoC->Resolve<Base>());
        });
        pIoC->Register<Base>([] { return std::make_shared<Base>(); });

        test::expect_eq(42, pIoC->Resolve<Dependant>()->pDependency->test());

        pIoC->Register<Base>([] { return std::make_shared<Derived>(); });

        test::expect_eq(69, pIoC->Resolve<Dependant>()->pDependency->test());
    }
}
