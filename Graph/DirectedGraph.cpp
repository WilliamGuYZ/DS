#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#define MAX_VERTEX_NUM 100

typedef int VertexInfo;//顶点域
typedef int EdgeInfo;//边的权值

struct EdgeListNode//边表结点
{
    VertexInfo vertex;
    EdgeInfo edge;
    EdgeListNode* next{nullptr};
};

struct EdgeList//边表（头结点）
{
    VertexInfo vertex;
    EdgeListNode* first{nullptr};
};

class DirectedGraph//有向图/无向图&邻接矩阵/邻接表并无绝对关系，此处用邻接表存储有向图
{
private:
    EdgeList vertexList[MAX_VERTEX_NUM];//顶点表（vertexList）由若干边表（头结点）（EdgeList）组成，边表由若干边表结点（EdgeListNode）组成（顺序+链式存储结构）
    int vertexNum;
    int edgeNum{0};

public:
    DirectedGraph(int vertexNum) : vertexNum(vertexNum)
    {
        for(VertexInfo v = 0;v < vertexNum;v++) vertexList[v].vertex = v;
    }

    VertexInfo firstNeighbor(VertexInfo v) const
    {
        EdgeListNode* p = vertexList[v].first;
        if(!p) return -1;
        return p -> vertex;
    }

    VertexInfo nextNeighbor(VertexInfo v,VertexInfo w) const
    {
        EdgeListNode* p = vertexList[v].first;
        while(p)
        {
            if(p -> vertex == w) break;
            p = p -> next;
        }
        if(!p || !p -> next) return -1;
        return p -> next -> vertex;
    }

    void BFS() const//广度优先遍历（队列的应用，类比二叉树的层序遍历）——邻接表O(|V|+|E|)
    {
        bool visited[vertexNum];
        for(VertexInfo v = 0;v < vertexNum;v++) visited[v] = false;
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            if(!visited[v]) bfs(v,visited);//若要讨论有向图的强连通性，则应用图的遍历算法的意义不大
        }
        cout << endl;
    }

    void bfs(VertexInfo v,bool visited[]) const//访问顶点v及其所有未被访问过的邻接顶点，按序重复至图中所有顶点均被访问过
    {
        queue<VertexInfo> q;
        q.push(v);
        while(!q.empty())
        {
            VertexInfo w = q.front();
            q.pop();
            cout << w << " ";
            visited[w] = true;
            for(VertexInfo k = firstNeighbor(w);k != -1;k = nextNeighbor(w,k))
            {
                if(!visited[k]) q.push(k);
            }
        }
    }

    void DFS() const//深度优先遍历（栈（递归）的应用）——邻接表O(|V|+|E|)
    {
        bool visited[vertexNum];
        for(VertexInfo v = 0;v < vertexNum;v++) visited[v] = false;
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            if(!visited[v]) dfs(v,visited);//若要讨论有向图的强连通性，则应用图的遍历算法的意义不大
        }
        cout << endl;
    }

    void dfs(VertexInfo v,bool visited[]) const//递归地访问顶点v及其任一未被访问过的邻接顶点，压栈退栈直至图中所有顶点均被访问过
    {
        cout << v << " ";
        visited[v] = true;
        for(VertexInfo w = firstNeighbor(v);w != -1;w = nextNeighbor(v,w))
        {
            if(!visited[w]) dfs(w,visited);
        }
    }

    bool TopologicalSorting() const//拓扑排序（AOV网（有向无环图））——若存在v到w的路径，则在拓扑序列中w一定在v之后
    {
        int indegrees[vertexNum];//拓扑排序不改变原图，需记录并动态调整各顶点的入度
        for(VertexInfo v = 0;v < vertexNum;v++) indegrees[v] = 0;
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            for(VertexInfo w = firstNeighbor(v);w != -1;w = nextNeighbor(v,w)) indegrees[w]++;
        }
        stack<VertexInfo> s;//栈的应用（队列亦可）——用空间换时间：若不使用栈（队列），则每次需遍历寻找入度为0的顶点
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            if(indegrees[v] == 0) s.push(v);
        }
        int count = 0;
        while(!s.empty())//每次删除入度为0的顶点及其出边
        {
            VertexInfo v = s.top();
            s.pop();
            for(VertexInfo w = firstNeighbor(v);w != -1;w = nextNeighbor(v,w))
            {
                if(--indegrees[w] == 0) s.push(w);//拓扑序列唯一的充要条件：每次检测到入度为0的顶点有且仅有1个
            }
            count++;
        }
        return count == vertexNum;//拓扑序列存在的充要条件：不存在回路（拓扑排序可用于判断有向图中是否存在环）
    }
};