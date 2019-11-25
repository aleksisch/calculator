#include "../include/MainHeader.h"

template <typename type_t>
CalcTree<type_t>::CalcTree()
{
    this->head_node = new TreeNode<type_t>(0);

    if (CalcTree<type_t>::log_file == nullptr)
        CalcTree<type_t>::log_file = BeginLatexFile(log_filename);
}

template <typename type_t>
CalcTree<type_t>::~CalcTree()
{
    CloseLatexFile(CalcTree<type_t>::log_file);

    this->head_node->FreeTree();
}

template <typename type_t>
type_t CalcTree<type_t>::GetResult(type_t variable_value)
{
    type_t res = this->head_node->GetResult(variable_value);

    #ifndef NO_LOG

    fprintf(CalcTree<type_t>::log_file, "$$$$Get \\quad result \\quad of \\quad expression, x = %.3lf: \\quad", variable_value);

    this->head_node->WriteToLatex(CalcTree<type_t>::log_file, false);

    fprintf(CalcTree<type_t>::log_file, " = %.3lf", res);

    #endif

    return res;
}

template <typename type_t>
void CalcTree<type_t>::WriteGraphFile(TreeNode<type_t>* start_node, const char* output_file)
{
    if (start_node == nullptr) start_node = this->head_node;

    FILE* graph_file = fopen(output_file, "w");

    start_node->WriteGraph(graph_file, true);

    fclose(graph_file);
}

template <typename type_t>
void CalcTree<type_t>::GraphToDot()
{
    FILE* file_graph = fopen(output_graphviz, "w");

    fprintf(file_graph, "digraph G{ \n");

    this->head_node->WriteDump(file_graph);

    fprintf(file_graph, "}");

    fclose(file_graph);

    char str_to_system[STR_LENGTH] = {};
    sprintf(str_to_system, "dot -Tjpg -O %s", output_graphviz);
    system(str_to_system);
}
