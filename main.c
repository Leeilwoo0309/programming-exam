#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/**
 * 파일 읽기하고 이후 작업(사용자 ㅇ입략 -> 일)
 */
int start() {
    FILE *_readFile, *_booleanFile, *_writeFile, *_booleanFileWrite;
    char _fileName[15], *_buffer;
    long _fileSize;
    char isDone[1];

    char date[10], dataFileName[10];
    printf("날짜를 입력해주세요 (예. 240612): ");
    scanf("%s", date);
    
    if (date == -1) { return 1; }

    sprintf(dataFileName, "%sb", date);
    _readFile = fopen(date, "r");
    _booleanFile = fopen(dataFileName, "r");

    if (_readFile == NULL) {
        _writeFile = fopen(date, "w");
        _booleanFileWrite = fopen(dataFileName, "w");

        char plan[1001];
        printf("%s의 하루 일과를 입력하세요: ", date);
        scanf("%s", plan);

        fwrite(plan, sizeof(char), strlen(plan), _writeFile);
        fwrite("0", sizeof(char), 1, _booleanFileWrite);

        fclose(_writeFile);
        fclose(_booleanFileWrite);

    } if (_booleanFile == NULL) {
        printf("오류\n");
        return 1;
    }
    
    // 파일 ㄹㄱ기 준비
    fseek(_readFile, 0, SEEK_END);
    _fileSize = ftell(_readFile);
    rewind(_readFile);

    // 파일 내용을 저장할 메모리 할당하는거
    _buffer = (char*) malloc(sizeof(char) * (_fileSize + 1));

    // 파일 내용 읽는거
    fread(_buffer, sizeof(char), _fileSize, _readFile);
    _buffer[_fileSize] = '\0';

    fread(isDone, sizeof(char), 1, _booleanFile);
    
    printf("%s: ", _buffer);

    while (1) {
        int selection;

        if (isDone[0] == '1') {
            printf("완료됨!\n");
        } else if (isDone[0] == '0') {
            printf("진행중..\n");
        }
        
        printf("----------------------------------------------------\n");
        printf("0: 프로그램 종료 / 1: 계획 수정하기 / 2: 다른 날 보기 \n> ");

        scanf("%d", &selection);

        if (selection == 1) {
            _booleanFileWrite = fopen(dataFileName, "w");
            char valueToWrite = (isDone[0] == '0') ? '1' : '0';
            fwrite(&valueToWrite, sizeof(char), 1, _booleanFileWrite);
            fclose(_booleanFileWrite);

            isDone[1] = &valueToWrite;
        } else if (selection == 2) {
            break;
        } else if (selection == 0) {
            return -1;
        }
    }

    fclose(_readFile);
    free(_buffer);

    return 0;
}


int main() {
    int ret;
    
    while (ret != -1) {
        ret = start();
    }
    
    return 0;
}