#include "testCore/test.hpp"

#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"

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

TEST_MODULE(Singletons)
{
    TEST(PolymorphicResolveDirect)
    {
        // Init test method
        std::shared_ptr<ioc::Singletons> pSing = std::make_unique<ioc::Singletons>();

        pSing->Register<Base>([] { return std::make_shared<Derived>(); });
        expect_eq(69, pSing->Resolve<Base>()->test());
    }

    TEST(PolymorphicResolveIndirect)
    {
        // Init test method
        std::shared_ptr<ioc::Container> pIoC = std::make_unique<ioc::Container>();
        std::shared_ptr<ioc::Singletons> pSing = std::make_unique<ioc::Singletons>();

        pIoC->Register<Base>([] { return std::make_shared<Derived>(); });
        pSing->Register<Base>([=] { return pIoC->Resolve<Base>(); });
        expect_eq(69, pSing->Resolve<Base>()->test());
    }

    TEST(SimpleResolveFailure)
    {
        // Init test method
        std::shared_ptr<ioc::Singletons> pSing = std::make_unique<ioc::Singletons>();

        expect_exception(std::runtime_error, pSing->Resolve<Base>()->test());
    }

    TEST(DependantResolve)
    {
        // Init test method
        std::shared_ptr<ioc::Singletons> pSing = std::make_unique<ioc::Singletons>();

        pSing->Register<ParameterizedClass>([](){
            return std::make_shared<ParameterizedClass>(ParameterizedClass::IocParams{ .s = "first" });
        });

        auto pFirst = pSing->Resolve<ParameterizedClass>();
        auto pSecond = pSing->Resolve<ParameterizedClass>();

        expect_eq(pFirst->s, "first");
        expect_eq(pSecond->s, "first");

        pFirst->s = "second";

        expect_eq(pFirst->s, "second");
        expect_eq(pSecond->s, "second");
    }
}
