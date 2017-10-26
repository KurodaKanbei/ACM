#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct couple
{
	double x, y;
	couple(){}
	couple(const double & _x, const double & _y) : x(_x), y(_y) {} 
	void scan() {scanf("%lf%lf", &x, &y); }
} cp1, cp2, x, y;
double operator * (const couple & a, const couple & b) {return a.x * b.y - a.y * b.x;}
couple operator - (const couple & a, const couple & b) {return couple(a.x - b.x, a.y - b.y);}
couple operator + (const couple & a, const couple & b) {return couple(a.x + b.x, a.y + b.y);}
couple operator * (const double & a, const couple & b) {return couple(a * b.x, a * b.y);}
bool les(const couple & a, const couple & b) {return a.x < b.x or a.x == b.x and a.y < b.y;}
bool mor(const couple & a, const couple & b) {return a.x > b.x or a.x == b.x and a.y > b.y;}
int n, m, mxi, mni, t1, t2, c1, c2, mi;
double eps = 1e-12;
int sign(const double & x) {return x > eps?1:x < -eps?-1:0;}
couple cross(const couple &a, const couple &b, const couple &c, const couple &d)
{
	if(sign((b - a) * (d - c)) == 0) return a;
	double lambda = (c - a) * (d - c) / ((b - a) * (d - c));
	return a + lambda * (b - a);
}
double s[50001];
struct convex_polygon
{
	couple a[50000];
	couple & operator [] (int x) {return a[(x % n + n) % n];}
	int get_max(bool (*cmp)(const couple & a, const couple & b)) {int rtn = 0; for(int i = 1; i < n; i++) if(cmp(a[i], a[rtn])) rtn = i; return rtn;}
} a;
int check(int id)
{
	return (sign((y - x) * (a[id - 1] - a[id]))) * sign((y - x) * (a[id + 1] - a[id])) == 0?-sign((y - x) * (a[id + 1] - a[id])):sign((sign((y - x) * (a[id - 1] - a[id]))) - sign((y - x) * (a[id + 1] - a[id])));
}
int check1(int id)
{
	return sign((y - x) * (a[id] - x)) * sign((y - x) * (a[id + 1] - x)) <= 0?0:sign((y - x) * (a[id] - x));
}
int di(int (*check)(int), int le, int ri)
{
	int nor = check(le), mid;
	if(le > ri) ri += n;
	while(le != ri)
	{
		mid = (le + ri) / 2;
		if(0 == check(mid)) return mid;
		else if(nor == check(mid)) le = mid + 1;
		else ri = mid - 1;
	}
	return le;
}
double area(int le, int ri)
{
	le %= n; ri %= n;
	return (le <= ri)?(s[ri] - s[le]):(s[n] - s[le] + s[ri]);
}
int main()
{
	freopen("sgu345.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		a[i].scan();
		if(i >= 3 and fabs((a[i] - a[i - 1]) * (a[i - 1] - a[i - 2])) < eps)
		{
			a[i - 1] = a[i];
			i--; n--;
		}
	}
	s[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		s[i] = s[i - 1] + a[i - 1] * a[i];
	}
	mni = a.get_max(les);
	mxi = a.get_max(mor);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		x.scan(); y.scan();
		if(check(mni)== 0 or check(mxi)== 0)
		{
			if(check(mxi) == 0) mi = mxi; else mi = mni;
			t1 = mi;
			t2 = di(check, mi + 1, mi - 1);
		}else
		{
			t1 = di(check, mni, mxi);
			t2 = di(check, mxi, mni);
		}
		c1 = di(check1, t1, t2);
		c2 = di(check1, t2, t1);
		if(check1(c1) and check1(c2)) {printf("0\n"); continue;}
		cp1 = cross(a[c1], a[c1 + 1], x, y);
		cp2 = cross(a[c2], a[c2 + 1], x, y);
		printf("%.10f\n", min(fabs(area(c1 + 1, c2) + cp1 * a[c1 + 1] + a[c2] * cp2 + cp2 * cp1) / 2, fabs(area(c2 + 1, c1) + a[c1] * cp1 + cp1 * cp2 + cp2 * a[c2 + 1]) / 2));
	}
	fclose(stdin);
	return 0;
}
