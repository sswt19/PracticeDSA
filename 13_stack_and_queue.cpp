
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

/*
1. Implement Stack Using Arrays
    https://www.codingninjas.com/codestudio/problems/stack-implementation-using-array_3210209


*/

// 1. Implement stack
class Stack
{
    int *stack;
    int cur_no_of_elements;
    int capacity;

public:
    Stack(int capacity)
    {
        // Write your code here.
        stack = new int[capacity];
        this->capacity = capacity;
        this->cur_no_of_elements = 0;
    }

    void push(int num)
    {
        // Write your code here.
        if (this->capacity > this->cur_no_of_elements)
        {
            this->stack[cur_no_of_elements] = num;
            this->cur_no_of_elements++;
        }
    }

    int pop()
    {
        // Write your code here.
        if (this->cur_no_of_elements > 0)
        {
            int top = this->stack[cur_no_of_elements - 1];
            this->cur_no_of_elements--;
            return top;
        }
        return -1;
    }

    int top()
    {
        // Write your code here.
        if (this->cur_no_of_elements > 0)
        {
            int top = this->stack[cur_no_of_elements - 1];
            return top;
        }
        return -1;
    }

    int isEmpty()
    {
        // Write your code here.
        return this->cur_no_of_elements == 0;
    }

    int isFull()
    {
        // Write your code here.
        return this->cur_no_of_elements == this->capacity;
    }
};
