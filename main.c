#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char clearPrompt[10] = "cls";

void showPlan(char buffer[], char isDone) {
    system(clearPrompt);
    printf("----------------------------------------------------\n");
    printf("%s: %s", buffer, isDone == '1' ? "[ V ] Complete!\n" : "[  ] Work in progress...\n");
    // if (isDone[0] == '1') {
    //     printf("Complete!\n");
    // } else if (isDone[0] == '0') {
    //     printf("Processing..\n");
    // }
    printf("----------------------------------------------------\n");
    printf("0: Quit / 1: Change completion  / 2: Delete / 3: Back.. \n> ");
}

int start() {
    FILE *_readFile, *_booleanFile, *_writeFile, *_booleanFileWrite;
    char _fileName[15], *_buffer, isDone[1], date[10], dataFileName[10];
    long _fileSize;

    system(clearPrompt);
    printf("----------------------------------------------------\n");
    printf("Please Enter the Date \n > ");
    scanf("%s", date);

    sprintf(dataFileName, "%sb", date);
    _readFile = fopen(date, "r");
    _booleanFile = fopen(dataFileName, "r");

    if (_readFile == NULL) {
        _writeFile = fopen(date, "w");
        _booleanFileWrite = fopen(dataFileName, "w");

        char plan[1001];

        printf("----------------------------------------------------\n");
        printf("Plan on %s (Don't Enter Space): ", date);
        scanf("%s", plan);
        printf("Complete!\n");
        Sleep(1000);
        

        fwrite(plan, sizeof(char), strlen(plan), _writeFile);
        fwrite("0", sizeof(char), 1, _booleanFileWrite);

        fclose(_writeFile);
        fclose(_booleanFileWrite);

        system(clearPrompt);

        return 0;
    }

    // 파일 읽기 준비
    fseek(_readFile, 0, SEEK_END);
    _fileSize = ftell(_readFile);
    rewind(_readFile);

    // 파일 내용을 저장할 메모리 할당하는거
    _buffer = (char*) malloc(sizeof(char) * (_fileSize + 1));

    // 파일 내용 읽는거
    fread(_buffer, sizeof(char), _fileSize, _readFile);
    _buffer[_fileSize] = '\0';

    fread(isDone, sizeof(char), 1, _booleanFile);    

    while (1) {
        int selection;
        
        // system(clearPrompt);
        // printf("----------------------------------------------------\n");
        // printf("%s: %s", _buffer, isDone[0] == '1' ? "[ V ] Complete!\n" : "[  ] Work in progress...\n");
        // // if (isDone[0] == '1') {
        // //     printf("Complete!\n");
        // // } else if (isDone[0] == '0') {
        // //     printf("Processing..\n");
        // // }
        // printf("----------------------------------------------------\n");
        // printf("0: Quit / 1: Change completion  / 2: Delete / 3: Back.. \n> ");
        showPlan(_buffer, isDone[0]);

        scanf("%d", &selection);

        if (selection == 1) {
            _booleanFileWrite = fopen(dataFileName, "w");

            char valueToWrite = (isDone[0] == '0') ? '1' : '0';
            
            fwrite(&valueToWrite, sizeof(char), 1, _booleanFileWrite);
            fclose(_booleanFileWrite);



            isDone[1] = &valueToWrite;

            break;
        } else if (selection == 2) {
            system("clear");
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
