#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char clearPrompt[10] = "cls";

void showPlan(char buffer[], char isDone) {
    system(clearPrompt);
    printf("\n--------------------------SCHEDULER--------------------------\n\n");
    printf("[ %c ] %s: %s",
        isDone == '1' ? 'V' : '\0',
        buffer,
        isDone == '1' ? "Complete!\n" : "Work in progress...\n"
    );
    printf("\n\n========================================================\n");
    printf(" 0: Quit / 1: Change completion  / 2: Delete / 3: Back..  ");
    printf("\n========================================================\n> ");
}

int execute() {
    FILE *_readFile, *_booleanFile, *_writeFile, *_booleanFileWrite;
    char _fileName[15], *_buffer, isDone[1], date[10], dataFileName[10];
    long _fileSize;

    system(clearPrompt);
    printf("\n--------------------------SCHEDULER--------------------------\n\n");
    printf("  Please Enter the Date > ");
    scanf("%s", date);

    sprintf(dataFileName, "%sb", date);
    _readFile = fopen(date, "r");
    _booleanFile = fopen(dataFileName, "r");

    if (_readFile == NULL) {
        _writeFile = fopen(date, "w");
        _booleanFileWrite = fopen(dataFileName, "w");

        char plan[1001];

        printf("\n--------------------------SCHEDULER--------------------------\n");
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
        int a = isDone[0];
        int selection;
        
        showPlan(_buffer, isDone[0]);

        scanf("%d", &selection);

        if (selection == 1) {
            _booleanFileWrite = fopen(dataFileName, "w");

            char valueToWrite = a == '1' ? '0' : '1';
            
            fwrite(&valueToWrite, sizeof(char), 1, _booleanFileWrite);
            fclose(_booleanFileWrite);

            isDone[0] = &valueToWrite;

            printf("Changed!");
            Sleep(1000);

            break;
        } else if (selection == 2) {
            fclose(_readFile);
            fclose(_writeFile);
            fclose(_booleanFile);
            fclose(_booleanFileWrite);

            char command1[100], command2[100];
            sprintf(command1, "del %s", date);
            system(command1);
            system("y");

            break;
        } else if (selection == 3) {
            system("cls");
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
        ret = execute();
    }

    return 0;
}
