class tire{
public:
    int nx[N][dif],end[N];
    int root,tot;

    int newNode(){
        for(int i=0;i<26;i++) nx[tot][i]=-1;
        end[tot]=0;
        return tot++;
    }

    void init(){
        tot=0;
        root=newNode();
    }

    void insert(char *s,int id){
        int len=strlen(s);
        int now=root;
        for(int i=0;i<len;i++){
            int c=s[i]-'a';
            if(nx[now][c]==-1) nx[now][c]=newNode();
            now=nx[now][c];
        }
        end[now]=id;
    }

    int query(char *s){
        int len=strlen(s);
        int now=root;
        for(int i=0;i<len;i++){
            int c=s[i]-'a';
            if(nx[now][c]==-1) return -1;
            now=nx[now][c];
        }
        if(end[now]>0) return end[now];
        else return -1;
    }
}tr;