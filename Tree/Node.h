template <typename Element>

struct Node
{
    Element data;
    Node<Element>* leftChild{nullptr};
    Node<Element>* rightChild{nullptr};
    Node<Element>* parent{nullptr};//可附加指向双亲的指针（三叉链表）
    //线索二叉树（物理/存储结构）结点的成员变量——二叉树的线索化利用结点的空链域指向其遍历前驱/后继
    bool leftTag{false};//leftTag为false时，leftChild指向左孩子；leftTag为true时，leftChild指向遍历前驱
    bool rightTag{false};//rightTag为false时，rightChild指向右孩子；rightTag为true时，rightChild指向遍历后继

    Node(Element data) : data(data) {}
};