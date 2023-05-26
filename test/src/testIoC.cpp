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
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();

        pIoC->Register<Base>([] { return std::make_shared<Derived>(); });
        assert(69 == pIoC->Resolve<Base>()->test());
    }

    TEST(SimpleResolveFailure)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();

        bool hasException = false;
        try
        {
            pIoC->Resolve<Base>()->test();
        }
        catch(std::runtime_error&)
        {
            hasException = true;
        }
        assert(hasException);
    }

    TEST(ParameterizedResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();

        pIoC->Register<ParameterizedClass>([](ParameterizedClass::IocParams p){
            return std::make_shared<ParameterizedClass>(std::move(p));
        });
        assert(pIoC->Resolve<ParameterizedClass>({"toto"})->s == "toto");
    }

    TEST(CascadedResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();

        pIoC->Register<Dependant>([=] {
            return std::make_shared<Dependant>(pIoC->Resolve<Base>());
        });
        pIoC->Register<Base>([] { return std::make_shared<Base>(); });
        assert(42 == pIoC->Resolve<Base>()->test());
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

        assert(pFirst->s == "first");
        assert(pSecond->s == "second");

        pFirst->s = "toto";

        assert(pFirst->s == "toto");
        assert(pSecond->s == "second");
    }

    TEST(ReplacementInjection)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();

        pIoC->Register<Dependant>([=] {
            return std::make_shared<Dependant>(pIoC->Resolve<Base>());
        });
        pIoC->Register<Base>([] { return std::make_shared<Base>(); });

        assert(42 == pIoC->Resolve<Base>()->test());

        pIoC->Register<Base>([] { return std::make_shared<Derived>(); });

        assert(69 == pIoC->Resolve<Base>()->test());
    }
}
