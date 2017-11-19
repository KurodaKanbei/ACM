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
ll sum[100005],f[100005],g[100005];
int a[100005],q[100005];
double cal(int j,int k)
{
	return (double)(sum[k]*sum[k]-sum[j]*sum[j]+g[j]-g[k])/(double)(sum[k]-sum[j]);
}
void tran(int x)
{
	int head=1,tail=0;
	for(int i=x;i<=n;i++)
	{
		while(head<tail&&cal(q[tail-1],q[tail])>cal(q[tail],i-1))tail--;
		q[++tail]=i-1;
	    while(head<tail&&cal(q[head],q[head+1])<sum[i])head++;
		int t=q[head];
		f[i]=g[t]+(sum[i]-sum[t])*sum[t];
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
	for(int i=1;i<=n;i++)a[i]=read();
	int top=0;
	for(int i=1;i<=n;i++)if(a[i]!=0)a[++top]=a[i];
	n=top;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i];
	dp();
	return 0;
}
