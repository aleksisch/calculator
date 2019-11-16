#ifndef CalcTree_H
#define CalcTree_H

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "WorkFile.h"

struct TreeNode
{
    int number;
    bool is_operator;
    TreeNode* left_child;
    TreeNode* right_child;

    TreeNode(const int num, bool oper = false ) :
        number(num),
        is_operator(oper),
        left_child(nullptr),
        right_child(nullptr)
    {
    }
};

class CalcTree
{
    public:

        CalcTree();

        ~CalcTree();

        int GraphToDot();

        int ReadGraphFile(const char* input_file = input_graph_file);

        int WriteGraphFile(const char* output_file = output_graph_file);

    private:

        TreeNode* head_node;

        int NodeToFile(TreeNode* current_node, FILE* output_file);

        int FillGraph(TreeNode* current, char** ptr_on_text);

        int WriteDump(FILE* file, TreeNode* current = nullptr);

        void FreeTree(TreeNode* current = nullptr);

        int WriteGraph(TreeNode* current_node, FILE* output_file);

};

#endif // CalcTree_H
