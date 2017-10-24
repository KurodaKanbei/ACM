LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;return a;
	}else{
		LL d=exgcd(b,a%b,x,y);
		LL t=x;x=y;y=t-a/b*y;
		return d;
	}
}
