//
// Created by luket on 19/08/2020.
//

#ifndef LUNALUXENGINE_TESTGROUND_SHADERPARCE_H
#define LUNALUXENGINE_TESTGROUND_SHADERPARCE_H
#include <string>
#include <vector>
namespace LunaLuxEngine
{
    class LLEShaderLanguage
    {
    private:
        enum class LLES_TOCKENS
        {
            IN,
            OUT,
            UNF,
            FUN,
            FUNI,
            FUNF,
            FUND,
            BRAK,
            FNE,
            GLB,
            INT,
            FLT,
            DUB,
            VEC2,
            VEC3,
            MAT4,
            DIV,
            MUL,
            ADD,
            SUB,
            EQL,
            RET,
            LEND,
            OTHER,
            NUL
        };
        struct TOCKEN
        {
        public:
            LLES_TOCKENS tocken = LLES_TOCKENS::NUL;
            std::string value = "";
        };

        std::vector<TOCKEN> parceFromFiletoTockens(std::string, bool);

        void parceVariablestoTockens(std::string &, std::vector<std::string> &, std::vector<TOCKEN> &, int &);

        bool parceVariablesTokentoTockens(std::string &, std::vector<std::string> &, std::vector<TOCKEN> &, int &);

        std::vector<TOCKEN> parceSubTockentoTockens(std::string, bool);

        std::string convertToGLSL(std::string, bool);

    public:
        std::string parceFileToShader(std::string, bool, bool);
    };
}
#endif //LUNALUXENGINE_TESTGROUND_SHADERPARCE_H