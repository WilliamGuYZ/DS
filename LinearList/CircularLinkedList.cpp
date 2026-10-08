#include "Node.h"

template <typename Element>

class CircularLinkedList
{
private:
    Node<Element>* list;

public:
    CircularLinkedList()
    {
        //循环单链表：
        //list = new Node<Element>();
        //list -> next = list;
        //循环双链表：
        //list = new Node<Element>();
        //list -> next = list;
        //list -> prev = list;
    }

    bool empty() const
    {
        //循环单链表：return list -> next == list;
        //循环双链表：return list -> next == list && list -> prev == list;
    }

    bool isTail(Node<Element>* target) const
    {
        return target -> next == list;
    }

    //循环链表的插入、删除等操作：类比单链表双链表（操作尾结点时需做特殊处理，以保持循环）——画图分析，先整体后细节
};