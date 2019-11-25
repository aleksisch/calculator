#include "../include/MainHeader.h"

#include "WorkString.h"

template <typename type_t>
void TreeNode<type_t>::FreeTree()
{
    if (this == nullptr) return;

    this->left_child-> FreeTree();
    this->right_child->FreeTree();

    delete this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::Copy()
{
    TreeNode<type_t>* copy_node = new TreeNode<type_t>(this->number, this->type_node);

    if (this->left_child != nullptr && this->left_child != nullptr)
    {
        copy_node->left_child  = this->left_child->Copy();
        copy_node->right_child = this->right_child->Copy();
    }

    return copy_node;
}

template <typename type_t>
type_t TreeNode<type_t>::GetResult(type_t variable_value)
{
    assert(this);

    if (this->type_node == VARIABLE)
        return variable_value;

    else if (this->type_node == VALUE)
        return this->number;

    type_t left_res =  this->left_child->GetResult(variable_value);
    type_t right_res = this->right_child->GetResult(variable_value);

    return ExecuteOperation(left_res, right_res, this->number);
}

template <typename type_t>
void TreeNode<type_t>::Addleft(type_t new_el, int type, TreeNode<type_t>* left, TreeNode<type_t>* right)
{
    this->left_child = new TreeNode<type_t>(new_el, type, left, right);
}

template <typename type_t>
void TreeNode<type_t>::Addleft(TreeNode<type_t>* to_add)
{
    this->left_child = to_add;
}

template <typename type_t>
void TreeNode<type_t>::Addright(type_t new_el, int type, TreeNode<type_t>* left, TreeNode<type_t>* right)
{
    this->right_child = new TreeNode<type_t>(new_el, type, left, right);
}

template <typename type_t>
void TreeNode<type_t>::Addright(TreeNode<type_t>* to_add)
{
    this->right_child = to_add;
}

template <typename type_t>
void TreeNode<type_t>::UpdateNode(type_t number, int type, TreeNode<type_t>* left, TreeNode<type_t>* right)
{
    this->UpdateNode(number, type);

    if (left  == nullptr) left  = new TreeNode<type_t>;
    if (right == nullptr) right = new TreeNode<type_t>;

    this->UpdateNode(left, right);
}

template <typename type_t>
void TreeNode<type_t>::UpdateNode(TreeNode<type_t>* left, TreeNode<type_t>* right)
{
    this->left_child->FreeTree();
    this->right_child->FreeTree();

    this->left_child  = left;
    this->right_child = right;
}

template <typename type_t>
void TreeNode<type_t>::UpdateNode(type_t number, int type)
{
    this->number = number;
    this->type_node = type;
}

template <typename type_t>
void TreeNode<type_t>::NodeToFile(FILE* output_file)
{
    assert(this && output_file);

    if (this->type_node != VALUE)
        this->WriteGraph(output_file);

    else
        fprintf(output_file, "%lf", this->number);
}

template <typename type_t>
void TreeNode<type_t>::WriteGraph(FILE* output_file, bool is_first)
{
    assert(this && output_file);

    if (this->left_child != nullptr && this->type_node != FUNC)
    {
        if (!is_first) fprintf(output_file, "(");

        this->left_child->NodeToFile(output_file);
    }

    fprintf(output_file, "%s", NodeDataToStr(this));

    if (this->right_child != nullptr)
    {
        this->right_child->NodeToFile(output_file);

        if (this->type_node != FUNC && (!is_first))
            fprintf(output_file, ")");
    }
}

template <typename type_t>
void TreeNode<type_t>::NodeToTex(FILE* output_file)
{
    assert(this && output_file);

    if (this->type_node != VALUE)
        this->WriteToLatex(output_file, false);

    else
        fprintf(output_file, "{%.3lf}", this->number);
}

template <typename type_t>
void TreeNode<type_t>::LogToLatex(FILE* output_file, const char* filename)
{
    WriteToLatex(output_file, false, filename);
}

template <typename type_t>
void TreeNode<type_t>::WriteToLatex(FILE* output_file, bool is_first, const char* filename)
{
    if (output_file == nullptr)
        output_file = BeginLatexFile(filename);

    assert(output_file && filename && this);

    char str_cmd[STR_LENGTH] = {};
    bool is_div = false;

    strcpy(str_cmd, NodeDataToStr(this));

    if (strcmp(str_cmd, "/") == 0)
    {
        is_div = true;
        fprintf(output_file, "\\frac");
        strcpy(str_cmd, "} {");
    }

    else if (strcmp(str_cmd, "*") == 0)
        strcpy(str_cmd, "\\cdot");

    fprintf(output_file, "{");

    if (this->left_child != nullptr && this->type_node != FUNC)
    {
        if (!(is_first || is_div))
            fprintf(output_file, "(");

        this->left_child->NodeToTex(output_file);
    }

    fprintf(output_file, "%s", str_cmd);

    if (this->right_child != nullptr)
    {
        this->right_child->NodeToTex(output_file);

        if (this->type_node != FUNC && (!is_first) && (!is_div))
            fprintf(output_file, ")");
    }

    fprintf(output_file, "}");

    if (is_first)
        CloseLatexFile(output_file);
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::Simplify()
{
    if (this == nullptr || this->left_child == nullptr || this->right_child == nullptr)
        return this;

    const type_t eps = 0.00001;

    TreeNode*& left  = this->left_child;
    TreeNode*& right = this->right_child;

    if (left->type_node != VALUE && left->type_node != VARIABLE)
        left = left->Simplify();

    if (right->type_node != VALUE && right->type_node != VARIABLE)
        right = right->Simplify();

    if (left->type_node == VALUE && right->type_node == VALUE)
    {
        this->number = ExecuteOperation(left->number, right->number, this->number);

        this->type_node = VALUE;

        delete left;
        delete right;

        this->left_child = nullptr;
        this->right_child = nullptr;

        return this;
    }

    if (MyRound(this->number) == MUL && this->type_node == OPERATION)
    {
        if ((left->number  <= eps  && left->type_node  == VALUE) ||
            (right->number <= eps  && right->type_node == VALUE))
        {
            this->UpdateNode(0, VALUE);

            left->FreeTree();
            left = nullptr;

            right->FreeTree();
            right = nullptr;

            return this;
        }

        if (right->number - 1 <= eps && right->type_node == VALUE)
        {
            right->FreeTree();
            right = nullptr;

            return left;
        }

        if (left->number - 1 <= eps && left->type_node == VALUE)
        {
            left->FreeTree();
            left = nullptr;

            return right;
        }
    }

    if (MyRound(this->number) == ADD && this->type_node == OPERATION)
    {
        if (right->number <= eps && right->type_node == VALUE)
        {
            right->FreeTree();
            right = nullptr;

            return left;
        }

        else if (left->number <= eps && left->type_node == VALUE)
        {
            left->FreeTree();
            left = nullptr;

            return right;
        }
    }

    return this;
}

template <typename type_t>
void TreeNode<type_t>::WriteDump(FILE* file)
{
    assert (this);

    if (this->left_child != nullptr && this->type_node != FUNC)
    {

        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(this->number), NodeDataToStr(this));
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(this->left_child->number),
                                                             NodeDataToStr(this->left_child));
        fprintf(file, "tree_node%p->tree_node%p\n\n", &(this->number), &(this->left_child->number));

        this->left_child->WriteDump(file);
    }

    if (this->right_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(this->number), NodeDataToStr(this));
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(this->right_child->number),
                                                             NodeDataToStr(this->right_child));
        fprintf(file, "tree_node%p->tree_node%p\n\n", &(this->number), &(this->right_child->number));

        this->right_child->WriteDump(file);
    }

}
