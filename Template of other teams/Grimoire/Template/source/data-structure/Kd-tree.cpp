int n;
LL norm(const LL &x) {
    //    For manhattan distance
   	//return std::abs(x);
    //    For euclid distance
    return x * x;
}

struct P{
	int a[2],val;
	int id;
	int& operator[](int s){return a[s];}
	const int& operator[](int s)const{return a[s];}
	
	LL dis(const P &b)const{
		LL ans=0;
        for (int i = 0; i < 2; ++i) {
            ans += norm(a[i] - b[i]);
        }
		return ans;
	}
}p[maxn];

bool operator==(const P &a,const P &b){
	for(int i=0;i<DIM;i++)
		if(a[i]!=b[i])
			return false;
	return true;
}
bool byVal(P a,P b){
	return a.val!=b.val ? a.val<b.val : a.id<b.id;
}

struct Rec{
	int mn[DIM],mx[DIM];
	Rec(){}
	Rec(const P &p){
		for(int i=0;i<DIM;i++){
			mn[i]=mx[i]=p[i];
		}
	}
	void add(const P &p){
		for(int i=0;i<DIM;i++){
			mn[i]=min(p[i],mn[i]);
			mx[i]=max(p[i],mx[i]);
		}
	}
	
    LL dis(const P &p) {
        LL ans = 0;
        for (int i = 0; i < 2; ++i) {
            //    For minimum distance
            ans += norm(min(max(p[i], mn[i]), mx[i]) - p[i]);
            //    For maximum distance
            //ans += std::max(norm(max[i] - p[i]), norm(min[i] - p[i]));
        }
        return ans;
    }
};
inline Rec operator+(const Rec &ls,const Rec &rs){
	static Rec rec;
	for(int i=0;i<DIM;i++){
		rec.mn[i]=min(ls.mn[i],rs.mn[i]);
		rec.mx[i]=max(ls.mx[i],rs.mx[i]);
	}
	return rec;
}
struct node{
	Rec rec;
	P sep;
	int sum,siz;
	node *c[2];
	node *rz(){
		sum=sep.val;
		rec=Rec(sep);
		siz=1;
		if(c[0]){
			sum+=c[0]->sum;
			rec=rec+c[0]->rec;
			siz+=c[0]->siz;
		}
		if(c[1]){
			sum+=c[1]->sum;
			rec=rec+c[1]->rec;
			siz+=c[1]->siz;
		}
		return this;
	}
	node(){sum=0;siz=1;c[0]=c[1]=0;}
}*root,*re,pool[maxn],*cur=pool;
node *sta[maxn];
P tmp[maxn];
int D,si;
void init(){
	si=0;
	cur=pool;
	root=0;
}
bool cmp(const P &A,const P &B){
	
	if(!(A[D]==B[D]))
		return A[D]<B[D];
	return A.id<B.id;
}
int top;
node *newnode(){
	if(si)return sta[si--];
	return cur++;
}
node* build(P *p,int l,int r,int d){
	int mid=(l+r)>>1;D=d;
	nth_element(p+l,p+mid,p+r+1,cmp);
	node *t=newnode();
	t->sep=p[mid];
	if(l<=mid-1)
		t->c[0]=build(p,l,mid-1,d^1);
	if(mid+1<=r)
		t->c[1]=build(p,mid+1,r,d^1);
	return t->rz();
}
void dfs(node *&t){
	if(t->c[0])dfs(t->c[0]);
	tmp[++top]=t->sep;
	if(t->c[1])dfs(t->c[1]);
	sta[++si]=t;*t=node();
	//delete t;
}
node* rebuild(node *&t){
	if(!t)return 0;
	top=0;dfs(t);
	return build(tmp,1,top,0);
}
#define siz(x) (x?x->siz:0)
void Add(node *&t,const P &p,int d=0){//调用前re=0;调用后rebuild(re);
	D=d;
	if(!t){
		t=newnode();
		t->sep=p;t->rz();
		return;
	}
	if(t->sep==p){
		t->sep.val+=p.val;
		t->rz();
		return;
	}
	if(p[D]<t->sep[D])
		Add(t->c[0],p,d^1);
	else
		Add(t->c[1],p,d^1);
	
	t->rz();
	
	if(max(siz(t->c[0]),siz(t->c[1]))>0.7*t->siz)
		re=t;
}
int ans;

bool Out(const Rec &a,const Rec &b){
	for(int i=0;i<DIM;i++){
		int l=max(a.mn[i],b.mn[i]);
		int r=min(a.mx[i],b.mx[i]);
		if(l>r)	
			return true;
	}
	return false;
}
bool In(const Rec &a,const Rec &b){
	for(int i=0;i<DIM;i++){
		if(a.mn[i]<b.mn[i])
			return false;
		if(a.mx[i]>b.mx[i])
			return false;
	}
	return true;
}

bool In(const P &a,const Rec &b){
	for(int i=0;i<DIM;i++){
		if(!(b.mn[i]<=a[i]&&a[i]<=b.mx[i]))
			return false;
	}
	return true;
}

void Q(node *t,const Rec &R){
	if(Out(t->rec,R))return ;
	if(In(t->rec,R)){
		ans+=t->sum;
		return;
	}
	if(In(t->sep,R))
		ans+=t->sep.val;
	if(t->c[0])
		Q(t->c[0],R);
	if(t->c[1])
		Q(t->c[1],R);
}

priority_queue<pair<long long, int> > kNN;
void query(node *t, const P &p, int k, int d = 0) {//用钱清空kNN
    D=d;
    if (!t || ((int)kNN.size() == k && t->rec.dis(p) > kNN.top().first)) {
        return;
    }
    kNN.push(make_pair(t->sep.dis(p), t->sep.id));
    if ((int)kNN.size() > k) {
        kNN.pop();
    }
    if (cmp(p, t->sep)) {
        query(t->c[0], p, k, d ^ 1);
        query(t->c[1], p, k, d ^ 1);
    } else {
        query(t->c[1], p, k, d ^ 1);
        query(t->c[0], p, k, d ^ 1);
    }
}
