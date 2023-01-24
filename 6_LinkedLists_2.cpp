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
1. Find intersection point of Y LinkedList
    https://leetcode.com/problems/intersection-of-two-linked-lists/
2. is Palindrome using constant space
    https://leetcode.com/problems/palindrome-linked-list/
3. Rotate List
    https://leetcode.com/problems/rotate-list/description/
*/

// 1 Find intersection point of Y LinkedList
class GetIntersectionOf2LL
{ /*
 Approaches: 1) use hashmap
 2) use the below method
 */
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        auto p1 = headA, p2 = headB;
        while (p1 || p2) // Both will become NULL at same time when we have traversed twice, distance covered a+b by both
        {
            if (p1 == p2) // found the intersection
                return p1;
            p1 = p1 ? p1->next : headB; // when p1 becomes NULL move it to second list
            p2 = p2 ? p2->next : headA; // when p2 becomes NULL move it first list
        }
        return NULL; // not found the intersection
    }
};

// 2 Palindrome check using constant space
class PalConstSpace
{
    ListNode *reverse(ListNode *head)
    {
        ListNode *prev = NULL, *curr = head;
        while (curr)
        {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

public:
    bool isPalindrome(ListNode *head)
    {
        bool isPal = true;
        auto slow = head, fast = head;
        while (fast && fast->next && fast->next->next)
        { // when size 3 and 4 slow will be at 2
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *secondHalfOfList = reverse(slow->next); // everything after slow should be reversed and matche with the first half of list
        auto t1 = head, t2 = secondHalfOfList;
        while (t2) // since t1 size can be greater than t2 when list is odd in size
        {
            if (t1->val != t2->val)
            {
                isPal = false;
                break;
            }
            t1 = t1->next;
            t2 = t2->next;
        }
        slow->next = reverse(secondHalfOfList); // bring the list to original state again
        return isPal;
    }
};

// 3 Rotate List
class RotateList
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (!head)
            return head;

        // k can be larger than no of nodes in list, so we need to find the size of list first and set k
        int listSize = 1;
        ListNode *lastNode = head; // lastNode will be used to join the Last node to head later
        while (lastNode->next)
        {
            listSize++;
            lastNode = lastNode->next;
        }

        // compute number of rotations required since k can be 2*10^9 and list size can be only 500
        k = k % listSize;
        // no rotations needed
        if (k == 0)
            return head;

        // find the new end node and break the LL there
        int newEndPos = listSize - k;
        auto newEndNode = head;
        int i = 1;
        while (i != newEndPos)
        {
            newEndNode = newEndNode->next;
            i++;
        }

        // join the last node to head
        lastNode->next = head;
        head = newEndNode->next; // node next to endnode will be new head
        newEndNode->next = NULL;
        return head;
    }
};

//