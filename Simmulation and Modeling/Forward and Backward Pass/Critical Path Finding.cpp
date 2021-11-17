#include<bits/stdc++.h>
#define MX 1005
using namespace std;

int arr[MX][4];
double cost[MX][5], node_t[MX][4];

int main()
{
    freopen("critical_path_finding.txt", "r", stdin);

    int n, m;
    cin>>n>>m;
    for(int i = 1; i <= n; i++)
        cin>>arr[i][0]>>arr[i][1]>>arr[i][2]>>cost[i][0];

    // forward pass calculation
    node_t[1][1] = 0;
    for(int i = 1; i <= n; i++)
    {
        cost[i][1] = node_t[arr[i][1]][1]; // est(k) = ent(s(k))
        cost[i][2] = cost[i][1] + cost[i][0]; // eft(k) = est(k) + t(k)
        node_t[arr[i][2]][1] = max(node_t[arr[i][2]][1], cost[i][2]); // ent(n) = max(lft(all activities terminating on node k))
    }

    // backword pass calculation
    for(int i = 0; i <= m ; i++)
    {
        node_t[i][2] = INT_MAX;
    }
    node_t[m][2] = node_t[m][1];

    for(int i = n; i >= 1; i--)
    {
        cost[i][4] = node_t[arr[i][2]][2]; // lft(k) = lnt(k)
        cost[i][3] = cost[i][4] - cost[i][0]; // lst(k) = lft(k) -t(k)
        node_t[arr[i][1]][2] = min(node_t[arr[i][1]][2], cost[i][3]); // lnt(n) = min(lst(all activities terminating on node k))
    }

    //  printing section
    puts("| Activity | S(k) | F(k)  | T(k)  | EST(k)  |  EFT(k) |  LST(k) |  LFT(k)  |");
    puts("............................................................................");
    for(int i = 1; i <= n ; i++)
    {
        printf("| %3d      | %3d  | %3d   | %5.2lf | %6.3lf  | %6.3lf  | %6.3lf  | %6.3lf   |\n",
               arr[i][0],arr[i][1],arr[i][2],cost[i][0],cost[i][1],cost[i][2],cost[i][3],cost[i][4]);
    }
    puts(".............................................................................\n");

    puts("| Nodes | ENT(k) | LNT(k) |  Slack |");
    puts("....................................");
    for(int i = 1; i <= m; i++)
    {
        node_t[i][3] = abs(node_t[i][2] - node_t[i][1]); // calculating slack
        printf("| %3d   | %6.3lf | %6.3lf | %6.3lf |\n",i, node_t[i][1],abs(node_t[i][2]),node_t[i][3]);
    }
    puts("....................................");

    return 0;
}
