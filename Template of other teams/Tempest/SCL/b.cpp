#include<cstdio>
#include<cstring>
#include<ctime>
int np=0, rela[2000022], n, nod[2000011], l, cl, v, p, idx[2000022],iddx[2000022], ll, Q, siz[2000022];
int ans[1000011], x, y;
struct recq
{
	int v, p;
} q[2000022];
bool f[2000022];
char c;
struct recmap
{
	int y, next, i;
} map[2000022], map1[2000011];
void build(int x, int y)
{
	map[++l].y = y;
	map[l].next = idx[x];
	idx[x] = l;
}
void build(int x, int y, int z)
{
	map1[++ll].y = y;
	map1[ll].i = z;
	map1[ll].next = iddx[x];
	iddx[x] = ll;
}
int getr(int x)
{
	int p = x, p1, p2;
	while(rela[p]!=p) p = rela[p];
	p1 = p; p = x;
	while(rela[p]!=p) {p2 = rela[p]; rela[p] = p1; p = p2;}
	return p1;
}
struct recsam
{
	int l, v;
	recsam * go[26], *p;
} *leaf, *root, polsam[2000022];
recsam * newrecsam(int _l)
{
	recsam * p = &polsam[++np];
	p->l = _l; p->v = np; p->p=0;
	memset(p->go, 0, sizeof(p->go));
	return p;
}
recsam * newrecsam(recsam & x)
{
	recsam * p = &polsam[++np];
	*p=x;
	p->v = np;
	return p;
}
int main()
{
	scanf("%d\n", &n);
	root = newrecsam(0); leaf = root;
	memset(siz, 0, sizeof(siz));
	for(int i = 1; i <= n; i++)
	{
		scanf("%c", &c); c -= 'a';
		recsam * np = newrecsam(i);
		nod[i] = np->v; siz[np->v] = 1;
		recsam * p = leaf;
		for(;p and p->go[c] == 0;p=p->p)p->go[c] = np;
		if(!p) np->p = root;
		else
		{
			recsam * q;
			if((q=p->go[c])->l == p->l+1) np->p = q;
			else
			{
				recsam * nq = newrecsam(*q);
				nq->l = p->l+1;
				nq->p = q->p;
				q->p = np->p = nq;
				for(;p and p->go[c] == q; p=p->p) p->go[c] = nq;
			}
		}
		leaf = np;
	}
	l = 0; memset(idx, 0, sizeof(idx));
	for(int i = 1; i <= np; i++) if(polsam[i].p)build(polsam[i].p->v, polsam[i].v);
	scanf("%d", &Q);
	ll = 0; memset(iddx, 0, sizeof(iddx));
	for(int i = 1; i <= Q; i++)
	{
		scanf("%d%d", &x, &y);
		build(nod[x], nod[y], i);
		build(nod[y], nod[x], i);
	}
	q[cl=1].v = 1;
	q[cl=1].p = idx[1];
	memset(f, false, sizeof(f));
	for(int i = 1; i <= np; i++) rela[i] = i;
	while(cl)
	{
		v = q[cl].v;
		q[cl].p = map[p=q[cl].p].next;
		if(p)
		{
			q[++cl].v = map[p].y;
			q[cl].p = idx[q[cl].v];
		}else
		{
			f[v] = true;
			for(int p = iddx[v]; p; p = map1[p].next)
				if(f[map1[p].y] == true) ans[map1[p].i] = getr(map1[p].y);
			siz[q[cl-1].v] += siz[v];
			rela[getr(v)] = getr(q[cl-1].v);
			cl--;
		}
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", ans[i]!=1?siz[ans[i]]:0);
	return 0;
}
