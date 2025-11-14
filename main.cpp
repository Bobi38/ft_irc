#include "tt.hpp"

int main(){
    Bigint a(456);
    const Bigint b(789);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << (a + b) << std::endl;
    std::cout << (a+=b) << std::endl;
    std::cout << a << std::endl;

    return 0;
}