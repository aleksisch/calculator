#pragma once

static const char* input_graph_file  = "input.txt";
static const char* output_graph_file = "out_graph.txt";
static const char* output_graphviz   = "tmp_dump.dt";
static const char* output_latex      = "node_latex.txt";
static const char* log_filename      = "result.txt";

static const int STR_LENGTH = 255;

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
    POW,
    VAR,
    SINH,
    COSH,
    TANH,
    NUM_OPER,
};

enum Return
{
    OK = 0,
    NIL,
    LONG_STRING,
    END_OF_GAME,
    BAD_NAME,
    NOT_READ,
    FUNC,
    VALUE,
    VARIABLE,
    OPERATION,
    UNKNOWN_OPERATION,
};
