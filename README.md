# C-_OOP
一、定义一个点类、一个线段类、一个圆类、一个三角形类和四边形类。其中点类能移动位置；线段类能计算线段的长度；圆类能计算圆的周长和面积；三角形类能求其面积和周长，且能判断其是否是等腰三角形、等边三角形和直角三角形；四边形类能求其面积和周长，且能判断其是否是菱形、矩形和正方形。要求这些类之间应有继承派生关系或子对象（对象成员）关系。
二、定义Point类
还有Point类作为下面类重要组成，主要定义了点的坐标表示x和y，以及通过成员函数获取私有成员x，y，此外，还有move函数，对点进行移动，移动的单位为ix，iy，同名构造函数Point对类的对象进行初始化，此外需要通过友元函数运算符重载<<和>>。
下面是Point类的内容。
class Point
{
public:
    Point(double i = 0, double j = 0) :x(i), y(j) {}
    void move(double ix = 0, double jy = 0) { x += ix; y += jy; }
    double getX() { return x; }
    double getY() { return y; }
    friend istream & operator >>(istream &, Point &);
    friend ostream & operator <<(ostream &, Point &);
private:
    double x, y;
};
三、定义Line类
Line类和Point类一样，同样是重要组成，在其中使用Point类定义了始末点startP和endP两个点，使用getLength函数获取线段的长度，然后对>>和<<进行重载。
下面为Line类的内容：
class Line
{
public:
    Line(double i1 = 0, double j1 = 0, double i2 = 0, double j2 = 0) :startP(i1, j1), endP(i2, j2) {}
    double getLength() { double dx, dy; dx = startP.getX() - endP.getX(); dy = startP.getY() - endP.getY(); return sqrt(dx*dx + dy * dy); }
    friend istream & operator >>(istream &, Line &);
    friend ostream & operator <<(ostream &, Line &);
private:
    Point startP, endP;
    friend class Quadrangle;//声明友元类
};

四、定义Circle类
Circle的基类是Shape，此类主要提供getLength和getArea两个纯虚函数，供派生类拓展其功能。
Circle类通过全局常量PI计算圆周长和面积。
下面是Circle类的内容：
class Shape
{
public:
    virtual double getArea() = 0;
    virtual double getLength() = 0;
};
//圆类
class Circle :public Shape
{
public:
    Circle(double i = 0, double j = 0, double k = 0) :centerP(i, j), r(k) {}
    double getLength() { return 2 * PI*r; }
    double getArea() { return PI * r*r; }
    void move(double ix = 0, double jy = 0) { centerP.move(ix, jy); }
    friend istream & operator >>(istream &, Circle &);
    friend ostream & operator <<(ostream &, Circle &);
private:
    Point centerP;
    double r;
};
五、在已有类Point、Line、Shape和Circle的基础上创建Triangle类
采用公有继承，继承自Shape类，使用构造函数Triangle，分别使用getLength函数和getArea函数获取三角形的周长和面积。周长计算使用Line类中的getLength函数进行获取，计算面积则采用海伦-秦九韶公式法。
使用typetri函数判断三角形的类型，可以判断等腰三角形、等边三角形、直角三角形、等腰直角三角形。该函数在类外实现，由于函数体较长，详见附录代码。
最后需要对>>和<<进行操作符重载。重载为友元函数。
以下为Triangle类的内容：
class Triangle :public Shape
{
public:
    Triangle(double i1 = 0, double j1 = 0, double k1 = 0,double i2 = 0, double j2 = 0, double k2 = 0) :a(i1, i2,j1,j2), b(j1,j2,k1,k2),c(k1,k2,i1,i2) {}
    double getLength() {
 return a.getLength()+b.getLength()+c.getLength(); }
    double getArea() {
        double s,p;
        p=a.getLength()+b.getLength()+c.getLength();
        p/=2;
     s=sqrt(p*(p-a.getLength())*(p-b.getLength())*(p-c.getLength()));
        return s;
    }
    //判断三角形类型
    void typetri();
    friend istream & operator >>(istream &, Triangle &);
    friend ostream & operator <<(ostream &, Triangle &);
private:
    Line a,b,c;
    int flag=2;
};
六、创建Quadrangle类

同样采用公有继承，是Shape的派生类，同名构造函数提供缺省初始化表，getLength函数获取四边形周长，getArea函数获取四边形面积，由于任意四边形是不稳定的，即面积不是确定的，是不可求的，所以这里采用当判断出四边形的类型之后再进行面积的计算，矩形和正方形均采用长×宽（边长×边长），菱形采用对角线之积的1/2进行计算。
在菱形的面积计算当中，需要用到始末点的坐标，这里对Point类进行友元类声明，即在Point类中加入friend class Quadrangle;语句，这样Quadrangle类就可以访问Point类中的私有成员了。
typerquadr函数用来判断四边形类型，可以判断菱形、正方形和矩形，依据三个图形在边和角之间的差异，具体实现详见附录代码。
class Quadrangle :public Shape
{
public:
    Quadrangle(double i1 = 0, double j1 = 0, double k1 = 0,double m1 = 0,double i2 = 0, double j2 = 0, double k2 = 0,double m2 = 0) :a(i1, i2,j1,j2), b(j1,j2,k1,k2),c(k1,k2,m1,m2),d(m1,m2,i1,i2) {}
    double getLength() { return a.getLength()+b.getLength()+c.getLength()+d.getLength(); }
    double getArea() {
        int op1;
        double s;
        double dx1,dx2,dy1,dy2,p,q;
        dx1=a.startP.getX()-b.endP.getX();
        dx2=d.startP.getX()-a.endP.getX();
        dy1=a.startP.getY()-b.endP.getY();
        dy2=d.startP.getY()-a.endP.getY();
        p=sqrt(dx1*dx1+dy1*dy1);
        q=sqrt(dx2*dx2+dy2*dy2);
        op1=typequadr();
        if(op1==0)
            cout<<"菱形：";
        if(op1==-1)
            cout<<"矩形：";
        if(op1==1)
            cout<<"正方形：";
        if(op1==-1||op1==1)
            s=a.getLength()*b.getLength();
        if(op1==0)
            s=p*q/2;
        return s;
    }
    //判断四边形类型
    int typequadr();
    friend istream & operator >>(istream &, Quadrangle &);
    friend ostream & operator <<(ostream &, Quadrangle &);
private:
    Line a,b,c,d;
    int flag=2;
};
七、运行结果

八、注意事项
在输入三角形和四边形线段坐标时，必须按序首尾相接输入！
输入示例（直接粘贴复制即可）：
0
0
1
1
0
0
0
1
0
0
1
0
0
0
6
1
1
6
0
0
0
1
0
1
1
0
1
0
0
0
1
0
1
1
1
1
2
0
2
0
1
0
0
0
0
1
0
1
1
1
1
1
1
0
1
0
0
0
1
0
1
1
1
1
2
1
2
1
2
0
2
0
1
0
