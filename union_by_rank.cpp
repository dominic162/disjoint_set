/*
    Disjoint set union by rank and path compression;
*/

#include<iostream>
using namespace std;

class Disjoint_set{
    private:
        int V;
        int * par;
        int * rank;
    
    public:

        int find_rep(int x){
            while(par[x] != x){
                x = par[x];
            }
            return x;
        }

        //Path compression
        int find_rep_eff(int x){

            if(par[x] == x){
                return x;
            }

            par[x] = find_rep_eff(par[x]);

            return par[x];

        }

        bool is_connected(int x , int y){
            int x_rep = find_rep_eff(x);
            int y_rep = find_rep_eff(y);

            return x_rep == y_rep;
        }

        //Union by rank it do union efficiently
        void do_union(int x , int y){

            int x_rep = find_rep_eff(x);
            int y_rep = find_rep_eff(y);

            if(x_rep == y_rep){
                return ;
            }

            if(rank[x_rep] > rank[y_rep]){
                par[y_rep] = x_rep;
            }
            else{
                if(rank[x_rep] < rank[y_rep]){
                    par[x_rep] = y_rep;
                }
                else{
                    par[x_rep] = y_rep;
                    rank[y_rep]++;
                }
            }
            return ;
        }

        Disjoint_set(int v):V(v){
            par  = new int [V];
            rank = new int [V];
            for(int i = 0 ; i < V ; ++i){
                par[i]  = i;
                rank[i] = 0;
            }
        }

        ~Disjoint_set(){
            delete []par;
            delete []rank;
        }

};

int main(){

    int v;
    cout<<"Enter no of vertices: ";
    cin>>v;

    Disjoint_set ds(v);
    
    char ch;
    do{

        cout<<"Enter 1 for checking if 2 vertices are in same set\n2 for union\n3 for exit\n";
        cin>>ch;

        if(ch != '3'){
            int v1,v2;
            cout<<"Enter 2 vertices: ";
            cin>>v1>>v2;
            if(ch == '1'){
                if(ds.is_connected(v1,v2)){
                    cout<<"In same set\n";
                }
                else{
                    cout<<"Not in same set\n";
                }
            }
            else{
                if(ch == '2'){
                    ds.do_union(v1,v2);
                }
                else{
                    cout<<"Invalid choice\n";
                }
            }
        }


    }while(ch != '3');

    return 0;
}