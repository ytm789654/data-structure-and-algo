#include <iostream>
#include <string>

using namespace std;

int cal_edit_dis(string a, string b)
{
    int dis[100][100];
    dis[0][0] = 0;
    int la = a.size();
    int lb = b.size();
    for(int i = 1; i<la; i++)
        dis[i][0] = i;

    for(int i = 1; i<lb; i++)
        dis[0][i] = i;
    
    for(int i = 1; i<= la; i++)
        for(int j = 1; j<= lb; j++)
            if(a[i-1] == b[j-1])
                dis[i][j] = dis[i-1][j-1];
            else
                dis[i][j] = min(dis[i-1][j], dis[i][j-1]) + 1;
    return dis[la][lb];
}

int main()
{
    string a = "abcdef";
    string b = "abcdfe";
    cout<<cal_edit_dis(a, b)<<endl;
    return 0;
}