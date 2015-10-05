class Point                                       //基础对象类，要做一个对Point类的智能指针
{
public:
    Point(int xVal = 0, int yVal = 0):x(xVal),y(yVal) { }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }
private:
    int x,y;
};
class RefPtr                                  //辅助类
{//该类成员访问权限全部为private，因为不想让用户直接使用该类
     friend class SmartPtr;      //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类
     RefPtr(Point *ptr):p(ptr), count(1) { }
     ~RefPtr() { delete p; }
      
     int count;                                                     //引用计数
     Point *p;                                                      //基础对象指针
};
  
class SmartPtr                                             //智能指针类
{
public:
     SmartPtr(Point *ptr):rp(new RefPtr(ptr)) { }                                 //构造函数
     SmartPtr(const SmartPtr &sp):rp(sp.rp) { ++rp->count; }            //复制构造函数
     SmartPtr& operator=(const SmartPtr& rhs) {                              //重载赋值操作符
      	++rhs.rp->count;                                                         //首先将右操作数引用计数加1，
      	if(--rp->count == 0)                                                     //然后将引用计数减1，可以应对自赋值
       	delete rp;
      	rp = rhs.rp;
      	return *this;
     }
    ~SmartPtr() {                                            //析构函数
 	      if(--rp->count == 0)                                  //当引用计数减为0时，删除辅助类对象指针，从而删除基础对
          delete rp;
    }
  
private:
 	  RefPtr *rp;                                                //辅助类对象指针
};
  
int main()
{
 Point *p1 = new Point(10, 8);
 SmartPtr sp1(p1);    //此时sp1.rp->count = 1
 SmartPtr sp2(sp1);    //首先将sp1.rp->count赋给sp2.rp->count,之后sp2.rp->count++,这时sp1,sp2的rp是同一个对象
 Point *p2 = new Point(5, 5);
 SmartPtr sp3(p2);
 sp3 = sp1;
  
 return 0;
}


template <typename T>
class SmartPointer{
public:
    SmartPointer(T* ptr){
        ref = ptr;
        ref_count = (unsigned*)malloc(sizeof(unsigned));
        *ref_count = 1;
    }
  
    SmartPointer(SmartPointer<T> &sptr){
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++*ref_count;
    }
  
    SmartPointer<T>& operator=(SmartPointer<T> &sptr){
        if (this != &sptr) {
            if (--*ref_count == 0){
                clear();
                cout<<"operator= clear"<<endl;
            }
            
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++*ref_count;
        }
        return *this;
    }
  
    ~SmartPointer(){
        if (--*ref_count == 0){
            clear();
            cout<<"destructor clear"<<endl;
        }
    }
  
    T getValue() { return *ref; }
    
private:
    void clear(){
        delete ref;
        free(ref_count);
        ref = NULL; // 避免它成为迷途指针
        ref_count = NULL;
    }
   
protected:  
    T *ref;
    unsigned *ref_count;
};

int main_smartpointer(){
    int *ip1 = new int();
    *ip1 = 11111;
    int *ip2 = new int();
    *ip2 = 22222;
    SmartPointer<int> sp1(ip1), sp2(ip2);
    SmartPointer<int> spa = sp1;
    sp2 = spa;
    return 0;
}