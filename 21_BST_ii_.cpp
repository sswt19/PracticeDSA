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
3. Kth Smallest in BST
4. Kth Largest in BST
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
//3
//recursive get whole list and return inorder[k-1] T:n S:n
//iterative T:n S:h
int kthSmallest(TreeNode *root, int k)
{
    //inorder iterative implementation LNR
    stack<TreeNode *> s;
    while (root)
    {
        s.push(root);
        root = root->left;
    }

    while (!s.empty())
    {
        if (k == 1)
            return s.top()->val;
        k--; //reducing k everytime a element is seen in inorder traversal
        auto temp = s.top();
        s.pop();                  // nodes's left subtree done so removing the node now
        auto right = temp->right; // now time for right subtree
        while (right)
        {
            s.push(right);
            right = right->left;
        }
    }
    return -1; //wrong test size(bst)<k or k is 0
}
//4
int kthLargest(TreeNode *root, int k)
{
    //inorder in Opposite way RNL and find kth element
    stack<TreeNode *> s;
    while (root)
    {
        s.push(root);
        root = root->right;
    }
    while (!s.empty())
    {
        if (k == 1)
            return s.top()->val;
        k--;
        auto temp = s.top();
        s.pop();
        auto left = temp->left;
        while (left)
        {
            s.push(left);
            left = left->right;
        }
    }
    return -1;
}