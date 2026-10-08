#include "Node.h"
#include <iostream>

using namespace std;

template <typename Element>

class BinaryThreadTree//在二叉树遍历的递归算法中进行线索化——二叉树的先序/中序/后序线索化利用结点的空链域指向其遍历前驱/后继
{
private:
    Node<Element>* root{nullptr};

public:
    void inOrderThread()//中序线索化
    {
        if(!root) return;
        Node<Element>* previous = nullptr;//随遍历过程动态调整previous
        inOrderThread(root,previous);
        previous -> rightTag = true;//中序遍历的最后一个结点既无右孩子，又无遍历后继（nullptr）
    }

    void inOrderThread(Node<Element>* node,Node<Element>*& previous)
    {
        if(!node) return;
        inOrderThread(node -> leftChild,previous);
        if(!node -> leftChild)
        {
            node -> leftChild = previous;
            node -> leftTag = true;
        }
        if(previous && !previous -> rightChild)
        {
            previous -> rightChild = node;
            previous -> rightTag = true;
        }
        previous = node;
        inOrderThread(node -> rightChild,previous);
    }

    void preOrderThread()//先序线索化
    {
        if(!root) return;
        Node<Element>* previous = nullptr;
        preOrderThread(root,previous);
        previous -> rightTag = true;//先序遍历的最后一个结点既无右孩子，又无遍历后继（nullptr）
    }

    void preOrderThread(Node<Element>* node,Node<Element>*& previous)
    {
        if(!node) return;
        if(!node -> leftChild)
        {
            node -> leftChild = previous;
            node -> leftTag = true;
        }
        if(previous && !previous -> rightChild)
        {
            previous -> rightChild = node;
            previous -> rightTag = true;
        }
        previous = node;
        if(!node -> leftTag) preOrderThread(node -> leftChild,previous);//理解：只有在先序线索化中，对根结点的处理先于对左子树的访问，因而leftChild可能指向遍历前驱，从而导致先序线索化陷入死循环
        preOrderThread(node -> rightChild,previous);
    }

    void postOrderThread()//后序线索化
    {
        if(!root) return;
        Node<Element>* previous = nullptr;
        postOrderThread(root,previous);
        if(!previous -> rightChild) previous -> rightTag = true;//后序遍历的最后一个结点可能有右孩子，但一定无遍历后继
    }

    void postOrderThread(Node<Element>* node,Node<Element>*& previous)
    {
        if(!node) return;
        postOrderThread(node -> leftChild,previous);
        postOrderThread(node -> rightChild,previous);
        if(!node -> leftChild)
        {
            node -> leftChild = previous;
            node -> leftTag = true;
        }
        if(previous && !previous -> rightChild)
        {
            previous -> rightChild = node;
            previous -> rightTag = true;
        }
        previous = node;
    }

    //线索二叉树的两大重点问题：1.如何进行二叉树的线索化；2.如何在线索二叉树中寻找结点的遍历前驱/后继——详略，此处以中序线索二叉树为例

    Node<Element>* firstNode(Node<Element>* node) const//寻找以node为根结点的子树的中序遍历的第一个结点
    {
        if(!node) return nullptr;
        auto p = node;
        while(!p -> leftTag) p = p -> leftChild;//注意循环条件：此处寻找子树中的firstNode，而非整棵中序线索二叉树
        return p;
    }

    Node<Element>* lastNode(Node<Element>* node) const//寻找以node为根结点的子树的中序遍历的最后一个结点
    {
        if(!node) return nullptr;
        auto p = node;
        while(!p -> rightTag) p = p -> rightChild;//注意循环条件：此处寻找子树中的lastNode，而非整棵中序线索二叉树
        return p;
    }

    Node<Element>* nextNode(Node<Element>* node) const//寻找中序线索二叉树中node的遍历后继
    {
        if(!node) return nullptr;
        if(node -> rightTag) return node -> rightChild;
        else return firstNode(node -> rightChild);//右子树中序遍历的第一个结点
    }

    Node<Element>* previousNode(Node<Element>* node) const//寻找中序线索二叉树中node的遍历前驱
    {
        if(!node) return nullptr;
        if(node -> leftTag) return node -> leftChild;
        else return lastNode(node -> leftChild);//左子树中序遍历的最后一个结点
    }

    void inOrderTraversal() const
    {
        for(auto p = firstNode(root);p;p = nextNode(p)) cout << p -> data << " ";//线索二叉树遍历的通用核心循环
        cout << endl;
    }

    //总结：中序线索二叉树——易于寻找中序前驱/后继；先序线索二叉树——易于寻找先序后继，难以寻找先序前驱；后序线索二叉树——易于寻找后序前驱，难以寻找后序后继
};