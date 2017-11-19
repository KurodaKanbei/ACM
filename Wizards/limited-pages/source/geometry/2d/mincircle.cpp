#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const double eps=1e-6;
struct couple
{
	double x, y;
	couple(){}
	couple(const double &xx, const double &yy)
	{
		x = xx; y = yy;
	}
} a[100001];
int n;
bool operator < (const couple & a, const couple & b)
{
	return a.x < b.x - eps or (abs(a.x - b.x) < eps and a.y < b.y - eps);
}
bool operator == (const couple & a, const couple & b)
{
	return !(a < b) and !(b < a);
}
inline couple operator - (const couple &a, const couple &b)
{	
	return couple(a.x-b.x, a.y-b.y);
}
inline couple operator + (const couple &a, const couple &b)
{
	return couple(a.x+b.x, a.y+b.y);
}
inline couple operator * (const couple &a, const double &b)
{
	return couple(a.x*b, a.y*b);
}
inline couple operator / (const couple &a, const double &b)
{
	return a*(1/b);
}
inline double operator * (const couple &a, const couple &b)
{
	return a.x*b.y-a.y*b.x;
}
inline double len(const couple &a)
{
	return a.x*a.x+a.y*a.y;
}
inline double di2(const couple &a, const couple &b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
inline double dis(const couple &a, const couple &b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct circle
{
	double r; couple c;
} cir;
inline bool inside(const couple & x)
{
	return di2(x, cir.c) < cir.r*cir.r+eps;
}
inline void p2c(int x, int y)
{
	cir.c.x = (a[x].x+a[y].x)/2;
	cir.c.y = (a[x].y+a[y].y)/2;
	cir.r = dis(cir.c, a[x]);
}
inline void p3c(int i, int j, int k)
{
	couple x = a[i], y = a[j], z = a[k];
	cir.r = sqrt(di2(x,y)*di2(y,z)*di2(z,x))/fabs(x*y+y*z+z*x)/2;
	couple t1((x-y).x, (y-z).x), t2((x-y).y, (y-z).y), t3((len(x)-len(y))/2, (len(y)-len(z))/2);
	cir.c = couple(t3*t2, t1*t3)/(t1*t2);
}
inline circle mi()
{
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	if(n == 1)
	{
		cir.c = a[1];
		cir.r = 0;
		return cir;
	}
	random_shuffle(a + 1, a + 1 + n);
	p2c(1, 2);
	for(int i = 3; i <= n; i++)
		if(!inside(a[i]))
		{
			p2c(1, i);
			for(int j = 2; j < i; j++)
				if(!inside(a[j]))
				{
					p2c(i, j);
					for(int k = 1; k < j; k++)
						if(!inside(a[k]))
							p3c(i,j, k);
				}
		}
	return cir;
}
