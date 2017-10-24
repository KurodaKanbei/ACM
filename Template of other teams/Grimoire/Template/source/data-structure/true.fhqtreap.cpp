const int mo=1e9+7;
int rnd(){
    static int x=1;
    return x=(x*23333+233);
}
int rnd(int n){
    int x=rnd();
    if(x<0)x=-x;
    return x%n+1;
}
struct node{
    int siz,key;
    int val;
    LL sum;
    node *c[2];
    node* rz(){
        sum=val;siz=1;
        if(c[0])sum+=c[0]->sum,siz+=c[0]->siz;
        if(c[1])sum+=c[1]->sum,siz+=c[1]->siz;
        return this;
    }
    node(){}
    node(int v){
        siz=1;key=rnd();
        val=v;sum=v;
        c[0]=c[1]=0;
    }
    
}pool[maxn*8],*root,*cur=pool,*old_root,*stop;
node *newnode(int v=0){
    *cur=node(v);
    return cur++;
}
node *old_merge(node *p,node *q){
    if(!p&&!q)return 0;
    node *u=0;
    if(!p||!q)return u=p?p->rz():(q?q->rz():0);
    if(rnd(sz(p)+sz(q))<sz(p)){
        u=p;
        u->c[1]=old_merge(u->c[1],q);
    }else{
        u=q;
        u->c[0]=old_merge(p,u->c[0]);
    }
    return u->rz();
}
node *merge(node *p,node *q){
    if(!p&&!q)return 0;
    node *u=newnode();
    if(!p||!q)return u=p?p->rz():(q?q->rz():0);
    if(rnd(sz(p)+sz(q))<sz(p)){
        *u=*p;
        u->c[1]=merge(u->c[1],q);
    }else{
        *u=*q;
        u->c[0]=merge(p,u->c[0]);
    }
    return u->rz();
}
node *split(node *u,int l,int r){
    if(l>r||!u)return 0;
    node *x=0;
    if(l==1&&r==sz(u)){
        x=newnode();
        *x=*u;
        return x->rz();
    }
    int lsz=sz(u->c[0]);
    if(r<=lsz)
        return split(u->c[0],l,r);
    if(l>lsz+1)
        return split(u->c[1],l-lsz-1,r-lsz-1);
    x=newnode();
    *x=*u;
    x->c[0]=split(u->c[0],l,lsz);
    x->c[1]=split(u->c[1],1,r-lsz-1);
    return x->rz();
}

