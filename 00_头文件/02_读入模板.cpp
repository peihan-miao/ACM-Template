1、快读
struct ioss
{
#define endl '\n'
    static const int LEN = 20000000;
    char obuf[LEN], *oh = obuf;
    std::streambuf *fb;
    ioss()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        fb = cout.rdbuf();
    }
    inline char gc()
    {

        static char buf[LEN], *s, *t, buf2[LEN];
        return (s == t) && (t = (s = buf) + fread(buf, 1, LEN, stdin)), s == t ? -1 : *s++;
    }
    inline ioss &operator>>(long long &x)
    {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
            sgn |= ch == '-';
        }
        for (x = 0; isdigit(ch); ch = gc())
            x = x * 10 + (ch ^ '0');
        sgn && (x = -x);
        return *this;
    }
    inline ioss &operator>>(int &x)
    {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
            sgn |= ch == '-';
        }
        for (x = 0; isdigit(ch); ch = gc())
            x = x * 10 + (ch ^ '0');
        sgn && (x = -x);
        return *this;
    }
    inline ioss &operator>>(char &x)
    {
        static char ch;
        for (; !isalpha(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
        }
        x = ch;
        return *this;
    }
    inline ioss &operator>>(string &x)
    {
        static char ch, *p, buf2[LEN];
        for (; !isalpha(ch) && !isdigit(ch); ch = gc())
            if (ch == -1)
                return *this;
        p = buf2;
        for (; isalpha(ch) || isdigit(ch); ch = gc())
            *p = ch, p++;
        *p = '\0';
        x = buf2;
        return *this;
    }
    inline ioss &operator<<(string &c)
    {
        for (auto &p : c)
            this->operator<<(p);
        return *this;
    }
    inline ioss &operator<<(const char *c)
    {
        while (*c != '\0')
        {
            this->operator<<(*c);
            c++;
        }
        return *this;
    }
    inline ioss &operator<<(const char &c)
    {
        oh == obuf + LEN ? (fb->sputn(obuf, LEN), oh = obuf) : 0;
        *oh++ = c;
        return *this;
    }
    inline ioss &operator<<(int x)
    {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'), x = -x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10)
            buf[++cnt] = x % 10 | 48;
        while (cnt)
            this->operator<<((char)buf[cnt--]);
        return *this;
    }
    inline ioss &operator<<(long long x)
    {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'), x = -x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10)
            buf[++cnt] = x % 10 | 48;
        while (cnt)
            this->operator<<((char)buf[cnt--]);
        return *this;
    }
    ~ioss()
    {
        fb->sputn(obuf, oh - obuf);
    }
} io;

2、__int128读入

inline __int128 read(){
   int X=0,w=0; char ch=0;
   while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
   while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
   return w?-X:X;
}

void print(__int128 x){
	if (!x) return ;
	if (x < 0) putchar('-'),x = -x;
	print(x / 10);
	putchar(x % 10 + '0');
}

3、
template<class T>inline void read(T &res){
    char c;T flag=1;
    while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9')res=res*10+c-'0';res*=flag;
}


4、整行读入，其中包含空格
//注意前后使用getchar()清除多余空字符
int i=0;
while((s[i]=getchar())!='\n') i++;
s[i]=0;


//注意前后使用cin.get()清除多余空字符
getline(cin,s);

在使用char参数或没有参数的情况下，get（）方法读取下一个字符，及时该字符是空格，制表符或换行符。get（char & ch）版本将输
入字符赋给其参数，而get（void）版本将输入字符转换为整型（通常为int）。然后将其返回。









