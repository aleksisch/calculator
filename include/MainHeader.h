#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

template <typename type_t>
class TreeNode;

void SkipToBrace(char** ptr_on_text);

template <typename type_t>
int MyRound(type_t num);

template <typename type_t>
int StrCmdToNum(const char* command, type_t* number, int* type_cmd);

template <typename type_t>
const char* NodeDataToStr(TreeNode<type_t>* current);

FILE* BeginLatexFile(const char* output);

void CloseLatexFile(FILE*& file);

void PrintError(int err_code, const char* function_name);


#include "constants.h"

#include "Node.h"

#include "CalcTree.h"

#include "OperationArray.h"

#include "WorkString.h"

#include "NodeFunction.h"

#include "CalcFunction.h"

#include "DiffRules.h"

#include "Parser.h"

#endif // MAINHEADER_H_INCLUDED
