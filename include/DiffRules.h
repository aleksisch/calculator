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

    TreeNode<type_t>*& left = this->left_child;
    TreeNode<type_t>*& right = this->right_child;

    switch(MyRound(this->number))
    {
        case (ADD):

            new_node->Addleft (left->DiffNode(false));
            new_node->Addright(right->DiffNode(false));

            break;

        case (SUB):

            new_node->Addleft (left->DiffNode(false));
            new_node->Addright(right->DiffNode(false));

            break;

        case (MUL):

            new_node->UpdateNode(ADD, OPERATION);

            new_node->left_child  = new TreeNode<type_t>(MUL, OPERATION, left->DiffNode(false), right->Copy());

            new_node->right_child = new TreeNode<type_t>(MUL, OPERATION, left->Copy(), right->DiffNode(false));

            break;

        case (DIV):

            new_node->left_child = new TreeNode<type_t>(SUB, OPERATION);

            new_node->left_child->left_child  = new TreeNode<type_t>(MUL, OPERATION, left->DiffNode(false), right->Copy());

            new_node->left_child->right_child = new TreeNode<type_t>(MUL, OPERATION, left->Copy(), right->DiffNode(false));

            new_node->right_child = new TreeNode<type_t>(POW, OPERATION);

            new_node->right_child->Addright(2);
            new_node->right_child->Addleft(right->Copy());

            break;

        case (SIN):

            new_node->UpdateNode(MUL, OPERATION);

            new_node->Addleft(right->DiffNode(false));

            new_node->right_child = new TreeNode<type_t>(COS, FUNC);

            new_node->right_child->Addleft();
            new_node->right_child->Addright(right->Copy());

            break;

        case (COS):

            new_node->UpdateNode(SUB, OPERATION);

            new_node->Addleft();
            new_node->Addright(SIN, FUNC);

            new_node->right_child->Addleft();
            new_node->right_child->Addright(right->DiffNode(false));

            break;

        case (TAN):
        {
            new_node->UpdateNode(DIV, OPERATION);

            new_node->Addleft(right->DiffNode(false));
            new_node->Addright(POW, FUNC);

            new_node->right_child->Addright(2);
            new_node->right_child->Addleft(this->Copy());
            new_node->right_child->left_child->UpdateNode(COS, FUNC);

            break;
        }

        case POW:
        {
            TreeNode<type_t>* tmp_node = new TreeNode<type_t>(LN, FUNC, new TreeNode<type_t>(), left->Copy());

            new_node->UpdateNode(MUL, OPERATION);

            new_node->Addright(this->Copy());
            new_node->Addleft(ADD, OPERATION);

            new_node->left_child->Addleft(new TreeNode<type_t>(MUL, OPERATION, tmp_node->DiffNode(false), right->Copy()));
            new_node->left_child->Addright(new TreeNode<type_t>(MUL, OPERATION, tmp_node, right->DiffNode(false)));

            break;
        }
        case LN:
            new_node->UpdateNode(DIV, OPERATION);

            new_node->Addleft(right->DiffNode(false));
            new_node->Addright(right->Copy());

            break;

        case SINH:

            new_node->UpdateNode(MUL, OPERATION);

            new_node->Addleft(right->DiffNode(false));
            new_node->Addright(this->Copy());
            new_node->right_child->UpdateNode(COSH, FUNC);

            break;

        case COSH:

            new_node->UpdateNode(MUL, OPERATION);

            new_node->Addleft(right->DiffNode(false));
            new_node->Addright(this->Copy());
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
