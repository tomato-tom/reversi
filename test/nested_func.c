#include <stdio.h>

// 2つの整数を加算する関数
int add(int a, int b) {
    return a + b;
}

// 2つの整数を減算する関数
int subtract(int a, int b) {
    return a - b;
}

int main() {
    // 関数ポインタの宣言
    int (*operation)(int, int);
    
    // 関数ポインタにaddのアドレスを代入
    operation = add;
    
    // 関数ポインタを通じてadd関数を呼び出し
    printf("10 + 5 = %d\n", operation(10, 5));
    
    // 関数ポインタにsubtractのアドレスを代入
    operation = subtract;
    
    // 関数ポインタを通じてsubtract関数を呼び出し
    printf("10 - 5 = %d\n", operation(10, 5));
    
    return 0;
}
