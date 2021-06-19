/*
    Indian Team Undergo Three-Day Hard Quarantine in Satthatum. There are some Quarantine Centers in the Satthatum. Quarantine Center are undirected acyclic graphs with N rooms and N-1 paths connecting them, where N is some integer. Note that a Quarantine Center can also have a single room.

There is exactly one Player living in each room of a quarantine centre. The players have unique ids from 1 to N.

For each player with id i, we know the id of players living in most distant rooms from ith player’s room in the same Quarantine Centre. If there are several such distant players, we only know the value of the one with smallest id among those.

You have to tell the total number of Quarantine Centres in Satthatum.

Input Format
The first line contains single integer n (1 ≤ n ≤ 10^4) — the number of palyer Quarantine Centers in the Satthatum.

The second line contains a sequence I1, I2, …, In of length n, where (1 ≤ Ii ≤ n) holds and Ii denotes the id of player living in most distant room from Player i living on the same Quarantine Centre. I If there are several such distant players living on the Quarantine Centre, Ii is the smallest id among those.

Constraints
1 ≤ n ≤ 10^4

Output Format
You have to tell the total number of Quarantine Centres in Satthatum.

Sample Input
5
2 1 5 3 3
Sample Output
2
Explanation
sample testcase, Quarantine Center is: 1-2.
3-4-5.
*/

#include<iostream>
#include<unordered_set>
using namespace std;

int find_rep(int * par , int x){
    if(par[x] == x){
        return x;
    }

    par[x] = find_rep(par , par[x]);
    return par[x];
}

int get_ans( int * arr ,int n ){

    int * par  = new int [n];
    int * rank = new int [n];
    for(int i = 0 ; i < n ; ++i){
        par[i] = i;
        rank[i] = 0;
    }

    for(int i = 0 ; i < n ; ++i){

        int x_r = find_rep(par , i);
        int y_r = find_rep(par , arr[i] - 1);

        if(x_r != y_r){

            if(rank[x_r] > rank[y_r]){

                par[y_r] = x_r;

            }
            else{
                par[x_r] = y_r;
                if(rank[x_r] == rank[y_r]){
                    rank[y_r]++;
                }
            }

        }
    }

    int ans = 0;
    unordered_set<int> st;

    for(int i = 0 ; i < n ; ++i){
        int x_r = find_rep(par , i);
        if(st.find(x_r) == st.end()){
            ans++;
            st.insert(x_r);
        }
    }

    delete []par;
    delete []rank;
    
    return ans;

}

int main(){

    int n;
    cin>>n;

    int * arr = new int [n];
    for(int i = 0 ; i < n ; ++i){
        cin>>arr[i];
    }

    int ans = get_ans(arr , n);
    cout<<ans;
    delete []arr;

    return 0;
}