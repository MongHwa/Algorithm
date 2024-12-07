#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> val[15];
int dp[2005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for(int i = 0; i < n; i++)
    {
        int c, g;
        cin >> c >> g;

        val[g].push_back(c);
    }

    for(int i = 1; i <= 10; i++)
    {
        sort(val[i].begin(), val[i].end(), greater<>());
        for(int j = 1; j < (int)val[i].size(); j++)
            val[i][j] += (val[i][j-1] + j*2);
    }

    fill(dp+1, dp+k+1, -1);

    for(int i = 1; i <= 10; i++)
        for(int x = k; x >= 0; x--)
            for(int j = 0; j < (int)val[i].size(); j++)
            {
                if(x-j-1 < 0)
                    break;
                if(dp[x-j-1] >= 0)
                    dp[x] = max(dp[x], dp[x-j-1] + val[i][j]);
            }
    
    cout << dp[k] << '\n';
}