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
*/
//2
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
//3
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
//4
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

//5