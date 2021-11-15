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
4. Tree from Preorder and Inorder
5. Tree from Inorder and PostOrder
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
class PreAndIn
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {

        unordered_map<int, int> inorder_map; // to get the index of element in inorder array in constant time
        int n = preorder.size();

        for (int i = 0; i < n; i++)
            inorder_map[inorder[i]] = i;

        int cur_index = 0; // this variable will traverse through the preorder array in NLR
        return buildTreeRec(preorder, 0, n - 1, cur_index, inorder_map);
    }
    TreeNode *buildTreeRec(vector<int> &preorder, int s, int e, int &cur, unordered_map<int, int> &um)
    { // [s,e] are index in inorder array for which we are constructing a tree
        if (s > e)
            return NULL;
        //preorder is NLR hence construct the N first then left subtree and then right subtree
        TreeNode *root = new TreeNode(preorder[cur]);
        cur++; // move to next value in preorder array
        //inorder is LNR
        int index = um[root->val];
        root->left = buildTreeRec(preorder, s, index - 1, cur, um); //everything left of index i.e [s,index-1] will be used to construct left subtree
        //since leftTree is already built cur value would have reached to the index of right SubTree in PreOrder
        root->right = buildTreeRec(preorder, index + 1, e, cur, um); //everything right of index i.e [index+1,e] will be used to construct right subtree

        return root;
    }
};
//5
class PostAndIn
{
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {

        unordered_map<int, int> inorder_map;
        int n = postorder.size();

        for (int i = 0; i < n; i++)
            inorder_map[inorder[i]] = i;

        int cur_index = n - 1; //LRN hence we will start from end
        return buildTreeRec(postorder, 0, n - 1, cur_index, inorder_map);
    }
    TreeNode *buildTreeRec(vector<int> &postorder, int s, int e, int &cur, unordered_map<int, int> &um)
    {
        //everything same logic but we will create right subtree first
        if (s > e)
            return NULL;

        TreeNode *root = new TreeNode(postorder[cur]);
        cur--;
        int index = um[root->val];
        //since we are starting from end(NRL): first node then right and then left
        root->right = buildTreeRec(postorder, index + 1, e, cur, um);
        root->left = buildTreeRec(postorder, s, index - 1, cur, um);

        return root;
    }
};