#ifndef _COMPILER_H_
#define _COMPILER_H_
#define TRUE 1
#define FALSE 0

enum StatementType
{
    NOOP_STMT = 1000,
    PRINT_STMT,
    ASSIGN_STMT,
    IF_STMT,
    GOTO_STMT
};

#define KEYWORDS    8
#define RESERVED    28
#define VAR         1
#define IF          2
#define WHILE       3
#define SWITCH      4
#define CASE        5
#define DEFAULT     6
#define PRINT       7
#define ARRAY       8
#define PLUS        9
#define MINUS       10
#define DIV         11
#define MULT        12
#define EQUAL       13
#define COLON       14
#define COMMA       15
#define SEMICOLON   16
#define LBRAC       17
#define RBRAC       18
#define LPAREN      19
#define RPAREN      20
#define LBRACE      21
#define RBRACE      22
#define NOTEQUAL    23
#define GREATER     24
#define LESS        25
#define ID          26
#define NUM         27
#define ERROR       28

#define MAX_TOKEN_LENGTH 200

extern char token[MAX_TOKEN_LENGTH];
extern int  ttype;

struct ValueNode
{
    char* name;
    int   value;
};

struct GotoStatement
{
    struct StatementNode* target;
};

struct AssignmentStatement
{
    struct ValueNode* left_hand_side;

    struct ValueNode* operand1;
    struct ValueNode* operand2;
    int op;
};

struct PrintStatement
{
    struct ValueNode* id;
};

struct IfStatement
{
    struct ValueNode* condition_operand1;
    struct ValueNode* condition_operand2;
    int condition_op;

    struct StatementNode* true_branch;
    struct StatementNode* false_branch;
};

struct StatementNode
{
    enum StatementType type;

    union
    {
        struct AssignmentStatement* assign_stmt;
        struct PrintStatement* print_stmt;
        struct IfStatement* if_stmt;
        struct GotoStatement* goto_stmt;
    };

    struct StatementNode* next; // next statement in the list or NULL
};


void debug(const char* format, ...);

int  getToken();
void ungetToken();

struct StatementNode* parse_generate_intermediate_representation();

#endif /* _COMPILER_H_ */
