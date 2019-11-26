#ifndef DECLARE_FUNC
#define DECLARE_FUNC

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

#else
#ifndef BODY_FUNC
#define BODY_FUNC

#define left_diff this->left_child->Diff()
#define right_diff this->right_child->Diff()


template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffSub()
{
    new_node = new
    new_node->UpdateNode(left_diff, right_diff);

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffAdd()
{
    return this;
}
template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffMul()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffDiv()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffPow()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffSin()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffCos()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffTan()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffLn()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffSinh()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffCosh()
{
    return this;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffTanh()
{
    return this;
}

#endif
#endif // DECLARE_FUNC
