#include <iostream>

using namespace std;

void learn_lambda_func_1()
{
    int value_1 = 1;
    //与参数传值类似，值捕获的前提是变量可以拷贝，不同之处则在于，被捕获的变量在lambda 表达
    //式被创建时拷贝，而非调用时才拷贝：
    auto copy_value_1 = [value_1] {
        return value_1;
    };
    value_1 = 100;
    auto stored_value_1 = copy_value_1();
    // 这时, stored_value_1 == 1, 而value_1 == 100.
    // 因为copy_value_1 在创建时就保存了一份value_1 的拷贝
}

void learn_lambda_func_2()
{
    int value_2 = 1;
    auto copy_value_2 = [&value_2] {
        return value_2;
    };
    value_2 = 100;
    auto stored_value_2 = copy_value_2();
    // 这时, stored_value_2 == 100 , value_1 == 100.
    // 因为copy_value_2 保存的是引用
}

/*
手动书写捕获列表有时候是非常复杂的，这种机械性的工作可以交给编译器来处理，这时候可以在
捕获列表中写一个& 或= 向编译器声明采用引用捕获或者值捕获.
 */
void learn_lambda_func_3()
{
    int value_2 = 1;
    auto copy_value_2 = [&] {
        return value_2;
    };
    value_2 = 100;
    auto stored_value_2 = copy_value_2();
    // 这时, stored_value_2 == 100 , value_1 == 100.
    // 因为copy_value_2 保存的是引用
}

//泛型Lambda
auto add = [](auto x, auto y) {
    return x + y;
};

// Lambda 表达式的本质是一个和函数对象类型相似的类类型（称为闭包类型）的对象（称为闭包对
// 象），当Lambda 表达式的捕获列表为空时，闭包对象还能够转换为函数指针值进行传递
using foo = void(int); // 定义函数类型, using 的使用见上一节中的别名语法
void functional(foo f) // 定义在参数列表中的函数类型foo 被视为退化后的函数指针类型foo *
{
    f(1); // 通过函数指针调用函数
}

int main()
{
    learn_lambda_func_1();
    learn_lambda_func_2();
    learn_lambda_func_3();

    auto s1 = add(1, 2);
    auto s2 = add(3.3, 4.4);

    auto f = [](int value) {
        std ::cout << value << std ::endl;
    };
    functional(f); // 传递闭包对象， 隐式转换为foo * 类型的函数指针值
    f(1);          // lambda 表达式调用
}