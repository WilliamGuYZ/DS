#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

template <typename Element>

class MaxHeap//堆（优先队列）——默认指二叉堆，是一种完全二叉树，一般采用二叉树的顺序存储结构——此处为大根堆（根≥左、右），注意大/小根（顶）堆的差异
{
private:
    vector<Element> list;
    int numOfElements;

public:
    void swap(int i,int j)
    {
        Element temp = list.at(i);
        list.at(i) = list.at(j);
        list.at(j) = temp;
    }

    void swim(int index)//上浮操作：若元素较大，则通过比较向上调整至合适位置，以满足大根堆的定义
    {
        for(int i = index;i > 1;i /= 2)
        {
            if(list.at(i) > list.at(i / 2)) swap(i / 2,i);
            else break;
        }
    }

    void sink(int index)//下沉操作：若元素较小，则通过比较向下调整至合适位置，以满足大根堆的定义
    {
        int i = index;
        while(i * 2 <= numOfElements)//只有分支结点才可能需要下沉——若无左孩子，则必无右孩子
        {
            int maxIndex = i * 2 + 1 <= numOfElements && list.at(i * 2 + 1) > list.at(i * 2) ? i * 2 + 1 : i * 2;//与孩子结点中的较大者进行下沉交换
            if(list.at(i) < list.at(maxIndex))
            {
                swap(i,maxIndex);
                i = maxIndex;
            }
            else break;
        }
    }

    void build()//建立大根堆：核心思路为检查所有分支结点是否满足大根堆的定义，若不满足则在原本合法大根堆的基础上逐结点调整——自下向上对各分支结点（(n / 2) ~ 1）进行sink操作（也可自上向下进行swim操作，但前者平均时间复杂度更低）
    {
        for(int i = numOfElements / 2;i >= 1;i--) sink(i);
    }

    MaxHeap()
    {
        list.push_back(0);//下标从1开始（在二叉树的顺序存储结构中，下标不仅反映结点编号，而且反映结点间的关系）
        string line;
        getline(cin,line);
        stringstream stream(line);
        Element e;
        while(stream >> e) list.push_back(e);
        numOfElements = list.size() - 1;
        build();//构造函数的核心为建立大根堆
    }

    void insert(Element e)//插入操作：先尾插，再在原本合法大根堆的基础上调整插入结点的位置
    {
        list.push_back(e);
        numOfElements++;
        swim(numOfElements);
    }

    Element remove(int index)//删除操作：先交换到表尾删除，再在原本合法大根堆的基础上调整交换结点的位置
    {
        if(numOfElements == 0) return nullptr;
        if(numOfElements == 1)
        {
            Element target = list.at(numOfElements);
            list.pop_back();
            numOfElements = 0;
            return target;
        }
        Element target = list.at(index);
        swap(index,numOfElements);
        list.pop_back();
        numOfElements--;
        if(index / 2 >= 1 && list.at(index) > list.at(index / 2)) swim(index);//一方面检查是否需要swim
        else if((index * 2 <= numOfElements && list.at(index) < list.at(index * 2)) || (index * 2 + 1 <= numOfElements && list.at(index) < list.at(index * 2 + 1))) sink(index);//另一方面检查是否需要sink
    }

    void heapSort()//堆排序（一般仅顺序表适用）
    {
        for(int i = numOfElements;i > 1;i--)//共(n - 1)趟
        {
            swap(1,i);//将表头的最大元素交换到表尾的已排序部分（交换过程无法保证稳定性）
            numOfElements--;//逻辑删除交换到表尾的元素
            sink(1);//在原本合法大根堆的基础上调整待排序部分的堆结构
        }
        numOfElements = list.size() - 1;//恢复表长
        for(int i = 1;i <= numOfElements;i++) cout << list.at(i) << " ";//基于大根堆的堆排序会得到递增序列
        cout << endl;
        build();//恢复堆结构
    }

    //总结：堆操作的核心思路——堆结构被破坏→在原本合法堆的基础上按定义调整堆结构
};