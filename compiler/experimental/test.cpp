#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"


#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"


using namespace llvm;

int main(int argc, char** argv)
{
    LLVMContext Context;

    // Create the "module" or "program" or "translation unit" to hold the
    // function
    Module* M = new Module("test", Context);



    std::vector<Type*> PutCharArgs = { Type::getInt32Ty(Context) };
    FunctionType* PutCharType = FunctionType::get(Type::getInt32Ty(Context), PutCharArgs, false);
    Function::Create(PutCharType, Function::ExternalLinkage, "putchar", M);





    // Create the main function: first create the type 'int ()'
    FunctionType* FT = FunctionType::get(Type::getInt32Ty(Context), /*not vararg*/ false);

    // By passing a module as the last parameter to the Function constructor,
    // it automatically gets appended to the Module.
    Function* F = Function::Create(FT, Function::ExternalLinkage, "main", M);

    // Add a basic block to the function... again, it automatically inserts
    // because of the last argument.
    BasicBlock* BB = BasicBlock::Create(Context, "EntryBlock", F);
    Value* Two = ConstantInt::get(Type::getInt32Ty(Context), 2);
    Value* Three = ConstantInt::get(Type::getInt32Ty(Context), 3);
    Instruction* Add = BinaryOperator::Create(Instruction::Add, Two, Three, "addresult");
    BB->getInstList().push_back(Add);




    IRBuilder<> Builder(Context);
    Builder.SetInsertPoint(BB);

    auto putchar = M->getFunction("putchar");

    Value* display = ConstantInt::get(Type::getInt32Ty(Context), 97);
    Builder.CreateCall(putchar, {display});


    // Create the return instruction and add it to the basic block
    BB->getInstList().push_back(ReturnInst::Create(Context, Three));





    // Initialize the target registry etc.
    LLVMInitializeX86Target();
    LLVMInitializeX86AsmParser();
    LLVMInitializeX86AsmPrinter();
    LLVMInitializeX86TargetInfo();
    LLVMInitializeX86TargetMC();

    auto TargetTriple = sys::getDefaultTargetTriple();
    M->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target)
    {
        errs() << Error;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    M->setDataLayout(TheTargetMachine->createDataLayout());

    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC);

    if (EC)
    {
        errs() << "Could not open file: " << EC.message();
        return 1;
    }

    legacy::PassManager pass;
    auto FileType = TargetMachine::CGFT_ObjectFile;


    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
    {
        errs() << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run(*M);
    dest.flush();

    llvm::raw_fd_ostream llvmir("output_ir", EC);
    llvm::WriteBitcodeToFile(*M, llvmir);
    llvmir.flush();

    // Delete the module and all of its contents.
    delete M;

    return 0;
}
