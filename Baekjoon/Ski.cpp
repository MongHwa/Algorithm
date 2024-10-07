#include <iostream>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

typedef tuple<int, int, int> ti3;
#define ll long long

int parent[250001];
int stage[501][501];
bool start[501][501];
int val[250001];

int dirx[] = {1, 0};
int diry[] = {0, 1};
vector<int> v[250001];
priority_queue<ti3, vector<ti3>, greater<ti3>> pq;

int find(int x)
{
    if(parent[x] < 0)
        return x;
    parent[x] = find(parent[x]);
    return parent[x];
}

void comb(int a, int b, int d, int t)
{
    a = find(a);
    b = find(b);

    if(a == b)
        return;
    if(v[a].size() < v[b].size())
        swap(a, b);
    
    bool afin = 0, bfin = 0;
    if(v[a].size() >= t)
        afin = 1;
    if(v[b].size() < t && v[a].size()+v[b].size() >= t)
        bfin = 1;
    
    if(!afin && bfin)
        for(int x : v[a])
            val[x] = d;
    for(int x : v[b])
    {
        v[a].push_back(x);
        if(bfin)
            val[x] = d;
    }

    v[b].clear();
    parent[b] = a;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, t;
    cin >> n >> m >> t;

    fill(parent, parent+n*m+1, -1);
    for(int i = 0; i < n*m; i++)
        v[i].push_back(i);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> stage[i][j];
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = 0; k < 2; k++)
            {
                int di = i + dirx[k];
                int dj = j + diry[k];

                if(di < 0 || di >= n || dj < 0 || dj >= m)
                    continue;
                pq.push({abs(stage[i][j]-stage[di][dj]), i*m+j, di*m+dj});
            }

    while(!pq.empty())
    {
        int d, u, v;
        tie(d, u, v) = pq.top(); pq.pop();

        if(find(u) == find(v))
            continue;
        
        comb(u, v, d, t);
    }

    ll ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            bool b;
            cin >> b;

            if(b)
                ans += val[i*m+j];
        }
    
    cout << ans << '\n';
}