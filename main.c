#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void todo() {
    printf("1: 할 일 확인");
}

char getFile() {
    FILE *file;
    char fileName[15];
    char *_kimchiContent[16383], temp;

    printf("학번을 입력하세요: ");  
    scanf("%s", fileName);

    file = fopen("a20622.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }  

    fclose(file);

    return _kimchiContent;
}


int main() {
    getFile();

    todo();
    
    // char* token = strtok(str, ","); // ","를 구분자로 사용하여 문자열 분할
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, ","); // 다음 분할 위치로 이동
    // }

    return 0;
}