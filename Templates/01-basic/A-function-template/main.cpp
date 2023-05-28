#include <iostream>
using namespace std;

template<typename T>
T Max1(T const& a, T const& b)
{
    std::cout << typeid(T).name() << std::endl;
    return b < a ? a : b;
}

template<typename T1, typename T2>
auto Max2(T1 a, T2 b) -> decltype(b < a ? a : b)
{
    return b < a ? a : b;
}

template<typename T1, typename T2>
auto Max3(T1 a, T2 b) -> decltype(true ? a : b) // 这个地方会做类型的转换提升
{
    return b < a ? a : b;
}

template<typename T1, typename T2>
std::common_type_t<T1, T2> Max4(T1 a, T2 b)
{
    return b < a? a : b;
}

template<typename T1,typename T2,
typename RT = std::decay_t<decltype(true ? T1() : T2())> >
RT Max5(T1 a, T2 b)
{
    return b < a ? a : b;
}

template<typename T = std::string>
void f(T arg = "")
{
    std::cout << arg << std::endl;
}

int main()
{
    std::cout << "enter function template" << std::endl;

    std::cout << Max1(17, 58) << std::endl;

    std::cout << Max2<double, int> (66.6, 10) <<  std::endl;

    auto num0 = Max3<float, double>(1000.0f, 100.0);
    std::cout << typeid(num0).name() << std::endl;

    auto num1 = Max4<float, double>(1000.0f, 100.0);
    std::cout << typeid(num1).name() << std::endl;

    auto num2 = Max5<int, short>(10, 100);
    std::cout << typeid(num2).name() << std::endl;

    f(100);

    return 0;
}