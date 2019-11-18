#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const char* input_graph_file = "in_graph.txt";
static const char* output_graph_file = "out_graph.txt";
static const char* output_graphviz = "tmp_dump.dt";

static const int STR_LENGTH = 255;
static const int MAX_DEPTH = 100;

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
    UNKNOWN_OPERATION,
    POW,
    VAR,
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
};

#include "WorkFile.h"
#include "CalcTree.h"


int StrCmdToNum(char* tmp_str, int* type_cmd);

const char* NodeDataToStr(TreeNode* current);

int ExecuteOperation(int first, int second, int operands);

#endif // MAINHEADER_H_INCLUDED
