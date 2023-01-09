#include <string>
#include "../../swarm/src/vm/runtime/external.h"

using namespace swarmc::Runtime;
using namespace swarmc::Type;
using namespace swarmc::ISA;

namespace egp {

    class HelloWorldFunctionCall : public IProviderFunctionCall {
    public:
        HelloWorldFunctionCall(IProvider* provider) :
            IProviderFunctionCall({}, "HELLO_WORLD", Primitive::of(Intrinsic::STRING)), _provider(provider) {}

        [[nodiscard]] IProvider* provider() const override {
            return _provider;
        }

        void execute(VirtualMachine*) override {
            setReturn(new StringReference("Hello from the example provider!"));
        }

        [[nodiscard]] std::string toString() const override {
            return "egp::HelloWorldFunctionCall<>";
        }

    protected:
        IProvider* _provider;
    };

    class HelloWorldFunction : public IProviderFunction {
    public:
        HelloWorldFunction(IProvider* provider) : IProviderFunction("HELLO_WORLD"), _provider(provider) {}

        [[nodiscard]] FormalTypes paramTypes() const override {
            return {};
        }

        [[nodiscard]] const Type* returnType() const override {
            return Primitive::of(Intrinsic::STRING);
        }

        [[nodiscard]] IFunction* curry(Reference*) const override {
            return new HelloWorldFunction(_provider);
        }

        [[nodiscard]] CallVector getCallVector() const override {
            return {};
        }

        [[nodiscard]] IProvider* provider() const override {
            return _provider;
        }

        [[nodiscard]] IProviderFunctionCall* call(CallVector) const override {
            return new HelloWorldFunctionCall(_provider);
        }

        [[nodiscard]] std::string toString() const override {
            return "egp::HelloWorldFunction<>";
        }
    protected:
        IProvider* _provider;
    };

    class ExampleProvider : public IProvider {
    public:
        ExampleProvider(IGlobalServices* global) : _global(global) {}

        [[nodiscard]] IProviderFunction* loadFunction(std::string name) override {
            if ( name == "HELLO_WORLD" ) return new HelloWorldFunction(this);
            return nullptr;
        }

        [[nodiscard]] IGlobalServices* global() const override {
            return _global;
        }

        void call(VirtualMachine* vm, IProviderFunctionCall* call) override {
            call->execute(vm);
        }

        [[nodiscard]] std::string toString() const override {
            return "egp::ExampleProvider<>";
        }

    protected:
        IGlobalServices* _global;
    };

    class ExampleProviderModule : public ProviderModule {
    public:
        [[nodiscard]] IProvider* build(IGlobalServices* global) override {
            return new ExampleProvider(global);
        }
    };

}

extern "C" egp::ExampleProviderModule* factory() {
    return new egp::ExampleProviderModule;
}
