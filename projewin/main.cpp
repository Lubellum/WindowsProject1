
// WindowsProject1.cpp : アプリケーションのエントリ ポイントを定義します。
//
#define GLEW_STATIC

#include "framework.h"
#include "WindowsProject1.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Object.h"
#include "Shape.h"
#include "Window.h"
#include "Matrix.h"
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

std::vector<wchar_t> string_to_wchar(std::string in_str)
{
    setlocale(LC_ALL, "Japanese_Japan.932");
    std::vector<wchar_t> out_wstr;
    const size_t newsizew = strlen(in_str.c_str()) + 1;
    size_t convertedChars = 0;
    out_wstr.resize(newsizew);
    mbstowcs_s(&convertedChars, out_wstr.data(), newsizew, in_str.c_str(), _TRUNCATE);
    return out_wstr;
}

std::string ReadFile(std::string path)
{
    std::ifstream file(path);
    std::string line;
    std::string source;
    while (std::getline(file, line))
    {
        source += line + "\n";
    }
    return source;
}

//struct Vertex
//{
//    //GLfloat position[4];
//    GLfloat position[2];
//};

//static constexpr CObject::tVertex vertex[] =
//{
//    { -0.5f, -0.5f },
//    {  0.5f, -0.5f },
//    {  0.5f,  0.5f },
//    { -0.5f,  0.5f }
//};

static constexpr CObject::tVertex vertex[] =
{
    { -2.0f, -2.0f },
    {  2.0f, -2.0f },
    {  2.0f,  2.0f },
    { -2.0f,  2.0f }
};

//static constexpr Vertex vertex[] =
//{
//    {   0.0f,  0.5f, 0.0f, 1.0f },
//    {  -0.5f, -0.5f, 0.0f, 1.0f },
//    {   0.5f, -0.5f, 0.0f, 1.0f }
//};

//static constexpr CObject::tVertex vertex[] =
//{
//    {   0.0f,  0.5f },
//    {  -0.5f, -0.5f },
//    {   0.5f, -0.5f }
//};


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    glfwInit();
    glfwDefaultWindowHints();
    CWindow* window = new CWindow();
    window->Initialize();

    //98,99行目の内容で代替
    //GLFWwindow * const window = glfwCreateWindow(1920, 1280, "Sample", NULL, NULL);
    //glfwMakeContextCurrent(window);
    //glewExperimental = GL_TRUE;
    //if (glewInit() != GLEW_OK)
    //{
    //    // GLEWの初期化に失敗
    //    std::cerr << "Can't initialize GLEW" << std::endl;
    //    return 1;
    //}
    // 後ほど
    //glfwSwapInterval(1);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    //glViewport(0, 0, 1280, 1280);

    const GLuint program = glCreateProgram();

    // todo:初期化あれこれ
    //CWindow player1 = name;
    //CWindow player2(name);
    //CWindow player3 = CWindow(name);

    //std::string vertShaderPath = "C:/Users/azuky/OneDrive/ドキュメント/GitHub/WindowsProject1/shader/shader.vert";
    std::string vertShaderPath("C:/Users/azuky/OneDrive/ドキュメント/GitHub/WindowsProject1/shader/shader.vert");
    //std::string vertShaderPath = std::string ("C:/Users/azuky/OneDrive/ドキュメント/GitHub/WindowsProject1/shader/shader.vert");
    std::string vsource = ReadFile(vertShaderPath);

    // todo: 共通化できそうだけど、、、まだ
    const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* v = (const GLchar*)vsource.c_str();
    glShaderSource(vobj, 1, &v, NULL);
    glCompileShader(vobj);
    glAttachShader(program, vobj);

    std::string fragShaderPath = "C:/Users/azuky/OneDrive/ドキュメント/GitHub/WindowsProject1/shader/shader.frag";
    std::string fsource = ReadFile(fragShaderPath);

    // todo: 共通化できそうだけど、、、まだ
    const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* f = (const GLchar*)fsource.c_str();
    glShaderSource(fobj, 1, &f, NULL);
    glCompileShader(fobj);
    glAttachShader(program, fobj);

    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    // uniform 変数の場所を取得する
    glLinkProgram(program);
    //const GLint aspectLoc = glGetUniformLocation(program, "aspect");
    // const GLint sizeLoc = glGetUniformLocation(program, "size");
    // const GLint scaleLoc = glGetUniformLocation(program, "scale");
    // const GLint locationLoc = glGetUniformLocation(program, "location");
    const GLint modelLoc = glGetUniformLocation(program, "model");
    const GLint modelViewLoc = glGetUniformLocation(program, "modelView");
    const GLint projectionLoc = glGetUniformLocation(program, "projection");

    // todo:
    Shape * shape = new Shape( 2, 4, vertex);

    while ( window->IsActive() )
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(5.0);
        glUseProgram(program);
        window->Update();
        //glUniform1f(aspectLoc, window->GetAspect());
        // glUniform2fv(sizeLoc, 1, window->GetSize());
        // glUniform1f(scaleLoc, window->GetScale());
        // glUniform2fv(locationLoc, 1, window->GetLocation());
        // 
        // 拡大縮小の変換行列を求める
         // 直交投影変換行列を求める
        const GLfloat* const size = window->GetSize();
        const GLfloat scale = (window->GetScale() * 2.0f);
        const CMatrix scaling = CMatrix::Scale(scale / size[0], scale / size[1], 1.0f);
        const GLfloat w = (size[0] / scale);
        const GLfloat h = (size[1] / scale);
        const CMatrix projection = CMatrix::Orthogonal(w, w, -h, h, 1.0f, 10.0f);

        // 平行移動の変換行列を求める
        const GLfloat* const position = window->GetLocation();
        const CMatrix translation = CMatrix::Translate(position[0], position[1], 0.0f);

        // モデル変換行列を求める
        //const CMatrix model = translation * scaling;
        const GLfloat* const location = window->GetLocation();
        const CMatrix model = CMatrix::Translate(location[0], location[1], 0.0f);

        // ビュー変換行列を求める
        //const CMatrix view = CMatrix::LookAt(
        //     0.0f,  0.0f,  0.0f,
        //    -1.0f, -1.0f, -1.0f,
        //     0.0f,  1.0f,  0.0f
        //);

        const CMatrix view = CMatrix::LookAt(
            3.0f, 4.0f, 5.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );

        // モデルビュー変換行列を求める
        const CMatrix modelView = view * model;

        // uniform 変数に値を設定する
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.Data());
        glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, modelView.Data());

        shape->Draw();
        window->SwapBuffers();
        glfwPollEvents();
        //glfwWaitEvents();
        
        //Sleep(16); お試し
    }


    glfwTerminate();
    
    return 0;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
