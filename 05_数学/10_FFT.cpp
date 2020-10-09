inline int lowbit(int x) { return x & -x; }

int calc(int n) {
    int k = 0;
    while ((1 << k) < n) k++;
    return k;
}

// FFT
const double pi = acos(-1.0);

const int N = (1 << 20);
using Complex = complex<double>;

void change(Complex p[], int n) {
    int k = calc(n);
    n = 1 << k;
    vector<int> r(n, 0);
    for (int i = 0; i < n; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int i = 0; i < n; i++) if (i < r[i]) swap(p[i], p[r[i]]);
}

void FFT(Complex p[], int n, int type) {
    change(p, n);
    for (int mid = 1; mid < n; mid <<= 1) { //待合并区间的长度的一半
        Complex wn(cos(pi / mid), type * sin(pi / mid)); //单位根
        for (int R = mid << 1, j = 0; j < n; j += R) { //R是区间的长度，j表示前已经到哪个位置了
            Complex w(1, 0); //幂
            for (int k = 0; k < mid; k++, w = w * wn) { //枚举左半部分
                Complex x = p[j + k], y = w * p[j + mid + k]; //蝴蝶效应
                p[j + k] = x + y;
                p[j + mid + k] = x - y;
            }
        }
    }
}

1.大数相乘
给出两个n位10进制整数x和y，你需要计算x*y。
int n,rev[N];
char x[N],y[N];
Complex a[N],b[N];
int ans[N];

void fft(Complex p[],int n,int type){
    for(int i=0;i<n;i++) if(i<rev[i]) swap(p[i],p[rev[i]]);
    for (int mid = 1; mid < n; mid <<= 1) { //待合并区间的长度的一半
        Complex wn(cos(pi / mid), type * sin(pi / mid)); //单位根
        for (int R = mid << 1, j = 0; j < n; j += R) { //R是区间的长度，j表示前已经到哪个位置了
            Complex w(1, 0); //幂
            for (int k = 0; k < mid; k++, w = w * wn) { //枚举左半部分
                Complex x = p[j + k], y = w * p[j + mid + k]; //蝴蝶效应
                p[j + k] = x + y;
                p[j + mid + k] = x - y;
            }
        }
    }
}

int main() {
    scanf("%d",&n);
    scanf("%s%s",x,y);
    for(int i=n-1;i>=0;i--) a[n-1-i].real(x[i]-'0');
    for(int i=n-1;i>=0;i--) b[n-1-i].real(y[i]-'0');
    int top=1,bit=0;
    while(top<=(n<<1)) top<<=1,bit++;
    for(int i=0;i<top;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    fft(a,top,1); fft(b,top,1);
    for(int i=0;i<top;i++) a[i]=a[i]*b[i];
    fft(a,top,-1);
    for(int i=0;i<top;i++){
        ans[i]+=(int)(a[i].real()/top+0.5);
        if(ans[i]>=10){
            ans[i+1]+=ans[i]/10; ans[i]%=10; top+=(i==top);
        }
    }
    while(!ans[top]&&top>=1) top--;
    top++;
    while(--top>=0) printf("%d",ans[top]);
}

