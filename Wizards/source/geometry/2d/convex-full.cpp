#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<map>
#include<stack>
#include<set>
#define e exp(1.0); //2.718281828
#define mod 1000000007
#define INF 0x7fffffff
#define inf 0x3f3f3f3f
typedef long long LL;
using namespace std;

#define zero(x) (((x)>0?(x):(-x))<eps)
const double eps=1e-8;

//判断数k的符号 -1负数 1正数 0零
int dcmp(double k) {
    return k<-eps?-1:k>eps?1:0;
}

inline double sqr(double x) {
    return x*x;
}
struct point {
    double x,y;
    point() {};
    point(double a,double b):x(a),y(b) {};
    void input() {
        scanf("%lf %lf",&x,&y);
    }
    friend point operator + (const point &a,const point &b) {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator - (const point &a,const point &b) {
        return point(a.x-b.x,a.y-b.y);
    }
    friend bool operator == (const point &a,const point &b) {
        return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
    }
    friend point operator * (const point &a,const double &b) {
        return point(a.x*b,a.y*b);
    }
    friend point operator * (const double &a,const point &b) {
        return point(a*b.x,a*b.y);
    }
    friend point operator / (const point &a,const double &b) {
        return point(a.x/b,a.y/b);
    }
    friend bool operator < (const point &a, const point &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
    double norm() {
        return sqrt(sqr(x)+sqr(y));
    }
};
//计算两个向量的叉积
double cross(const point &a,const point &b) {
    return a.x*b.y-a.y*b.x;
}
double cross3(point A,point B,point C) { //叉乘
    return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
}
//计算两个点的点积
double dot(const point &a,const point &b) {
    return a.x*b.x+a.y*b.y;
}
double dot3(point A,point B,point C) { //点乘
    return (C.x-A.x)*(B.x-A.x)+(C.y-A.y)*(B.y-A.y);
}

//向量长度
double length(const point &a) {
    return sqrt(dot(a,a));
}
//两个向量的角度
double angle(const point &a,const point &b) {
    return acos(dot(a,b)/length(a)/length(b));
}
//计算两个点的距离
double dist(const point &a,const point &b) {
    return (a-b).norm();
}
//op沿远点逆时针旋转角度A
point rotate_point(const point &p,double A) {
    double tx=p.x,ty=p.y;
    return point(tx*cos(A)-ty*sin(A),tx*sin(A)+ty*cos(A));
}
double TriArea(const point &a, const point &b, const point &c) {
    return fabs( cross( b - a, c - a ) ) / 2;
}
point Normal(const point &a) {
    double L = length(a);
    return point(-a.y/L, a.x/L);
}
//求两条直线的交点，p和q分别为两条直线上的点，v和w分别为直线的方向向量
point GetLineIntersection(point p, point v, point q, point w) {
    point u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}
//求点p到直线ab的距离
double DistanceToLine(point p, point a, point b) {
    point v1 = b - a, v2 = p - a;
    return fabs(cross(v1,v2)) / length(v1);
}
//求点p到线段ab的距离
double DistanceToSegment(point p, point a, point b) {
    if(a==b) return length(p - a);
    point v1 = b - a, v2 = p - a, v3 = p - b;
    if(dcmp(dot(v1,v2)) < 0) return length(v2);
    else if(dcmp(dot(v1,v3)) > 0) return length(v3);
    else return fabs(cross(v1,v2)) / length(v1);
}
//判断直线a1a2和直线b1b2是否规范相交
bool SegmentProperIntersection(point a1, point a2, point b1, point b2) {
    double c1 = cross(a2-a1,b1-a1), c2 = cross(a2-a1, b2-a1);
    double c3 = cross(b2-b1, a1-b1), c4 = cross(b2-b1, a2-b1);
    return dcmp(c1) * dcmp(c2) <0 && dcmp(c3) * dcmp(c4) < 0;
}

//判断点p是否在直线a1a2上
bool OnSegment(point p, point a1, point a2) {
    return dcmp(cross(a1-p,a2-p)) ==0 && dcmp(dot(a1-p,a2-p))<0;
}
//判断线段a1a2和线段b1b2是否相交，可以在端点处相交
bool SegmentIntersection(point a1, point a2, point b1, point b2) {
    return SegmentProperIntersection(a1, a2, b1, b2) || OnSegment(a1, b1, b2) || OnSegment(a2, b1, b2);
}

double SegmentToSegment(point a1, point a2, point b1, point b2) {
    //线段间的最短距离分为四种情况
    double t1 = DistanceToSegment(b1, a1, a2);
    double t2 = DistanceToSegment(b2, a1, a2);
    double t3 = DistanceToSegment(a1, b1, b2);
    double t4 = DistanceToSegment(a2, b1, b2);
    return min(t1,min(t2,min(t3,t4)));
}
//使点集逆时针转
void antiClockSort(point *ch, int n) {
    double res = cross(ch[1] - ch[0], ch[2] - ch[0]);
    if(dcmp(res) >= 0) return;
    reverse(ch, ch+n);
}

int ConvexHull(point* P, int cnt, point* res) {
    sort(P, P + cnt);
    cnt = (int) (unique(P, P + cnt) - P);
    int m = 0;
    for (int i = 0; i < cnt; i++) {
        while (m > 1 && cross(res[m - 1] - res[m - 2], P[i] - res[m - 2]) <= 0)
            m--;
        res[m++] = P[i];
    }
    int k = m;
    for (int i = cnt - 2; i >= 0; i--) {
        while (m > k && cross(res[m - 1] - res[m - 2], P[i] - res[m - 2]) <= 0)
            m--;
        res[m++] = P[i];
    }
    if (cnt > 1) m--;
    return m;
}

//判断点是否在多边形内
int isPointInPolygon(point p, point *a, int n) {
    int cnt = 0;
    for(int i=0; i<n; ++i) {
        if(OnSegment(p, a[i], a[(i+1)%n])) return -1;
        double k = cross(a[(i+1)%n]-a[i], p-a[i]);
        double d1 = a[i].y - p.y;
		double  d2 = a[(i+1)].y - p.y;
        if(k>0 &&d1<=0 &&d2>0)//点在线段的左侧
            cnt++;
        if(k<0 &&d2<=0 &&d1>0)//点在线段的右侧
            cnt++;
        //k==0，点和线段共线的情况不考虑
    }
    if(cnt&1)return 1;
    return 0;
}
//判断凸包是否相离
bool two_getaway_ConvexHull(point *cha, int n1, point *chb, int m1) {
    if(n1==1 && m1==1) {
        if(cha[0]==chb[0])
            return false;
    } else if(n1==1 && m1==2) {
        if(OnSegment(cha[0], chb[0], chb[1]))
            return false;
    } else if(n1==2 && m1==1) {
        if(OnSegment(chb[0], cha[0], cha[1]))
            return false;
    } else if(n1==2 && m1==2) {
        if(SegmentIntersection(cha[0], cha[1], chb[0], chb[1]))
            return false;
    } else if(n1==2) {
        for(int i=0; i<n1; ++i)
            if(isPointInPolygon(cha[i], chb, m1))
                return false;
    } else if(m1==2) {
        for(int i=0; i<m1; ++i)
            if(isPointInPolygon(chb[i], cha, n1))
                return false;
    } else {
        for(int i=0; i<n1; ++i) {
            for(int j=0; j<m1; ++j) {
                if(SegmentIntersection(cha[i], cha[(i+1)%n1], chb[j], chb[(j+1)%m1]))
                    return false;
            }
        }
        for(int i=0; i<n1; ++i)
            if(isPointInPolygon(cha[i], chb, m1))
                return false;
        for(int i=0; i<m1; ++i)
            if(isPointInPolygon(chb[i], cha, n1))
                return false;
    }
    return true;
}
//旋转卡壳求两个凸包最近距离
double solve(point *P, point *Q, int n, int m) {
    if(n==1 && m==1) {
        return length(P[0] - Q[0]);
    } else if(n==1 && m==2) {
        return DistanceToSegment(P[0], Q[0], Q[1]);
    } else if(n==2 && m==1) {
        return DistanceToSegment(Q[0], P[0], P[1]);
    } else if(n==2 && m==2) {
        return SegmentToSegment(P[0], P[1], Q[0], Q[1]);
    }

    int yminP = 0, ymaxQ = 0;
    for(int i=0; i<n; ++i) if(P[i].y < P[yminP].y) yminP = i;
    for(int i=0; i<m; ++i) if(Q[i].y > Q[ymaxQ].y) ymaxQ = i;
    P[n] = P[0];
    Q[n] = Q[0];
    double INF2 = 1e100;
    double arg, ans = INF2;

    for(int i=0; i<n; ++i) {
        //当叉积负正转正时，说明点ymaxQ就是对踵点
        while((arg=cross(P[yminP] - P[yminP+1],Q[ymaxQ+1] - Q[ymaxQ])) < -eps)
            ymaxQ = (ymaxQ+1)%m;
        double ret;

        if(arg > eps) { //卡住第二个凸包上的点。
            ret = DistanceToSegment(Q[ymaxQ], P[yminP], P[yminP+1]);
            ans  = min(ans,ret);
        } else { //arg==0，卡住第二个凸包的边
            ret = SegmentToSegment(P[yminP],P[yminP+1],Q[ymaxQ],Q[ymaxQ+1]);
            ans = min(ans,ret);
        }
        yminP = (yminP+1)%n;
    }
    return ans;
}
double mindis_twotubao(point *P, point *Q, int n, int m){
    //尼玛，hdu2823要判是否分离，poj3608不判
    //return min(solve(P, Q, n, m),solve(Q,P,m,n));
    //判断凸包是不是相离，如果不是，输出0
    if(two_getaway_ConvexHull(P,n,Q,m)==true) return min(solve(P, Q, n, m),solve(Q,P,m,n));
    else return 0.0;
}

const int N=10005;
point a[N],b[N];
point cha[N],chb[N];
int main() {
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=0;i<n;++i) scanf("%lf%lf",&a[i].x,&a[i].y);
        for(int i=0;i<m;++i) scanf("%lf%lf",&b[i].x,&b[i].y);
        //先求凸包
        int n1 = ConvexHull(a, n, cha);
        int m1 = ConvexHull(b, m, chb);
        printf("%.4f\n",mindis_twotubao(cha,chb,n1,m1));
    }
    return 0;
}
