#include "parser.h"

void Parser::parse()
{
    vector<string> vec;
    char c; 
    string text;

    const string terminalStrings[] = { "id" , "+" , "*" , "(" , ")" , "$" , "e" };
    const string tokenStrings[] = { "E" , "E_" , "T" , "T_" , "F" };
    while(!this->inputFile.eof())
    {
       
        
        if(!text.empty() && (c=='(' || c==')'))
        {
            
            
            vec.push_back(text);
            text.clear(); 
        }
        
        if(!text.empty() && (text=="id" || text=="+" || text=="*"))
        {
            
            vec.push_back(text);
            text.clear();
        }
        
        
         this->inputFile.get(c); 
        
         if(c!=' ')
            text+=c;
          

    }

    vector<string> help;
    
    string pos;
    string poshelp;
    string lcut;
    string savelcut;
    int orIndex;
    bool error=false;
    
  
        stack.push_back(Symbol(E, NONTERM));
        pos="| "+tokenStrings[(int)E];
        help.push_back(pos);
        pos.clear();
   
     
    
    

    for(int i=0; i<vec.size() && error==false; i++)
    {
        

        if(vec[i]=="id")
        {
            

            if(stack.back().getSymbol()==(int)T_)
            {
                
                error=true;
                break;
            }
            
            
            if(stack.back().getSymbol()==(int)E && this->table[E][ID]==0)
            {
                
                if(pos.empty())
                {
                    stack.pop_back();
                    pos="|";
                    for(int j=0; j< this->rules[0].size(); j++)
                    {
                        stack.push_back(this->rules[0][j]);
                        pos+=" "+tokenStrings[this->rules[0][this->rules[0].size()-1-j].getSymbol()];
                     
                    }

                    help.push_back(pos);
                }
                else
                {
                    stack.pop_back();   
                    int index;
                
                    for(int j=0; j<pos.size(); j++)
                    {
                        if(pos[j]=='|')
                        {
                            orIndex=j;
                            break;
                        }
                    }

                    for(int j=orIndex; j<pos.size(); j++)
                    {
                        if(pos[j]=='E')
                        {
                            index=j;
                            break;
                        }
                    }

                    pos.erase(index,2);

                    for(int j=0; j< this->rules[0].size(); j++)
                    {
                        stack.push_back(this->rules[0][j]);
                        poshelp+=tokenStrings[this->rules[0][this->rules[0].size()-1-j].getSymbol()]+ " ";
                    }

                    pos.insert(index,poshelp);
                    help.push_back(pos);
                    poshelp.clear();



                }
                
                
            }
            
            if(stack.back().getSymbol()==(int)T && this->table[T][ID]==3)
            {
               
               
                stack.pop_back();   
                int index;
                
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='|')
                    {
                        orIndex=j;
                        break;
                    }
                }
                
                
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='T')
                    {
                        index=j;
                        break;
                    }
                }

                pos.erase(index,2);
                for(int j=0; j< this->rules[3].size(); j++)
                {
                     stack.push_back(this->rules[3][j]);
                     poshelp+=tokenStrings[this->rules[3][this->rules[3].size()-1-j].getSymbol()]+ " ";
                }
                pos.insert(index,poshelp);
                help.push_back(pos);
                poshelp.clear();
               
            }

            if(stack.back().getSymbol()==(int)F && this->table[F][ID]==7)
            {
                
               
                stack.pop_back();
                int index;
                
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='|')
                    {
                        orIndex=j;
                        break;
                    }
                }
                
                
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='F')
                    {
                        index=j;
                        break;
                    }
                }
                pos.erase(index,2);

                poshelp=terminalStrings[this->rules[7][0].getSymbol()]+ " ";

                pos.insert(index,poshelp);
                help.push_back(pos);
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='i' && pos[j+1]=='d')
                    {
                        index=j;
                        break;
                    }
                    
                }

                accepted.push_back(this->rules[7][0]);
                int size=lcut.size();
                
                lcut+=terminalStrings[this->rules[7][0].getSymbol()] + " ";
                savelcut+=terminalStrings[this->rules[7][0].getSymbol()] + " ";
                pos.erase(index,3);
                pos.insert(size,savelcut);
                help.push_back(pos);
               
                poshelp.clear();
                savelcut.clear();
                
                
            }


        }


        if(vec[i]=="+")
        {
               
            if(stack.back().getSymbol()==(int)T_ && this->table[T_][PLUS]==5)
            {   
                
                stack.pop_back();
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='T'&& pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                
                help.push_back(pos);

            }

            if(stack.back().getSymbol()==(int)E_ && this->table[E_][PLUS]==1)
            {
               
                
                stack.pop_back();
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='E' && pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                poshelp+=terminalStrings[this->rules[1][this->rules[1].size()-1].getSymbol()] + " ";
                for(int j=0; j<this->rules[1].size()-1; j++)
                {
                    stack.push_back(this->rules[1][j]);

                    poshelp+=tokenStrings[this->rules[1][this->rules[1].size()-2-j].getSymbol()] + " ";
                    
                }


                accepted.push_back(this->rules[1][2]);

               
                int size=lcut.size();  
                lcut+=terminalStrings[this->rules[1][2].getSymbol()] + " ";
                savelcut+=terminalStrings[this->rules[1][2].getSymbol()] + " ";
              
                pos.insert(index,poshelp);
             
                help.push_back(pos); 
                poshelp.clear();

                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='|')
                    {
                        orIndex=j;
                        break;
                    }
                }
                
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='+')
                    {
                        index=j;
                        break;
                    }
                }
              
                
                pos.erase(index,2);
             
                pos.insert(size,savelcut);
                help.push_back(pos);
                savelcut.clear();

            }
        }

        if(vec[i]=="*")
        {
           
            if(stack.back().getSymbol()==(int)T_ && this->table[T_][ASTERISK]==4)
            {
                stack.pop_back();
                
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='T' && pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                poshelp+=terminalStrings[this->rules[4][this->rules[4].size()-1].getSymbol()] + " ";

                for(int j=0; j<this->rules[4].size()-1; j++)
                {
                    stack.push_back(this->rules[4][j]);

                    poshelp+=tokenStrings[this->rules[4][this->rules[4].size()-2-j].getSymbol()] + " ";
                      

                }

                accepted.push_back(this->rules[4][2]);

                int size=lcut.size();  
                lcut+=terminalStrings[this->rules[4][2].getSymbol()] + " ";
                savelcut+=terminalStrings[this->rules[4][2].getSymbol()] + " ";

                pos.insert(index,poshelp);
                help.push_back(pos); 
                poshelp.clear();

                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='|')
                    {
                        orIndex=j;
                        break;
                    }
                }
                
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='*')
                    {
                        index=j;
                        break;
                    }
                }

                pos.erase(index,2);
             
                pos.insert(size,savelcut);
                help.push_back(pos);
                savelcut.clear();

            }
        }

        if(vec[i]=="(")
        {
            
            
            if(stack.back().getSymbol()==(int)E && this->table[E][LPAREN]==0)
            {
                if(pos.empty())
                {
                    stack.pop_back();
                    pos="|";
                    for(int j=0; j< this->rules[0].size(); j++)
                    {
                        stack.push_back(this->rules[0][j]);
                        pos+=" "+tokenStrings[this->rules[0][this->rules[0].size()-1-j].getSymbol()];
                     
                    }

                    help.push_back(pos);
                }
                else
                {
                    stack.pop_back();   
                    int index;
                
                    for(int j=0; j<pos.size(); j++)
                    {
                        if(pos[j]=='|')
                        {
                            orIndex=j;
                            break;
                        }
                    }

                    for(int j=orIndex; j<pos.size(); j++)
                    {
                        if(pos[j]=='E')
                        {
                            index=j;
                            break;
                        }
                    }

                    pos.erase(index,2);

                    for(int j=0; j< this->rules[0].size(); j++)
                    {
                        stack.push_back(this->rules[0][j]);
                        poshelp+=tokenStrings[this->rules[0][this->rules[0].size()-1-j].getSymbol()]+ " ";
                    }

                    pos.insert(index,poshelp);
                    help.push_back(pos);
                    poshelp.clear();



                }
            }

            if(stack.back().getSymbol()==(int)T && this->table[T][LPAREN]==3)
            {

                stack.pop_back();   
                int index;
                
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='|')
                    {
                        orIndex=j;
                        break;
                    }
                }
                
                
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='T')
                    {
                        index=j;
                        break;
                    }
                }

                pos.erase(index,2);
                for(int j=0; j< this->rules[3].size(); j++)
                {
                     stack.push_back(this->rules[3][j]);
                     poshelp+=tokenStrings[this->rules[3][this->rules[3].size()-1-j].getSymbol()]+ " ";
                }
                pos.insert(index,poshelp);
                help.push_back(pos);
                poshelp.clear();
               
            }
            
            
            if(stack.back().getSymbol()==(int)F && this->table[F][LPAREN]==6)
            {
                stack.pop_back();

                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='|')
                    {
                        orIndex=j;
                        break;
                    }
                }
                
                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='F')
                    {
                        index=j;
                    }
                }

                pos.erase(index,2);
                poshelp+=terminalStrings[this->rules[6][this->rules[6].size()-1].getSymbol()] + " ";
                poshelp+=tokenStrings[this->rules[6][this->rules[6].size()-2].getSymbol()] + " ";
                poshelp+=terminalStrings[this->rules[6][this->rules[6].size()-3].getSymbol()] + " ";
                for(int j=0; j<this->rules[6].size()-1; j++)
                {
                    stack.push_back(this->rules[6][j]);

                }

                pos.insert(index,poshelp);
                help.push_back(pos);


                for(int j=orIndex; j<pos.size(); j++)
                {
                    if(pos[j]=='(')
                    {
                        index=j;
                        break;
                    }
                    
                }

                accepted.push_back(this->rules[6][2]);
                int size=lcut.size();
                
                lcut+=terminalStrings[this->rules[6][2].getSymbol()] + " ";
                savelcut+=terminalStrings[this->rules[6][2].getSymbol()] + " ";
                pos.erase(index,2);
                pos.insert(size,savelcut);
                help.push_back(pos);
               
                poshelp.clear();
                savelcut.clear();
            }
        }


        if(vec[i]==")")
        {
            if(stack.back().getSymbol()==(int)T_ && this->table[T_][RPAREN]==5)
            {   

                stack.pop_back();
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='T'&& pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                
                help.push_back(pos);
            }


            if(stack.back().getSymbol()==(int)E_ && this->table[E_][RPAREN]==2)
            {   

                stack.pop_back();
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='E'&& pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                
                help.push_back(pos);
            }
            
            if(stack.back().getSymbol()==RPAREN)
            {   

                stack.pop_back();
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]==')')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,2);
                accepted.push_back(this->rules[6][0]);
                int size=lcut.size();
                
                lcut+=terminalStrings[this->rules[6][0].getSymbol()] + " ";
                savelcut+=terminalStrings[this->rules[6][0].getSymbol()] + " ";
                
                pos.insert(size,savelcut);
                help.push_back(pos);
               
                poshelp.clear();
                savelcut.clear();

            }

        }
    }

  
  

 

    while(error==false && !stack.empty())
    {
        if(stack.back().getSymbol()==T_)
        {
                stack.pop_back();
                
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='T'&& pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                
                help.push_back(pos);


        }

        if(stack.back().getSymbol()==E_)
        {
                stack.pop_back();
                int index;
                for(int j=0; j<pos.size(); j++)
                {
                    if(pos[j]=='E'&& pos[j+1]=='_')
                    {
                        index=j;
                        break;
                    }
                    
                }

                pos.erase(index,3);
                
                help.push_back(pos);
        }

        if(stack.back().getSymbol()==RPAREN && stack.back().getType()==TERM)
        {
            error=true;
            break;
        }
        

    }
    for(int i=0; i<help.size(); i++)
    {
        cout<<help[i]<<endl;
    }

   

    if(stack.back().getSymbol()==RPAREN || stack.back().getSymbol()==T_)
    {
        cout<<"syntax error"<<endl;
        exit(1);
    }

    
 


}





terminal Parser::nextToken()
{

}

void Parser::printLM()
{


 
}