#include <iostream>

using namespace std;

void quick_sort(int *a, int left, int right)
{
    int l = left;
    int r = right;
    int pivot = a[l];
    if(r<=l)
        return ;
    while(l<r)
    {
        while(l<r && a[r]<=pivot)
            r--;
        if(l<r)
            a[l] = a[r];
        while(l<r && a[l]>=pivot)
            l++;
        if(l<r)
            a[r] = a[l];
    }
    a[l] = pivot;
    quick_sort(a, left, l-1);
    quick_sort(a, l+1, right);
}

int main()
{
    int a[9] = {9, 5,4,1,6,8,0,3,1};
    quick_sort(a,0,8);
    for(int i =0;i<9;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}