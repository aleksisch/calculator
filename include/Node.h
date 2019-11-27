#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template <typename type_t>
class TreeNode
{
    public:

        TreeNode<type_t>(const type_t num = 0, int type_node_t = VALUE, TreeNode<type_t>* left_t = nullptr, TreeNode<type_t>* right_t = nullptr) :
            number(num),
            type_node(type_node_t),
            left_child(left_t),
            right_child(right_t)
        {}

        type_t GetResult(type_t variable_value);

        void WriteDump(FILE* file);

        void FreeTree();

        TreeNode<type_t>* Copy();

        TreeNode<type_t>* DiffNode(bool is_first = true);

        void UpdateNode(type_t number, int type, TreeNode<type_t>* left, TreeNode<type_t>* right);
        void UpdateNode(type_t number, int type);

        void UpdateNode(TreeNode<type_t>* left, TreeNode<type_t>* right);

        void Addright(TreeNode<type_t>* to_add);

        void Addright(type_t new_elem = 0, int type = VALUE, TreeNode<type_t>* left = nullptr, TreeNode<type_t>* right = nullptr);

        void Addleft (TreeNode<type_t>* to_add);

        void Addleft (type_t new_elem = 0, int type = VALUE, TreeNode<type_t>* left = nullptr, TreeNode<type_t>* right = nullptr);

        void WriteGraph(FILE* output_file, bool is_first = false);

        void NodeToFile(FILE* output_file);

        void WriteToLatex(FILE* output_file = nullptr, bool is_first = true, const char* out_filename = output_latex);

        type_t number;

        int type_node;

        TreeNode<type_t>* left_child;

        TreeNode<type_t>* right_child;

        TreeNode<type_t>* Simplify();

        void LogToLatex(FILE* output_file, const char* filename = output_latex);

        TreeNode<type_t>* DiffSub();
        TreeNode<type_t>* DiffAdd();
        TreeNode<type_t>* DiffMul();
        TreeNode<type_t>* DiffDiv();
        TreeNode<type_t>* DiffPow();
        TreeNode<type_t>* DiffSin();
        TreeNode<type_t>* DiffCos();
        TreeNode<type_t>* DiffTan();
        TreeNode<type_t>* DiffLn();
        TreeNode<type_t>* DiffSinh();
        TreeNode<type_t>* DiffCosh();
        TreeNode<type_t>* DiffTanh();

    private:

        void NodeToTex(FILE* output_file);

};

#include "DiffRules.h"

#endif // NODE_H_INCLUDED
