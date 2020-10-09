//minamoto
#include<bits/stdc++.h>
#define R register
#define ll long long
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
const int N=(1<<17)+5;int P;
inline int add(R int x,R int y){return 0ll+x+y>=P?0ll+x+y-P:x+y;}
inline int dec(R int x,R int y){return x-y<0?x-y+P:x-y;}
inline int mul(R int x,R int y){return 1ll*x*y-1ll*x*y/P*P;}
int ksm(R int x,R int y){
    R int res=1;
    for(;y;y>>=1,x=mul(x,x))(y&1)?res=mul(res,x):0;
    return res;
}
const double Pi=acos(-1.0);
struct cp{
    double x,y;
    inline cp(){}
    inline cp(R double xx,R double yy):x(xx),y(yy){}
    inline cp operator +(const cp &b)const{return cp(x+b.x,y+b.y);}
    inline cp operator -(const cp &b)const{return cp(x-b.x,y-b.y);}
    inline cp operator *(const cp &b)const{return cp(x*b.x-y*b.y,x*b.y+y*b.x);}
    inline cp operator *(const double &b)const{return cp(x*b,y*b);}
    inline cp operator ~()const{return cp(x,-y);}
}w[2][N];
int r[21][N],ifac[N],lg[N],inv[N];double iv[21];
void Pre(){
    iv[0]=1;
    fp(d,1,17){
        fp(i,0,(1<<d)-1)r[d][i]=(r[d][i>>1]>>1)|((i&1)<<(d-1));
        lg[1<<d]=d,iv[d]=iv[d-1]*0.5;
    }
    inv[0]=inv[1]=ifac[0]=ifac[1]=1;
    fp(i,2,131072)inv[i]=mul(P-P/i,inv[P%i]),ifac[i]=mul(ifac[i-1],inv[i]);
    for(R int i=1,d=0;i<131072;i<<=1,++d)fp(k,0,i-1)
        w[1][i+k]=cp(cos(Pi*k*iv[d]),sin(Pi*k*iv[d])),
        w[0][i+k]=cp(cos(Pi*k*iv[d]),-sin(Pi*k*iv[d]));
}
int lim,d;
void FFT(cp *A,int ty){
    fp(i,0,lim-1)if(i<r[d][i])swap(A[i],A[r[d][i]]);
    cp t;
    for(R int mid=1;mid<lim;mid<<=1)
        for(R int j=0;j<lim;j+=(mid<<1))
            fp(k,0,mid-1)
                A[j+k+mid]=A[j+k]-(t=w[ty][mid+k]*A[j+k+mid]),
                A[j+k]=A[j+k]+t;
    if(!ty)fp(i,0,lim-1)A[i]=A[i]*iv[d];
}
void MTT(int *a,int *b,int len,int *c){
    static cp f[N],g[N],p[N],q[N];
    lim=len,d=lg[lim];
    fp(i,0,len-1)f[i]=cp(a[i]>>16,a[i]&65535),g[i]=cp(b[i]>>16,b[i]&65535);
    fp(i,len,lim-1)f[i]=g[i]=cp(0,0);
    FFT(f,1),FFT(g,1);
    fp(i,0,lim-1){
        cp t,f0,f1,g0,g1;
        t=~f[i?lim-i:0],f0=(f[i]-t)*cp(0,-0.5),f1=(f[i]+t)*0.5;
        t=~g[i?lim-i:0],g0=(g[i]-t)*cp(0,-0.5),g1=(g[i]+t)*0.5;
        p[i]=f1*g1,q[i]=f1*g0+f0*g1+f0*g0*cp(0,1);
    }
    FFT(p,0),FFT(q,0);
    fp(i,0,lim-1)c[i]=((((ll)(p[i].x+0.5)%P<<16)%P<<16)+((ll)(q[i].x+0.5)<<16)+((ll)(q[i].y+0.5)))%P;
}
void calc(int *a,int *b,int n,int k){
    static int f[N],g[N],h[N],sum[N],isum[N];
    int len=1;while(len<=n+n)len<<=1;
    fp(i,0,n)f[i]=mul(a[i],mul(ifac[i],ifac[n-i]));
    for(R int i=n-1;i>=0;i-=2)f[i]=P-f[i];
    int t=dec(k,n);
    fp(i,0,n+n)g[i]=add(i,t);
    sum[0]=g[0];fp(i,1,n+n)sum[i]=mul(sum[i-1],g[i]);
    isum[n+n]=ksm(sum[n+n],P-2);
    fd(i,n+n,1)isum[i-1]=mul(isum[i],g[i]);
    fp(i,1,n+n)g[i]=mul(isum[i],sum[i-1]);g[0]=isum[0];
    fp(i,n+1,len-1)f[i]=0;fp(i,n+n+1,len-1)g[i]=0;
    
    MTT(f,g,len,h);
    int res=1,p1=k-n,p2=k;
    fp(i,p1,p2)res=1ll*res*i%P;
    res=dec(res,0);
    
    fp(i,0,n)g[i]=(0ll+P+p1+i)%P;
    sum[0]=g[0];fp(i,1,n)sum[i]=mul(sum[i-1],g[i]);
    isum[n]=ksm(sum[n],P-2);
    fd(i,n,1)isum[i-1]=mul(isum[i],g[i]);
    fp(i,1,n)g[i]=mul(isum[i],sum[i-1]);g[0]=isum[0];
    
    for(R int i=0;i<=n;p2=add(p2,1),++i)
        b[i]=mul(h[i+n],res),res=mul(res,mul(g[i],p2+1));
}
int solve(int bl){
    static int a[N],b[N],c[N];
    int s=0;for(int p=bl;p;p>>=1)++s;a[0]=1,--s;
    int qwq=ksm(bl,P-2);
    for(int p=0;s>=0;--s){
        if(p){
            calc(a,b,p,p+1);
            fp(i,0,p)a[p+i+1]=b[i];a[p<<1|1]=0;
            calc(a,b,p<<1,mul(p,qwq));
            p<<=1;fp(i,0,p)a[i]=mul(a[i],b[i]);
        }
        if(bl>>s&1){
            fp(i,0,p)a[i]=mul(a[i],(1ll*bl*i+p+1)%P);
            p|=1,a[p]=1;
            fp(i,1,p)a[p]=mul(a[p],(1ll*bl*p+i)%P);
        }
    }
    int res=1;
    fp(i,0,bl-1)res=mul(res,a[i]);
    return res;
}
int GetFac(int n){
    int s=sqrt(n),res=solve(s);
    fp(i,s*s+1,n)res=mul(res,i);
    return res;
}
int Fac(int n){
    if(n>P-1-n){
        int res=ksm(GetFac(P-1-n),P-2);
        return (P-1-n)&1?res:P-res;
    }
    return GetFac(n);
}
int n;
int main(){
//  freopen("testdata.in","r",stdin);
    scanf("%d%d",&n,&P),Pre();
    printf("%d\n",Fac(n));
    return 0;
}