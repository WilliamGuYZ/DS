#include <iostream>

using namespace std;

template <typename Element>

class SequenceList//顺序表（线性表的位序从1开始——position针对逻辑结构，数组的下标从0开始——index针对物理（存储）结构）
{
private:
    Element* list;//动态分配（静态分配不便扩容）
    int capacity;
    int length{0};

public:
    SequenceList(int initialCapacity)
    {
        if(initialCapacity < 0) throw invalid_argument("Invalid capacity!");
        list = new Element[initialCapacity];
        capacity = initialCapacity;
    }

    ~SequenceList()
    {
        delete[] list;
    }

    bool empty() const
    {
        return length == 0;
    }

    int size() const
    {
        return length;
    }

    void resize(int newCapacity)
    {
        if(newCapacity < 0) throw invalid_argument("Invalid capacity!");
        Element* newList = new Element[newCapacity];
        int newLength = min(length,newCapacity);
        for(int i = 0;i < newLength;i++) newList[i] = list[i];
        delete[] list;
        list = newList;
        capacity = newCapacity;
        length = newLength;
    }

    void insert(int position,Element e)
    {
        if(length == capacity) resize(capacity + 1);
        int index = position - 1;
        if(index < 0 || index > length) throw out_of_range("Invalid position!");
        for(int i = length;i > index;i--) list[i] = list[i - 1];
        list[index] = e;
        length++;
    }

    Element remove(int position)
    {
        int index = position - 1;
        if(index < 0 || index >= length) throw out_of_range("Invalid position!");
        Element e = list[index];
        for(int i = index;i < length - 1;i++) list[i] = list[i + 1];
        length--;
        return e;
    }

    void update(int position,Element e)
    {
        int index = position - 1;
        if(index < 0 || index >= length) throw out_of_range("Invalid position!");
        list[index] = e;
    }

    Element get(int position) const//按序查找（顺序表O(1)，链表O(n)）
    {
        int index = position - 1;
        if(index < 0 || index >= length) throw out_of_range("Invalid position!");
        return list[index];
    }

    int locate(Element e) const//按值查找（折半查找O(log n)，顺序查找O(n)）
    {
        for(int i = 0;i < length;i++)
        {
            if(list[i] == e) return i + 1;
        }
        throw runtime_error("Not found!");
    }

    void print() const
    {
        for(int i = 0;i < length;i++) cout << list[i] << " ";
        cout << endl;
    }
};