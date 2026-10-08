#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

template <typename Element>

class LinearList//插入排序：每次将一个待排序元素插入到已排序部分的适当位置，直至整体有序
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

    void directInsertSort()//直接插入排序（顺序表、链表均适用）
    {
        for(int i = 1;i < list.size();i++)//共(n - 1)趟（待排序元素分别为1 ~ (n - 1)）
        {
            if(list.at(i) < list.at(i - 1))//已排序部分为0 ~ (i - 1)，顺序查找i的插入位置
            {
                int target = list.at(i),index = i - 1;
                while(index >= 0)
                {
                    if(target < list.at(index)) list.at(index + 1) = list.at(index);//边比较边移动
                    else break;//保证稳定性：若比较时遇到相等元素，则不移动
                    index--;
                }
                list.at(index + 1) = target;
            }
        }
        for(Element e : list) cout << e << " ";
        cout << endl;
    }

    void binaryInsertSort()//折半插入排序（一般仅顺序表适用）
    {
        for(int i = 1;i < list.size();i++)//共(n - 1)趟（待排序元素分别为1 ~ (n - 1)）
        {
            if(list.at(i) < list.at(i - 1))//已排序部分为0 ~ (i - 1)，折半查找待排序元素的插入位置
            {
                int target = list.at(i),low = 0,high = i - 1;
                while(low <= high)
                {
                    int middle = (low + high) / 2;
                    if(target < list.at(middle)) high = middle - 1;
                    else low = middle + 1;//保证稳定性：若比较时遇到相等元素，则向右半部分查找
                }
                for(int j = i - 1;j >= low;j--) list.at(j + 1) = list.at(j);//low = high + 1时结束比较，low即为插入位置，整体移动low ~ (i - 1)
                list.at(low) = target;
            }
        }
        for(Element e : list) cout << e << " ";
        cout << endl;
    }

    void shellSort(int distance)//希尔排序（一般仅顺序表适用）
    {
        for(int d = distance;d >= 1;d /= 2)//通过增量d划分出若干形如L[i,i + d,……,i + k * d]的子序列；对每个子序列进行直接插入排序；缩小增量d并重复上述过程（对于不同子序列中的相等元素，无法保证稳定性）
        {
            for(int i = d;i < list.size();i++)//相当于把直接插入排序的所有1改成d
            {
                if(list.at(i) < list.at(i - d))
                {
                    int temp = list.at(i),index = i - d;
                    while(index >= 0)
                    {
                        if(temp < list.at(index)) list.at(index + d) = list.at(index);
                        else break;
                        index -= d;
                    }
                    list.at(index + d) = temp;
                }
            }
        }
        for(Element e : list) cout << e << " ";
        cout << endl;
    }
};