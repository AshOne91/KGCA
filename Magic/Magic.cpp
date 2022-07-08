// Magic.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    int count = 0;
    printf("홀수 입력 3 부터 :");
    scanf_s("%d", &count, sizeof(int));

    int** map = nullptr;

    map = (int**)malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i)
    {
        *(map + i) = (int*)malloc(sizeof(int) * count);
    }

    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count; ++j)
        {
            *(*(map + i) + j) = 0;
        }
    }

    int y = 0;
    int x = count / 2;
    int value = 1;

    while (1)
    {
        if (value == (count * count) + 1)
        {
            break;
        }
        map[y][x] = value++;

        int tempY = y - 1;
        int tempX = x + 1;

        if (tempY < 0)
        {
            tempY = count - 1;
        }

        if (tempX >= count)
        {
            tempX = 0;
        }

        if (map[tempY][tempX] != 0)
        {
            y = y + 1;
            x = x;
        }
        else
        {
            y = tempY;
            x = tempX;
        }
    }

    for (int y = 0; y < count; ++y)
    {
        for (int x = 0; x < count; ++x)
        {
            printf("%d", map[y][x]);
            printf(" ");
        }
        printf("\r\n");
    }

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
