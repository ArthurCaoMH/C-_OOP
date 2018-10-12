#include <iostream>
#include <math.h>
using namespace std;
const double PI = 3.141593;
//点类
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
istream & operator >>(istream & in, Point & p) { cout << "点的坐标为："; cin >> p.x >> p.y; return in; }
ostream & operator <<(ostream & out, Point & p) { out << "点的坐标为："; cout << "(" << p.x << "," << p.y << ")"; return out; }
//线段类
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
istream & operator >>(istream & in, Line & lin) { cout << "线段始"; cin >> lin.startP; cout << "线段终"; cin >> lin.endP; return in; }
ostream & operator <<(ostream & out, Line & lin) { cout << "线段始" << lin.startP << ",线段终" << lin.endP << endl; return out; }
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
istream & operator >>(istream & in, Circle & cir) { cout << "圆心"; in >> cir.centerP; cout << "圆的半径长度为："; in >> cir.r; return in; }
ostream & operator <<(ostream & out, Circle & cir) { out << "圆心" << cir.centerP << ",圆的半径长度为：" << cir.r << endl; return out; }
//三角形类
class Triangle :public Shape
{
public:
    Triangle(double i1 = 0, double j1 = 0, double k1 = 0,double i2 = 0, double j2 = 0, double k2 = 0) :a(i1, i2,j1,j2), b(j1,j2,k1,k2),c(k1,k2,i1,i2) {}
    double getLength() { return a.getLength()+b.getLength()+c.getLength(); }
    double getArea() {
        double s,p;
        p=a.getLength()+b.getLength()+c.getLength();
        p/=2;
        s= sqrt(p*(p-a.getLength())*(p-b.getLength())*(p-c.getLength()));
        return s;
    }
    //判断三角形是否是等腰三角形、等边三角形和直角三角形
    void typetri();
    friend istream & operator >>(istream &, Triangle &);
    friend ostream & operator <<(ostream &, Triangle &);
private:
    Line a,b,c;
    int flag=2;
};
istream & operator >>(istream & in, Triangle & tri) { cout << "边1:\n"; in >> tri.a; cout << "边2:\n"; in >> tri.b; cout << "边3:\n"; in >> tri.c; return in; }
ostream & operator <<(ostream & out, Triangle & tri) { out << "边1，" << tri.a << "边2，" << tri.b<<"边3，"<<tri.c<< endl; return out; }
void Triangle::typetri()
{
        double x,y,z;
        x=a.getLength();
        y=b.getLength();
        z=c.getLength();
        if(x==y||x==z||y==z)
           {
            flag=0;
            if(x==y && y==z)
                flag=1;
            //允许浮点数计算误差
            if(fabs(x*x+y*y-z*z)<=0.001||fabs(x*x==y*y+z*z)<=0.001||fabs(y*y==z*z+x*x)<=0.001)
                flag=-2;
        }
        if(fabs(x*x+y*y-z*z)<=0.001||fabs(x*x==y*y+z*z)<=0.001||fabs(y*y==z*z+x*x)<=0.001)
            flag=-1;
        if(flag==-2)
            cout<<"等腰直角三角形\n";
        if(flag==-1)
            cout<<"直角三角形\n";
        if(flag==0)
            cout<<"等腰三角形\n";
        if(flag==1)
            cout<<"等边三角形\n";
        if(flag==2)
            cout<<"普通三角形\n";
    }
//四边形类，输入要求，四个点是顺序连接的
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
istream & operator >>(istream & in, Quadrangle & quadr) { cout << "边1:\n"; in >> quadr.a; cout << "边2:\n"; in >> quadr.b; cout << "边3:\n"; in >> quadr.c;cout << "边4:\n"; in >> quadr.d; return in; }
ostream & operator <<(ostream & out, Quadrangle & quadr) { out << "边1，" << quadr.a << "边2，" << quadr.b<<"边3，"<<quadr.c<<"边4，"<<quadr.d<< endl; return out; }

int Quadrangle::typequadr()
{
        double x,y,z,p,q1,dx,dy;
        x=a.getLength();
        y=b.getLength();
        z=c.getLength();
        p=d.getLength();
        dx = a.startP.getX() - b.endP.getX();
        dy = a.startP.getY() - b.endP.getY();
        q1=dx*dx + dy * dy;
        if(x==y&&y==z&&z==p)
           {
            flag=0;//至少是菱形
            if(q1==x*x+y*y)
                flag=1;//勾股定理判断直角
        }
        if(x==z&&y==p&&(q1==x*x+y*y))
        {
            flag=-1;//至少是矩形
            if(x==y)
                flag=1;//正方形
        }
        return flag;
    }
void main()
{
    Point p1, p2;   Line l1, l2;   Circle c1, c2;Triangle t1,t2;Quadrangle q1,q2;
    cin >> p1 >> p2 >> l1 >> l2 >> c1 >> c2>>t1>>t2>>q1>>q2;
    cout << "两条线段的长度分别为：" << l1.getLength() << "," << l2.getLength() << endl;
    cout << "两个圆的周长分别为：" << c1.getLength() << "," << c2.getLength() << endl;
    cout << "两个圆的面积分别为：" << c1.getArea() << "," << c2.getArea() << endl;

    cout<<"两个三角形的周长分别为："<<t1.getLength()<<","<<t2.getLength()<<endl;
    cout<<"两个三角形的面积分别为："<<t1.getArea()<<","<<t2.getArea()<<endl;
    cout<<"两个三角形的类型分别是：";
    t1.typetri();
    cout<<"，";
    t2.typetri();
    cout<<endl;
    cout<<"两个四边形的周长分别为："<<q1.getLength()<<","<<q2.getLength()<<endl;
    cout<<"两个四边形类型和面积分别为："<<q1.getArea()<<","<<q2.getArea()<<endl;
    cout<<endl;
    cout << p1 << p2 << l1 << l2 << c1 << c2 <<t1<<t2<<q1<<q2<< endl;
}
