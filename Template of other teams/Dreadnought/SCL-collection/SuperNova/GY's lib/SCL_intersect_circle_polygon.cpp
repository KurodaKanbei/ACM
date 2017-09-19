#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps = 1e-12, PI = acos(-1.);
int sign(double x)
{
	return x < -eps?-1:(x > eps?1:0);
}
struct triple
{
	double x, y, z;
	triple(){}
	triple(const double & _x, const double & _y, const double & _z) : x(_x), y(_y), z(_z){}
	void scan() {scanf("%lf%lf%lf", &x, &y, &z);}
	void print(char ch) {printf("%lf %lf %lf%c", x, y, z, ch);}
	double sqrlen() const {return x * x + y * y + z * z;}
	double len() const {return sqrt(sqrlen());}
} p1, p2, p3, dir, co;
double sign(triple x)
{
	return sign(x.x) == 0?(sign(x.y) == 0?sign(x.z):sign(x.y)):sign(x.x);
}
triple operator + (const triple & a, const triple & b)
{
	return triple(a.x + b.x, a.y + b.y, a.z + b.z);
}
triple operator - (const triple & a, const triple & b)
{
	return triple(a.x - b.x, a.y - b.y, a.z - b.z);
}
triple operator * (const double & a, const triple & b)
{
	return triple(a * b.x, a * b.y, a * b.z);
}
triple operator * (const triple & a, const triple & b)
{
	return triple(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
double operator % (const triple & a, const triple & b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

double t, ans, r;
double fix(double x)
{
	if(x > 1) return 1;
	else if(x < -1) return -1;
	else return x;
}
double calc(triple pa, triple pb)
{
		if(pa.len() < pb.len()) swap(pa, pb);
		if(pb.len() < eps) return 0;
		double a, b, c, B, C, sinB, cosB, sinC, cosC, S, h, theta;
		a = pb.len();
		b = pa.len();
		c = (pb - pa).len();
		cosB = fix(pb % (pb - pa) / a / c);
		sinB = fix((pb * (pb - pa)).len() / a / c);
		B = acos(cosB);
		cosC =	fix(pa % pb / a / b);
		sinC = fix((pa * pb).len() / a / b);
		C = acos(cosC);
		if(a > r)
		{
			S = C / 2 * r * r;
			h = a * b * sinC / c;
			if(h < r and B < PI / 2) S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
		}else if(b > r)
		{
			theta = PI - B - asin(fix(sinB / r * a));
			S = .5 * a * r * sin(theta) + (C - theta) / 2 * r * r;
		}else
			S = .5 * sinC * a * b;
		//printf("%lf\n", S);
		return S;
}
int main()
{
	p1.scan();
	p2.scan();
	p3.scan();
	dir = (p2 - p1) * (p3 - p1);
	double t = dir % p1 / (dir % dir);
	co = t * dir;
	//co.print('\n');
	if(co.sqrlen() > 10000) 
	{
		printf("0\n");
		return 0;
	}
	r = sqrt(10000 - co.sqrlen());
	p1 = p1 - co;
	p2 = p2 - co;
	p3 = p3 - co;
	double ans = 0;
	ans += calc(p1, p2) * sign(p1 * p2);
	ans += calc(p2, p3) * sign(p2 * p3);
	ans += calc(p3, p1) * sign(p3 * p1);
	printf("%.10f\n", fabs(ans));
	fclose(stdin);
	return 0;
}
