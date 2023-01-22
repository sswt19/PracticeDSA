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

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*
1. Reverse a LL
    https://leetcode.com/problems/reverse-linked-list/
2. Middle Node
    https://leetcode.com/problems/middle-of-the-linked-list/
3. Merge two Sorted Lists Constant Space
    https://leetcode.com/problems/merge-two-sorted-lists/
4. Remove Nth node from end
    https://leetcode.com/problems/remove-nth-node-from-end-of-list/
5. Delete a given Node when a node is given
    https://leetcode.com/problems/delete-node-in-a-linked-list/
6. Add two numbers in LL (Number are in reverse order)
    https://leetcode.com/problems/add-two-numbers/
7. Check cycle
    https://leetcode.com/problems/linked-list-cycle/
8. Find starting point of cycle
    https://leetcode.com/problems/linked-list-cycle-ii/
9. Remove Cycle
    https://practice.geeksforgeeks.org/problems/remove-loop-in-linked-list/1
*/
// 1 Reverse a LL
class ReverseLL
{
public: // Recursive
    ListNode *reverseList(ListNode *head)
    {
        // recursive
        if (!head || !head->next) // if size is 0 or 1 nothing to do
            return head;
        // 1->2->3->4->5
        ListNode *newHead = reverseList(head->next); // reverse from 2 to 5 newHead is 5, 5->4->3->2
        head->next->next = head;                     // 1 still points to 2 so using 1 to set 1->2->NULL to 2->1->2
        head->next = NULL;                           // break the cycle set 1->NULL now list becomes 5->4->3->2->1
        return newHead;
    }
    // Iterative
    ListNode *reverseListIterative(ListNode *head)
    {                          // will work for size 0 and 1 too
        ListNode *prev = NULL; // used to point to prev value by head
        while (head)
        {
            ListNode *next = head->next; // to know the next value since head->next will point to previous now
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};

// 2. Middle Node
class MiddleElementLL
{

public:
    // If there are two middle nodes, return the second middle node
    ListNode *middleNode(ListNode *head)
    {
        // for odd return middle for even return second middle
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) // if size=2=>fast at 3 and slow at 2, size=3 fast at 3 slow at 2
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    // If there are two middle nodes, return the first middle node
    ListNode *middleNode2(ListNode *head)
    {
        // for odd return middle for even return first middle
        // the only difference will be starting point, we will start from 0 so after 1st step fast=0->1->2 and slow=0-1, so slow=head and fast=head->next
        // where as in previous case we started slow and fast from 1 instead of 0
        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next) // if size=2=>fast at 2 and slow at 1, size=3 fast at 4 slow at 2
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

// 3 Merge two Sorted Lists Constant Space
class MergeTwoSortedLL
{
public:
    ListNode *mergeTwoLists(ListNode *p1, ListNode *p2)
    {

        ListNode head;          // to create starting point of list with head->next
        ListNode *temp = &head; // temp is used to traverse the list and insert at end to the list
        while (p1 && p2)
        {
            if (p1->val <= p2->val)
            {
                temp->next = p1;
                p1 = p1->next;
            }
            else
            {
                temp->next = p2;
                p2 = p2->next;
            }
            temp = temp->next;
        }
        //*** Directly attach the list, we don't need to attach one by one as we did in array
        if (p1) // attach the whole remaining list
            temp->next = p1;
        if (p2) // similar
            temp->next = p2;
        return head.next;
    }
};

// 4
class RemoveNthFromEnd
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // to remove Nth we need access to N+1th node from end, Exception when n is the size of list
        // Hence the ahead pointer should be n times ahead
        ListNode *fast = head;
        while (n && fast)
        {
            fast = fast->next;
            n--;
        }
        // fast has become NULL, n given is greater than what the list size is
        if (n > 0)
            return NULL;
        // it means n is size of list and we need to remove head root node
        if (fast == NULL && n == 0)
        {
            auto toDelete = head;
            head = head->next;
            toDelete->next = NULL;
            delete toDelete;
            return head;
        }
        //** by this while loop fast will be at last node and after slow there will be N nodes hence slow will be at n+1th node from end
        auto slow = head; // currently slow is n+1 node from fast, so we will move both fast and slow one by one till fast is the last node
        while (fast->next)
        {
            fast = fast->next;
            slow = slow->next;
        }
        auto toDelete = slow->next;
        slow->next = slow->next->next;
        toDelete->next = NULL;
        delete toDelete;
        return head;
    }
};

// 5 Delete a given Node when a node is given
class DeleteNodeinConstantTime
{
public:
    void deleteNode(ListNode *node)
    {

        node->val = node->next->val;
        auto temp = node->next;
        node->next = temp->next;
        delete temp;
    }
};

// 6 Add two numbers in LL (Number are in reverse order)
class AddTwoNumsInLL
{ /*
    for number in left to right first reverse then add them and then reverse again
    below the numbers are in reverse order
 */
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode dummyHead;
        ListNode *temp = &dummyHead; // temp will point to where we have to add new node
        int carry = 0;

        while (l1 || l2) // OR beacuse if the length of integers are different we should coninue with the longer integer
        {
            int sum = carry;
            if (l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            temp->next = new ListNode(sum % 10);
            temp = temp->next;
            carry = sum / 10;
        }
        if (carry)
            temp->next = new ListNode(carry);
        return dummyHead.next;
    }
};

// 7 Detect Cycle
class DetectCycleinLL
{ /*
  Approaches: 1) use hashmap
  2) use the below method
  */
public:
    bool hasCycle(ListNode *head)
    {
        auto slow = head;
        auto fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        // we have reached end of the list and there was no cycle
        return false;
    }
};

// 8 Find starting point of cycle
class DetectCycleStart
{
public:
    ListNode *detectCycleStart(ListNode *head)
    {
        auto slow = head, fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                // find starting point now
                slow = head;
                while (slow != fast)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return NULL;
    }
};

// 9 Remove Cycle
class RemoveCycle
{
public:
    // Use same logic as detect start of cycle keep a pointer just before the start of cycle break it
    void removeLoop(ListNode *head)
    {
        auto slow = head, fast = head;
        ListNode *prev = NULL;
        while (fast && fast->next)
        {
            prev = fast->next; // will always be one step behind fast
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                // find starting point now
                slow = head;
                while (slow != fast)
                {
                    prev = fast; // will always be one step behind fast
                    slow = slow->next;
                    fast = fast->next;
                }
                prev->next = NULL; // break the cycle
            }
        }
    }
};

//