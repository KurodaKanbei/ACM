#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef double type_p;
const double eps = 1e-6;
const int maxn = 510;
double dp[maxn][maxn];
inline double eq(double x, double y)
{
    return fabs(x-y)<eps;
}
inline int eq(int x, int y)
{
    return x==y;
}
struct point
{
    type_p x,y;
};
type_p xmult(point a, point b, point o)
{
    return (a.x-o.x)*(o.y-b.y)-(a.y-o.y)*(o.x-b.x);//b at ao left if negative, at right if positive
}
type_p dist(point a, point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
point o;
bool cmp_angle(point a,point b)
{
    if(eq(xmult(a,b,o),0.0))
    {
        return dist(a,o)<dist(b,o);
    }
    return xmult(a,o,b)>0;
}
/*
Input:  p:  Point set
        pn: size of the point set

Output: the area of the largest empty convex
*/
double empty_convex(point *p, int pn)
{
    double ans=0;
    for(int i=0; i<pn; i++)
    {
        for(int j=0; j<pn; j++)
        {
            dp[i][j]=0;
        }
    }

    for(int i=0; i<pn; i++)
    {
        int j = i-1;
        while(j>=0 && eq(xmult(p[i], p[j], o),0.0))j--;//coline

        bool flag= j==i-1;

        while(j>=0)
        {
            int k = j-1;
            while(k >= 0 && xmult(p[i],p[k],p[j])>0)k--;
            double area = fabs(xmult(p[i],p[j],o))/2;
            if(k >= 0)area+=dp[j][k];
            if(flag) dp[i][j]=area;
            ans=max(ans,area);
            j=k;
        }
        if(flag)
        {
            for(int j=1; j<i; j++)
            {
                dp[i][j] = max(dp[i][j],dp[i][j-1]);
            }
        }
    }
    return ans;
}
double largest_empty_convex(point *p, int pn)
{
    point data[maxn];
    double ans=0;
    for(int i=0; i<pn; i++)
    {
        o=p[i];
        int dn=0;
        for(int j=0; j<pn; j++)
        {
            if(p[j].y>o.y||(p[j].y==o.y&&p[j].x>=o.x))
            {
                data[dn++]=p[j];
            }
        }
        sort(data, data+dn, cmp_angle);
        ans=max(ans, empty_convex(data, dn));
    }
    return ans;
}
int main()
{
    point p[110];
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int pn;
        scanf("%d",&pn);
        for(int i=0; i<pn; i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
        printf("%.1f\n",largest_empty_convex(p,pn));
    }
    return 0;
}
