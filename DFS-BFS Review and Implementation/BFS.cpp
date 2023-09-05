#include <bits/stdc++.h>
using namespace std;

class Graph{
public:
    Graph(int);
    void readgraph();
    bool BFS(int,int,int*);
    int *find_shortest_path(int,int);
private:
    int *push(int *,int);
    int **G;
    int n;
};

int main(){
    int n,beg,end;
    int *path;
    cout<<"Enter size of graph:";
    cin>>n;

    Graph mygraph(n);
    mygraph.readgraph();

    cout<<"Enter begin and end:";
    cin>>beg>>end;
    path=mygraph.find_shortest_path(beg,end);

    //view result
    if(path[1]==-1){
        cout<<"no path found :(";
        return 0;
    }
    cout<<"the path is:";
    for(int i=n-1;i>=0;i--){
        if(path[i]!=-1) cout<<path[i]<<" ";
    }
    return 0;
}

Graph :: Graph(int n1){
    n=n1;
    G=new int *[n];
    for(int i=0;i<n;i++)
        G[i]=new int [n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            G[i][j]=0;
}

void Graph :: readgraph(){
    int p,q;
    while(true){
        cout<<"Enter 2 connected vertex or -1 -1 to finish:";
        cin>>p>>q;
        if(p==-1 || q==-1) break;
        G[p][q]=1;G[q][p]=1;
    }
}

int *Graph :: find_shortest_path(int beg,int end){
    int *re=new int [n];
    int father[n];
    for(int i=0;i<n;i++){
        re[i]=-1;
        father[i]=-1;
    }
    if(BFS(beg,end,father)){
        int v=end,i=0;
        while(v!=-1){
            re[i]=v;
            v=father[v];
            i++;
        }
    }
    return re;
}

bool Graph :: BFS(int beg,int end,int father[]){
    int *que=new int [n];
    int *visited=new int [n];
    for(int i=0;i<n;i++){
        que[i]=-1;
        visited[i]=0;
    }
    que[0]=beg;
    visited[beg]=1;
    for(int i=0;i<n;i++){
        if(que[i]==-1) return false;
        for(int j=0;j<n;j++){
            if(G[que[i]][j]==1 && visited[j]==0){
                que=push(que,j);
                visited[j]=1;
                father[j]=que[i];
                if(j==end) return true;
            }
        }
    }
    return false;
}

int * Graph :: push(int *q,int a){
    for(int i=0;i<n;i++){
        if(q[i]==-1){
            q[i]=a;
            return q;
        }
    }
}
