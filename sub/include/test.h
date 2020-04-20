
template <class T>
class Father
{
public:
    Father() : value(0) {}
    Father(T v) : value(0) {}
    ~Father() {}
    void add(T x, T y) 
    {
        value = x + y;
    }

private:
    T value;
};

class Invoker
{
public:
    Invoker() {}
    ~Invoker() {}

private:
    Father<float> father;
};