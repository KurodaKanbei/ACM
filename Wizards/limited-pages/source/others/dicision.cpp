 #include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 9000000000000000000LL
#define mp make_pair
#define pa pair<ll,int>
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,K;
ll a[100005],sum[100005],f[100005],g[100005];
struct data{
    int l,r,p;
}q[100005];
ll cal(int i,int j)
{
    return g[i]+(sum[j]-sum[i])*sum[i];
}
int find(data t,int q)
{
    int l=t.l,r=t.r,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(cal(q,mid)>cal(t.p,mid))r=mid-1;
        else l=mid+1;
    }
    return l;
}
void tran(int x)
{
    int head=1,tail=0;
    q[++tail]=(data){0,n,x-1};
    for(int i=x;i<=n;i++)
    {
        if(i>q[head].r)head++;
        f[i]=cal(q[head].p,i);
        if(tail<head||cal(i,n)>cal(q[tail].p,n))
        {
            while(head<=tail&&cal(i,q[tail].l)>cal(q[tail].p,q[tail].l))
                tail--;
            if(head<=tail)
            {
                int t=find(q[tail],i);
                q[tail].r=t-1;
                q[++tail]=(data){t,n,i};
            }
            else q[++tail]=(data){i,n,i};
        }
    }
    for(int i=x;i<=n;i++)swap(f[i],g[i]);
}
void dp()
{
    for(int i=1;i<=K;i++)
        tran(i);
    printf("%lld\n",g[n]);
}
int main()
{
    n=read();K=read();
    for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i];
    dp();
    return 0;
}
