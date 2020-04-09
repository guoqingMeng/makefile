#include "test1.h"
#include "test2.h"

class caller
{
public:
    caller() {}
    ~caller() {}
    virtual int add(int x, int y) = 0;

private:
};

class invoker
{
public:
    invoker() : mCaller(NULL) {}
    ~invoker() {}
    void setCall(caller *p)
    {
        mCaller = p;
    }
    void fun()
    {
        int sum = mCaller->add(100, 200);
        printf("sum is %d\n", sum);
    }

private:
    caller *mCaller;
};

class child : public caller
{
public:
    child() {}
    ~child() {}
    int add(int x, int y)
    {
        return x + y;
    }

private:
};

class Test
{
public:
    Test() : val(100) {
        value = 0;
    }
    ~Test() {}
    int get() const
    {
        return val;
    }

private:
    int value;
    const int val;
};

int main()
{
    const Test t;
    printf("%d\n", t.get());
    return 0;

    caller *p = new child();
    invoker ivk;
    ivk.setCall(p);
    ivk.fun();
    return 0;
}