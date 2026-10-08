#include "Node.h"
#include <iostream>

using namespace std;

template <typename Element>

class SingleLinkedList//带头结点的单链表（线性表中的位序从1开始，但链表中的头结点（非数据结点）占据position为0的位置）
{
private:
    Node<Element>* list;

public:
    SingleLinkedList()
    {
        list = new Node<Element>();
    }

    ~SingleLinkedList()
    {
        Node<Element>* p1 = list,p2;
        while(p1)
        {
            p2 = p1 -> next;
            delete p1;
            p1 = p2;
        }
    }

    bool empty() const
    {
        return !list -> next;
    }

    int size() const
    {
        int count = 0;
        for(auto p = list -> next;p;p = p -> next) count++;
        return count;
    }

    Node<Element>* get(int position) const//按序查找
    {
        if(position < 0 || position > size()) throw out_of_range("Invalid position!");
        auto p = list;
        for(int i = 0;i != position;i++) p = p -> next;
        return p;
    }

    Node<Element>* locate(Element e) const//按值查找
    {
        for(auto p = list -> next;p;p = p -> next)
        {
            if(p -> data == e) return p;
        }
        throw runtime_error("Not found!");
    }

    void insertAfter(Node<Element>* oldNode,Node<Element>* newNode)
    {
        newNode -> next = oldNode -> next;
        oldNode -> next = newNode;
    }

    void insertBefore(Node<Element>* oldNode,Node<Element>* newNode)
    {
        Element e = newNode -> data;
        newNode -> data = oldNode -> data;
        oldNode -> data = e;
        insertAfter(oldNode,newNode);
    }

    void insertNode(int position,Element e)
    {
        if(position < 1 || position > size() + 1) throw out_of_range("Invalid position!");
        auto oldNode = get(position - 1);
        Node<Element>* newNode = new Node<Element>(e);
        insertAfter(oldNode,newNode);
    }

    Node<Element>* deleteNode(int position)
    {
        if(position < 1 || position > size()) throw out_of_range("Invalid position!");
        auto p = get(position - 1);
        auto target = p -> next;
        p -> next = target -> next;
        target -> next = nullptr;
        return target;
    }

    void reverse()//逆转链表（画图分析，先整体后细节）
    {
        Node<Element>* p1 = nullptr;
        auto p2 = list -> next;
        if(!p2) return;//0个数据结点——无需操作
        auto p3 = list -> next -> next;
        if(!p3) return;//1个数据结点——无需操作
        while(p2)
        {
            p2 -> next = p1;
            p1 = p2;
            p2 = p3;
            if(p3) p3 = p3 -> next;
        }
        list -> next = p1;
    }

    void print() const
    {
        for(auto p = list -> next;p;p = p -> next) cout << p -> data << " ";
        cout << endl;
    }
};