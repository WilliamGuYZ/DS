#include <stdexcept>

using namespace std;

const int MAX_SIZE = 100;

template <typename Element>

class Queue//顺序队列（队列为操作受限的线性表，其基本操作为一般线性表的子集）
{
private:
    Element list[MAX_SIZE];
    //为解决“假溢出”（end + 1 = MAX_SIZE）等问题，采用循环队列（逻辑上的循环）——此数据结构的实现关注以下问题：begin与end的指向含义、队列初始状态、入队出队操作、队空队满判断条件、队列长度计算……
    //<法一>调整begin与end的指向含义，通过牺牲一个存储单元以区分队空与队满
    int begin{0};//begin指向队首元素
    int end{0};//end指向队尾元素的下一个位置

public:
    Queue() = default;

    bool empty() const
    {
        return begin == end;
    }

    bool full() const
    {
        return (end + 1) % MAX_SIZE == begin;
    }

    int size() const
    {
        return (end - begin + MAX_SIZE) % MAX_SIZE;
    }

    void enqueue(Element e)//队尾插入
    {
        if((end + 1) % MAX_SIZE == begin) throw runtime_error("Queue is full!");
        list[end] = e;
        end = (end + 1) % MAX_SIZE;
    }

    Element dequeue()//队首删除
    {
        if(begin == end) throw runtime_error("Queue is empty!");
        Element e = list[begin];
        begin = (begin + 1) % MAX_SIZE;
        return e;
    }

    //<法二>维护flag变量以标识上一次操作是入队还是出队，以区分队空与队满
    //<法三>维护length变量以记录队列长度
};