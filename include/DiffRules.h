#pragma once

#include "CalcTree.h"
#include "OperationArray.h"

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffNode(bool is_first)
{
    assert(this);

    TreeNode<type_t>* new_node = new TreeNode<type_t>(this->number, this->type_node);

    if (this->type_node == VARIABLE)
    {
        new_node->UpdateNode(1, VALUE);
        return new_node;
    }

    else if (this->type_node == VALUE)
    {
        new_node->UpdateNode(0, VALUE);
        return new_node;
    }

    else
        for (int op = 0; op < NUM_OPER; op++)
            if (MyRound(this->number) == Operation<type_t>[op].num)
            {
                new_node = (this->*(Operation<type_t>[op].func))();
                break;
            }

    if (is_first)
    {

        fprintf(CalcTree<type_t>::log_file, "$$$$Differencial\\quad before \\quad Simplify \\quad is \\quad ");

        new_node->LogToLatex(CalcTree<type_t>::log_file);

        new_node = new_node->Simplify();

        fprintf(CalcTree<type_t>::log_file, "$$$$Differencial\\quad after \\quad ");

        new_node->LogToLatex(CalcTree<type_t>::log_file);
    }

    return new_node;
}
