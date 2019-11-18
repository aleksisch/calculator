#ifndef CalcTree_H
#define CalcTree_H

struct TreeNode
{
    TreeNode(const int num = 0, TreeNode* left_t = nullptr, TreeNode* right_t = nullptr, bool oper = 0) :
        number(num),
        type_node(oper),
        left_child(left_t),
        right_child(right_t)
    {
    }

    TreeNode* Copy();
    TreeNode* DiffNode();
    int number;
    int type_node;
    TreeNode* left_child;
    TreeNode* right_child;
};

class CalcTree
{
    public:

        CalcTree();

        ~CalcTree();

        void GraphToDot();

        void ReadGraphFile(const char* input_file = input_graph_file);

        void WriteGraphFile(TreeNode* start_node = nullptr, const char* output_file = output_graph_file);

        int GetResult(TreeNode* current = nullptr);

        TreeNode* GetHead();

    private:

        TreeNode* head_node;

        void NodeToFile(TreeNode* current_node, FILE* output_file);

        void FillGraph(TreeNode* current, char** ptr_on_text);

        void WriteDump(FILE* file, TreeNode* current = nullptr);

        void FreeTree(TreeNode* current = nullptr);

        void WriteGraph(TreeNode* current_node, FILE* output_file, bool is_first = true);

};
#endif // CalcTree_H
