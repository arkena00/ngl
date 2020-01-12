#include <ngl/cluster.hpp>

#include <ngl/log.hpp>

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
    cluster::cluster(std::string name, std::string source)
        : name_{ std::move(name) }
        , source_{ std::move(source) }
        , lexer_{ source_ }
        , parser_{ lexer_ }
        , root_{ nullptr }
    {
        root_ = graph_.add(name_);
        node_ = root_;

        ngl_info("Process cluster {}", name_);
        ngl::ast_listener listener{ *this };
        ngl::traverse(ast(), listener);

    }

    ngl::ast* cluster::ast()
    {
        return parser_.ast();
    }

    ngl::graph& cluster::graph()
    {
        return graph_;
    }

    void cluster::process(ngl::lang::identifier& id)
    {
        /*
        using namespace llvm;

        LLVMContext Context;

        Module* M = new Module("cluster", Context);



        std::vector<Type*> PutCharArgs = { Type::getInt32Ty(Context) };
        FunctionType* PutCharType = FunctionType::get(Type::getInt32Ty(Context), PutCharArgs, false);
        Function::Create(PutCharType, Function::ExternalLinkage, "putchar", M);*/
    }

    nds::node<std::string>* cluster::root()
    {
        return root_;
    }

    void cluster::set_node(nds::node<std::string>* node)
    {
        node_ = node;
    }

    nds::node<std::string>* cluster::node()
    {
        return node_;
    }

} // namespace ngl