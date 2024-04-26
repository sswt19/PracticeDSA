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
1. Level Order Traversal
    :https://leetcode.com/problems/binary-tree-level-order-traversal/description/
1.1 Level Order Successor
2. Level order traversal in spiral form/Zig-Zag
    :https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
3. Left & Right View of BTree
    :https://practice.geeksforgeeks.org/problems/left-view-of-binary-tree/1
    :https://practice.geeksforgeeks.org/problems/right-view-of-binary-tree/1
4. Top View of Binary Tree
    :https://practice.geeksforgeeks.org/problems/top-view-of-binary-tree/1
5. Bottom View of Binary Tree
    :https://practice.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1
6. Min Height of Binary Tree:
    The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
7. Vertical Order Traversal
8. Populate Next Right pointers of Tree
    a) using queue O(n) space :LOT
    b) using constant space :LOT
9. Maximum Width of Binary Tree
*/

// 1 LOT
class LOT
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> levels;
        if (!root)
            return levels;

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size(); // Gives the no of nodes in level we will be processing
            vector<int> lev(size);
            for (int i = 0; i < size; i++)
            {
                auto temp = q.front();
                q.pop();
                lev[i] = temp->val;
                // Push Children to queue
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
            levels.push_back(lev);
        }
        return levels;
    }
    // 1.1 LOT successor
    int levelOrderSuccessor(TreeNode *root, int key)
    {
        if (!root)
            return -1;

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size(); // Gives the no of nodes in level we will be processing

            for (int i = 0; i < size; i++)
            {
                auto temp = q.front();
                q.pop();
                // Push Children to queue
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
                // check for level order successor only when it's children are pushed, Ex test case successor of root node
                if (temp->val == key)
                    return q.empty() ? -1 : q.front()->val; // if q is empty no LS exist so return -1
            }
        }
        return -1; // key does not exist return -1
    }
};

// 2 Zig-Zag/Spiral LOT
class LOT_ZZ
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        if (!root)
            return {};

        vector<vector<int>> levels;
        queue<TreeNode *> q;
        q.push(root);
        int odd_hight = true;
        while (!q.empty())
        {
            int size = q.size();
            vector<int> lev(size);
            for (int i = 0; i < size; i++)
            {
                auto temp = q.front();
                q.pop();
                if (odd_hight) // insert from end if odd height
                    lev[i] = temp->val;
                else
                    lev[size - 1 - i] = temp->val;

                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
            odd_hight = !odd_hight; // alternate the reverseOrder
            levels.push_back(lev);
        }
        return levels;
    }
};

// 3 Left & Right View
class LeftRightView
{
public:
    // LeftView
    vector<int> leftSideView(TreeNode *root)
    {
        vector<int> lView;
        if (!root)
            return lView;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int levSize = q.size();
            for (int i = 0; i < levSize; i++)
            {
                auto temp = q.front();
                q.pop();
                if (i == 0)
                    lView.push_back(temp->val);
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
        }
        return lView;
    }

    // 4 RightView
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> rView;
        if (!root)
            return rView;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int levSize = q.size();
            for (int i = 0; i < levSize; i++)
            {
                auto temp = q.front();
                q.pop();
                if (i == levSize - 1)
                    rView.push_back(temp->val);
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
        }
        return rView;
    }
};

// 4 Top View : there is no chance of collision
class TopView
{
public:
    vector<int> topView(TreeNode *root)
    {
        if (!root)
            return {};

        unordered_map<int, int> nodeAtX; // No Need for vector since we want only topView node and not all nodes at postion X
        int minX = 0, maxX = 0;          // later useful in traversing unordered_map from dist minX to maxX
        queue<pair<TreeNode *, int>> q;  // Node and it's location in X axis
        q.push({root, 0});

        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();

            minX = min(minX, temp.second);
            maxX = max(maxX, temp.second);

            if (nodeAtX.find(temp.second) == nodeAtX.end()) // level order so it will be visible from top view, once set no need to change
                nodeAtX[temp.second] = temp.first->val;

            if (temp.first->left)
                q.push({temp.first->left, temp.second - 1});
            if (temp.first->right)
                q.push({temp.first->right, temp.second + 1});
        }
        vector<int> topView(maxX - minX + 1);
        for (int i = minX; i <= maxX; i++) // used here minX and maxX for constant time search
            topView[i - minX] = nodeAtX[i];
        return topView;
    }
};

