#include "../include/CalcTree.h"

int CalcTree::WriteDump(FILE* file, TreeNode* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(current->number), NodeDataToStr(current));
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(current->left_child->number),
                                                             NodeDataToStr(current->left_child));
        fprintf(file, "tree_node%p->tree_node%p\n\n", &(current->number), &(current->left_child->number));

        WriteDump(file, current->left_child);
    }

    if (current->right_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(current->number), NodeDataToStr(current));
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(current->right_child->number),
                                                             NodeDataToStr(current->right_child));
        fprintf(file, "tree_node%p->tree_node%p\n\n", &(current->number), &(current->right_child->number));

        WriteDump(file, current->right_child);
    }
}

int CalcTree::GraphToDot()
{
    char input_path[STR_LENGTH] = {};
    sprintf(input_path, "%s", output_graphviz);

    FILE* file_graph = fopen(input_path, "w");

    fprintf(file_graph, "digraph G{ \n");

    WriteDump(file_graph);

    fprintf(file_graph, "}");

    fclose(file_graph);

    char str_to_system[STR_LENGTH] = {};

    sprintf(str_to_system, "dot -Tjpg -O %s", output_graphviz);

    system(str_to_system);
}

const char* NodeDataToStr(TreeNode* current)
{
    if (current->left_child != nullptr &&
        current->right_child != nullptr)
    switch ( current->number)
    {
    case ADD:
        return "+";
    case SUB:
        return "-";
    case MUL:
        return "*";
    case DIV:
        return "/";
    default:
        return "unknown cmd";
    }

    std::string res = std::to_string(current->number);
    return res.c_str();
}
