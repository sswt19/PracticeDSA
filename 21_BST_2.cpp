#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

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
    :https://www.codingninjas.com/codestudio/problems/920457
    :https://www.codingninjas.com/codestudio/problems/920464
3. Kth Smallest in BST
    :https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/
4. Kth Largest in BST
    :https://practice.geeksforgeeks.org/problems/kth-largest-element-in-bst/1
5. Find a pair with a given sum in BST
    :https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
6. BST iterator
    :https://leetcode.com/problems/binary-search-tree-iterator/
7. Largest BST in BT
    :https://www.codingninjas.com/codestudio/problems/893103
8. Serialize and deserialize Binary Tree
    :https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
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
    else // found what to delete
    {
        if (!root->left && !root->right) // both children don't exist
        {
            delete root;
            return NULL;
        }
        else if (root->right && root->left) // both exist
        {
            auto temp = root->right;
            while (temp && temp->left) // find the smallest value in right subtree
                temp = temp->left;
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val); // delete the another occurence of same value in BST
        }
        else // any one of them exist
        {
            auto temp = root;
            root = root->left ? root->left : root->right;
            delete temp;
        }
    }
    return root;
}

// 2 Floor and Ceil of a number in BST
class FloorAndCeil
{
    /*
        Floor Value Node: Node with greatest data lesser than or equal to key value.
        Ceil Value Node: Node with smallest data larger than or equal to key value.
        F<=k
        C>=k
        but in inorder precedessor and successor the value can not be equal to key
    */
public:
    void floorAndCeil(TreeNode *root, int key, int &floor, int &ceil)
    {
        // given floor and ceil exists, we are trying to fing the key in bst and while finding it we are setting both ceil and floor
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
};

// 3 Kth Smallest in BST
class KthSmallestInBST
{
    /*
        1. recursive get whole list and return inorder[k-1] T:n S:n
        2. iterative T:n S:h
    */
public:
    int kthSmallest(TreeNode *root, int k)
    {
        // inorder iterative implementation LNR
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
            k--; // reducing k everytime a element is seen in inorder traversal
            auto temp = s.top();
            s.pop();                  // nodes's left subtree done so removing the node now
            auto right = temp->right; // now time for right subtree
            while (right)
            {
                s.push(right);
                right = right->left;
            }
        }
        return -1; // wrong test size(bst)<k or k is 0
    }
};

// 4 Kth Largest in BST
class KthSmallestInBST
{
    /*
        1. recursive get whole list and return inorder[k-1] T:n S:n
        2. iterative T:n S:h
    */
public:
    int kthLargest(TreeNode *root, int k)
    {
        // inorder in Opposite way RNL and find kth element, take reference from KthSmallestCode comments
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
};

// 5 Find a pair with a given sum in BST
class PairWithGivenSum
{
    /*
        1. Use hash map and traverse whole tree till we find the pair, it will work for both BT and BST
        2. Use inorder to get sorted array, and then use 2 pointers to find given sum, only works on BST
    */
public:
    // 1 using hash map
    bool findTarget(TreeNode *root, int k)
    {
        unordered_map<int, int> um;
        return findTarget(root, k, um);
    }
    bool findTarget(TreeNode *root, int k, unordered_map<int, int> &um)
    {
        if (!root)
            return false;
        if (um.find(k - root->val) != um.end()) // check if k-val present in hash map
            return true;
        um[root->val] = 1;                                                      // add val to hash map
        return findTarget(root->left, k, um) || findTarget(root->right, k, um); // search in both left and right subtree
    }
    // 2 using inorder
    bool findTargetInorder(TreeNode *root, int k)
    {
        if (!root)
            return false;
        vector<int> inord;
        inorder(root, inord);

        // Two Sum
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
};

// 6 just break any of the iterative traversal into BST iterator: here inorder is used
class BSTIterator
{
    stack<TreeNode *> s;

public:
    BSTIterator(TreeNode *root)
    {
        while (root) // inorder
        {
            s.push(root);
            root = root->left;
        }
    }
    // The max amount of time a node is visited is 2, the avg time complexity of next() is 1
    int next()
    {
        auto temp = s.top();
        s.pop();                  // seen left subtree and current node
        auto right = temp->right; // process right subtree
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

// 7 Size of the largest BST in a Binary Tree
class LargestBST
{
public:
    //<isBST,<minNode,maxNode>>
    pair<int, pair<int, int>> largestBst(Node *root, int &Bst)
    {
        if (!root)
            return {0, {INT_MAX, INT_MIN}}; // for leaf nodes

        // find size of left and right children BST, and if they are BST
        auto left = largestBst(root->left, Bst);
        auto right = largestBst(root->right, Bst);

        // if left and right are BST and parent satisfies BST with children node, return new size and small and large elements
        if (left.first != -1 && right.first != -1 && root->data < right.second.first && root->data > left.second.second)
        {
            int size = 1 + left.first + right.first;           // new size
            int minV = min({root->data, left.second.first});   // in case left is leaf, parent will be the min node
            int maxV = max({root->data, right.second.second}); // in case rigth is lead, parent will be the max node
            Bst = max(Bst, size);                              // whenever combine, compare with global BST size
            return {size, {minV, maxV}};
        }
        return {-1, {-1, -1}}; // the current subtree is not BST
    }
};

// 8 Serialize and deserialize Binary Tree
class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        // for leaf nodes
        if (!root)
            return "#";
        // we will use preorder traversal,  ',' used to find when number ends
        return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        stringstream tree(data);
        return deserialize_helper(tree);
    }
    TreeNode *deserialize_helper(stringstream &tree)
    {
        string temp;
        getline(tree, temp, ',');

        if (temp == "#")
            return NULL;
        else
        {
            TreeNode *root = new TreeNode(stoi(temp));
            root->left = deserialize_helper(tree);  // first complete the left subtree since it was made first
            root->right = deserialize_helper(tree); // then the right subtree
            return root;
        }
    }
};