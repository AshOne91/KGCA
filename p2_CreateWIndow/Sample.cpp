#include "Sample.h"

int APIENTRY wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    Sample demo;
    demo.Init();
    demo.Run();
    demo.Release();
    MessageBox(NULL, L"title", L"title",MB_OK);

    return 0;
}



bool Sample::Init()
{
    TWindow::Init();
    return false;
}

bool Sample::Frame()
{
    return false;
}

bool Sample::Render()
{
    return false;
}

bool Sample::Release()
{
    return false;
}
