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
    int err2 = 0;

    printf("tmp1 %d %d\n", tmp_number, err);

    if (err == NOT_READ)
    {
        current->left_child = new TreeNode();
        FillGraph(current->left_child, ptr_on_text);
        err2 = FirstWordFromText(ptr_on_text, &tmp_number);
    }

    else if (err == OK)
    {
        printf("tmp2 %d %d\n", tmp_number, err);
        current->number = tmp_number;
        return OK;
    }

    else PrintError(err, "FillGraph, can't read first print");

    err = FirstWordFromText(ptr_on_text, &tmp_number);
    printf("tmp3 %d %d\n", tmp_number, err);

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
    if (current_node  != nullptr)
    {
        fprintf(output_file, "(\n\t%d%d%d\"\n", current_node->number);
        WriteGraph(current_node, output_file);
    }

    fprintf(output_file, " }\n");
}

int CalcTree::WriteGraph(TreeNode* current_node, FILE* output_file)
{
    NodeToFile(current_node->left_child, output_file);
    NodeToFile(current_node->right_child, output_file);

    return OK;
}


int CalcTree::WriteGraphFile(const char* output_file)
{
    FILE* graph_file = fopen(output_file, "w");

    fprintf(graph_file, "{ \"%d\"\n", head_node->number);

    WriteGraph(head_node, graph_file);

    fprintf(graph_file, "}");

    fclose(graph_file);
}
