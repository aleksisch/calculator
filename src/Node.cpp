#include "../include/MainHeader.h"

TreeNode* TreeNode::Copy()
{
    TreeNode* copy_node = new TreeNode(this->number);

    if (this->left_child != nullptr && this->left_child != nullptr)
    {
        copy_node->left_child  = this->left_child->Copy();
        copy_node->right_child = this->right_child->Copy();
    }

    return copy_node;
}

void TreeNode::Addleft(int new_el)
{
    this->left_child = new TreeNode(new_el);
}

void TreeNode::Addleft(TreeNode* to_add)
{
    this->left_child = to_add;
}

void TreeNode::Addright(int new_el)
{
    this->right_child = new TreeNode(new_el);
}

void TreeNode::Addright(TreeNode* to_add)
{
    this->right_child = to_add;
}

TreeNode* TreeNode::DiffNode()
{
    printf("in start %d %d\n", this->number, this->type_node);
    TreeNode* new_node = new TreeNode(this->number, this->type_node);
    if (this->type_node == VARIABLE)
    {
    printf("in var %d\n", this->number);

        new_node->number = 1;
        return new_node;
    }

    else if (this->type_node == VALUE)
    {

        printf("in value %d %d\n", this->number, VALUE);
        new_node->number = 0;
        return new_node;
    }

    printf("in switch %d\n", this->number);

    switch(this->number)
    {
        case (ADD):
            new_node->Addleft (this->left_child->DiffNode());
            new_node->Addright(this->right_child->DiffNode());

            return new_node;

        case (SUB):

            new_node->Addleft (this->left_child->DiffNode());
            new_node->Addright(this->right_child->DiffNode());

            return new_node;

        case (MUL):

            new_node->number = ADD;

            new_node->left_child  = new TreeNode(MUL, OPERATION, this->left_child->DiffNode(), this->right_child->Copy());
            new_node->right_child = new TreeNode(MUL, OPERATION, this->right_child->DiffNode(), this->left_child->Copy());

            return new_node;

        case (DIV):
     {

            new_node->left_child = new TreeNode(SUB, OPERATION);

            new_node->left_child->left_child  = new TreeNode(MUL, OPERATION, this->left_child->DiffNode(), this->right_child->Copy());

            new_node->left_child->right_child = new TreeNode(MUL, OPERATION, this->left_child->Copy(), this->right_child->DiffNode());

            new_node->right_child = new TreeNode(POW, OPERATION);

            new_node->right_child->Addleft(2);
            new_node->right_child->Addright(this->right_child);

            return new_node;
    }
        case (LN):
            return new_node;
        case (SIN):
            return new_node;
        case (COS):
            return new_node;
        case (TAN):
            return new_node;

    }
}
