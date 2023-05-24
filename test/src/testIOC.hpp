#ifndef __TESTIOC_HPP__
#define __TESTIOC_HPP__

#include "test.hpp"
 
#include "engine/ioc/container.hpp"

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

class TestIOC : public Test
{
    public:
        bool init() override
        {
            return true;
        }

        void run() override
        {
            // PolymorphicResolve
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();

                pIoC->Register<Base>([] { return std::make_shared<Derived>(); });
                assert(69 == pIoC->Resolve<Base>()->test());
            }

            // SimpleResolveFailure
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();

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

            // ParameterizedResolve
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();

                pIoC->Register<ParameterizedClass>([](ParameterizedClass::IocParams p){
                    return std::make_shared<ParameterizedClass>(std::move(p));
                });
                assert(pIoC->Resolve<ParameterizedClass>({"toto"})->s == "toto");
            }

            // CascadedResolve
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();

                pIoC->Register<Dependant>([this] {
                    return std::make_shared<Dependant>(pIoC->Resolve<Base>());
                });
                pIoC->Register<Base>([] { return std::make_shared<Base>(); });
                assert(42 == pIoC->Resolve<Base>()->test());
            }

            // IndependantResolve
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();

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

            // ReplacementInjection
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();

                pIoC->Register<Dependant>([this] {
                    return std::make_shared<Dependant>(pIoC->Resolve<Base>());
                });
                pIoC->Register<Base>([] { return std::make_shared<Base>(); });

                assert(42 == pIoC->Resolve<Base>()->test());

                pIoC->Register<Base>([] { return std::make_shared<Derived>(); });

                assert(69 == pIoC->Resolve<Base>()->test());
            }
        }

        void shutdown() override
        {
        }
    private:
        std::unique_ptr<ioc::Container> pIoC;

};

#endif
