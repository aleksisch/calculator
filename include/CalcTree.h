#pragma once

template <typename type_t>
class CalcTree
{
    public:

        CalcTree();

        ~CalcTree();

        void GraphToDot();

        void ReadGraphFile(const char* input_file = input_graph_file);

        void WriteGraphFile(TreeNode<type_t>* start_node = nullptr, const char* output_file = output_graph_file);

        TreeNode<type_t>* head_node;

        type_t GetResult(type_t variable_value);

        static FILE* log_file;

    private:

        void FillGraph(TreeNode<type_t>* current, char** ptr_on_text);

        void WriteDump(FILE* file);
};

template <typename type_t>
FILE* CalcTree<type_t>::log_file;

template <typename type_t>
int MyRound(type_t num)
{
    return static_cast<int> (std::round(num));
}
