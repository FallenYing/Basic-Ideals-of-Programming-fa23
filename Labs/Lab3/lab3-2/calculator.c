//------------------------------------------------------------------------------
/*  Grammar:
    Expression:
        Term
        Term "+"|"-" Term ...
    Term:
        Primary
        Primary "*"|"/" Primary ...
    Primary:
        Number
        "(" Expression ")"
    Number:
        floating-point-literal
*/
//------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Token {
    char kind;        // what kind of token
    double value;     // for numbers: a value
} Token;

typedef struct Token_Buffer {
    Token token;
    bool full;
} Token_Buffer;

void put_back(Token_Buffer* tb, Token t);               // put token back to token_buffer
Token get_token(Token_Buffer* tb);                      // get token from token_buffer or stdin
double expression(Token_Buffer* tb);                    // read and evaluate a Expression
double term(Token_Buffer* tb);                          // read and evaluate a Term
double primary(Token_Buffer * tb);                      // read and evaluate a Primary
void error(char* str);

int main(void) {
    Token_Buffer tb = { .full = false, .token = { 0, 0 } };
    Token t = { 0, 0 };
    double val = 0;
    while (true) {
        t = get_token(&tb);
        if (t.kind == 'q') {
            break;
        }
        if (t.kind == ';') {
            printf("= %f\n", val);
        }
        else {
            put_back(&tb, t);
            val = expression(&tb);
        }
    }
    printf("calculator exit\n");
    return 0;
}

void error(char* str) {
    printf(str);
    putchar('\n');
    exit(1);
}

void put_back(Token_Buffer* tb, Token t) {
    tb->token = t;
    tb->full = true;
}

Token get_token(Token_Buffer* tb) {
    if (tb->full) {
        tb->full = false;
        return tb->token;
    }
    char ch;
    scanf(" %c", &ch);
    switch (ch) {
    case ';':
    case 'q':
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
        return (Token){ch, 0};
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        ungetc(ch, stdin);
        double val;
        scanf("%lf", &val);
        return (Token){'n', val};
    default:
        error("Bad token");
    }
}

double expression(Token_Buffer* tb) {
    double num = term(tb);
    Token t = get_token(tb);
    while (t.kind == '+' || t.kind == '-') {
        if (t.kind == '+') {
            num += term(tb);
        } else if (t.kind == '-') {
            num -= term(tb);
        }
        t = get_token(tb);
    }
    put_back(tb, t);
    return num;
}

double term(Token_Buffer* tb) {
    double num = primary(tb);
    Token t = get_token(tb);
    while (t.kind == '*' || t.kind == '/') {
        if (t.kind == '*') {
            num *= primary(tb);
        } else if (t.kind == '/') {
            double d = primary(tb);
            if (d == 0) error("divide by zero");
            num /= d;
        }
        t = get_token(tb);
    }
    put_back(tb, t);
    return num;
}

double primary(Token_Buffer * tb) {
    double num;
    Token t = get_token(tb);
    if (t.kind == 'n') {
        num = t.value;
    } else if (t.kind == '(') {
        num = expression(tb);
        t = get_token(tb);
        if (t.kind != ')') error("')' expected");
        put_back(tb, get_token(tb));
    } else error("primary expected");
    return num;
}

