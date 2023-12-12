//前序
// 存储遍历结果的数组
vector<int> v;
// 前序遍历函数
vector<int> preorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return v;
    v.emplace_back(root->val); // 输入数组语句
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    return v;
}
//中序
// 存储遍历结果的数组
vector<int> v;
// 中序遍历函数
vector<int> inorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return v;
    inorderTraversal(root->left);
    v.emplace_back(root->val); // 输入数组语句
    inorderTraversal(root->right);
    return v;
}
//后序
// 存储结果数组
vector<int> v;
// 后序遍历函数
vector<int> postorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return v;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    v.emplace_back(root->val); // 输入语句
    return v;
}