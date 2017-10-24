#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int in(){
    int r=0,f=1;char c=getchar();
    while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
    while(isdigit(c))r=r*10+c-'0',c=getchar();
    return r*f;
}
int n,m;
#define sz(x) (x?x->siz:0)
struct node{
    int siz,key;
    LL val,sum;
    LL mu,a,d;
    node *c[2],*f;
    void split(int ned,node *&p,node *&q);
    node* rz(){
        sum=val;siz=1;
        if(c[0])sum+=c[0]->sum,siz+=c[0]->siz;
        if(c[1])sum+=c[1]->sum,siz+=c[1]->siz;
        return this;
    }
    void make(LL _mu,LL _a,LL _d){
        sum=sum*_mu+_a*siz+_d*siz*(siz-1)/2;
        val=val*_mu+_a+_d*sz(c[0]);
        mu*=_mu;a=a*_mu+_a;d=d*_mu+_d;
    }
    void pd(){
        if(mu==1&&a==0&&d==0)return;
        if(c[0])c[0]->make(mu,a,d);
        if(c[1])c[1]->make(mu,a+d+d*sz(c[0]),d);
        mu=1;a=d=0;
    }
    node(){mu=1;}
}nd[maxn*2],*root;
node *merge(node *p,node *q){
    if(!p||!q)return p?p->rz():(q?q->rz():0);
    p->pd();q->pd();
    if(p->key<q->key){
        p->c[1]=merge(p->c[1],q);
        return p->rz();
    }else{
        q->c[0]=merge(p,q->c[0]);
        return q->rz();
    }
}
void node::split(int ned,node *&p,node *&q){
    if(!ned){p=0;q=this;return;}
    if(ned==siz){p=this;q=0;return;}
    pd();
    if(sz(c[0])>=ned){
        c[0]->split(ned,p,q);c[0]=0;rz();
        q=merge(q,this);
    }else{
        c[1]->split(ned-sz(c[0])-1,p,q);c[1]=0;rz();
        p=merge(this,p);
    }
}
int tot;
void C(int l,int r,int v){
    node *p,*q,*x,*y;
    root->split(l-1,p,q);
    q->split(r-l+1,x,y);
    x->make(0,v,0);x->pd();
    root=merge(p,merge(x,y));
}
void A(int l,int r,int d){
    node *p,*q,*x,*y;
    root->split(l-1,p,q);
    q->split(r-l+1,x,y);
    x->make(1,d,d);x->pd();
    root=merge(p,merge(x,y));
}
void I(int ps,int v){
    node *p,*q;
    root->split(ps-1,p,q);
    node *x=nd+(++tot);
    x->key=rand();x->val=v;x->rz();
    root=merge(merge(p,x),q);
}
LL Q(int l,int r){
    node *p,*q,*x,*y;
    root->split(l-1,p,q);
    q->split(r-l+1,x,y);
    LL ans=x->sum;
    root=merge(p,merge(x,y));   
    return ans;
}
int main(){
//  freopen("bzoj3188.in","r",stdin);
    n=in();m=in();
    for(int i=1;i<=n;i++){
        nd[i].val=in();
        nd[i].key=rand();
        nd[i].rz();
        root=merge(root,nd+i);
    }tot=n;
    while(m--){
        int ty=in();
        int l,r;
        if(ty==1){
            l=in();r=in();
            C(l,r,in());
        }else if(ty==2){
            l=in();r=in();
            A(l,r,in());
        }else if(ty==3){
            int ps=in();
            I(ps,in());
        }else if(ty==4){
            l=in();r=in();
            printf("%lld\n",Q(l,r));
        }
    }
    return 0;
}
