#define SIZE 1000

using namespace std;

class DisjointSet//并查集（逻辑结构中的非线性结构，本质是集合）——采用树的双亲表示法（顺序存储结构），每个子集合用一颗树表示，所有表示子集合的树构成表示全集合的森林，存放在数组内
{
private:
    int set[SIZE];//数组元素的下标表示元素名，数组元素的值反映与子集合的从属关系（常为对应父结点/根结点元素的下标）

public:
    DisjointSet()
    {
        for(int i = 0;i < SIZE;i++) set[i] = -1;//根结点元素的值表示对应子集合元素数量的相反数，初始状态下各结点属于不同的子集合
    }

    int Find(int x)//查的优化：先找到根结点，再将查找路径上的所有结点都挂到根结点下
    {
        int root = x;
        while(set[root] >= 0) root = set[root];
        int temp = x;
        while(temp != root && set[temp] != root)
        {
            set[temp] = root;
            temp = set[temp];
        }
        return root;
    }

    void Union(int root1,int root2)//并的优化：让小树合并到大树
    {
        if(root1 == root2) return;
        if(set[root1] > set[root2])//root1挂至root2
        {
            set[root1] = root2;
            set[root2] += set[root1];
        }
        else//root2挂至root1
        {
            set[root2] = root1;
            set[root1] += set[root2];
        }
    }
};