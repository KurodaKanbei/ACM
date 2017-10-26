// 求$\max\{cx\,|\,Ax \leq b, x \geq 0\}$的解
typedef vector<double> VD;
VD simplex(vector<VD> A, VD b, VD c) {
	int n = A.size(), m = A[0].size() + 1, r = n, s = m - 1;
	vector<VD> D(n + 2, VD(m + 1, 0)); vector<int> ix(n + m);
	for (int i = 0; i < n + m; ++ i) ix[i] = i;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m - 1; ++ j) D[i][j] = -A[i][j];
		D[i][m - 1] = 1; D[i][m] = b[i];
		if (D[r][m] > D[i][m]) r = i;
	}
	for (int j = 0; j < m - 1; ++ j) D[n][j] = c[j];
	D[n + 1][m - 1] = -1;
	for (double d; ; ) {
		if (r < n) {
			int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t;
			D[r][s] = 1.0 / D[r][s]; vector<int> speedUp;
			for (int j = 0; j <= m; ++ j) if (j != s) {
				D[r][j] *= -D[r][s];
				if(D[r][j]) speedUp.push_back(j);
			}
			for (int i = 0; i <= n + 1; ++ i) if (i != r) {
				for(int j = 0; j < speedUp.size(); ++ j)
				D[i][speedUp[j]] += D[r][speedUp[j]] * D[i][s];
				D[i][s] *= D[r][s];
		}} r = -1; s = -1;
		for (int j = 0; j < m; ++ j) if (s < 0 || ix[s] > ix[j])
			if (D[n + 1][j] > EPS || (D[n + 1][j] > -EPS && D[n][j] > EPS)) s = j;
		if (s < 0) break;
		for (int i = 0; i < n; ++ i) if (D[i][s] < -EPS)
			if (r < 0 || (d = D[r][m] / D[r][s] - D[i][m] / D[i][s]) < -EPS
					|| (d < EPS && ix[r + m] > ix[i + m])) r = i;
		if (r < 0) return VD(); // 无边界
	}
	if (D[n + 1][m] < -EPS) return VD(); // 无解
	VD x(m - 1);
	for (int i = m; i < n + m; ++ i) if (ix[i] < m - 1) x[ix[i]] = D[i - m][m];
	return x; // 最优值在 D[n][m]
}

namespace simplex {
	const double eps=1e-9;
	const int N=2310,M=2010;
	int n,m;
	int Left[M],Down[N],idx[N],va[N];
	double a[M][N],b[M],c[N],v;
	void init(int p,int q) {
		n=p; m=q;
		rep(i,1,m+1) rep(j,1,n+1) a[i][j]=0;
		rep(j,1,m+1) b[j]=0; rep(i,1,n+1) c[i]=0;
		rep(i,1,n+1) idx[i]=0;
		v=0;
	}
	void pivot(int x,int y) {
		swap(Left[x],Down[y]);
		double k=a[x][y];
		a[x][y]=1; b[x]/=k;
		int t=0;
		rep(j,1,n+1) {
			a[x][j]/=k;
			if (abs(a[x][j])>eps) va[++t]=j;
		}
		rep(i,1,m+1) if(i!=x&&abs(a[i][y])>eps) {
			k=a[i][y];
			a[i][y]=0;
			b[i]-=k*b[x];
			rep(j,1,t+1) a[i][va[j]]-=k*a[x][va[j]];
		}
		k=c[y];
		c[y]=0;
		v+=k*b[x];
		rep(j,1,t+1) c[va[j]]-=k*a[x][va[j]];
	}
	int solve() {
		rep(i,1,n+1) Down[i]=i;
		rep(i,1,m+1) Left[i]=n+i;
		while(1) {
			int x=0;
			rep(i,1,m+1) if (b[i]<-eps) { x=i; break; }
			if(x==0) break;
			int y=0;
			rep(j,1,n+1) if (a[x][j]<-eps) { y=j; if(rand()&1) break; }
			if(y==0) { puts("Infeasible"); return -1; } //Infeasible
			pivot(x,y);
		}
		while(1) {
			int y=0;
			rep(i,1,n+1) if (c[i]>eps&&(y==0||c[i]>c[y])) y=i;
			if(y==0) break;
			int x=0;
			rep(j,1,m+1) if (a[j][y]>eps) if (x==0||b[j]/a[j][y]<b[x]/a[x][y]) x=j;
			if(x==0) { puts("Unbounded"); return -2; } // Unbounded
			pivot(x,y);
		}
		printf("%.10lf\n",v);
		rep(i,1,m+1) if(Left[i]<=n) idx[Left[i]]=i;
		rep(i,1,n+1) printf("%.10lf ",b[idx[i]]);
		puts("");
		return 1;
	}
}

namespace simplex {
	const int N=410,M=30010;
	int n,m;
	int Left[M],Down[N],idx[N];
	ll a[M][N],b[M],c[N],v;
	void init(int p,int q) {
		n=p; m=q;
		rep(i,1,m+1) rep(j,1,n+1) a[i][j]=0;
		rep(j,1,m+1) b[j]=0; rep(i,1,n+1) c[i]=0;
		rep(i,1,n+1) idx[i]=0;
		v=0;
	}
	int va[N];
	void pivot(int x,int y) {
		swap(Left[x],Down[y]);
		ll k=a[x][y];
		a[x][y]=1; b[x]/=k;
		int t=0;
		rep(j,1,n+1) {
			a[x][j]/=k;
			if (a[x][j]) va[++t]=j;
		}
		rep(i,1,m+1) if(i!=x&&a[i][y]) {
			k=a[i][y];
			a[i][y]=0;
			b[i]-=k*b[x];
			rep(j,1,t+1) a[i][va[j]]-=k*a[x][va[j]];
		}
		k=c[y];
		c[y]=0;
		v+=k*b[x];
		rep(j,1,t+1) c[va[j]]-=k*a[x][va[j]];
	}
	int solve() {
		rep(i,1,n+1) Down[i]=i;
		rep(i,1,m+1) Left[i]=n+i;
		while(1) {
			int x=0;
			rep(i,1,m+1) if (b[i]<0) { x=i; break; }
			if(x==0) break;
			int y=0;
			rep(j,1,n+1) if (a[x][j]<0) { y=j; if(rand()&1) break; }
			if(y==0) { puts("Infeasible"); return -1; } //Infeasible
			pivot(x,y);
		}
		while(1) {
			int y=0;
			rep(i,1,n+1) if (c[i]>0&&(y==0||c[i]>c[y])) y=i;
			if(y==0) break;
			int x=0;
			rep(j,1,m+1) if (a[j][y]>0) if (x==0||b[j]/a[j][y]<b[x]/a[x][y]) x=j;
			if(x==0) { puts("Unbounded"); return -2; } // Unbounded
			pivot(x,y);
		}
		printf("%lld\n",v);
		rep(i,1,m+1) if(Left[i]<=n) idx[Left[i]]=i;
		rep(i,1,n+1) printf("%lld ",b[idx[i]]);
		puts("");
		return 1;
	}
}
