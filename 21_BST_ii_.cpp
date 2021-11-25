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
5. Two Sum BST
6. BST iterator

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
// 5
bool findTarget(TreeNode *root, int k)
{
    unordered_map<int, int> um;
    return findTarget(root, k, um);
}
bool findTarget(TreeNode *root, int k, unordered_map<int, int> &um)
{
    if (!root)
        return false;
    if (um.find(k - root->val) != um.end())
        return true;
    um[root->val] = 1;
    return findTarget(root->left, k, um) || findTarget(root->right, k, um);
}
// using inorder
bool findTargetInorder(TreeNode *root, int k)
{
    if (!root)
        return false;
    vector<int> inord;

    inorder(root, inord);

    //Two Sum
    int s = 0, e = inord.size() - 1;

    while (s < e)
    {
        int sum = inord[s] + inord[e];
        if (sum == k)
            return true;
        else if (sum > k)
            e--;
        else
            s++;
    }
    return false;
}
void inorder(TreeNode *root, vector<int> &inord)
{
    if (!root)
        return;
    inorder(root->left, inord);
    inord.push_back(root->val);
    inorder(root->right, inord);
}
//6 just break any of the iterative traversal into BST iterator: here inorder is used
class BSTIterator
{
    stack<TreeNode *> s;

public:
    BSTIterator(TreeNode *root)
    {

        while (root) //inorder
        {
            s.push(root);
            root = root->left;
        }
    }

    int next()
    {
        auto temp = s.top();
        s.pop();                  //seen left subtree and current node
        auto right = temp->right; //seen right subtree
        while (right)
        {
            s.push(right);
            right = right->left;
        }
        return temp->val;
    }

    bool hasNext()
    {
        return !s.empty();
    }
};