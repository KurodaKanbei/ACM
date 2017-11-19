//判断点是否在多边形内
int isPointInPolygon(point p, point *a, int n) {
    int cnt = 0;
    for(int i=0; i<n; ++i) {
        if(OnSegment(p, a[i], a[(i+1)%n])) return -1;
        double k = cross(a[(i+1)%n]-a[i], p-a[i]);
        double d1 = a[i].y - p.y;
		double  d2 = a[(i+1)].y - p.y;
        if(k>0 &&d1<=0 &&d2>0) cnt++;
        if(k<0 &&d2<=0 &&d1>0) cnt++;
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
    //return min(solve(P, Q, n, m),solve(Q,P,m,n));
    if(two_getaway_ConvexHull(P,n,Q,m)==true) return min(solve(P, Q, n, m),solve(Q,P,m,n));
    else return 0.0;
}
