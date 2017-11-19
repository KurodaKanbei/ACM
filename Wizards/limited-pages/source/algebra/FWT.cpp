void FWT(LL a[],int n,int ty){ //the length is 2^n
	for(int d=1;d<n;d<<=1){
		for(int m=(d<<1),i=0;i<n;i+=m){
			if(ty==1){
				for(int j=0;j<d;j++){
					LL x=a[i+j],y=a[i+j+d];
					a[i+j]=x+y;
					a[i+j+d]=x-y;
    	            //and:a[i+j]=x+y; or:a[i+j+d]=x+y;    
				}
			}else{
				for(int j=0;j<d;j++){
					LL x=a[i+j],y=a[i+j+d];
					a[i+j]=(x+y)/2;
					a[i+j+d]=(x-y)/2;
    	            //and:a[i+j]=x-y; or:a[i+j+d]=y-x;    
				}
			}
		}
	}
}
