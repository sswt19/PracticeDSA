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
1.Delete a Node in BST
2. Floor and Ceil of a number in BST 
*/
// 1
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (!root)
        return root;
    if (root->val > key)
        root->left = deleteNode(root->left, key);
    else if (root->val < key)
        root->right = deleteNode(root->right, key);
    else //found what to delete
    {
        if (!root->left && !root->right) //both children don't exist
        {
            delete root;
            return NULL;
        }
        else if (root->right && root->left) //both exist
        {
            auto temp = root->right;
            while (temp && temp->left) //find the smallest value in right subtree
                temp = temp->left;
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val); // delete the another occurence of same value in BST
        }
        else //any one of them exist
        {
            auto temp = root;
            root = root->left ? root->left : root->right;
            delete temp;
        }
    }
    return root;
}
//2
/*
Floor Value Node: Node with greatest data lesser than or equal to key value. 
Ceil Value Node: Node with smallest data larger than or equal to key value.
F<=k
C>=k
but in inorder precedessor and successor the value can not be equal to key
*/
void floorAndCeil(TreeNode *root, int key, int &floor, int &ceil)
{
    floor = ceil = -1;

    while (root)
    {
        if (root->val == key)
        {
            floor = ceil = key; // when key is present
            return;
        }
        else if (root->val > key)
        {
            ceil = root->val;
            root = root->left;
        }
        else
        {
            floor = root->val;
            root = root->right;
        }
    }
}