template <typename Element>

struct Node
{
    Element data;
    Node* next{nullptr};
    Node* prev{nullptr};

    Node() {}//头结点（不含数据的表头结点，占据链表中position为0的位置，用于简化链表操作中对特殊情况的处理）
    Node(Element data) : data(data) {}//数据结点
};