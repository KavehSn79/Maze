#include <iostream>
#include <vector>

using namespace std;
//////////////////////////////////////////////////////////////////       BTree
template <typename T>
class BTreeNode{
public:
    T *keys;
    int deg;
    BTreeNode **ptrz;
    int n;
    bool isleaf;
    BTreeNode(int ,bool );
    void insertNonFull(T );
    void split(int , BTreeNode *);
    BTreeNode *search(T k){
        int i = 0;
        while (i<n && k>keys[i])
            i++;
        if (keys[i] == k)
            return this;
        if (isleaf)
            return NULL;
        return ptrz[i]->search(k);
    }
};

template <typename T>
class BTree{
private:
    BTreeNode<T> *root;
    int deg;
public:
    BTree(int d){root=NULL; deg=d;}
    BTreeNode<T>* search(T k)
    {return (root == NULL)? NULL : root->search(k); }
    void insert(T k) {
        if (root == NULL){
            root = new BTreeNode<T>(deg, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else{
            if (root->n == 2*deg-1){
                BTreeNode<T> *s = new BTreeNode<T>(deg, false);
                s->ptrz[0] = root;
                s->split(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->ptrz[i]->insertNonFull(k);
                root = s;
            }
            else
                root->insertNonFull(k);
        }
    }
};

template <typename T>
BTreeNode<T>::BTreeNode(int d, bool il) {
    deg = d;
    keys = new T[2*deg-1];
    ptrz = new BTreeNode *[2*deg];
    n=0;
    isleaf = il;
}

template <typename T>
void BTreeNode<T>::split(int indx, BTreeNode *p) {
    BTreeNode *p0 = new BTreeNode(p->deg, p->isleaf);
    p0->n = deg-1;
    for(int i=0; i<deg-1; i++){
        p0->keys[i]=p->keys[i+deg];
    }
    if(!(p->isleaf)){
        for(int i=0; i<deg; i++){
            p0->ptrz[i] = p->ptrz[i+deg];
        }
    }
    p->n = deg-1;
    for(int i=n; i>=indx+1; i--){
        ptrz[i+1]=ptrz[i];
    }
    ptrz[indx+1] = p0;
    for(int i=n-1;i>=indx;i--){
        keys[i+1]=keys[i];
    }
    keys[indx]=p->keys[deg-1];
    n++;
}

template <typename T>
void BTreeNode<T>::insertNonFull(T k) {
    int indx = n-1;
    if(isleaf==true){
        while(indx>=0 && keys[indx]>k){
            keys[indx+1]=keys[indx];
            indx--;
        }
        keys[indx+1]=k;
        n++;
    }
    else{
        while(indx>=0 && keys[indx]>k){
            indx--;
        }
        if(ptrz[indx+1]->n == (2*deg-1)){
            split(indx+1,ptrz[indx+1]);
            if(keys[indx+1]<k)
                indx++;
        }
        ptrz[indx+1]->insertNonFull(k);
    }
}

//////////////////////////////////////////////////////////////////
struct path{
    int row;
    int col;
    int num;
    int dif;
    vector<path> ways;
    path(int a,int b): row(a) , col(b)
    {}
};

bool check_eq(path a, path b){
    if(a.row==b.row && b.col==a.col)
        return true;
    return false;
}

int getNum(vector<path> vec, path a){
    for(int i=0;i<vec.size();i++)
        if (check_eq(vec[i], a))
            return vec[i].num;
    return -1;
}

class Maze{
    private:
        int m,n,V;
        int **maze;
        int **graph;
        vector<path> roads;
        vector<int> sol;/// Correct path of the maze
    public:
        Maze(int ,int );
        void printMaze();
        void makeMaze();
        void maze2graph();
        void print(int ,int, int ** );
        int minDist(int *, BTree<int> );
        void dijkstra(int );
        void findPath(int *,int );
        int findEndVnum();
        void solveMaze();
};

Maze::Maze(int a, int b) {
    m = a;
    n = b;
    maze = new int*[m];
    for(int i=0;i<m;i++)
        maze[i]=new int[n];
}

int Maze::findEndVnum() {
    int indx;
    for(int i=0; i<n; i++){
        if(maze[m-1][i]!=0)
            indx = i;
    }
    path p(m-1,indx);
    for(int i=0; i<roads.size(); i++) {
        if (check_eq(p, roads[i])) {
            return roads[i].num;
        }
    }
}

void Maze::printMaze() {
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            cout<<maze[i][j]<<' ';
        cout<<endl;
    }
}

void Maze::makeMaze() {
    int **t;
    t = new int*[m];
    for(int i=0;i<m;i++)
        t[i]=new int[n];
    for(int i=0;i<m;i++) {
        for (int j = 0; j < n; j++) {
            cin>>t[i][j];
        }
        maze[i]=t[i];
    }
}

void Maze::maze2graph() {
    int v = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(maze[i][j]!=0){
                path a(i,j);
                a.dif = maze[i][j];
                a.num = v;
                if(j+1<n && maze[i][j+1]!=0){
                    path t(i,j+1);
                    t.dif = maze[i][j+1];
                    a.ways.push_back(t);
                }
                if(i+1<m && maze[i+1][j]!=0){
                    path t(i+1,j);
                    t.dif = maze[i+1][j];
                    a.ways.push_back(t);
                }
                if(j-1>=0 && maze[i][j-1]!=0){
                    path t(i,j-1);
                    t.dif = maze[i][j-1];
                    a.ways.push_back(t);
                }
                if(i-1>=0 && maze[i-1][j]!=0){
                    path t(i-1,j);
                    t.dif = maze[i-1][j];
                    a.ways.push_back(t);
                }
                roads.push_back(a);
                v++;
            }
        }
    }
    int k = v;
    graph = new int*[k];
    for(int i=0; i<k; i++)
        graph[i] = new int[k];
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            graph[i][j] = 0;
    for(int i=0; i<roads.size(); i++){
        for(int j=0; j<roads[i].ways.size(); j++){
            int num0=roads[i].num;
            int num1=getNum(roads,roads[i].ways[j]);
            int dif0=roads[i].dif;
            int dif1=roads[i].ways[j].dif;
            graph[num0][num1]=dif0+dif1;
        }
    }
    V = k;
}

