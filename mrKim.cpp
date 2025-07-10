#include<iostream>
using namespace std;

int visited[11]={0};

// ✅ GOOD: Properly resetting the visited array
void init(){
    for(int i=0;i<11;i++){
        visited[i]=0;
    }
}

struct coord{
    int x,y;
    coord(int x,int y): x(x),y(y){}  // ✅ GOOD: Parameterized constructor
    coord(): x(0),y(0){}             // ✅ GOOD: Default constructor
};

int dfs(int i,int c,int n,coord vertices[]){
    if(c==n){
        // ✅ CORRECT: Return distance from current to home
        return abs(vertices[i].x-vertices[1].x)+abs(vertices[i].y-vertices[1].y);
    }

    int minAns=1e9;
    // ❌ MISTAKE #1: Loop should go till j < n+2, not n
    // ✅ FIXED: for(int j=2; j<n+2; j++) — because vertices[2] to vertices[n+1] are customers
    for(int j=2;j<n+2;j++){
        if(!visited[j]){
            visited[j]=1;

            // ❌ MISTAKE #2: Using i instead of j for dfs() leads to wrong traversal
            // ✅ FIXED: dfs(j, ...) ensures we move to the next customer correctly
            int cost=dfs(j,c+1,n,vertices)+abs(vertices[j].x-vertices[i].x)+abs(vertices[j].y-vertices[i].y);
            
            minAns=min(cost,minAns);
            visited[j]=0;
        }
    }
    return minAns;
}

int main(){
    for(int t=0;t<10;t++){
        int n;
        cin>>n;
        coord vertices[n+2]; // ✅ GOOD: Storing office, home, and customers

        for(int i=0;i<n+2;i++){
            int x1,y1;
            cin>>x1>>y1;
            vertices[i].x=x1;
            vertices[i].y=y1;
        }

        init();
        visited[0]=1; // ✅ CORRECT: Starting at office

        // ❌ MISTAKE #3: dfs(0,0,n,...) will be fine only if office is at index 0
        // ✅ GOOD: Office is at index 0, Home at index 1 by assumption in problem

        int ans1 = dfs(0,0,n,vertices);

        // ✅ GOOD: Output formatting
        cout<<"# "<<t<<" "<<ans1<<endl;
    }
    return 0;
}

/*

Try every unvisited customer i:

Mark it as visited.

Compute distance from current position to that customer.

Recursively solve for remaining customers.

After recursion, unmark the customer (backtrack).

Track the minimum total path length using ans = min(...).
*/