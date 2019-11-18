#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

static const char* input_graph_file = "in_graph.txt";
static const char* output_graph_file = "out_graph.txt";
static const char* output_graphviz = "tmp_dump.dt";

static const int STR_LENGTH = 255;
static const int MAX_DEPTH = 100;

enum Return
{
    OK = 0,
    NIL,
    LONG_STRING,
    END_OF_GAME,
    BAD_NAME,
    NOT_READ,

};

enum Operands
{
    SUB,
    ADD,
    DIV,
    MUL,
    SIN,
    COS,
    LN,
    TAN,
    FUNC,
    UNKNOWN_OPERATION,
};

#endif // CONSTANTS_H_INCLUDED
