#include <stdexcept>

using namespace std;

const int MAX_SIZE = 100;

template <typename Element>

class Stack//顺序栈（栈为操作受限的线性表，其基本操作为一般线性表的子集）
{
private:
    Element list[MAX_SIZE];
    int top{-1};//栈底相对不变，栈顶动态变化

public:
    Stack() = default;

    bool empty() const
    {
        return top == -1;
    }

    bool full() const
    {
        return top + 1 == MAX_SIZE;
    }

    int size() const
    {
        return top + 1;
    }

    void push(Element e)//栈顶插入
    {
        if(top + 1 == MAX_SIZE) throw runtime_error("Stack is full!");
        list[++top] = e;
    }

    Element pop()//栈顶删除
    {
        if(top == -1) throw runtime_error("Stack is empty!");
        return list[top--];
    }
};