#include <stdexcept>

using namespace std;

template <typename Element>

struct Node
{
    Element data;
    Node<Element>* leftChild{nullptr};
    Node<Element>* rightChild{nullptr};

    Node(Element data) : data(data) {}
};

template <typename Element>

class BinarySearchTree//二叉查找（排序）树：左＜根＜右
{
private:
    Node<Element>* root{nullptr};

public:
    BinarySearchTree() = default;

    ~BinarySearchTree()
    {
        deleteTree(root);
    }

    void deleteTree(Node<Element>* node)//以后序遍历递归算法的思想进行树的删除
    {
        if(!node) return;
        deleteTree(node -> leftChild);
        deleteTree(node -> rightChild);
        delete node;
    }

    Node<Element>* searchNode(Element e) const
    {
        if(!root) throw runtime_error("Empty tree!");
        auto p = root;
        while(p)
        {
            if(e < p -> data) p = p -> leftChild;
            else if(e > p -> data) p = p -> rightChild;
            else return p;
        }
        throw runtime_error("Not found!");
    }

    void insertNode(Element e)
    {
        auto newNode = new Node<Element>(e);
        if(!root)
        {
            root = newNode;
            return;
        }
        auto p = root;
        while(p)
        {
            if(e < p -> data)
            {
                if(p -> leftChild) p = p -> leftChild;
                else
                {
                    p -> leftChild = newNode;
                    break;
                }
            }
            else if(e > p -> data)
            {
                if(p -> rightChild) p = p -> rightChild;
                else
                {
                    p -> rightChild = newNode;
                    break;
                }
            }
            else throw runtime_error("Value already exists!");
        }
    }

    Node<Element>* deleteNode(Element e)
    {
        if(!root) throw runtime_error("Empty tree!");
        Node<Element>* target = root,parent;
        while(target)
        {
            if(e == target -> data) break;
            else
            {
                parent = target;
                target = e < target -> data ? target -> leftChild : target -> rightChild;
            }
        }
        if(!target) throw runtime_error("Not found!");
        //target即为删除的目标结点，本质为考虑由谁替代target的位置
        if(target -> leftChild && target -> rightChild)//目标结点的左右子树均存在
        {
            //用右子树的最小结点替代目标结点（左子树的最大结点亦可）
            auto temp = deleteNode(min(target -> rightChild));//走下面的else分支进行右子树最小结点的删除
            if(target == root) root = temp;//parent为空的情况
            else if(target == parent -> leftChild) parent -> leftChild = temp;
            else parent -> rightChild = temp;
            temp -> leftChild = target -> leftChild;
            temp -> rightChild = target -> rightChild;
        }
        else//目标结点的左右子树至多存在其一
        {
            //直接用子树替代目标结点
            auto sub = target -> leftChild ? target -> leftChild : target -> rightChild;
            if(target == root) root = sub;//parent为空的情况
            else if(target == parent -> leftChild) parent -> leftChild = sub;
            else parent -> rightChild = sub;
        }
        target -> leftChild = nullptr;
        target -> rightChild = nullptr;
        return target;
    }

    Element max(Node<Element>* node) const//“最右下”结点即为max
    {
        if(!node) throw runtime_error("Empty tree!");
        auto p = node;
        while(p -> rightChild) p = p -> rightChild;
        return p -> data;
    }

    Element min(Node<Element>* node) const//“最左下”结点即为min
    {
        if(!node) throw runtime_error("Empty tree!");
        auto p = node;
        while(p -> leftChild) p = p -> leftChild;
        return p -> data;
    }
};