#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
using namespace std;

int dx[] = {+1,+1,+2,+2,-1,-1,-2,-2};
int dy[] = {+2,-2,+1,-1,+2,-2,+1,-1};
int totaldis[11][11];///every cell's distance for every knight
int visitedknight[11][11];///counting for how much knight visit every cell
void bfs(pair<int,int> source,int row, int col, int nodeValue)
{
    //cout<<source.second<<endl;
    int dis[row][col];
    int vis[row][col];
    memset(vis,-1,sizeof(vis));
    memset(dis,0,sizeof(dis));
    queue<pair<int,int> >Q ;
    Q.push(source);
    vis[source.first][source.second] = 0 ;
    dis[source.first][source.second] = 0;
    visitedknight[source.first][source.second]++;
    totaldis[source.first][source.second] = totaldis[source.first][source.second]+0;
    while(!Q.empty())
    {
        pair<int,int >top;
        top = Q.front();
        Q.pop();
        for(int i=0; i<8; i++ )
        {
            int x = top.first + dx[i] ;
            int y = top.second + dy[i] ;
            if(x>=0 and x < row and y>=0 and y < col and vis[x][y] == -1)
            {
                int dist = dis[top.first][top.second] + 1;
                if(dist % nodeValue == 0)///every cell distance by every knight jump wise
                {
                    totaldis[x][y] =totaldis[x][y]+ (dist/nodeValue) ;
                }
                else
                    totaldis[x][y] =totaldis[x][y]+ (dist/nodeValue)+1;
                vis[x][y] = 0;
                dis[x][y] = dist;
                visitedknight[x][y]++;
                Q.push(make_pair(x,y));
            }

        }
    }
}
int main()
{
    int t,Case = 0;
    cin>>t;
    while(t--)
    {
        Case++;
        int row,col,res = INT_MAX;
        vector< vector<int> >vc;
        cin>>row>>col;
        int matrix[row][col];
        memset(totaldis,0,sizeof(totaldis));
        memset(visitedknight,0,sizeof(visitedknight));
        for(int i=0; i<row; i++)
        {
            string s;
            cin>>s;
            for(int j=0; j<col; j++)
            {
                vector<int> tmp;
                matrix[i][j] = s[j] - '0';
                if(matrix[i][j]> 0 and matrix[i][j]<=9)
                {
                    tmp.push_back(i);
                    tmp.push_back(j);
                    tmp.push_back(matrix[i][j]);
                    vc.push_back(tmp);
                }
                tmp.clear();
            }
        }
        for(int i=0; i<vc.size(); i++ )
        {
            //cout<<vc[i][0]<<" "<<vc[i][1]<<" "<<vc[i][2]<<endl;
            pair<int,int> k;
            k = make_pair(vc[i][0],vc[i][1]);
            bfs(k,row,col,vc[i][2]);
        }

        bool ch = false;
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(visitedknight[i][j]>= vc.size() and visitedknight[i][j]<=res)
                {
                    ch = true;
                    res =min(totaldis[i][j],res);
                }
                //   cout<<visitedknight[i][j]<<" ";
            }

            // cout<<endl;
        }
        if(ch)
            cout<<"Case "<<Case<<": "<<res<<endl;
        else
            cout<<"Case "<<Case<<": "<<-1<<endl;
    }

}
