#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> cal_next(const string& str)
{
    int n = str.size();

    //next[0] = 0 is set here.
    vector<int> next = vector<int> (n-1, 0);
    int len = 0;

    for(int i = 1; i<n-1;)
    {
        if(len>0)
        {
            if(str[i] == str[len])
            {
                len++;
                next[i] = len;
                i++;
            }
            else
            {
                //next[i-1] == len
                len = next[len - 1];
                if(len<0)
                    len = 0;
            }
        }
        else //len == 0
        {
            if (str[i] == str[0])
            {
                len = 1;
                next[i] = 1;
            }
            else
            {
                len = 0;
                next[i] = 0;
            }
            i++;
        }
    }
    return next;
}

int search(const string& s, const string& pattern)
{
    vector<int> next = cal_next(pattern);
    int ret = -1;
    for(int i = 0, j =0; i<s.size(); )
        {
            if(s[i] == pattern[j])
            {
                i++;j++;
                if(j == pattern.size())
                    return i-j;
            }
            else if(j!=0)
                j = next[j-1];
            else
                i++;
        }
    return ret;
}

int main()
{
    string s = "leetcode";
    string pattern = "leeto";
    vector<int> ret = cal_next(pattern);
    for(int i = 0; i< ret.size(); i++)
        cout<<ret[i];
    cout<<endl;

    cout<<search(s, pattern)<<endl;
    return 0;
}

/*
须呈现：调查问卷、链接与二维码、统计数据列表截图以及调研结果分析
64.5 213 34542 72
57.5 241 31893 119

12100F 散片 555 铭瑄 H-610M 469 华硕H610-E 545 华硕H610-A 608

主板+CPU 12100F+铭瑄H610M 994 备选 12100F+华硕H610A 1174 或者R5 5500 + 华硕A320 M-K 874
内存 金百达 8*2 16G 3200 239
显卡 GTX 970 350
硬盘 自带 0
电源 长城V5金牌全模组500W 309
散热 利民AX120RSE 70

1962 2142 1842



ABCDABCEABCFABC
ABCDABCEABCFABH

KMP算法
匹配失败时的信息再利用
当匹配失败时，我们可以尝试在已匹配部分末端（后缀）找一找是否存在与待查询字符串前端（前缀）相同的部分，如果有 我们可以跳过这个相同的部分继续匹配：

ABACABACABABE
ABACABABE

leetcode
      l
在匹配时，发现B与C无法匹配，但是已经匹配的部分ABACABA里  后缀ABA与前缀ABA相同，所以直接从前缀ABA后C字符开始匹配
ABACABACABABE
         ABACABABE

为什么是从后缀找而不是中间？
假如从中间找一段子串能匹配成功，那么一直到后缀部分也应该完全匹配，那和从后缀开始找是一样的。

现在问题成了如何找到这个最长的后缀

对于一个长度为n的模式字符串，考虑到没有必要分析到最后一个字符（因为这表示已经完全匹配成功了）我们定义一个长度n-1的数组next，表示分别以前n-1个字符结束的子字符串的最长可用后缀。
例如对长度为9的字符串ABACABABE 我们只需要长度为7的数组分别表示ABACABAB结束时的最长可用后缀。

请注意 由于数组和字符串我们是从0开始计下标的
而next[i]表示的是第i+1个字符匹配失败时，前i个字符是匹配成功的，根据next[i]的值x，可以跳过前x个字符的比对。

仍然以ABACABABE为例 我们手动计算一下next数组
next[0] = 0;因为下标1的字符匹配失败时，已匹配的子串为单字符A，单字符没有前后缀一说。
next[1] = 0;因为下标2的字符匹配失败时，已匹配的子串为AB 没有可用后缀。
next[2] = 1;因为下标3的字符匹配失败时，已匹配的子串为ABA 后缀“A”与前缀“A”相同，这说明我们可以跳过1个字符A开始匹配。
next[3] = 0;因为下标4的字符匹配失败时，已匹配的子串为ABAC 没有可用后缀。
next[4] = 1;因为下标5的字符匹配失败时，已匹配的子串为ABACA 后缀“A”与前缀“A”相同，这说明我们可以跳过1个字符A开始匹配。
next[5] = 2;因为下标6的字符匹配失败时，已匹配的子串为ABACAB 后缀“AB”与前缀“AB”相同，这说明我们可以跳过2个字符AB开始匹配。
next[6] = 3;因为下标7的字符匹配失败时，已匹配的子串为ABACABA 后缀“ABA”与前缀“ABA”相同，这说明我们可以跳过3个字符ABA开始匹配。
next[7] = 2;因为下标8的字符匹配失败时，已匹配的子串为ABACABAB 后缀“AB”与前缀“AB”相同，这说明我们可以跳过2个字符AB开始匹配。

考察next[5]的计算，数组前一项next[4] = 1 表明上一个字符是可用后缀的起点，但是不确定当前下标为5的字符能不能加入可用后缀 于是也有两种情况：
case A： 下标为3的字符可以加入可用后缀 这要求 str[5] == str[1] (因为此时str[4] == str[0]，只要保证新加入的字符与前缀对应字符相等即可) 请注意此时比对的前缀下标1 刚好是next[4]的值，如果str[5] == str[1] 那么next[5] = next[4]+1
case B:    str[5] != str[1]此种情况下str[5]不能与str[4]一起组成可用后缀，处理方式之后再分析

类似的可以由str[6] == str[2] 计算出next[6] = next[5] + 1

考察next[7]的计算，此时str[7]!=str[3] 也就是说str[4:7]不能整体作为可用后缀，但是str[4:7]中仍然可能有部分可以作为后缀
而因为next[6] = 3 这说明 str[0:2] == str[4:6] 要从str[4:7]中找可用后缀 就相当于 str[0:2] + str[7]找可用后缀 此时则只需要考察 next[next[7-1] - 1] = next[2] = 1， next[2]指向的下标1 str[1]与 str[7]的关系 此处相等， 所以next[7] = next[2]+1 = 2。 也可以理解为用str[7]代替str[3]再求next[3]。
不难看出这里实际上是一个递归的过程，递归的去更短的字符串里找前缀，直到找到一个相等的下标y next[i] = next[y-1] + 1 或者直到与下标0比较 str[i] == str[0] next[i] = 1  str[i] != str[0] next[i] = 0       
 */