#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

template <typename Element>

class LinearList//交换排序：基于元素之间关键字的大小比较进行位置交换
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

    void bubbleSort()//冒泡排序（顺序表、链表均适用）
    {
        int total = list.size() - 1;
        for(int i = 0;i < total;i++)//最多(n - 1)趟
        {
            bool flag = false;
            for(int j = total;j > i;j--)//每趟将i ~ (n - 1)的最小元素从后往前冒泡到i
            {
                if(list.at(j) < list.at(j - 1))//保证稳定性：若冒泡时遇到相邻元素相等的情况，则不交换其位置
                {
                    Element temp = list.at(j - 1);
                    list.at(j - 1) = list.at(j);
                    list.at(j) = temp;
                    flag = true;
                }
            }
            if(!flag) break;//若某趟冒泡未发生交换，则说明已整体有序，可提前结束
        }
        for(Element e : list) cout << e << " ";
        cout << endl;
    }

    void quickSort()//快速排序（一般仅顺序表适用）
    {
        quickSort(0,list.size() - 1);
        for(Element e : list) cout << e << " ";
        cout << endl;
    }

    void quickSort(int low,int high)
    {
        if(low < high)
        {
            int pivotPosition = partition(low,high);//按枢轴对序列进行一次划分（一次划分&一趟排序）
            //递归地对左右子序列进行快速排序（用递归工作栈/递归调用树表示递归过程）
            quickSort(low,pivotPosition - 1);
            quickSort(pivotPosition + 1,high);
        }
    }

    int partition(int low,int high)//每次划分可确定枢轴的最终位置，并将待排序列划分为左右子序列（左≤枢轴≤右）
    {
        Element pivot = list.at(low);//通常将序列首元素确定为枢轴——枢轴的选择会影响划分均匀程度，从而影响递归深度
        int left = low,right = high;
        while(left < right)//将序列中小于枢轴的元素移动到枢轴左侧，大于枢轴的元素移动到枢轴右侧（移动过程中无法保证稳定性）
        {
            while(left < right && list.at(right) >= pivot) right--;
            list.at(left) = list.at(right);
            while(left < right && list.at(left) <= pivot) left++;
            list.at(right) = list.at(left);
        }
        list.at(left) = pivot;
        return left;
    }
};