// 5 Bottom View: Collision possible: example for X=0 both 3 and 4 can be used for bottom View
class BottomView
{
    // we are using what is encountered last in LOT so we will use 4
    /*
                20
              /    \
            8       22
          /   \     /   \
        5      3 4     25
    */
public:
    vector<int> bottomView(TreeNode *root)
    {
        if (!root)
            return {};
        unordered_map<int, int> nodeAtX;
        int minX = 0, maxX = 0;
        queue<pair<TreeNode *, int>> q;
        q.push({root, 0});

        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();

            minX = min(minX, temp.second);
            maxX = max(maxX, temp.second);

            nodeAtX[temp.second] = temp.first->val; // only change here, we use what is encountered last in LOT

            if (temp.first->left)
                q.push({temp.first->left, temp.second - 1});
            if (temp.first->right)
                q.push({temp.first->right, temp.second + 1});
        }
        vector<int> botView(maxX - minX + 1);
        for (int i = minX; i <= maxX; i++)
            botView[i - minX] = nodeAtX[i];
        return botView;
    }
};

// 6 Min Height of Binary Tree
int minDepth(TreeNode *root)
{
    if (!root)
        return 0;
    queue<TreeNode *> q;
    q.push(root);
    int height = 0;

    while (!q.empty())
    {
        height += 1; // Always same as the level we are going through
        int levSize = q.size();
        for (int i = 0; i < levSize; i++)
        {
            auto temp = q.front();
            q.pop();
            if (!temp->left && !temp->right) // first leaf node encountered return the height
                return height;
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
    return height; // will never be called
}

// 7:Vertical Order Traversal of a Binary Tree and because of below requirement code became complicated
/*
If two nodes have the same position,
check the layer, the node on higher level(close to root) goes first
if they also in the same level, order from small to large
*/
/*
 only same as 6 bottomview just replace
 nodeAtX[temp.second] = temp.first->val
 with
 nodeAtX[temp.second].push_back(temp.first->val)
*/
vector<vector<int>> verticalTraversal(TreeNode *root)
{

    unordered_map<int, vector<int>> nodesAtX;
    int minX = 0, maxX = 0;
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});

    while (!q.empty())
    {
        int levSize = q.size();
        unordered_map<int, vector<int>> nodesAtXsameLevel;
        for (int i = 0; i < levSize; i++)
        {
            auto temp = q.front();
            q.pop();

            minX = min(minX, temp.second);
            maxX = max(maxX, temp.second);

            nodesAtXsameLevel[temp.second].push_back(temp.first->val);
            if (temp.first->left)
                q.push({temp.first->left, temp.second - 1});
            if (temp.first->right)
                q.push({temp.first->right, temp.second + 1});
        }
        for (auto p : nodesAtXsameLevel)
        {
            sort(p.second.begin(), p.second.end());
            nodesAtX[p.first].insert(nodesAtX[p.first].end(), p.second.begin(), p.second.end());
        }
    }
    vector<vector<int>> VertView(maxX - minX + 1);
    for (int i = minX; i <= maxX; i++)
        VertView[i - minX] = nodesAtX[i];
    return VertView;
}

// 8. Populate Next Right pointers of Tree
TreeNode *connectSpaceConstant(TreeNode *root)
{
    if (!root)
        return NULL;

    TreeNode *head = root;           // Need to return root so using head for traversing current level
    TreeNode nextLevel = TreeNode(); // nextLevel.next is used to move to next level after traversing current level
    TreeNode *curr = &nextLevel;
    // curr wil be used to set next pointer of each node
    // and at start of each level it sets the nextLevel.next
    // curr is one level below the level of head

    while (head) // to check all nodes traversed
    {
        while (head) // to check current level traversed
        {
            if (head->left)
            {
                curr->next = head->left;
                curr = curr->next;
            }
            if (head->right)
            {
                curr->next = head->right;
                curr = curr->next;
            }
            head = head->next;
        }
        head = nextLevel.next; // moved to nextLevel
        nextLevel.next = NULL; // reset
        curr = &nextLevel;     // at start of new level it will set the nextLevel.next first
    }
    return root;
}

TreeNode *connectBFSQueue(TreeNode *root)
{
    if (!root)
        return root;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            auto temp = q.front();
            q.pop();
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
            temp->next = (i == size - 1) ? NULL : q.front(); // for last node in level point it to NULL
        }
    }
    return root;
}
// 9
int widthOfBinaryTree(TreeNode *root)
{
    if (!root)
        return 0;
    long long maxWidth = 0;
    queue<pair<TreeNode *, unsigned long long>> q;
    q.push({root, 0}); // we will be treating it as a Perfect BT so that every parent has 2 child even if it is null
    // we will use heap way of solving to represent position as pos*i+1 and pos*1+2 to calculate the nodes b/w twp nodes
    while (!q.empty())
    {
        int levelSize = q.size();
        long long left = q.front().second;
        long long right = q.front().second;
        for (int i = 0; i < levelSize; i++)
        {
            auto temp = q.front();
            q.pop();
            right = temp.second;
            if (temp.first->left)
                q.push({temp.first->left, 2 * temp.second + 1});
            if (temp.first->right)
                q.push({temp.first->right, 2 * temp.second + 2});
        }
        maxWidth = (maxWidth < right - left + 1) ? right - left + 1 : maxWidth;
    }
    return maxWidth;
}