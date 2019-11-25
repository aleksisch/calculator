#ifndef DIFFRULES_H_INCLUDED
#define DIFFRULES_H_INCLUDED

#include "CalcTree.h"

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

    TreeNode<type_t>*& left  = this->left_child;
    TreeNode<type_t>*& right = this->right_child;

    TreeNode<type_t>* left_diff  = left->DiffNode(false);

    TreeNode<type_t>* right_diff = right->DiffNode(false);

    switch(MyRound(this->number))
    {
        case (ADD):
        case (SUB):

            new_node->UpdateNode(left_diff, right_diff);

            break;

        case (MUL):

            new_node->UpdateNode(ADD, OPERATION);

            new_node->Addleft (MUL, OPERATION, left_diff, right->Copy());
            new_node->Addright(MUL, OPERATION, left->Copy(), right_diff);

            break;

        case (DIV):

            new_node->Addleft(SUB, OPERATION);

            new_node->left_child->Addleft (MUL, OPERATION, left_diff, right->Copy());
            new_node->left_child->Addright(MUL, OPERATION, left->Copy(), right_diff);

            new_node->Addright(POW, OPERATION);

            new_node->right_child->Addright(2);
            new_node->right_child->Addleft(right->Copy());

            break;

        case (SIN):

            new_node->UpdateNode(MUL, OPERATION, right_diff, nullptr);

            new_node->right_child->UpdateNode(COS, FUNC, nullptr, right->Copy());

            break;

        case (COS):

            new_node->UpdateNode(SUB, OPERATION, nullptr, nullptr);

            new_node->right_child->UpdateNode(SIN, FUNC, nullptr, right_diff);

            break;

        case (TAN):
        {
            new_node->UpdateNode(DIV, OPERATION, right_diff, nullptr);

            new_node->right_child->UpdateNode(POW, FUNC, this->Copy(), nullptr);

            new_node->right_child->right_child->UpdateNode(2, VALUE);

            new_node->right_child->left_child->UpdateNode(COS, FUNC);

            break;
        }

        case POW:
        {
            TreeNode<type_t>* tmp_node = new TreeNode<type_t>(LN, FUNC, new TreeNode<type_t>(), left->Copy());

            new_node->UpdateNode(MUL, OPERATION, nullptr, this->Copy());

            new_node->left_child->UpdateNode(ADD, OPERATION);

            new_node->left_child->Addleft (MUL, OPERATION, tmp_node->DiffNode(false), right->Copy());
            new_node->left_child->Addright(MUL, OPERATION, tmp_node, right_diff);

            break;
        }
        case LN:

            new_node->UpdateNode(DIV, OPERATION, right_diff, right->Copy());

            break;

        case SINH:

            new_node->UpdateNode(MUL, OPERATION, right_diff, this->Copy());

            new_node->right_child->UpdateNode(COSH, FUNC);

            break;

        case COSH:

            new_node->UpdateNode(MUL, OPERATION, right_diff, this->Copy());

            new_node->right_child->UpdateNode(SINH, FUNC);

            break;

        default:

            PrintError(UNKNOWN_OPERATION, "Be careful, return nullptr, diff_node");

            return nullptr;
    }

    if (is_first)
    {
        new_node = new_node->Simplify();

        fprintf(CalcTree<type_t>::log_file, "$$$$Differencial\\quad is \\quad ");

        new_node->LogToLatex(CalcTree<type_t>::log_file);
    }

    return new_node;
}

#endif // DIFFRULES_H_INCLUDED
