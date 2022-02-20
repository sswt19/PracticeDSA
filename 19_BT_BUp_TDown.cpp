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
Bottom UP: getting the information from children nodes and processing it in parent node
Top Down: Passing down information of parent node to lower nodes
Bottom Up
1. MinDepth
2. MaxDepth
3. Check Height Balanced BT
4. Diameter of BT
5. Path from root to given node
6. LCA
7. Flatten BT or BT to DLL
8. Maximum Path Sum
*/
/*
Top Down: Passing down information of parent node to lower nodes
1. Check two trees are same
2. A tree is symmetric or 2 trees are mirror of each other
3. Count Good Nodes in Binary Tree
*/
//1
int minDepth(TreeNode *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    if (!root->left)
        return minDepth(root->right) + 1;
    if (!root->right)
        return minDepth(root->left) + 1;
    return min(minDepth(root->right), minDepth(root->left)) + 1; //getting info from bottom row
}
//2
int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

//3
/*
For each node the difference between left and right subtree can be max 1
*/
pair<bool, int> isBalanced(TreeNode *root)
{
    // we will get if both left and right subtree are balanced as well as their height to get height difference
    if (!root) //base case
        return {true, 0};

    //get info from child nodes
    auto left = isBalanced(root->left);
    auto right = isBalanced(root->right);

    if (left.first && right.first && abs(left.second - right.second) <= 1)
        return {true, max(left.second, right.second) + 1};

    return {false, -1};
}
//4 The diameter of a binary tree is the length of the longest path between any two nodes in a tree.This path may or may not pass through the root.

