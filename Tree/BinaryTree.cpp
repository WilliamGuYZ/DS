#include "Node.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <typename Element>

class BinaryTree
{
private:
    Node<Element>* root{nullptr};

public:
    //二叉树遍历的非递归算法：栈与队列的应用

    void preOrderTraversal() const//先序遍历
    {
        if(!root) return;
        stack<Node<Element>*> nodes;
        auto p = root;
        while(p || !nodes.empty())
        {
            if(p)
            {
                nodes.push(p);//入栈序列为先序序列
                cout << p -> data << " ";//入栈时访问
                p = p -> leftChild;
            }
            else
            {
                p = nodes.top();
                nodes.pop();//出栈序列为中序序列
                p = p -> rightChild;
            }
        }
        cout << endl;
    }

    void inOrderTraversal() const//中序遍历
    {
        if(!root) return;
        stack<Node<Element>*> nodes;
        auto p = root;
        while(p || !nodes.empty())
        {
            if(p)
            {
                nodes.push(p);//入栈序列为先序序列
                p = p -> leftChild;
            }
            else
            {
                p = nodes.top();
                nodes.pop();//出栈序列为中序序列
                cout << p -> data << " ";//出栈时访问
                p = p -> rightChild;
            }
        }
        cout << endl;
    }

    void postOrderTraversal() const//后序遍历
    {
        if(!root) return;
        stack<Node<Element>*> nodes;
        auto p = root;
        Node<Element>* visited = nullptr;
        while(p || !nodes.empty())
        {
            if(p)
            {
                nodes.push(p);//入栈序列为先序序列
                p = p -> leftChild;
            }
            else
            {
                p = nodes.top();
                if(p -> rightChild && p -> rightChild != visited) p = p -> rightChild;
                else
                {
                    nodes.pop();//出栈序列为后序序列
                    cout << p -> data << " ";//出栈时访问
                    visited = p;
                    p = nullptr;
                }
            }
        }
        cout << endl;
    }

    void levelOrderTraversal() const//层序遍历
    {
        if(!root) return;
        queue<Node<Element>*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            auto p = nodes.front();
            nodes.pop();//出入队列序列均为层序序列
            cout << p -> data << " ";//出队列时访问
            if(p -> leftChild) nodes.push(p -> leftChild);
            if(p -> rightChild) nodes.push(p -> rightChild);
        }
        cout << endl;
    }
};