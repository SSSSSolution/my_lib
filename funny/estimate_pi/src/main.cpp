#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <thread>
#include <vector>
#include <memory>
#include <future>

double estimate_pi(int64_t n)
{
    int64_t point_in_circle = 0;
    int64_t point_in_total = 0;
    unsigned int seed = static_cast<unsigned int>(rand());
    printf("thread %d's random seed is %u\n", std::this_thread::get_id(), seed);
    for (int64_t i = 0; i < n; i++)
    {
        double x = static_cast<double>(rand_r(&seed))/static_cast<double>(RAND_MAX);
        double y = static_cast<double>(rand_r(&seed))/static_cast<double>(RAND_MAX);
        point_in_total++;
        if ((x*x + y*y) <= 1.0)
        {
            point_in_circle++;
        }
    }

    return 4 * static_cast<double>(point_in_circle) / point_in_total;
}

int main1(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: %s n thread_num\n", argv[0]);
        exit(-1);
    }

    int64_t n = std::atoll(argv[1]);
    assert(n > 0);

    assert(std::atoi(argv[2]) >= 1);
    size_t thread_num = static_cast<size_t>(std::atoi(argv[2]));

    std::vector<std::shared_ptr<std::thread>> thread_pool(128);
    std::vector<std::future<double>> futures(128);
    std::vector<double> results(128);

    for (size_t i = 0; i < thread_num; i++)
    {
        futures[i] = std::async(estimate_pi, n);
    }

    for (size_t i = 0; i < thread_num; i++)
    {
        futures[i].wait();
    }

    for (size_t i = 0; i < thread_num; i++)
    {
        results[i] = futures[i].get();
    }

    double res = 0;
    for (size_t i = 0; i < thread_num; i++)
    {
        printf("thread %d's result: %lf\n", static_cast<int>(i), results[i]);
        res += results[i];
    }
    res /= thread_num;

    printf("the final result is: %lf\n", res);

}

#include <iostream>
#include <chrono>
#include <future>
#include <stdio.h>

class A
{
public:
    A()
    {
        std::cout << " A()" << std::endl;
    }
    ~A()
    {
        std::cout << " ~A()" << std::endl;
    }
};

bool func(std::shared_ptr<A> a)
{
    std::cout << "in func: a.use_count:" << a.use_count() << std::endl;
//    std::this_thread::sleep_for(std::chrono::seconds(1));
    return true;
}

int main()
{
    auto a = std::make_shared<A>();
    std::cout << "before loop: a.use_count:" << a.use_count() << std::endl;
    std::future<bool> fut[3];
    for (int i = 0; i < 3; i++)
    {
        fut[i] = std::async([&a](){
            return func(a);
        });
    }
    std::cout << "after loop: a.use_count:" << a.use_count() << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "fut: " << fut[i].get() << std::endl;
    }
}














