#include "../include/MainHeader.h"

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

int CalcTree::GetResult(TreeNode* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child == nullptr || current->right_child == nullptr)
        return current->number;

    int left_res = GetResult(current->left_child);
    int right_res = GetResult(current->right_child);

    return ExecuteOperation(GetResult(current->left_child),
                            GetResult(current->right_child), current->number);
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

void CalcTree::FillGraph(TreeNode* current, char** ptr_on_text)
{
    int tmp_number = 0;
    int ret = FirstWordFromText(ptr_on_text, &tmp_number);

    if (ret == NOT_READ)
    {
        current->left_child = new TreeNode();
        FillGraph(current->left_child, ptr_on_text);
    }

    else if (ret == OK)
        current->left_child = new TreeNode(tmp_number);

    else if (ret != FUNC)
        PrintError(ret, "FillGraph, can't read first print");

    if (ret == FUNC)
    {
        current->left_child = new TreeNode();
        current->number = tmp_number;
    }

    else
    {
        ret = FirstWordFromText(ptr_on_text, &tmp_number);

        if (ret == OK)
            current->number = tmp_number;

        else
            PrintError(ret, "FillGraph, can't read second print");
    }

    ret = FirstWordFromText(ptr_on_text, &tmp_number);

    if (ret == NOT_READ)
    {
        current->right_child = new TreeNode();
        FillGraph(current->right_child, ptr_on_text);
    }

    else if (ret == OK)
        current->right_child = new TreeNode(tmp_number);

    else
        PrintError(ret, "FillGraph, can't read right child");

    (*ptr_on_text)++;

}


void CalcTree::ReadGraphFile(const char* input_file)
{
    size_t size = 0;

    char* text = ReadFile(input_file, &size, "r");

    FillGraph(head_node, &text);
}

void CalcTree::NodeToFile(TreeNode* current_node, FILE* output_file)
{
    if (current_node->left_child  != nullptr && current_node->right_child != nullptr)
    {
        WriteGraph(current_node, output_file, false);
    }
    else
        fprintf(output_file, "%d", current_node->number);
}

void CalcTree::WriteGraph(TreeNode* current_node, FILE* output_file, bool is_first)
{
    if (!is_first)
        fprintf(output_file, "(");

    NodeToFile(current_node->left_child, output_file);

    fprintf(output_file, "%s", NodeDataToStr(current_node));

    NodeToFile(current_node->right_child, output_file);

    if (!is_first)
        fprintf(output_file, ")");
}


void CalcTree::WriteGraphFile(TreeNode* start_node, const char* output_file)
{
    if (start_node == nullptr) start_node = head_node;
    FILE* graph_file = fopen(output_file, "w");

    WriteGraph(start_node, graph_file);

    fclose(graph_file);
}
