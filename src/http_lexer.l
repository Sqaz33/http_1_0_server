%option c++

%option noyywrap

%{
    #include "http_parser.hpp"
%}

STRING  [^0-9 .:\/\n\r]+

%%

"HTTP"          { return yy::parser::token_type::HTTP;   }
[0-9]+          { return yy::parser::token_type::NUMBER; }
"."             { return yy::parser::token_type::DOT;    }
":"             { return yy::parser::token_type::COLON;  }
" "             { return yy::parser::token_type::SPACE;  }
"\r"            { return yy::parser::token_type::CR;   }
"\n"            { return yy::parser::token_type::LF;   }
"/"             { return yy::parser::token_type::SLASH;  }
{STRING}        { return yy::parser::token_type::STRING; }
.               { return yy::parser::token_type::ERR;    }
 

%%