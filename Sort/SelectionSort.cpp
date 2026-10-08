#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

template <typename Element>

class LinearList//选择排序：每次在待排序部分中选择一个最小（大）的元素加入已排序部分
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

    void selectionSort()//简单选择排序（顺序表、链表均适用）
    {
        int total = list.size() - 1;
        for(int i = 0;i < total;i++)//共(n - 1)趟，每趟将i ~ (n - 1)的最小元素交换到i（交换时相等元素的相对位置可能改变，无法保证稳定性）
        {
            int minIndex = i;
            for(int j = i + 1;j <= total;j++)
            {
                if(list.at(j) < list.at(minIndex)) minIndex = j;
            }
            Element temp = list.at(i);
            list.at(i) = list.at(minIndex);
            list.at(minIndex) = temp;
        }
        for(Element e : list) cout << e << " ";
        cout << endl;
    }

    //堆排序：详见Heap.cpp
};