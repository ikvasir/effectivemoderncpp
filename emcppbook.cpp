// ScotMayersBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>
 
using namespace std;

///returning type of variables and some objects using boost library.
template<typename T>
std::string boost_type_name()
{
    return boost::typeindex::type_id_with_cvr<T>().pretty_name();
}


//////////////////////////////////////////////
//PART1_1 template type
//PART1_2 auto
//PART1_3 decltype
//PART1_4 displaing types
//PART2_1 auto more prefereable
//PART2_2 auto is bad
//PART3_1 {} () = 
//PART3_2 nullptr instead NULL and 0
//PART3_3 using insted typedef
//PART3_4 enums
//PART3_5 =deleted
//PART3_6 override
//PART3_7 ::iterator -> ::const_iterator
//PART3_8 noexcept
//PART3_9 constexpr
//PART3_10 const functions - thread free
//PART3_11 special funcs
//PART4_1 unique_ptr 
//PART3_2 shared_ptr 
#define PART4_2
//////////////////////////////////////////////

#ifdef PART1_1

// changing the type of template param between T - T& - T&& to see different type convertion after template oppenning
//T      or T&          or T&&
//TYPE_T or TYPE_T_LREF or TYPE_T_RREF
#define TYPE_T_RREF


template<typename T>

#ifdef TYPE_T
       void f(T param) 
#endif

#ifdef TYPE_T_LREF
       void f(T& param) 
#endif

#ifdef TYPE_T_RREF
        void f(T&& param) 
#endif

{
    cout << " | T =  " << boost_type_name<T>();
    cout << " | param = " << boost_type_name<decltype(param)>() << endl;
};



//function
void someFunc(int, double) {};

#endif

#ifdef PART1_3

#include <vector>
template<typename Container, typename Index>
decltype(auto) containerReturn(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}


struct Point {
    int x, y;
};
#endif

#ifdef PART1_4

struct Widjet { char* name; };
#endif

#ifdef PART2_1
#include <functional>
#endif

#ifdef PART2_2
#include <vector>
#include <type_traits>
#endif

#ifdef PART3_1
#include <string>
class bracer
{public:
    bracer() { cout << "default constructor"<<endl; }
    bracer(string str) {cout<<"one arg constructor : " << str << endl;}
    bracer(string str1, string str2) {cout << "two arg constructor :" << str1 << str2 << endl;}
    bracer(const bracer& br) { cout << "copy constructor" << endl; }
    bracer& operator=(const bracer& other) { cout << "operator= overloading" << endl; return *this; }
    bracer(initializer_list<string> il) { cout << "initializer list constructor" << endl; }
};

#endif

#ifdef PART3_3
#include <string>

void f(int x, const std::string& st) { cout << x << st << endl; };
typedef void (*FPTD)(int, const std::string&);
using FPU = void(*) (int, const std::string&);

#include< map>
#include <vector>

template<typename T>
using mapVec = map<vector<T>, T>;

#endif

#ifdef PART3_5
#include<iostream>
template<class T>
class deleters
{
public: 
    deleters<T>& operator=(const deleters<T>&) = delete;
    deleters<T>(const deleters<T>&) = delete;
    deleters<T>(T _t) : var(_t) {};

private:
    T var;
};


#endif

#ifdef PART3_6

class Base
{

public:
    //virtual int doWork() { std::cout << "Base::doWork\n"; };
    virtual int& doWork()&   { std::cout << "Base::doWork&::data "  << data << endl; return data; };
    virtual int&& doWork()&& { std::cout << "Base::doWork&&::data " << data << endl; return std::move(data); };
    Base&& takeObject() { return std::move(*this); }
private:
private:
    int data = 1;
};

class Derived :public Base
{

public:
   // virtual int doWork()  { std::cout << "Derived::doWork\n"; };
    virtual int& doWork()&   { std::cout << "Derived::doWork::data "   << data << endl;  return data; };
    //virtual int&& doWork()&& { std::cout << "Derived::doWork&&::data " << data << endl;  return std::move(data); };

    Derived&& takeObject() { return std::move(*this); }
private:
    int data = 2;
};

#endif

#ifdef PART3_7
#include <vector>
#endif

#ifdef PART3_8
 void func()noexcept {};
#endif

#ifdef PART3_9
 class X
 {
      int value;
    public:
        constexpr X(const int value_)  noexcept:value(value_){};
        constexpr const int mul(const X& x) const  noexcept{ return value * x.value; }
 };

#endif

