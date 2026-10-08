#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

template <typename Element>

class LinearList//（二路）归并排序（顺序表、链表均适用）
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

    void mergeSort()
    {
        vector<Element> temp(list.size());
        mergeSort(temp,0,list.size() - 1);
        for(Element e : list) cout << e << " ";
        cout << endl;
    }

    void mergeSort(vector<Element>& temp,int low,int high)//temp选择引用类型可避免副本带来的空间开销
    {
        if(low < high)
        {
            int middle = (low + high) / 2;//将待排序列均匀划分为两个子序列
            //递归地对两个子序列进行二路归并排序（用二叉调用树分析二路归并的递归过程）
            mergeSort(temp,low,middle);
            mergeSort(temp,middle + 1,high);
            merge(temp,low,middle,middle + 1,high);//二路归并：将两个已经有序的子序列合并为一个
        }
    }

    void merge(vector<Element>& temp,int low1,int high1,int low2,int high2)
    {
        for(int i = low1;i <= high1;i++) temp.at(i) = list.at(i);
        for(int i = low2;i <= high2;i++) temp.at(i) = list.at(i);
        int index1 = low1,index2 = low2,index = index1;
        while(index1 <= high1 && index2 <= high2)
        {
            if(temp.at(index1) <= temp.at(index2)) list.at(index++) = temp.at(index1++);//保证稳定性：若遇到相等元素，则不改变其相对位置
            else list.at(index++) = temp.at(index2++);
        }
        while(index1 <= high1) list.at(index++) = temp.at(index1++);
        while(index2 <= high2) list.at(index++) = temp.at(index2++);
    }
};