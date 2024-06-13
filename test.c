#include <stdio.h>

int main() {
    char str[100]; // 입력받을 문자열을 저장할 배열
    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin); // fgets 함수를 사용하여 문자열 입력

    printf("입력한 문자열: %s\n", str);
    return 0;
}
