#include <iostream>
#include <queue>

using namespace std;

#define MAX_VERTEX_NUM 100
#define VERTEX_ITSELF 0//简单图中不含自环（与多重边）
#define NON_EXISTING_EDGE INT_MAX//边不存在（∞）

typedef int VertexInfo;//邻接矩阵用行/列下标表示顶点域
typedef int EdgeInfo;//边的信息：1（或weight）/∞/0

class UndirectedGraph//有向图/无向图&邻接矩阵/邻接表并无绝对关系，此处用邻接矩阵存储无向图
{
private:
    EdgeInfo edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vertexNum;
    int edgeNum{0};

public:
    UndirectedGraph(int vertexNum) : vertexNum(vertexNum)
    {
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            for(VertexInfo w = 0;w < vertexNum;w++)
            {
                edges[v][w] = v == w ? VERTEX_ITSELF : NON_EXISTING_EDGE;
            }
        }
    }

    VertexInfo firstNeighbor(VertexInfo v) const
    {
        for(VertexInfo w = 0;w < vertexNum;w++)
        {
            if(edges[v][w] != VERTEX_ITSELF && edges[v][w] != NON_EXISTING_EDGE) return w;
        }
        return -1;
    }

    VertexInfo nextNeighbor(VertexInfo v,VertexInfo w) const
    {
        for(VertexInfo k = w + 1;k < vertexNum;k++)
        {
            if(edges[v][k] != VERTEX_ITSELF && edges[v][k] != NON_EXISTING_EDGE) return k;
        }
        return -1;
    }

    void BFS() const//广度优先遍历（队列的应用，类比二叉树的层序遍历）——邻接矩阵O(|V|*|V|)
    {
        bool visited[vertexNum];
        for(VertexInfo v = 0;v < vertexNum;v++) visited[v] = false;
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            if(!visited[v]) bfs(v,visited);//对于无向图，BFS调用bfs的次数等于连通分量数
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

    void DFS() const//深度优先遍历（栈（递归）的应用）——邻接矩阵O(|V|*|V|)
    {
        bool visited[vertexNum];
        for(VertexInfo v = 0;v < vertexNum;v++) visited[v] = false;
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            if(!visited[v]) dfs(v,visited);//对于无向图，DFS调用dfs的次数等于连通分量数
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

    void Floyd() const//求各顶点之间的最短路径
    {
        EdgeInfo distances[vertexNum][vertexNum];
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            for(VertexInfo w = 0;w < vertexNum;w++) distances[v][w] = edges[v][w];
        }
        for(VertexInfo k = 0;k < vertexNum;k++)//尝试以k为中转点能否在v与w之间找到更短的路径
        {
            for(VertexInfo v = 0;v < vertexNum;v++)
            {
                for(VertexInfo w = 0;w < vertexNum;w++)
                {
                    if(distances[v][k] != NON_EXISTING_EDGE && distances[k][w] != NON_EXISTING_EDGE && distances[v][k] + distances[k][w] < distances[v][w]) distances[v][w] = distances[v][k] + distances[k][w];
                }
            }
        }
        for(VertexInfo v = 0;v < vertexNum;v++)
        {
            for(VertexInfo w = 0;w < vertexNum;w++)
            {
                if(distances[v][w] != VERTEX_ITSELF && distances[v][w] != NON_EXISTING_EDGE) cout << v << " -> " << w << " : " << distances[v][w] << endl;
            }
        }
    }
};