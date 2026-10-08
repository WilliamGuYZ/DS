#include "Node.h"
#include <stdexcept>

using namespace std;

template <typename Element>

class DoubleLinkedList
{
private:
    Node<Element>* list;

public:
    DoubleLinkedList()
    {
        list = new Node<Element>();
    }

    ~DoubleLinkedList()
    {
        Node<Element>* p1 = list,p2;
        while(p1)
        {
            p2 = p1 -> next;
            delete p1;
            p1 = p2;
        }
    }

    int size() const
    {
        int count = 0;
        for(auto p = list -> next;p;p = p -> next) count++;
        return count;
    }

    Node<Element>* get(int position) const
    {
        if(position < 0 || position > size()) throw out_of_range("Invalid position!");
        auto p = list;
        for(int i = 0;i != position;i++) p = p -> next;
        return p;
    }

    void insertNode(int position,Element e)
    {
        if(position < 1 || position > size() + 1) throw out_of_range("Invalid position!");
        auto oldNode = get(position - 1);
        Node<Element>* newNode = new Node<Element>(e);
        newNode -> next = oldNode -> next;
        if(oldNode -> next) oldNode -> next -> prev = newNode;
        newNode -> prev = oldNode;
        oldNode -> next = newNode;
    }

    Node<Element>* deleteNode(int position)
    {
        if(position < 1 || position > size()) throw out_of_range("Invalid position!");
        auto p = get(position - 1);
        auto target = p -> next;
        p -> next = target -> next;
        if(target -> next) target -> next -> prev = p;
        target -> next = nullptr;
        target -> prev = nullptr;
        return target;
    }

    void reverse()
    {
        Node<Element>* p1 = nullptr;
        auto p2 = list -> next;
        if(!p2) return;
        auto p3 = list -> next -> next;
        if(!p3) return;
        while(p2)
        {
            p2 -> next = p1;
            p2 -> prev = p3;
            p1 = p2;
            p2 = p3;
            if(p3) p3 = p3 -> next;
        }
        list -> next = p1;
        p1 -> prev = list;
    }
};