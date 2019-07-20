#include <ngl/cluster.hpp>

#include <nds/encoder/graph.hpp>
#include <ngl/ast/listener.hpp>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

namespace ngl
{
    cluster::cluster(std::string source)
        : source_{ std::move(source) }
        , lexer_{ source_ }
        , parser_{ lexer_ }
    {
        ngl::ast_listener listener{ *this };
        ngl::traverse(ast(), listener);

        std::cout << "\n\n";
        nds::encoders::dot<>::encode<nds::console>(graph_);
    }

    ngl::ast* cluster::ast()
    {
        return parser_.ast();
    }

    void cluster::build()
    {
        using namespace llvm;

        LLVMContext Context;

        Module* M = new Module("cluster", Context);



        std::vector<Type*> PutCharArgs = { Type::getInt32Ty(Context) };
        FunctionType* PutCharType = FunctionType::get(Type::getInt32Ty(Context), PutCharArgs, false);
        Function::Create(PutCharType, Function::ExternalLinkage, "putchar", M);
    }

} // namespace ngl