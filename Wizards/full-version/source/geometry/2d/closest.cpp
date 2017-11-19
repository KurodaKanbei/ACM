#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double eps = 1e-8;
const int INF = 0x7fffffff;
int n;

struct Point
{
	double x,y;
	Point(double x=0, double y=0):x(x),y(y) {}
	bool operator < (const Point& p) const
	{
		if(x != p.x)	return x < p.x;
		else	return y < p.y;
	}
}p[200000+5],temp[200000+5];

bool cmpy(Point a, Point b)
{
	return a.y < b.y;
}

double Dis(Point a, Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double Closest_Pair(int left, int right)
{
	double d = INF;
	if(left == right)
		return d;
	if(left +1 == right)
		return Dis(p[left],p[right]);
	int mid = (left+right)>>1;
	double d1 = Closest_Pair(left,mid);
	double d2 = Closest_Pair(mid,right);
	d = min(d1,d2);
	int k = 0;
	for(int i = left; i <= right; i++)
	{
		if(fabs(p[mid].x - p[i].x) <= d)
			temp[k++] = p[i];
	}
	sort(temp,temp+k,cmpy);
	for(int i = 0; i < k; i++)
	{
		for(int j = i+1; j < k && temp[j].y - temp[i].y < d; j++)
		{
			double d3 = Dis(temp[i],temp[j]);
			d = min(d,d3);
		}
	}
	return d;
}

int main()
{
	cin>>n;
	for(int i=0; i<n; i++)
	{
		double a,b;
		scanf("%lf%lf",&a,&b);
		p[i] = Point(a,b);
	}
	sort(p,p+n);
	printf("%.3f",Closest_Pair(0,n-1));
}

