#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
using namespace std;
using ll = long long;
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
    :https://leetcode.com/problems/search-in-a-binary-search-tree/description/
2. Insert in BST
3. Sorted array to balanced BST
    :https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
4. check BT is BST
    :https://leetcode.com/problems/validate-binary-search-tree/
5. LCA in BST
6. Find the inorder predecessor/next smaller of a given Key in BST.
7. Find the inorder successor/next greater of a given Key in BST.
*/
// 1 Search Given Key in BST
class SearchKeyInBST
{
public:
    TreeNode *searchBST_rec(TreeNode *root, int val)
    {
        if (!root)
            return NULL;
        // same as BS
        if (root->val == val)
            return root;
        else if (root->val > val)
            return searchBST_rec(root->left, val);
        else
            return searchBST_rec(root->right, val);
    }
    TreeNode *searchBST_Iterative(TreeNode *root, int val)
    {
        while (root)
        {
            if (root->val == val)
                return root;
            else if (root->val > val)
                root = root->left;
            else
                root = root->right;
        }
        return NULL; // was not present
    }
};

// 2
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
        last = temp; // since temp will become NULL we need to know the parent node where we insert new node
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

// 3 Construct BST from given keys
class SortedArrToBST
{
public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return sortedToBSTRec(nums, 0, nums.size() - 1);
    }

    TreeNode *sortedToBSTRec(vector<int> &nums, int s, int e)
    {
        if (s > e) // for leaf nodes
            return NULL;

        int mid = s + (e - s) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        // set the left and right subtree
        root->left = sortedToBSTRec(nums, s, mid - 1);
        root->right = sortedToBSTRec(nums, mid + 1, e);

        return root;
    }
};

// 4 check BT is BST
class ValidBST
{
    /*
    1.BT
    2.TD
    3.Iterative
    */
public:
    // 1 BU, we will set the valid variable
    pair<long long, long long> isBSTbottomUp(TreeNode *root, bool &valid)
    {
        if (!root)
            return {1e14, -1e14};

        auto left = isBSTbottomUp(root->left, valid);
        auto right = isBSTbottomUp(root->right, valid);

        if (left.second < root->val && right.first > root->val)
        {
            long long rootVal = root->val;
            long long minV = min(rootVal, left.first);   // in case left child is null root->val should be min value
            long long maxV = max(rootVal, right.second); // similarly for right child
            return {minV, maxV};
        }
        valid = false;
        return {-1, -1};
    }
    // 2 TD
    bool isBSTTopDown(TreeNode *root, ll mi, ll ma)
    {
        if (!root)
            return true;
        if (root->val > mi && root->val < ma)
        {
            bool left = isBSTTopDown(root->left, mi, root->val);
            bool right = isBSTTopDown(root->right, root->val, ma);
            return left && right;
        }
        return false;
    }
    // 3 Iterative Inorder the next value should be higher then last
    bool isValidBST(TreeNode *root)
    {
        if (!root)
            return true;

        // using inorder LNR
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
};

// 5
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    // if not confirmed both are present or not
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
// 6
// Check why go right and all left will not work
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
            root = root->left; // since current value is greater or equal to B the next smaller is in left subtree
    }
    return nextSmaller;
}
// 7
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
            root = root->right; // since current value is less or equal to B the next greater is in right subtree
    }
    return nextGreater;
}
// This one is what I thought at first
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