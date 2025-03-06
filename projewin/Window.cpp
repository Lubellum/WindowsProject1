#include "Window.h"

CWindow::CWindow()
    : mWindow(), mSize(), mScale(), mLocation()
{
}

CWindow::~CWindow()
{
}

void CWindow::Initialize()
{
    mWindow = glfwCreateWindow(1920, 1080, "Sample", nullptr, nullptr);
    mScale = 100.0f; //1を100ドットで表現
    mLocation[0] = 0.0f;
    mLocation[1] = 0.0f;

    if (mWindow == NULL)
    {
        // ウィンドウが作成できなかった
        std::cerr << "Can't create GLFW window." << std::endl;
        exit(1);
    }
    // 現在のウィンドウを処理対象にする
    glfwMakeContextCurrent(mWindow);
    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        // GLEW の初期化に失敗した
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }

    glfwSetWindowUserPointer(mWindow, this);

    glfwSetWindowSizeCallback(mWindow, Resize);
    Resize(mWindow, 1920, 1080);

    glfwSetScrollCallback(mWindow, Wheel);
    
    // 垂直同期のタイミングを待つ
    glfwSwapInterval(1);
}

void CWindow::Terminate()
{
    glfwDestroyWindow(mWindow);
}

bool CWindow::IsActive()
{
    //// 例1
    // ウィンドウを閉じる必要がなければ false を返す
    //// (glfwWindowShouldClose(mwindow) == 0 && glfwGetKey(mwindow, GLFW_KEY_ESCAPE) == 0);
    //if (glfwWindowShouldClose(mWindow) == 0)
    //{
    //    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE))
    //    {
    //        return false;
    //    }
    //    else
    //    {
    //        return true;
    //    }
    //}
    //else
    //{
    //    return false;
    //}

    // 例2
    // (glfwWindowShouldClose(mWindow) || glfwGetKey(mWindow, GLFW_KEY_ESCAPE))
    if (glfwWindowShouldClose(mWindow))
    {
        return false;
    }
    else if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void CWindow::Update()
{
    if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        // マウスカーソルの位置を取得する
        double x, y;
        glfwGetCursorPos(mWindow, &x, &y);

        // マウスカーソルの正規化デバイス座標系上での位置を求める
        mLocation[0] = static_cast<GLfloat>(x) * 2.0f / mSize[0] - 1.0f;
        mLocation[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / mSize[1];
    }

    // キーボードの状態を調べる
    if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mLocation[0] -= 10.0f / mSize[0];
    }
    else if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mLocation[0] += 10.0f / mSize[0];
    }
    else if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mLocation[1] -= 10.0f / mSize[1];
    }
    else if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mLocation[1] += 10.0f / mSize[1];
    }
}

void CWindow::SwapBuffers() const
{
    // カラーバッファを入れ替える
    glfwSwapBuffers(mWindow);
}

void CWindow::Resize(GLFWwindow* const aWindow, const int aWidth, const int aHeight)
{
    // フレームバッファのサイズを調べる
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(aWindow, &fbWidth, &fbHeight);
    // フレームバッファ全体をビューポートに設定する
    glViewport(0, 0, fbWidth, fbHeight);
    // このインスタンスの this ポインタを得る
    CWindow* const instance = static_cast<CWindow*>(glfwGetWindowUserPointer(aWindow));
    if (instance != nullptr)
    {
        // このインスタンスが保持する縦横比を更新する
        //instance->mAspect = static_cast<GLfloat>(aWidth) / static_cast<GLfloat>(aHeight);
        instance->mSize[0] = static_cast<GLfloat>(aWidth);
        instance->mSize[1] = static_cast<GLfloat>(aHeight);
    }
}

// std::clampで代用可
GLfloat CWindow::Correct(const GLfloat aScale, GLfloat aMin, GLfloat aMax)
{
    if (aScale < aMin)
    {
        return aMin;
    }

    if (aScale > aMax)
    {
        return aMax;
    }
}

void CWindow::Wheel(GLFWwindow* const aWindow, double aX, double aY)
{
    CWindow* const instance = static_cast<CWindow*>(glfwGetWindowUserPointer(aWindow));
    if (instance != nullptr)
    { 
        GLfloat nowScale = instance->GetScale();
        nowScale += static_cast<GLfloat>(aY * 5.0);
        const GLfloat correctScale = instance->Correct(nowScale, 50, 200);
        instance->mScale = correctScale;
    }
}

//void CWindow::Wheel(GLFWwindow* const aWindow, double aX, double aY)
//{
//    CWindow* const instance = static_cast<CWindow*>(glfwGetWindowUserPointer(aWindow));
//    GLfloat* aScale = static_cast<GLfloat*>(&(instance->mScale));
//
//    if (instance != nullptr)
//    {
//        if (*aScale > 50 && *aScale <= 200)
//        {
//            // ワールド座標系に対するデバイス座標系の拡大率を更新する
//            *aScale += static_cast<GLfloat>(aY * 5.0);
//        }
//    }
//}


// 縦横比を取り出す
GLfloat CWindow::GetAspect() const
{ 
    return mAspect;
}

// ウィンドウのサイズを取り出す
const GLfloat* CWindow::GetSize() const
{
    return mSize;
}

// ワールド座標系に対するデバイス座標系の拡大率を取り出す
GLfloat CWindow::GetScale() const
{
    return mScale;
}

// 位置を取り出す
const GLfloat* CWindow::GetLocation() const
{
    return mLocation;
}
