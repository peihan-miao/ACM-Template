1.解同余方程模板
ll a[N][N],x[N];
inline ll gcd(ll a,ll b) {
    return b ? gcd(b, a % b) : a;
}

inline ll lcm(ll a,ll b) {
    return a/gcd(a,b)*b;
}

ll inv(ll a,ll p){
    if(a == 1) return 1;
    return inv(p%a,p)*(p-p/a)%p;
}

int Gauss(int equ,int var) {
    int max_r, col, k;
    for (k = 0, col = 0; k < equ && col < var; k++, col++) {
        max_r = k;
        for(int i = k+1; i < equ;i++)
            if(abs(a[i][col]) > abs(a[max_r][col]))
                max_r = i;
        if(a[max_r][col] == 0){
            k--;
            continue;
        }
        if(max_r != k)
            for(int j = col; j < var+1;j++)
                swap(a[k][j],a[max_r][j]);
        for(int i = k+1;i < equ;i++) {
            if (a[i][col] != 0) {
                ll LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                ll ta = LCM/abs(a[i][col]);
                ll tb = LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col] < 0)tb = -tb;
                for(int j = col;j < var+1;j++)
                    a[i][j] = ((a[i][j]*ta - a[k][j]*tb)%mod + mod)%mod;
            }
        }
    }
    for(int i = k;i < equ;i++)
        if(a[i][col] != 0)
            return -1;//无解
    if(k < var) return var-k;//多解
    for(int i = var-1;i >= 0;i--){
        ll temp = a[i][var];
        for(int j = i+1; j < var;j++) {
            if (a[i][j] != 0) {
                temp -= a[i][j] * x[j];
                temp = (temp % mod + mod) % mod;
            }
        }
        x[i] = (temp*inv(a[i][i],mod))%mod;
    }
    return 0;
}

2.
const double EPS = 1e-9;
inline int sign(double x){return (x>EPS)-(x<-EPS);}
double A[250][250];

bool gauss(int n){
    int i,j,k,r;
    for(i=0;i<n;i++){
        //选一行与r与第i行交换，提高数据值的稳定性
        r=i;
        for(j=i+1;j<n;j++)
            if(fabs(A[j][i]) > fabs(A[r][i]))r=j;
        if(r!=i)for(j=0;j<=n;j++)swap(A[r][j],A[i][j]);
        //i行与i+1~n行消元
        /*  for(k=i+1;k<n;k++){   //从小到大消元，中间变量f会有损失
              double f=A[k][i]/A[i][i];
              for(j=i;j<=n;j++)A[k][j]-=f*A[i][j];
          }*/
        for(j=n;j>=i;j--){   //从大到小消元，精度更高
            for(k=i+1;k<n;k++)
                A[k][j]-=A[k][i]/A[i][i]*A[i][j];
        }
    }
    //判断方程时候有解
    for(i=0;i<n;i++)if(sign(A[i][i])==0)return 0;
    //回代过程
    for(i=n-1;i>=0;i--){
        for(j=i+1;j<n;j++)
            A[i][n]-=A[j][n]*A[i][j];
        A[i][n]/=A[i][i];
    }
    return 1;
}