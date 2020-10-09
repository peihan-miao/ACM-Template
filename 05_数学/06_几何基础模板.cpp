class Point{
public:
    double x, y;
    Point(double x = 0,double y = 0) :x(x), y(y) {}
    Point operator + (Point a){
        return Point(x + a.x, y + a.y);
    }
    Point operator - (Point a){
        return Point(x - a.x, y - a.y);
    }
    bool operator < (const Point& a) const{
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
    bool operator == (Point a){
        if (x == a.x && y == a.y) return true;
        return false;
    }
    double abs(void){
        return sqrt(x * x + y * y);
    }
};

typedef Point Vector;

//叉积
double cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}

//点积
double dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y;
}

//判断方向
bool isclock(Point p0, Point p1, Point p2){
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) < 0) return true;
    return false;
}

typedef vector<Point> Polygon;

//求凸包
Polygon andrewScan(Polygon s) {
    Polygon u, l;
    if (s.size() < 3) return s;
    sort(s.begin(), s.end());
    u.push_back(s[0]);
    u.push_back(s[1]);
    l.push_back(s[s.size() - 1]);
    l.push_back(s[s.size() - 2]);
    for (int i = 2; i < s.size(); i++){
        for (int n = u.size(); n >= 2 && isclock(u[n - 2], u[n - 1], s[i]) != true; n--)
            u.pop_back();
        u.push_back(s[i]);
    }
    for (int i = s.size() - 3; i >= 0; i--){
        for (int n = l.size(); n >= 2 && isclock(l[n - 2], l[n - 1], s[i]) != true; n--)
            l.pop_back();
        l.push_back(s[i]);
    }
    for (int i = 1; i < u.size() - 1; i++)
        l.push_back(u[i]);
    return l;
}

//判断符号
int signal(double x){
    if(fabs(x)<eps)
        return 0;
    else
        return x<0?-1:1;
}

//判断线段相交
bool segmentCross(Point a,Point b,Point c,Point d){
//快速排斥实验
    if(max(c.x,d.x)<min(a.x,b.x)||max(a.x,b.x)<min(c.x,d.x)||max(c.y,d.y)<min(a.y,b.y)||max(a.y,b.y)<min(c.y,d.y)){
        return false;
    }
    //跨立实验
    if(cross(a-d,c-d)*cross(b-d,c-d)>0||cross(d-b,a-b)*cross(c-b,a-b)>0){
        return false;
    }
    return true;
}

//得到多边形面积
double getArea(Polygon s){
    double sum=0;
    double x1,y1,x2,y2;
    int n = s.size()-1;
    for(int i=1;i<=n-1;i++){
        x1=s[i].x-s[0].x;
        y1=s[i].y-s[0].y;
        x2=s[i+1].x-s[0].x;
        y2=s[i+1].y-s[0].y;
        sum+=(x1*y2-x2*y1)/2;
    }
    return fabs(sum);
}

//判断点是否存在于多边形中
bool isOk(Point x,double area,Polygon s){
    double sum=0;
    int n = s.size();
    for(int i=0;i<n;i++){
        Point &y = s[i],&z = s[(i+1)%n];
        sum+=fabs(cross(y-x,z-x))/2;
    }
    return fabs(sum-area)<=eps;
}


已知平面三个点，求外接圆圆心
double x=((y2-y1)*(y3*y3-y1*y1+x3*x3-x1*x1)-(y3-y1)*(y2*y2-y1*y1+x2*x2-x1*x1))/(2*(x3-x1)*(y2-y1)-2*((x2-x1)*(y3-y1)));
double y=((x2-x1)*(x3*x3-x1*x1+y3*y3-y1*y1)-(x3-x1)*(x2*x2-x1*x1+y2*y2-y1*y1))/(2*(y3-y1)*(x2-x1)-2*((y2-y1)*(x3-x1)));
printf("%.3lf %.3lf\n",x,y);


如何判断三角形是钝角、直角、还是锐角三角形
1、设c为最长的边
    若a^2+b^2<c^2,则为钝角三角形
    若a^2+b^2=c^2,则为直角三角形
    若a^2+b^2>c^2,则为锐角三角形
2、三点中，若存在点乘<0，则说明存在钝角
//i为顶点
bool check(int i,int j,int k){
    return ((p[i].x-p[j].x)*(p[i].x-p[k].x)+(p[i].y-p[j].y)*(p[i].y-p[k].y))<0;
}

点乘是向量的内积，叉乘是向量的外积
点乘，也叫数量积。结果是一个向量在另一个向量方向上投影的长度，是一个标量。
叉乘，也叫向量积。结果是一个和已有两个向量都垂直的向量。

在一条直线上，同向是叉乘为0，点乘为正，反向为叉乘为0，点乘为负

向量的点乘:a * b，x1*x2+y1*y2
公式：a * b = |a| * |b| * cosθ 点乘又叫向量的内积、数量积，是一个向量和它在另一个向量上的投影的长度的乘积；
是标量。 点乘反映着两个向量的“相似度”，两个向量越“相似”，它们的点乘越大。

向量的叉乘：a ∧ b，x1*y2-x2*y1
a ∧ b = |a| * |b| * sinθ 向量积被定义为： 模长：（在这里θ表示两向量之间的夹角(共起点的前提下)（0° ≤ θ ≤ 180°），
它位于这两个矢量所定义的平面上。） 方向：a向量与b向量的向量积的方向与这两个向量所在平面垂直，且遵守右手定则。
（一个简单的确定满足“右手定则”的结果向量的方向的方法是这样的：若坐标系是满足右手定则的，当右手的四指从a以不超过180度的转角转向b时，
竖起的大拇指指向是c的方向。c = a ∧ b）

3、现有一个边长为正整数的三角形，问能否以其三个顶点为圆心画三个圆，使三个圆两两外切
    只要满足a+b>c，则必定有解，且结果为(a+b-c)/2,(a+c-b)/2,(b+c-a)/2;













