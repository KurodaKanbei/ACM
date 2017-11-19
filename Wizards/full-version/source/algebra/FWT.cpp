void FWT(LL a[],int n,int ty){
	for(int d=1;d<n;d<<=1){
		for(int m=(d<<1),i=0;i<n;i+=m){
			if(ty==1){
				for(int j=0;j<d;j++){
					LL x=a[i+j],y=a[i+j+d];
					a[i+j]=x+y;
					a[i+j+d]=x-y;
    	            //xor:a[i+j]=x+y,a[i+j+d]=x-y;    
    	            //and:a[i+j]=x+y;    
    	            //or:a[i+j+d]=x+y;    
				}
			}else{
				for(int j=0;j<d;j++){
					LL x=a[i+j],y=a[i+j+d];
					a[i+j]=(x+y)/2;
					a[i+j+d]=(x-y)/2;
	                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;    
    	            //and:a[i+j]=x-y;    
    	            //or:a[i+j+d]=y-x;    
				}
			}
		}
	}
}
	FWT(a,1<<n,1);
	FWT(b,1<<n,1);
	for(int i=0;i<(1<<n);i++)
		c[i]=a[i]*b[i];
	FWT(c,1<<n,-1);
