%language "c++"

%define parse.trace   /* uncom for trace */ 

%skeleton "lalr1.cc"
%param { std::pair<FlexLexer*, http_server::Request*> flexNRequest }
%define api.value.type variant

%code requires
{
  #include <string>
  #include <utility>
  #include <sstream>
  #include <iostream>

  #include "request.hpp"
  #include "header.hpp"

  class FlexLexer; 
}

%code 
{
  #include <FlexLexer.h>

  namespace yy {
      parser::token_type yylex(parser::semantic_type* yylval, 
                               std::pair<FlexLexer*, http_server::Request*> flexNRequest); 
  }

  static std::stringstream content;
  static std::stringstream uriSS;
}


%defines

%token ERR

%token HTTP
%token<int> NUMBER
%token DOT
%token COLON
%token SPACE
%token CR
%token LF
%token<std::string> STRING
%token SLASH
%nterm req_line
%nterm headers
%nterm msg_body
%nterm header
%nterm spaces
%nterm msg_body_char
%nterm opt_msg_body
%nterm uri
%nterm uri_char
%nterm opt_spaces

%start request

%%

request:       req_line headers CR LF opt_msg_body { 
                                               flexNRequest.second->setContent(content.str()); 
                                               content.str(""); 
                                               content.clear(); 
                                             }  

req_line:      STRING SPACE uri SPACE HTTP SLASH NUMBER DOT NUMBER CR LF  {
                                                                            flexNRequest.second->setMethod(std::move($1));
                                                                            flexNRequest.second->setUri(uriSS.str());
                                                                            uriSS.str("");
                                                                            uriSS.clear();
                                                                            flexNRequest.second->sethttpVersionMajor($7);
                                                                            flexNRequest.second->sethttpVersionMinor($9);
                                                                          }

uri_char: HTTP   { uriSS << "HTTP"; }
        | NUMBER { uriSS << $1;     }
        | DOT    { uriSS << '.';    }
        | COLON  { uriSS << ':';    }
        | STRING { uriSS << $1;     }
        | SLASH  { uriSS << '/';    }

uri: uri_char
   | uri uri_char

headers:       header
             | headers header

header:        STRING opt_spaces COLON opt_spaces uri CR LF   { 
                                                                http_server::Header h; 
                                                                h.name = std::move($1);
                                                                h.value = uriSS.str();
                                                                uriSS.str("");
                                                                uriSS.clear();
                                                                flexNRequest.second->addHeader(std::move(h)); 
                                                               }

opt_spaces: /* empty */
          | spaces

spaces:        SPACE
             | spaces SPACE

msg_body_char: HTTP   { content << "HTTP";       }
             | NUMBER { content << $1;           }
             | DOT    { content << '.';          }
             | COLON  { content << ':';          }
             | SPACE  { content << ' ';          }
             | CR     { content << '\r';         }
             | LF     { content << '\n';         }
             | STRING { content << $1;           }
             | SLASH  { content << '/';          }

msg_body:      msg_body_char
             | msg_body msg_body_char    

opt_msg_body: /* empty */
            | msg_body 

%%

namespace yy {
parser::token_type yylex(parser::semantic_type* yylval, 
                         std::pair<FlexLexer*, http_server::Request*> flexNRequest) 
{   
    auto* lexer = flexNRequest.first;
    auto tt = static_cast<parser::token_type>(lexer->yylex());
     switch (tt) {
        case (yy::parser::token_type::NUMBER):
            yylval->as<int>() 
                = std::stoi(lexer->YYText());
            break;
        case (yy::parser::token_type::STRING):
            yylval->emplace<std::string>() = 
                std::string(lexer->YYText(), lexer->YYLeng());
            break;
    }
    return tt;
}

  void parser::error(const std::string& e) { }
}