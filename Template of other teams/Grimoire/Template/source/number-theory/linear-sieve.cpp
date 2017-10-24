void sieve(){
	f[1]=mu[1]=phi[1]=1;
	for(int i=2;i<maxn;i++){
		if(!minp[i]){
			minp[i]=i;
			minpw[i]=i;
			mu[i]=-1;
			phi[i]=i-1;
			f[i]=i-1;
			p[++p[0]]=i;//Case 1 prime
		}
		for(int j=1;j<=p[0]&&(LL)i*p[j]<maxn;j++){
			minp[i*p[j]]=p[j];
			if(i%p[j]==0){
				//Case 2 not coprime
				minpw[i*p[j]]=minpw[i]*p[j];
				phi[i*p[j]]=phi[i]*p[j];
				mu[i*p[j]]=0;
				if(i==minpw[i]){
					f[i*p[j]]=i*p[j]-i;//Special Case for f($p^k$)
				}else{
					f[i*p[j]]=f[i/minpw[i]]*f[minpw[i]*p[j]];
				}
				break;
			}else{
				//Case 3 coprime
				minpw[i*p[j]]=p[j];
				f[i*p[j]]=f[i]*f[p[j]];
				phi[i*p[j]]=phi[i]*(p[j]-1);
				mu[i*p[j]]=-mu[i];
			}
		}
	}
}
