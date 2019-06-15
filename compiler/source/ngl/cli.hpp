#ifndef COMPILER_SOURCE_NGL_CLI_HPP_NGL
#define COMPILER_SOURCE_NGL_CLI_HPP_NGL

namespace ngl
{
    class compiler;

    class cli
    {
    public:
        cli(ngl::compiler&, const char** argv);

    private:
        ngl::compiler& nglc_;
    };
} // ngl

#endif // COMPILER_SOURCE_NGL_CLI_HPP_NGL
