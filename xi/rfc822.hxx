// vim:ts=3:sts=3:sw=3

#ifndef XI_RFC822_H_
#define XI_RFC822_H_

#include <string.h>

/* RFC822 STANDARD FOR THE FORMAT OF ARPA INTERNET TEXT MESSAGES */
#define CHAR_SP                 ' '
#define CHAR_CR                 '\r'
#define CHAR_LF                 '\n'
#define CHAR_HT                 '\t'

#define CHAR_RAQUOT             '>'
#define CHAR_LAQUOT             '<'
#define CHAR_SQUOTE             '\''
#define CHAR_DQUOTE             '\"'
#define CHAR_QUOTE              '\"'
#define CHAR_EQ                 '='

#define RFC822_CRLF             "\r\n"

#define IS_LITERAL(s,x)         ((x != '\0') && (strchr(s, x) != NULL))
#define IS_CHAR_RANGE(x,a,z)    ((x >= a) && (x <= z))

#define IS_CHAR_QUOTE(x)        (CHAR_QUOTE == x)
#define IS_CHAR_SPACE(x)        ((CHAR_SP == x) || (CHAR_HT == x))
#define IS_CHAR_CRLF(x)         ((CHAR_CR == x) || (CHAR_LF == x))
#define IS_CHAR_DIGIT(x)        IS_CHAR_RANGE(x, '0', '9')
#define IS_CHAR_ASCII(x)        (x <= 127)
#define IS_CHAR_ALPHA(x)        (IS_CHAR_RANGE(x,'a','z') || IS_CHAR_RANGE(x,'A','Z'))
#define IS_CHAR_ALNUM(x)        (IS_CHAR_ALPHA(x) || IS_CHAR_DIGIT(x))
#define IS_CHAR_HEX(x)          (IS_CHAR_DIGIT(x) || IS_CHAR_RANGE(x, 'a', 'f') || IS_CHAR_RANGE(x, 'A', 'F'))
#define IS_CHAR_BRACKET(x)      LITERAL("()<>[]{}", x)


#endif
