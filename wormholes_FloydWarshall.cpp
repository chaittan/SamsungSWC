#include <iostream>

using namespace std;

struct node
{
    int x, y;
    node(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

int abs(int x)
{
    return (x <= 0) ? -1 * x : x;
}

int distance(node *n1, node *n2)
{
    return abs((n1->x) - (n2->x)) + abs(n1->y - n2->y);
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n;
        cin>>n;
        struct node *arr[2 * n + 2];
        int cost[2 * n + 2][2 * n + 2];
        for (int i = 0; i < 2 * n + 2; i++)
        {
            for (int j = 0; j < 2 * n + 2; j++)
            {
                cost[i][j] = -1;
            }
        }
        int sx, sy, tx, ty;
        cin >> sx >> sy >> tx >> ty;
        arr[0] = new node(sx, sy);
        arr[2 * n + 1] = new node(tx, ty);

        for (int i = 0; i < n; i++)
        {
            int sx, sy, tx, ty, value;
            cin >> sx >> sy >> tx >> ty >> value;
            arr[2 * i + 1] = new node(sx, sy);
            arr[2 * i + 2] = new node(tx, ty);
            cost[2 * i + 1][2 * i + 2] = value;
            cost[2 * i + 2][2 * i + 1] = value;
        }

        for (int i = 0; i < 2 * n + 2; i++)
        {
            for (int j = 0; j < 2 * n + 2; j++)
            {
                if (cost[i][j] == -1)
                {
                    cost[i][j] = distance(arr[i], arr[j]);
                }
            }
        }

        for (int k = 0; k < 2 * n + 2; k++)
        {
            for (int i = 0; i < 2 * n + 2; i++)
            {
                for (int j = 0; j < 2 * n + 2; j++)
                {
                    if (i == j || j == k || i == k) continue;

                    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
                }
            }
        }

        cout << cost[0][2 * n + 1] << endl;
    }
    return 0;
}