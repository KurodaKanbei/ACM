LL prho(LL n,LL c){
	LL i=1,k=2,x=rand()%(n-1)+1,y=x;
	while(1){
		i++;x=(x*x%n+c)%n;
		LL d=__gcd((y-x+n)%n,n);
		if(d>1&&d<n)return d;
		if(y==x)return n;
		if(i==k)y=x,k<<=1;
	}
}
void factor(LL n,vector<LL>&fat){
	if(n==1)return;
	if(isprime(n)){
		fat.push_back(n);
		return;
	}LL p=n;
	while(p>=n)p=prho(p,rand()%(n-1)+1);
	factor(p,fat);
	factor(n/p,fat);
}
