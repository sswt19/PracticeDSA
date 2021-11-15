#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *next;
    TreeNode() : val(0), left(nullptr), right(nullptr), next(NULL) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(NULL) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
1. Inorder Iterative and Recursive
2. PreOrder Iterative and Recursive
3. PostOrder Iterative and Recursive
4. 
5.
6.
7.
8.
*/

//1
vector<int> inorderTraversalIterative(TreeNode *root)
{
    //LNR: inorder
    vector<int> inorder;
    stack<TreeNode *> st;
    while (root)
    {
        st.push(root);
        root = root->left;
    }
    while (!st.empty())
    {
        //when a node is popped it's left subtree has been parsed so insert it in inorder vector
        auto temp = st.top();
        st.pop();
        inorder.push_back(temp->val);
        //Now time to traverse right subtree of the current node
        temp = temp->right; //this line: make sure to set to right child of current node
        //in the same way as we did at top
        while (temp)
        {
            st.push(temp);
            temp = temp->left;
        }
    }
    return inorder;
}
void inorderRec(TreeNode *root, vector<int> &inorder)
{
    if (!root)
        return;
    inorderRec(root->left, inorder);
    inorder.push_back(root->val);
    inorderRec(root->right, inorder);
}

//2
vector<int> preorderTraversal(TreeNode *root)
{
    //NLR: preorder
    vector<int> preorder;
    stack<TreeNode *> st;
    while (root)
    {
        st.push(root);
        preorder.push_back(root->val); //since we need node first we fill add node first then it's left subtree
        root = root->left;
    }
    while (!st.empty())
    {
        //when a node is popped it is and it's left subtree has been parsed
        auto temp = st.top();
        st.pop();
        //Now time to traverse right subtree of the current node
        temp = temp->right; //this line: make sure to set to right child of current node
        //in the same way as we did at top
        while (temp)
        {
            st.push(temp);
            preorder.push_back(temp->val);
            temp = temp->left;
        }
    }
    return preorder;
}
void preorderRec(TreeNode *root, vector<int> &preorder)
{
    if (!root)
        return;
    preorder.push_back(root->val);
    preorderRec(root->left, preorder);
    preorderRec(root->right, preorder);
}
//3
vector<int> postorderTraversal(TreeNode *root)
{
    //LRN: postorder
    vector<int> postorder;
    unordered_map<TreeNode *, bool> rightSeen;
    stack<TreeNode *> st;
    while (root)
    {
        st.push(root);
        root = root->left;
    }
    while (!st.empty())
    {
        //when a node is popped it is and it's left subtree has been parsed
        auto temp = st.top();
        if (rightSeen[temp])
        {
            st.pop(); // pop only when both left and right subtrees are seen
            postorder.push_back(temp->val);
        }
        else
        {
            rightSeen[temp] = true; // marking it true since we will be traversing the right tree now and when it is on top of stack again right subtrees are already parsed
            temp = temp->right;     //this line: make sure to set to right child of current node
            while (temp)
            {
                st.push(temp);
                temp = temp->left;
            }
        }
    }
    return postorder;
}
void postorderRec(TreeNode *root, vector<int> &postorder)
{
    if (!root)
        return;
    postorderRec(root->left, postorder);
    postorderRec(root->right, postorder);
    postorder.push_back(root->val);
}
//4