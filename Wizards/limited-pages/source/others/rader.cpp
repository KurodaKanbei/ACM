int h() {
    int i,j,k,count=0;
    bool visit[N];
    memset(visit,0,sizeof(visit));
    for(i=R[0];i;i=R[i]) {
        if(visit[i]) continue;
        count++;
        visit[i]=1;
        for(j=D[i];j!=i;j=D[j]) {
            for(k=R[j];k!=j;k=R[k])
                visit[C[k]]=1;
        }
    }
    return count;
}
void Dance(int k) {
    int i,j,c,Min,ans;
    ans=h();
    if(k+ans>K || k+ans>=ak) return;
    if(!R[0]) {
        if(k<ak) ak=k;
        return;
    }
    for(Min=N,i=R[0];i;i=R[i])
        if(S[i]<Min) Min=S[i],c=i;
    for(i=D[c];i!=c;i=D[i]) {
        remove(i);
        for(j=R[i];j!=i;j=R[j])
            remove(j);
        Dance(k+1);
        for(j=L[i];j!=i;j=L[j])
            resume(j);
        resume(i);
    }
    return;
}