#ifdef PART3_10
#include <mutex>
#include <chrono>
 class X
 {
     static int x;
 public:
     void const inc() 
     {
        // std::lock_guard<std::mutex> lg(mx);

         std::cout << x++ <<std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
        // mutable std::mutex mx;
 };

 int X::x = { 0 };

#endif

#ifdef PART3_11
 class test
 {
 public:
     test() { std::cout << "ctor->"; };//ctor
     ~test() { std::cout << "dtor|"; };//dtor
     test(const test& rhs) {};//copy 
     test& operator=( test& rhs) { std::cout << "copy assignment->"; return rhs;};//copy assignment 

     test(test&& rhs) {};//move 
     test& operator=(test&& rhs) { std::cout << "move assignment->"; return rhs; };// move assignment 
 };
#endif

#ifdef PART4_2
#include <vector>
#include <memory>
 class X:public std::enable_shared_from_this<X>
 {
     int _x;
     vector<shared_ptr<X>> vec;
 public:
     X(int&& x) :_x(x) {};
     void add_vec() {vec.emplace_back(shared_from_this()); };
 };

#endif


int main()
{

#ifdef PART1_1

    //general
    int x = 12;
    int& sx = x;
    const int cx = x;
    const int& rx = x;

    //pointers
    int* ptr = &x;
    int* const ptrc1 = &x;
    const int* ptrc2 = &x;
    const int* const ptrcc = &x;

    //arrays
    int arr[] = { 1,2,3 };
    int* ptrToArr = arr;

    const int carr[] = { 1,2 };
    const int* ptrToCArr = arr;

    std::cout << "template<typename T>" << endl
#ifdef TYPE_T
        << "void f(T param)"
#endif
#ifdef TYPE_T_LREF
        << "void f(T& param)"
#endif
#ifdef TYPE_T_RREF
        << "void f(T&& param)"
#endif
        << endl;

    std::cout << "type passed to f | T type| param type" << endl;
    std::cout << boost_type_name<decltype(x)>(); f(x);
    std::cout << boost_type_name<decltype(sx)>(); f(sx);
    std::cout << boost_type_name<decltype(cx)>(); f(cx);
    std::cout << boost_type_name<decltype(rx)>(); f(rx);

    std::cout << boost_type_name<decltype(ptr)>(); f(ptr);
    std::cout << boost_type_name<decltype(ptrc1)>(); f(ptrc1);
    std::cout << boost_type_name<decltype(ptrc2)>(); f(ptrc2);
    std::cout << boost_type_name<decltype(ptrcc)>(); f(ptrcc);

    std::cout << boost_type_name<decltype(arr)>(); f(arr);
    std::cout << boost_type_name<decltype(ptrToArr)>(); f(ptrToArr);
    std::cout << boost_type_name<decltype(carr)>(); f(carr);
    std::cout << boost_type_name<decltype(ptrToCArr)>(); f(ptrToCArr);

    std::cout << boost_type_name<decltype(someFunc)>(); f(someFunc);


#ifdef TYPE_T_RREF
    std::cout << " number 12 "; f(12);
#endif // TYPE_RREF



#endif

#ifdef PART1_2

    auto x(20); cout << boost_type_name<decltype(x)>() << endl;
    auto& y = x; cout << boost_type_name<decltype(y)>() << endl;
    auto&& z = 30; cout << boost_type_name<decltype(z)>() << endl;

    auto a{ 20 }; cout << boost_type_name<decltype(a)>() << endl;
    auto b = { 20 }; cout << boost_type_name<decltype(b)>() << endl;

#endif

#ifdef PART1_3

    Point A;
    std::cout << boost_type_name<decltype(A)>() << endl;

    vector<int> ivec = { 1,2,3 };
    std::cout << boost_type_name<decltype(ivec)>() << endl;

    auto var1 = containerReturn(ivec, 0);
    std::cout << boost_type_name<decltype(var1)>() << endl;

    decltype(var1) var2;
    std::cout << boost_type_name<decltype(var2)>() << endl;


    const int& cx = 1;
    std::cout << boost_type_name<decltype(cx)>() << endl;

    auto x2 = cx;
    std::cout << boost_type_name<decltype(x2)>() << endl;

    decltype(auto) x3 = cx;
    std::cout << boost_type_name<decltype(x3)>() << endl;

    auto lambda = []() {return 3; };
    std::cout << boost_type_name<decltype(lambda)>() << endl;




#endif

#ifdef PART1_4
    int x = 5;
    cout << typeid(x).name() << endl;
    cout << boost_type_name<decltype(x)>() << endl;
    cout << endl;

    const int& y = x;
    cout << typeid(y).name() << endl;
    cout << boost_type_name<decltype(y)>() << endl;
    cout << endl;

    Widjet w;
    const Widjet& z = w;
    cout << typeid(z).name() << endl;
    cout << boost_type_name<decltype(z)>() << endl;



#endif

#ifdef PART2_1

    //using auto in all parts of lambda
    auto lambda = [](auto&& x, auto&& y) { cout << x + y << " " << boost_type_name<decltype(x + y)>() << endl; };
   lambda(2,3);
   lambda(1.4f, 5);
   lambda(1, 5.1f);

   //declaring lambda without auto
   std::function<bool(const int&, const int&)> lambdaF = [](const int& a, const int& b) {return a >= b; };
   cout << std::boolalpha;
   cout << lambdaF(1, 2)<<endl;
   cout << lambdaF(4, 3) << endl;


#endif 

#ifdef PART2_2
   vector<char> vecChar = { 'a','b','c' };
   vector<int> vecInt = { 1,2,3 };
   vector<bool> vecBool = { 1,1,0 };

   auto c = vecChar[1];
   auto i = vecInt[1];
   auto b = vecBool[1];

   cout << boolalpha;
   cout << std::is_same<decltype(c),char>::value << endl;
   cout << std::is_same<decltype(i),int>::value << endl;
   cout << std::is_same<decltype(b),bool>::value << endl;
 
#endif

#ifdef PART3_1

   bracer a; 
   bracer b{};
   a = b;
   bracer c(" 123 ");
   bracer d = c;
  
   bracer e();//function

   bracer f( "1","2" );
   bracer g{ "3","4" };
   bracer h{ {} };
   bracer i({});

#endif

#ifdef PART3_2
   
   auto x = { nullptr };
   auto y = { 0 };
   auto z = { NULL };
   auto c = { false };
   cout << boost_type_name<decltype(x)><<endl;
   cout << boost_type_name<decltype(y)> << endl;
   cout << boost_type_name<decltype(z)> << endl;
   cout << boost_type_name<decltype(c)> << endl;
 
#endif

#ifdef PART3_3

   f(1, "23");

   FPTD ff=f;
   FPU fu = f;
   
   ff(4, std::string("56"));
   fu(7, std::string("89"));


   mapVec<int> mv{ {{1, 2, 3, 4},10} };
   cout << mv[{1, 2, 3, 4}] << endl;

#endif

#ifdef PART3_4
   enum class iEnum: int { a=1, b=2, c=3 };
   cout << static_cast<int>(iEnum::b) << endl;

   constexpr auto lambda = []<typename E>(E enumerator) { return static_cast<underlying_type_t<E>>(enumerator); };
   cout << lambda(iEnum::c);


#endif

#ifdef PART3_5

  //deleters<int> dINT;   //error:no default constructor exists for class "deleters<int>"
   deleters<int> dINT2(4);
   deleters<int> dINT3(5);
   //dINT2 = dINT3;	//error: function "deleters<T>::operator=(const deleters<T> &) [with T=int]"  cannot be referenced -- it is a deleted function

#endif

#ifdef PART3_6


   std::unique_ptr<Base>    ptrBD = std::make_unique <Derived>();
   std::unique_ptr<Base>    ptrBB = std::make_unique <Base>();
   std::unique_ptr<Derived> ptrDD = std::make_unique <Derived>();

   //lvalue version call
   ptrBB.get()->doWork();
   ptrBD.get()->doWork();
   ptrDD.get()->doWork();

   //rvalue version call
   ptrBB.get()->takeObject().doWork();
   ptrBD.get()->takeObject().doWork();
   //ptrDD.get()->takeObject().doWork();
 
  
#endif

#ifdef PART3_7
   vector<int> vec = {0,1,2,3,4,5 };
   auto iter = std::find_if(vec.cbegin(), vec.cend(), [](const int i) {return i % 2; });
   //*iter = -1;
   std::cout << *iter;
#endif

#ifdef PART3_8
    auto lambda = []() {};
    cout << noexcept(lambda())<<endl;
    cout << noexcept(func());

#endif

#ifdef PART3_9

    constexpr const  X x(4);
    constexpr auto y = x.mul(2);
    std::cout << y;
#endif // PART3_9

#ifdef PART3_10


    X x;
    x.inc();
    x.inc();
    x.inc();
    x.inc();
    x.inc();

    thread a([&]() {x.inc();});
    thread b([&]() {x.inc(); });
    thread c([&]() {x.inc(); });
    thread d([&]() {x.inc(); });
    thread e([&]() {x.inc(); });

    a.join();
    b.join();
    c.join();
    d.join();
    e.join();



#endif

#ifdef PART3_11
    std::cout << "t#";
    test t;
    std::cout << std::endl;
    std::cout << "tt#";
    test tt;
    std::cout << std::endl;
    std::cout << "move#";
    t=test();
    std::cout << std::endl;
    std::cout << "copy#";
    t=tt;
    std::cout << std::endl;
   
#endif

#ifdef PART4_2
    X x(12345);

    
    shared_ptr<X> ptr1 = make_shared<X>(x);
    cout << ptr1.use_count() << endl;
    cout  << endl;

    shared_ptr<X> ptr2 = ptr1;
    cout << ptr1.use_count() << endl;
    cout << ptr2.use_count() << endl;
    cout << endl;

    shared_ptr<X> ptr3 = std::move(ptr2);
    cout << ptr1.use_count() << endl;
    cout << ptr2.use_count() << endl;
    cout << ptr3.use_count() << endl;
    

    ptr1.get()->add_vec();
    //ptr2.get()->add_vec();
    ptr3.get()->add_vec();

#endif

    return 0;
}
