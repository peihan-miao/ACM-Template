1.KMP模板

//求取循环节的基础
void getNext(){
    int i,j;
    j=nx[0]=-1;
    i=0;
    while(i<n){
        while(-1!=j && x[i]!=x[j]) j=nx[j];
        nx[++i]=++j;
    }
}

//消除循环节
void getNext(){
    int i,j;
    j=nx[0]=-1;
    i=0;
    while(i<m){
        while(-1!=j && x[i]!=x[j]) j=nx[j];
        if(x[++i]==x[++j]) nx[i] = nx[j];
        else nx[i]=j;
    }
}

//返回x在y中匹配次数，包含重叠
int KMP() {
    int i, j;
    int ans = 0;
    getNext(x, m, nx);
    i = j = 0;
    while (j < n) {
        while (i != -1 && x[i] != y[j])
            i = nx[i];
        i++; j++;
        if (i == m)
            ans++;
    }
    return ans;
}

2、扩展KMP
void pre_EKMP(){
    nx[0]=m;
    int j = 0;
    while(j+1<m&&x[j]==x[j+1]) j++;
    nx[1]=j;
    int k = 1;
    for(int i=2;i<m;i++){
        int p = nx[k]+k-1;
        int L = nx[i-k];
        if(i+L<p+1) nx[i]=L;
        else{
            j = max(0,p-i+1);
            while(i+j<m&&x[i+j]==x[j]) j++;
            nx[i]=j;
            k=i;
        }
    }
}

void EKMP(){
    pre_EKMP();
    int j = 0;
    while(j<n&&j<m&&x[j]==y[j]) j++;
    extend[0]=j;
    int k = 0;
    for(int i=1;i<n;i++){
        int p = extend[k]+k-1;
        int L = nx[i-k];
        if(i+L<p+1) extend[i]=L;
        else{
            j = max(0,p-i+1);
            while(i+j<n&&j<m&&y[i+j]==x[j]) j++;
            extend[i]=j;
            k=i;
        }
    }
}

3、Manacher
//内存开两倍
const int N = 110100;
char Ma[N];
int Mp[N],top;
void Manacher(char *s,int len){
    top=0;
    Ma[top++]='$';
    Ma[top++]='#';
    for(int i=0;i<len;i++){
        Ma[top++]=s[i];
        Ma[top++]='#';
    }
    Ma[top]=0; Mp[top]=0;
    int id=0,mx=0;
    for(int i=1;i<top;i++){
        Mp[i]=mx>i?min(Mp[2*id-i],mx-i):1;
        while(Ma[i+Mp[i]]==Ma[i-Mp[i]]) Mp[i]++;
        if(i+Mp[i]>mx){
            mx=i+Mp[i];
            id=i;
        }
    }
}
