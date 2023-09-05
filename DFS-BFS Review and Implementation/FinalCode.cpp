#include <bits/stdc++.h>
using namespace std;

int **edges;

class Graph{
public:
    Graph(int);
    vector<string> find_all_path(int,int,int*);
    void readgraph(int);
private:
    int **G;
    int n;
};

int* copyarr(int *,int *,int);
string str(int);
int numer(string);
bool check_edge(int,int,string);
int path_dlt(string,string,int);
int max_of_dlt(vector<string>,vector<string>,int);
int counter(string,char);

int main(){
    int n,q;
    cin>>n>>q;

    Graph mygraph(n);
    mygraph.readgraph(q);

    int s1,t1,l1;
    cin>>s1>>t1>>l1;
    int s2,t2,l2;
    cin>>s2>>t2>>l2;
    s1--;s2--;t1--;t2--;

    int *visited=new int [n];
    for(int i=0;i<n;i++) visited[i]=0;
    vector<string> result1;
    result1=mygraph.find_all_path(s1,t1,visited);

    vector<string> result2;
    for(int i=0;i<n;i++) visited[i]=0;
    result2=mygraph.find_all_path(s2,t2,visited);

    //edit results & check is they satisfy the condition l1 & l2.
    for(int i=0;i<result1.size();i++){
        if(result1[i][0]=='-')
            result1[i]=str(s1)+result1[i];

        if(counter(result1[i],'-')>l1)
            result1.erase(result1.begin()+i);
    }
    for(int i=0;i<result2.size();i++){
        if(result2[i][0]=='-')
            result2[i]=str(s2)+result2[i];

        if(counter(result2[i],'-')>l2)
            result2.erase(result2.begin()+i);
    }

    if(result1.empty() || result2.empty()) cout<<-1;
    else cout<<max_of_dlt(result1,result2,q);
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

void Graph :: readgraph(int y){
    edges=new int *[y];
    int p,q;
    for(int i=0;i<y;i++){
        cin>>p>>q;
        p--;q--;
        edges[i]=new int [2];
        edges[i][0]=p;edges[i][1]=q;
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

int numer(string s){
    int re=0;
    string dict="0123456789";
    for(int i=0;i<s.size();i++){
        for(int j=0;j<10;j++){
            if(dict[j]==s[i]) re=re*10 + j;
        }
    }
    return re;
}

int max_of_dlt(vector<string> a,vector<string> b,int q){
    int maximum=0;
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            if(path_dlt(a[i],b[j],q)>maximum) maximum=path_dlt(a[i],b[j],q);
        }
    }
    return maximum;
}

int path_dlt(string path1,string path2,int q){
    int re=0;
    for(int i=0;i<q;i++){
        if(check_edge(edges[i][0],edges[i][1],path1) && check_edge(edges[i][0],edges[i][1],path2))
            re++;
    }
    return re;
}

bool check_edge(int a,int b,string path){//check if ab not in path,return true.
    int i=0;
    string strnum1="",strnum2="";
    while(path[i]!='-'){
        strnum1+=path[i];
        i++;
    }
    i++;
    while(i<path.size()){
        strnum2="";
        while(path[i]!='-'){
            strnum2+=path[i];
            i++;
            if(i==path.size()) break;
        }
        i++;
        if((a==numer(strnum1) && b==numer(strnum2)) || (b==numer(strnum1) && a==numer(strnum2)))
            return false;
        strnum1=strnum2;
    }
    return true;
}

int counter(string s,char a){
    int c=0;
    for(int i=0;i<s.size();i++){
        if(s[i]==a) c++;
    }
    return c;
}
