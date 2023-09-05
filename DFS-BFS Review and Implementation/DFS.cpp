#include <bits/stdc++.h>
using namespace std;

class Graph{
public:
    Graph(int);
    vector<string> find_all_path(int,int,int*);
    void readgraph();
private:
    int **G;
    int n;
};

int* copyarr(int *,int *,int);
string str(int);

int main(){
    int n;
    cout<<"Enter size of graph:";
    cin>>n;
    Graph mygraph(n);
    mygraph.readgraph();

    int beg,end;
    cout<<"Enter begin and end of path:";
    cin>>beg>>end;

    int *visited=new int [n];
    for(int i=0;i<n;i++)
        visited[i]=0;
    vector<string> result;

    result=mygraph.find_all_path(beg,end,visited);

    cout<<"the paths are:\n";
    for(int i=0;i<result.size();i++){
        cout<<beg<<result[i]<<endl;
    }
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

vector<string> Graph :: find_all_path(int beg,int end,int *visited){
    vector<string> result;
    if(beg==end){
        result.push_back(str(end));
        return result;
    }
    visited[beg]=1;
    vector<string> re;
    for(int i=0;i<n;i++){
        if(G[beg][i]==1 && visited[i]==0){
            int *copy_visited=new int [n];
            copy_visited=copyarr(copy_visited,visited,n);
            re=find_all_path(i,end,visited);
            visited=copy_visited;
            delete copy_visited;

            for(int j=0;j<re.size();j++){
                result.push_back(str(beg)+"-"+re[j]);
            }
        }
    }
    return result;
}

int* copyarr(int *a,int *b,int n){
    for(int i=0;i<n;i++)
        a[i]=b[i];
    return a;
}

string str(int a){
    string dict="0123456789",re="";
    while(a!=0){
        re=dict[a%10] + re;
        a=a/10;
    }
    return re;
}
