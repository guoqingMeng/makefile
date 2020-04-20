#include "test1.h"
#include "test2.h"
#include "test.h"
#include "opencv2/opencv.hpp"
#include <assert.h>
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
    Test() : val(100)
    {
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

class AA
{
public:
    AA() {}
    AA(int v) {}
    ~AA() {}

    static void setValue(int v)
    {
        value = v;
        printf("value = %d\n", value);
    }

private:
    static int value;
    // int value;
};
class Point
{
public:
    Point()
    {
    }
    void init()
    {
    }

    static void output()
    {
        printf("value = %d\n", value);
        printf("debug_str_ = %s\n", debug_str_.c_str());
    }

private:
    static std::string debug_str_;
    static int value;
};
std::string Point::debug_str_ = "";
int Point::value = 0;

void read_bin_file_char(std::string file, int size, unsigned char *buffer)
{
    FILE *fp;
    std::cout << file.c_str() << std::endl;
    fp = fopen(file.c_str(), "rb");

    if (fp != NULL)
    {
        int ret = fread(buffer, size * sizeof(unsigned char), 1, fp);

        fclose(fp);
    }
    else
    {
        std::cout << "fp is null!" << std::endl;
        printf("open %s fail errno = %d reason = %s \n", file.c_str(), errno, strerror(errno));
        return;
    }
}
int main()
{
    cv::Mat src[30];
    unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char)*640*480*3);
    read_bin_file_char("/home/q/project/devoloper/mobile_terminal/test/sub/input.bin", 640*480*3, buffer);
    cv::Mat image(cv::Size(480, 640), CV_8UC3, buffer);

    std::vector<cv::Mat> mat_v;
    cv::split(image, mat_v);
    cv::merge(mat_v, image);

    



    unsigned char *buffer1 = (unsigned char*)malloc(sizeof(unsigned char)*640*480*3);
    read_bin_file_char("/home/q/project/devoloper/mobile_terminal/test/sub/result_0.bin", 640*480*3, buffer1);
    cv::Mat image1(cv::Size(480, 640), CV_8UC3, buffer1);

    unsigned char *buffer2 = (unsigned char*)malloc(sizeof(unsigned char)*640*480*3);
    read_bin_file_char("/home/q/project/devoloper/mobile_terminal/test/sub/test_yolo_tmp_3_0.bin", 640*480*3, buffer2);
    cv::Mat image2(cv::Size(480, 640), CV_8UC3, buffer2);

    cv::imshow("image", image);
    cv::imshow("image1", image1);
    cv::imshow("image2", image2);
    cv::waitKey(0);

    return 0;

    Point pt;
    pt.init();
    pt.output();
    return 0;
    AA a;
    a.setValue(100);
    return 0;
    bool f = false;
    assert(f);

    const Test t;
    printf("%d\n", t.get());
    return 0;

    caller *p = new child();
    invoker ivk;
    ivk.setCall(p);
    ivk.fun();
    return 0;
}