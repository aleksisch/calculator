#include "CalcTree.h"

int CalcTree::WriteDump(FILE* file, TreeNode* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(current->data), current->data);
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(current->left_child->data),
                                                             current->left_child->data);
        fprintf(file, "tree_node%p->tree_node%p\n\n", current->data, current->left_child->data);

        WriteDump(file, current->left_child);
    }

    if (current->right_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(current->data), current->data);
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(current->right_child->data),
                                                             current->right_child->data);
        fprintf(file, "tree_node%p->tree_node%p\n\n", current->data, current->right_child->data);

        WriteDump(file, current->right_child);
    }
}

int CalcTree::GraphToDot()
{
    char input_path[STR_LENGTH] = {};
    sprintf(input_path, "%s%s", path_to_graphviz, output_graphviz);

    FILE* file_graph = fopen(input_path, "w");

    fprintf(file_graph, "digraph G{ \n");

    WriteDump(file_graph);

    fprintf(file_graph, "}");

    fclose(file_graph);

    char str_to_system[STR_LENGTH] = {};

    sprintf(str_to_system, "cd/d %s && dot.exe -Tjpg -O %s", path_to_graphviz, output_graphviz);

    system(str_to_system);
}
