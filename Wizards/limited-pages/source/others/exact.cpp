#pragma comment(linker, "/STACK:1024000000,1024000000")  
int head,sz;  
int U[maxn],D[maxn],L[maxn],R[maxn];
int H[maxn],ROW[maxn],C[maxn],S[maxn],O[maxn];  
void remove(int c) {  
    L[R[c]]=L[c];  
    R[L[c]]=R[c];  
    for(int i=D[c]; i!=c; i=D[i])  
        for(int j=R[i]; j!=i; j=R[j]) {
            U[D[j]]=U[j];  
            D[U[j]]=D[j];  
            --S[C[j]];  
        }  
}  
void resume(int c) {
    for(int i=U[c]; i!=c; i=U[i]) { 
        for(int j=L[i]; j!=i; j=L[j]) {
            ++S[C[j]];  
            U[D[j]]=j;  
            D[U[j]]=j;  
        }  
    }  
    L[R[c]]=c;  
    R[L[c]]=c;  
}  
void init(int m) {
    head=0;//头指针为0  
    for(int i=0; i<=m; i++) {
        U[i]=i;D[i]=i;L[i]=i-1;R[i]=i+1;S[i]=0;  
    }  
    R[m]=0;L[0]=m;S[0]=INF+1;sz=m+1;  
    memset(H,0,sizeof(H));  
}  
void insert(int i, int j) {
    if(H[i]) {
        L[sz] = L[H[i]];R[sz] = H[i];
			L[R[sz]] = sz;R[L[sz]] = sz;  
    } else {
        L[sz] = sz;R[sz] = sz;  
        H[i] = sz;  
    }  
    U[sz] = U[j];D[sz] = j;  
    U[D[sz]] = sz;D[U[sz]] = sz;  
    C[sz] = j;ROW[sz] = i;  
    ++S[j];++sz;  
}  
bool dfs(int k,int len) {
    if(R[head]==head) return true;    
    int s=INF,c;  
    for (int t=R[head]; t!=head; t=R[t])  
        if (S[t]<s) s=S[t],c=t;  
    remove(c);  
    for(int i=D[c]; i!=c; i=D[i]) {
        O[k]=ROW[i];  
        for(int j=R[i]; j!=i; j=R[j]) 
			remove(C[j]);  
        if(dfs(k+1,len)) return true;  
        for(int j=L[i]; j!=i; j=L[j])  
            resume(C[j]);  
    }  
    resume(c);  
    return  false;  
} 
