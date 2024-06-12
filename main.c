#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void todo() {
    printf("1: 할 일 확인");
}

char getFile() {
    FILE *_readFile;
    char _fileName[15], *_buffer;
    long _fileSize;

    printf("학번을 입력하세요: ");  
    scanf("%s", _fileName);

    _readFile = fopen(_fileName, "r");
    if (_readFile == NULL) {
        perror("파일 열기 실패");
        return 1;
    } 
    
    fseek(_readFile, 0, SEEK_END);
    _fileSize = ftell(_readFile);
    rewind(_readFile);

    // 파일 내용을 저장할 메모리 할당
    _buffer = (char*)malloc(sizeof(char) * (_fileSize + 1));
    if (_buffer == NULL) {
        perror("메모리 할당 실패");
        fclose(_readFile);
        return 1;
    }

    // 파일 내용 읽기
    fread(_buffer, sizeof(char), _fileSize, _readFile);
    _buffer[_fileSize] = '\0'; // 문자열 끝에 null 문자 추가

    // 파일 내용 출력
    printf("파일 내용:\n%s\n", _buffer);

    // 자원 해제
    fclose(_readFile);
    return _buffer;
    // free(_buffer);

}


int main() {
    printf("%s", getFile());

    todo();
    
    // char* token = strtok(str, ","); // ","를 구분자로 사용하여 문자열 분할
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, ","); // 다음 분할 위치로 이동
    // }

    return 0;
}