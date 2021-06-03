#include "symbol.h"



Type Symbol::getType()
{
    return this->type;
    
}

int Symbol::getSymbol()
{
    return this->symbol;
}


void Symbol::printSymbol()
{

const string terminalStrings[] = { "id" , "+" , "*" , "(" , ")" , "$" , "e" };
const string tokenStrings[] = { "E" , "E_" , "T" , "T_" , "F" };

if(this->getType()==NONTERM)
{
    cout<<tokenStrings[this->getSymbol()]<<'\t'<<"NONTERM"<<endl;
}

if(this->getType()==TERM)
{
    cout<<terminalStrings[this->getSymbol()]<<'\t'<<"TERM"<<endl;
}

}