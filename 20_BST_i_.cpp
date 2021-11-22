#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
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
1. Search Given Key in BST
2. Insert in BST
3. Sorted array to balanced BST
4. check BT is BST
5. LCA in BST
6. Find the inorder predecessor/next smaller of a given Key in BST.
7. Find the inorder successor/next greater of a given Key in BST.  
*/
//1
TreeNode *searchBST_rec(TreeNode *root, int val)
{
    if (!root)
        return NULL;
    //same as BS
    if (root->val == val)
        return root;
    else if (root->val > val)
        return searchBST_rec(root->left, val);
    else
        return searchBST_rec(root->right, val);
}
TreeNode *searchBST_Iterative(TreeNode *root, int val)
{
    if (!root)
        return NULL;
    while (root)
    {
        if (root->val == val)
            return root;
        else if (root->val > val)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}
//2
TreeNode *insertIntoBSTRec(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);
    if (root->val > val)
        root->left = insertIntoBSTRec(root->left, val);
    else
        root->right = insertIntoBSTRec(root->right, val);
    return root;
}
TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);
    TreeNode *last = NULL, *temp = root;
    while (temp)
    {
        last = temp; //since temp will become NULL we need to know the parent node where we insert new node
        if (temp->val > val)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (last->val > val) // to know to insert in left or right
        last->left = new TreeNode(val);
    else
        last->right = new TreeNode(val);
    return root;
}
//3
TreeNode *sortedToBSTRec(vector<int> &nums, int s, int e)
{
    if (s > e)
        return NULL;
    int mid = s + (e - s) / 2;

    TreeNode *root = new TreeNode(nums[mid]);
    root->left = sortedToBSTRec(nums, s, mid - 1);
    root->right = sortedToBSTRec(nums, mid + 1, e);
    return root;
}
TreeNode *sortedArrayToBST(vector<int> &nums)
{
    return sortedToBSTRec(nums, 0, nums.size() - 1);
}

//4
class ValidBSTBottomUp
{
public:
    bool isValidBST(TreeNode *root)
    {
        bool valid = true; // will be set to false if tree is not a bst at any node
        isBSTBottomUp(root, valid);
        return valid;
    }

    pair<int, int> isBSTBottomUp(TreeNode *root, bool &valid)
    {
        if (!root)                       // not a base case
            return {-1, -1};             //will never be called unless the tree is null
        if (!root->left && !root->right) // base case
            return {root->val, root->val};
        if (!root->left) // donot call on left if not present
        {
            auto right = isBSTBottomUp(root->right, valid);
            if (right.first <= root->val)
                valid = false;
            return {root->val, right.second};
        }
        if (!root->right) // donot call on right if not present
        {
            auto left = isBSTBottomUp(root->left, valid);
            if (left.second >= root->val)
                valid = false;
            return {left.first, root->val};
        }
        // both subtree exist for current node
        auto left = isBSTBottomUp(root->left, valid);
        auto right = isBSTBottomUp(root->right, valid);
        if (left.second >= root->val || right.first <= root->val) // note: >= and <= since they can't be equal as well
            valid = false;
        return {left.first, right.second};
    }
};
using ll = long long;
class ValidBSTTopDown
{
public:
    bool isValidBST(TreeNode *root)
    {
        return isBST(root, -1e14, 1e14);
    }
    bool isBST(TreeNode *root, ll mi, ll ma)
    {
        if (!root)
            return true;
        if (root->val > mi && root->val < ma)
        {
            bool left = isBST(root->left, mi, root->val);
            bool right = isBST(root->right, root->val, ma);
            return left && right;
        }
        return false;
    }
};
//Iterative Inorder the next value should be higher then last
bool isValidBST(TreeNode *root)
{
    if (!root)
        return true;

    //using inorder LNR
    stack<TreeNode *> st;
    while (root)
    {
        st.push(root);
        root = root->left;
    }
    long long last = LONG_MIN;
    while (!st.empty())
    {
        TreeNode *temp = st.top();
        st.pop();

        if (temp->val <= last)
            return false;
        last = temp->val;

        temp = temp->right;
        while (temp)
        {
            st.push(temp);
            temp = temp->left;
        }
    }
    return true;
}
// 5
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    //if not confirmed both are present or not
    /*
    bool present1=searchBST_Iterative(root,p->val);
    bool present2=searchBST_Iterative(root,q->val);
    if(!present1 || !present2)
        return NULL;
    */
    while (root)
    {
        if (root->val > p->val && root->val > q->val)
            root = root->left;
        else if (root->val < p->val && root->val < q->val)
            root = root->right;
        else
            break;
    }
    return root;
}
//6
//Check why go right and all left will not work
TreeNode *getPredeccessor(TreeNode *root, int B)
{
    TreeNode *nextSmaller = NULL;
    while (root)
    {
        if (root->val < B)
        {
            nextSmaller = root;
            root = root->right; // since everything on left subtree will be smaller than root and smaller than B they can't be next smaller value
        }
        else
            root = root->left; //since current value is greater or equal to B the next smaller is in left subtree
    }
    return nextSmaller;
}
//7
TreeNode *getSuccessor(TreeNode *root, int B)
{
    TreeNode *nextGreater = NULL;
    while (root)
    {
        if (root->val > B)
        {
            nextGreater = root;
            root = root->left; // since weverything on right subtree will be greater than root and grater than B they can't be next greater value
        }
        else
            root = root->right; //since current value is less or equal to B the next greater is in right subtree
    }
    return nextGreater;
}
//This one is what I thought at first
TreeNode *getSuccessor(TreeNode *root, int val)
{
    TreeNode *nextGreater = NULL;
    while (root)
    {
        if (root->val > val)
        {
            nextGreater = root;
            root = root->left;
        }
        else if (root->val < val)
            root = root->right;
        else // if found the value it's just right child will contain the next  greater value
        {
            root = root->right;
            break;
        }
    }
    while (root && root->left)
        root = root->left;
    return root ? root : nextGreater;
}