void Maze::print(int a, int b, int **arr) {
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
            cout<<arr[i][j]<<' ';
        }
        cout<<endl;
    }
}

int Maze::minDist(int *dist, BTree<int> bt) {
    int min = INT_MAX;
    int min_index;
    for(int i=0; i<V; i++)
        if(bt.search(i)==NULL && dist[i]<=min)
            min = dist[i], min_index=i;
    return min_index;
}

void Maze::findPath(int *parent,int end) {
    if(parent[end]==-1)
        return;
    sol.push_back(end);
    findPath(parent,parent[end]);
}

void Maze::dijkstra(int src) {
    int *dist = new int[V];
    int *parent = new int[V];
    BTree<int> sptset(3);         
                  // using B-Tree to store visited vertex
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[0] = -1;
    }
    dist[src] = 0;
    for(int c=0; c<V-1; c++){
        int u = minDist(dist,sptset);
        sptset.insert(u);
        for(int v=0; v<V; v++)
            if(sptset.search(v)==NULL && graph[u][v] && dist[u]!=INT_MAX && dist[u]+graph[u][v]<dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }
    int e = findEndVnum();
    sol.push_back(0);
    findPath(parent,e);
    solveMaze();
}

void Maze::solveMaze() {
    for(int i=0; i<sol.size(); i++){
        for(int j=0; j<roads.size(); j++){
            if(sol[i]==roads[j].num){
                maze[roads[j].row][roads[j].col]=-1;
            }
        }
    }
    printMaze();
}

int main() {
    int m,n;
    cin>>m>>n;
    Maze maze(m,n);
    maze.makeMaze();
    //maze.printMaze();
    cout<<endl;
    maze.maze2graph();
    maze.dijkstra(0);
    return 0;
}