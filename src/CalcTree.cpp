#include "../include/CalcTree.h"
#include "../include/WorkFile.h"

CalcTree::CalcTree()
{
    this->head_node = new TreeNode(0);
}

CalcTree::~CalcTree()
{
    FreeTree();
}

TreeNode* CalcTree::GetHead()
{
    return this->head_node;

}

int GetCurrentResult(int first, int second, int operands)
{
    switch (operands)
    {
    case (ADD):
        return first + second;
    case (SUB):
        return first - second;
    case (MUL):
        return first * second;
    case (DIV):
        return first / second;

    default: return 0;
    }
}

int CalcTree::GetResult(TreeNode* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child == nullptr || current->right_child == nullptr)
        return current->number;

    int left_res = GetResult(current->left_child);
    int right_res = GetResult(current->right_child);

    return GetCurrentResult(left_res, right_res, current->number);
}
void CalcTree::FreeTree(TreeNode* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
        FreeTree(current->left_child);

    if (current->right_child != nullptr)
        FreeTree(current->right_child);

    delete current;
}

int CalcTree::FillGraph(TreeNode* current, char** ptr_on_text)
{
    int tmp_number = 0;
    int err = FirstWordFromText(ptr_on_text, &tmp_number);

    if (err == NOT_READ)
    {
        current->left_child = new TreeNode();
        FillGraph(current->left_child, ptr_on_text);
    }

    else if (err == OK)
        current->left_child = new TreeNode(tmp_number);

    else PrintError(err, "FillGraph, can't read first print");

    err = FirstWordFromText(ptr_on_text, &tmp_number);

    if (err == OK)
        current->number = tmp_number;

    else PrintError(err, "FillGraph, can't read first print");

    err = FirstWordFromText(ptr_on_text, &tmp_number);

    if (err == NOT_READ)
    {
        current->right_child = new TreeNode();
        FillGraph(current->right_child, ptr_on_text);
    }

    else if (err == OK)
        current->right_child = new TreeNode(tmp_number);

    else
        PrintError(err, "FillGraph, can't read");

    (*ptr_on_text)++;
    return OK;
}


int CalcTree::ReadGraphFile(const char* input_file)
{
    size_t size = 0;

    char* text = ReadFile(input_file, &size, "r");

    int err = FillGraph(head_node, &text);

    if (err) PrintError(err, "ReadGraphFile");

    return 0;
}

int CalcTree::NodeToFile(TreeNode* current_node, FILE* output_file)
{
    if (current_node->left_child  != nullptr && current_node->right_child != nullptr)
    {
        WriteGraph(current_node, output_file, false);
    }
    else
        fprintf(output_file, "%d", current_node->number);
}

int CalcTree::WriteGraph(TreeNode* current_node, FILE* output_file, bool is_first)
{
    if (!is_first)
        fprintf(output_file, "(");

    NodeToFile(current_node->left_child, output_file);

    fprintf(output_file, "%s", NodeDataToStr(current_node));

    NodeToFile(current_node->right_child, output_file);

    if (!is_first)
        fprintf(output_file, ")");

    return OK;
}


int CalcTree::WriteGraphFile(TreeNode* start_node, const char* output_file)
{
    if (start_node == nullptr) start_node = head_node;
    FILE* graph_file = fopen(output_file, "w");

    WriteGraph(start_node, graph_file);

    fclose(graph_file);
}
