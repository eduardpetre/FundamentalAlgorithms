#include<bits/stdc++.h>

using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

int n, intrebari, parinte[100001], rang[100001], tip, a, b;

int find1(int node){    //aflam multimea in care se afla elementul "node"
    if(parinte[node]==node)
        return node;
    return parinte[node]=find1(parinte[node]);
}

void union1(int x, int y){
    //unesc multimea cu rang mai mic de cea cu rang mai mare (le schimb parintii)

    if(rang[x]>rang[y])
        parinte[y]=x, rang[x]+=rang[y];
    else
        parinte[x]=y, rang[y]+=rang[x];
}

int main(){
    fin >> n >> intrebari;

    for(int i=1; i<=n; i++)
        parinte[i]=i, rang[i]=1;

	while(intrebari--){

        fin>>tip>>a>>b;

        if(tip==1)
            //find returneaza multimea in care se afla a si b, iar union va uni cele doua multimi
            union1(find1(a), find1(b));
        else
        {
            if(find1(a)==find1(b))
                fout << "DA\n";
            else
                fout << "NU\n";
        }
    }
    return 0;
}
