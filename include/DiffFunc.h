#ifndef DECLARE_FUNC
#define DECLARE_FUNC

#define left_diff  this->left_child->DiffNode(false)
#define right_diff this->right_child->DiffNode(false)

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffSub()
{
    assert(this);
    return new TreeNode<type_t>(this->number, this->type_node, left_diff, right_diff);
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffAdd()
{
    assert(this);
    return new TreeNode<type_t>(this->number, this->type_node, left_diff, right_diff);
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffMul()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(ADD, OPERATION);

    new_node->Addleft (MUL, OPERATION, left_diff, this->right_child->Copy());
    new_node->Addright(MUL, OPERATION, this->left_child->Copy(), right_diff);

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffDiv()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(this->number, this->type_node);

    new_node->Addleft(SUB, OPERATION);
    new_node->Addright(POW, OPERATION);

    new_node->left_child->Addleft (MUL, OPERATION, left_diff, this->right_child->Copy());
    new_node->left_child->Addright(MUL, OPERATION, this->left_child->Copy(), right_diff);

    new_node->right_child->Addright(2);
    new_node->right_child->Addleft(this->right_child->Copy());

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffPow()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(MUL, OPERATION, nullptr, this->Copy());

    TreeNode<type_t>* tmp_node = new TreeNode<type_t>(LN, FUNC, new TreeNode<type_t>(), this->left_child->Copy());

    new_node->Addleft(ADD, OPERATION);

    new_node->left_child->Addleft (MUL, OPERATION, tmp_node->DiffNode(false), this->right_child->Copy());
    new_node->left_child->Addright(MUL, OPERATION, tmp_node, right_diff);
    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffSin()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(MUL, OPERATION, right_diff, nullptr);

    new_node->right_child->UpdateNode(COS, FUNC, nullptr, this->right_child->Copy());

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffCos()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(SUB, OPERATION, nullptr, nullptr);

    new_node->right_child->UpdateNode(SIN, FUNC, nullptr, right_diff);

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffTan()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(DIV, OPERATION, right_diff, nullptr);

    new_node->right_child->UpdateNode(POW, OPERATION, this->Copy(), nullptr);

    new_node->right_child->right_child->UpdateNode(2, VALUE);
    new_node->right_child->left_child->UpdateNode(COS, FUNC);

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffLn()
{
    assert(this);
    return new TreeNode<type_t>(DIV, OPERATION, right_diff, this->right_child->Copy());
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffSinh()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(MUL, OPERATION, right_diff, this->Copy());

    new_node->right_child->UpdateNode(COSH, FUNC);

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffCosh()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(MUL, OPERATION, right_diff, this->Copy());

    new_node->right_child->UpdateNode(SINH, FUNC);

    return new_node;
}

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffTanh()
{
    assert(this);
    TreeNode<type_t>* new_node = new TreeNode<type_t>(DIV, OPERATION, right_diff, nullptr);

    new_node->right_child->UpdateNode(POW, OPERATION, this->Copy(), nullptr);

    new_node->right_child->right_child->UpdateNode(2, VALUE);
    new_node->right_child->left_child->UpdateNode(COSH, FUNC);

    return new_node;
}


#endif // DECLARE_FUNC
