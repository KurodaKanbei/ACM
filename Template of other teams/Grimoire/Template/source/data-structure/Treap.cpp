#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
#define sz(x) (x?x->siz:0)
struct Treap{
	struct node{
		int key,val;
		int siz,s;
		node *c[2];
		node(int v=0){
			val=v;
			key=rand();
			siz=1,s=1;
			c[0]=c[1]=0;		
		}
		void rz(){siz=s;if(c[0])siz+=c[0]->siz;if(c[1])siz+=c[1]->siz;}
	}pool[maxn],*cur,*root;
	Treap(){cur=pool;}
	node* newnode(int val){return *cur=node(val),cur++;}
	void rot(node *&t,int d){
		if(!t->c[d])t=t->c[!d];
		else{
			node *p=t->c[d];t->c[d]=p->c[!d];
			p->c[!d]=t;t->rz();p->rz();t=p;
		}
	}
	void insert(node *&t,int x){
		if(!t){t=newnode(x);return;}
		if(t->val==x){t->s++;t->siz++;return;}
		insert(t->c[x>t->val],x);
		if(t->key<t->c[x>t->val]->key)
			rot(t,x>t->val);
		else t->rz();
	}
	void del(node *&t,int x){
		if(!t)return;
		if(t->val==x){
			if(t->s>1){t->s--;t->siz--;return;}
			if(!t->c[0]||!t->c[1]){
				if(!t->c[0])t=t->c[1];
				else t=t->c[0];
				return;
			}
			int d=t->c[0]->key<t->c[1]->key;
			rot(t,d);
			del(t,x);
			return;
		}
		del(t->c[x>t->val],x);
		t->rz();
	}
	int pre(node *t,int x){
		if(!t)return INT_MIN;
		int ans=pre(t->c[x>t->val],x);
		if(t->val<x)ans=max(ans,t->val);
		return ans;
	}
	int nxt(node *t,int x){
		if(!t)return INT_MAX;
		int ans=nxt(t->c[x>=t->val],x);
		if(t->val>x)ans=min(ans,t->val);
		return ans;	
	}
	int rank(node *t,int x){
		if(!t)return 0;
		if(t->val==x)return sz(t->c[0]);
		if(t->val<x)return sz(t->c[0])+t->s+rank(t->c[1],x);
		if(t->val>x)return rank(t->c[0],x);
	}
	int kth(node *t,int x){
		if(sz(t->c[0])>=x)return kth(t->c[0],x);
		if(sz(t->c[0])+t->s>=x)return t->val;
		return kth(t->c[1],x-t->s-sz(t->c[0]));
	}
	void deb(node *t){
		if(!t)return;
		deb(t->c[0]);
		printf("%d ",t->val);
		deb(t->c[1]);
	}
	void insert(int x){insert(root,x);}
	void del(int x){del(root,x);}
	int pre(int x){return pre(root,x);}
	int nxt(int x){return nxt(root,x);}
	int rank(int x){return rank(root,x);}
	int kth(int x){return kth(root,x);}
	void deb(){deb(root);puts("");}
}T;