pair<int, int> diameterOfBT(TreeNode *root)
{
    //This function returns number of nodes in diameter
    /*pair<diameter,height>*/
    if (!root)
        return {0, 0};
    //Bottom Up : get information from child subtrees first
    auto leftSubTree = diameterOfBT(root->left);
    auto rightSubTree = diameterOfBT(root->right);

    int diam = max({leftSubTree.first, rightSubTree.first, leftSubTree.second + rightSubTree.second + 1});
    int height = max(leftSubTree.second, rightSubTree.second) + 1;

    return {diam, height};
}
int diameterOfBinaryTree(TreeNode *root) //No of edges in diameter = no of node in diameter -1
{
    return diameterOfBT(root).first - 1;
}
//5 Path
bool path(TreeNode *root, TreeNode *p, list<TreeNode *> &pathfromTop)
{
    if (root == NULL)
        return false;
    if (root == p)
    {
        pathfromTop.push_front(root);
        return true;
    }
    if (path(root->left, p, pathfromTop) || path(root->right, p, pathfromTop))
    {
        pathfromTop.push_front(root);
        return true;
    }
    return false;
}
//6 LCA: p and q can be same, different, may not be present in tree
class LCA
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {

        TreeNode *ans = NULL;
        lca(root, p, q, ans);
        return ans; // return NULL if not found LCA
    }
    bool lca(TreeNode *root, TreeNode *p, TreeNode *q, TreeNode *&ans)
    {
        if (!root)
            return false;

        auto foundInLeft = lca(root->left, p, q, ans);
        auto foundInRight = lca(root->right, p, q, ans);

        if (foundInLeft && foundInRight) // if in different paths
            ans = root;
        if ((root == p || root == q) && (foundInLeft || foundInRight)) // if in same path
            ans = root;
        if (root == p && root == q) //if both p and q are same
            ans = root;
        return foundInLeft || foundInRight || (root == p || root == q);
    }
};
class LCAUsingPath
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {

        list<TreeNode *> path1, path2;
        path(root, p, path1);
        path(root, q, path2);
        TreeNode *lca = NULL;
        while (!path1.empty() && !path2.empty())
        {
            if (path1.front()->val != path2.front()->val) //first different value in path is where they diverged
                break;
            lca = path1.front();
            path1.pop_front();
            path2.pop_front();
        }
        return lca; // return NULL if not found LCA
    }
};
//7
//in NLR inorder way
class BTtoDLL
{
public:
    void flatten(TreeNode *root)
    {
        flattenRec(root).second;
    }
    pair<TreeNode *, TreeNode *> flattenRec(TreeNode *root)
    {
        if (!root)
            return {NULL, NULL};
        if (!root->left && !root->right)
            return {root, root};

        auto leftSubTreeLL = flattenRec(root->left);
        auto rightSubTreeLL = flattenRec(root->right);
        //DLL in order NLR
        root->left = NULL; //TreeNode->left should be NULL
        // connect N->L or N->R if L doesn't exist
        root->right = leftSubTreeLL.first ? leftSubTreeLL.first : rightSubTreeLL.first; // One of the L ro R subtree will always exist else it will be returned in second base case
        if (leftSubTreeLL.first)
        {
            //             if left subtree is there connect pointers(right and left) b/w root and left and left and right
            leftSubTreeLL.first->left = root;                   //connect N<-L
            leftSubTreeLL.second->right = rightSubTreeLL.first; //connect L->R
            if (rightSubTreeLL.first)
                rightSubTreeLL.first->left = leftSubTreeLL.second; // connect L<-R
        }
        else
            rightSubTreeLL.first->left = root; //connect N<-R since L doen't exist

        auto last = rightSubTreeLL.second ? rightSubTreeLL.second : leftSubTreeLL.second;
        return {root, last};
    }
};
//In LNR way
// Iterative
TreeNode *bToDLL(TreeNode *root)
{
    if (!root)
        return root;

    stack<TreeNode *> st;
    TreeNode *head = NULL;
    while (root)
    {
        st.push(root);
        head = root;
        root = root->left;
    }
    TreeNode *last = NULL;

    while (!st.empty())
    {
        TreeNode *temp = st.top();
        st.pop();
        temp->left = last;
        if (last)
            last->right = temp;
        last = temp;

        temp = temp->right;
        while (temp)
        {
            st.push(temp);
            temp = temp->left;
        }
    }
    if (last)
        last->right = NULL;
    return head;
}
//8
class MaxPathSum
{
public:
    int maxPathSum(TreeNode *root)
    {
        int ans = INT_MIN;
        maxPathSumWithRoot(root, ans);
        return ans;
    }
    int maxPathSumWithRoot(TreeNode *root, int &ans) //Returns max path sum which contains root
    {
        if (!root)
            return 0;
        int left = maxPathSumWithRoot(root->left, ans);
        int right = maxPathSumWithRoot(root->right, ans);

        int maxPathWithCurrentNode = root->val + max({left, right, 0});     //itself, left+ itself or right+itself
        ans = max({ans, left + right + root->val, maxPathWithCurrentNode}); // set the maxPathSum

        return maxPathWithCurrentNode;
    }
};

/*
Top Down
*/

//1 identical tree
bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (p == NULL && q == NULL)
        return true;
    if (p && q)
        return (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
    else //only one of the node is present
        return false;
}
//2 A tree is symmetric or  2 trees are mirror of each other
bool isSymmetric(TreeNode *root)
{
    if (!root)
        return true;
    return isSym(root->left, root->right);
}
bool isSym(TreeNode *root1, TreeNode *root2)
{
    if (!root1 && !root2)
        return true;
    if (root1 && root2)
        return root1->val == root2->val && isSym(root1->left, root2->right) && isSym(root1->right, root2->left);

    return false;
}
//3 Count Good Nodes:Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
int goodNodes(TreeNode *root)
{
    int goodCount = 0;
    goodNodes(root, goodCount, INT_MIN);
    return goodCount;
}
void goodNodes(TreeNode *root, int &ans, int maxValue)
{
    if (!root)
        return;
    if (root->val >= maxValue)
        ans++;
    goodNodes(root->left, ans, max(maxValue, root->val));
    goodNodes(root->right, ans, max(maxValue, root->val));
}