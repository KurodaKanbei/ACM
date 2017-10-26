    #include<iostream>  
    #include<cstdlib>  
    #include<cstdio>  
    #include<cstring>  
    #include<cmath>  
    #include<algorithm>  
    using namespace std;  
    int const N=50005;  
    double eps=1e-8;  
    double pi=acos(-1.0);  
    struct P  
    {  
        double x,y;  
        void read(){scanf("%lf%lf",&x,&y);}  
        P(){}  
        P(double x,double y):x(x),y(y){}  
        double operator *(const P& p)const{return x*p.y-y*p.x;}  
        P operator -(const P& p)const{return P(x-p.x,y-p.y);}  
        P operator +(const P& p)const{return P(x+p.x,y+p.y);}  
        P operator *(double const& d)const{return P(x*d,y*d);}  
        P operator /(double const& d)const{return P(x/d,y/d);}  
        double angle()const{return atan2(y,x);}  
        void out(){printf("P: %f %f\n",x,y);}  
    };  
    P p[N*2],Q[N];  
    double sum[N*2];  
    bool cmp(const P& p1,const P&p2)  
    {  
        if(fabs(p1.y-p2.y)<1e-8)return p1.x<p2.x;  
        else return  p1.y<p2.y;  
    }  
    int Poly(int n)  
    {  
        sort(p,p+n,cmp);  
        int N=0;  
        for(int i=0;i<n;i++)  
        {  
            while(N>=2&&(Q[N-1]-Q[N-2])*(p[i]-Q[N-1])<eps)N--;  
            Q[N++]=p[i];  
        }  
        int t=N+1;  
        for(int i=n-2;i>=0;i--)  
        {  
            while(N>=t&&(Q[N-1]-Q[N-2])*(p[i]-Q[N-1])<eps)N--;  
            Q[N++]=p[i];  
        }  
        N--;  
        for(int i=0;i<N;i++)p[i]=Q[i];  
        return N;  
    }  
    double Avg[N];  
    int n;  
    P u,v;  
    int mid(double s)  
    {  
        if(s<0)s+=2*pi;  
        int L=1,R=n,m;  
        int r;  
        while(L<=R)  
        {  
            m=(L+R)/2;  
            if(Avg[m]>s+eps)R=m-1;  
            else if(Avg[m+1]>s-eps)return m;  
            else L=m+1;  
        }  
        return n;  
    }  
    P calc(int L,int R,double &s1,double &s2)  
    {  
        if(R<L)R+=n;  
        if((u-v)*(p[L]-v)<-eps)swap(u,v);  
        if((u-v)*(p[R]-v)> eps)swap(u,v);  
        int s=L,e=R,m;  
        while(s+1<e)  
        {  
            m=(s+e)>>1;  
            if((u-v)*(p[m]-v)>-eps)s=m;  
            else e=m;  
        }  
        s1+=sum[s]-sum[L];  
        s2+=sum[R]-sum[e];  
        P r;  
        double t1=(p[e]-p[s])*(u-p[s]);  
        double t2=(p[s]-p[e])*(v-p[e]);  
        r=(u*t2+v*t1)/(t1+t2);  
        s1+=p[s]*r;  
        s2+=r*p[e];  
        return r;  
    }  
    double solve()  
    {  
        u.read();v.read();  
        int k1,k2;  
        k1=mid((u-v).angle());  
        k2=mid((v-u).angle());  
        double t1=(u-v)*(p[k1]-v);  
        double t2=(u-v)*(p[k2]-v);  
        if(t1*t2>-eps)return 0.0;  
        double s1,s2;  
        P a,b;  
        s1=s2=0.0;  
        a=calc(k1,k2,s1,s2);  
        b=calc(k2,k1,s2,s1);  
        s1+=a*b;  
        s2+=b*a;  
        return min(s1,s2)/2.0;  
    }  
    int main()  
    { 
        int m;  
        while(~scanf("%d",&n))  
        {  
            for(int i=0;i<n;i++)p[i].read();  
            n=Poly(n);  
            for(int i=0;i<n;i++)  
            p[i+n]=p[i];  
            int n2=n*2;  
            p[n2]=p[0];  
            for(int i=1;i<=n2;i++)  
            {  
                sum[i]=sum[i-1]+p[i-1]*p[i];  
            }  
      
            for(int i=1;i<=n+1;i++)  
            {  
                Avg[i]=(p[i]-p[i-1]).angle();  
                if(Avg[i]<Avg[i-1]-eps)Avg[i]+=2*pi;  
            }  
            scanf("%d",&m);  
            while(m--)  
            printf("%.6f\n",solve());  
      
        }  
      
      
        return 0;  
    }  
