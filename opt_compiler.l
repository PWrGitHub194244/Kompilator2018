%option noyywrap
%option yylineno
%{
    #include <stdlib.h>
    #include <string.h>
    #include "opt_compiler.tab.h"
%}

%x CMT

%%

"["             { BEGIN(CMT);       }
<CMT>"]"        { BEGIN(INITIAL);   }
<CMT>(\n|.)
<CMT><<EOF>>    { printf("Błąd: niezakończony komentarz.\n"); yyterminate(); }

"DECLARE"           { return VAR;      }
"IN"         { return BEG;      }
"END"           { return END;      }

":="            { return ASG;      }
"IF"            { return IF;       }
"THEN"          { return THEN;     }
"ELSE"          { return ELSE;     }
"WHILE"         { return WHILE;    }
"FOR"           { return FOR;      }
"FROM"          { return FROM;     }
"TO"            { return TO;       }
"DOWNTO"        { return DOWNTO;   }
"ENDIF"         { return ENDIF;    }
"ENDWHILE"      { return ENDWHILE; }
"ENDFOR"        { return ENDFOR;   }
"ENDDO"        { return ENDDO;   }
"DO"            { return DO;       }

"WRITE"         { return WRITE;    }
"READ"          { return READ;     }

"=="             { return EQ;       }
"<"             { return LT;       }
">"             { return GT;       }
"<="            { return LE;       }
">="            { return GE;       }
"!="            { return NE;       }

"+"             { return ADD;      }
"-"             { return SUB;      }
"*"             { return MUL;      }
"/"             { return DIV;      }
"%"             { return MOD;      }
"("             { return LB;       }
")"             { return RB;       }
":"             { return COLON;       }

[0-9]+          { yylval.str = (char *)strdup(yytext);
                    return NUM;    }
[_a-z]+         { yylval.str = (char *)strdup(yytext);
                    return IDE;    }

";"             { return SEM;      }
[ \t\r\n]+
.

%%
