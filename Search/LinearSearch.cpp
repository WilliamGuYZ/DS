#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

template <typename Element>

class LinearList
{
private:
    vector<Element> list;

public:
    LinearList()
    {
        string line;
        getline(cin,line);
        stringstream stream(line);
        Element e;
        while(stream >> e) list.push_back(e);
    }

    int sequenceSearch(Element key) const//顺序查找（适用于顺序表与链表）
    {
        list.push_back(key);//优化1：为避免数组越界检查等不必要的判断，可在表头（尾）设置哨兵标记
        int index = 0;
        while(list[index] != key) index++;
        list.pop_back();
        return index == list.size() ? -1 : index;
        //优化2：为减少查找成功时的平均查找长度，可先对表中记录按查找概率进行排序（类比哈夫曼树）
        //优化3：为减少查找失败时的平均查找长度，可先对表中记录进行排序（有序表查找的二叉判定树）
    }

    int binarySearch(Element key) const//折半查找（仅适用于有序的顺序表）
    {
        int left = 0,right = list.size() - 1;
        while(left <= right)
        {
            int mid = (left + right) / 2;//向下（上）取整——由查找过程构造折半查找的二叉判定树
            if(key < list[mid]) right = mid - 1;
            else if(key > list[mid]) left = mid + 1;
            else return mid;
        }
        return -1;
    }
};