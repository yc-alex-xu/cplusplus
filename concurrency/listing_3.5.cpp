/*
modification of code from book "CPP-Concurrency-In-Action-2ed-2019"
 */
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include <iostream>
using namespace std;

struct empty_stack : std::exception
{
    const char *what() const throw()
    {
        return "empty stack";
    }
};

template <typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack &other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    threadsafe_stack &operator=(const threadsafe_stack &) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }
    //使用std::shared_ptr可以避免内存分配管理的问题，并避免多次使用new和delete操作。
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T &value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        value = data.top();
        data.pop();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

int main()
{
    threadsafe_stack<int> si;
    si.push(4);
    si.push(5);
    auto p = si.pop();
    cout << "the value pop out is:" << *p << endl;
    if (!si.empty())
    {
        int x;
        si.pop(x);
        cout << "the value pop out is:" << x << endl;
    }
    try
    {
        si.pop();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
