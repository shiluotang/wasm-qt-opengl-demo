#ifndef MYWIDGET_H_INCLUDED
#define MYWIDGET_H_INCLUDED

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLWindow>
// 提供 OpenGL API 支持
#include <QOpenGLFunctions>

class MyGLWidget
    : public QOpenGLWidget
    , protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget() {}

protected:
    // 1. 初始化：只運行一次（設定著色器、緩衝區等）
    void initializeGL() override {
        // 初始化封裝好的 OpenGL 函數
        initializeOpenGLFunctions();
        // 設定背景色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    // 2. 視窗縮放：當網頁窗口大小改變時觸發
    void resizeGL(int w, int h) override {
        glViewport(0, 0, w, h);
    }

    // 3. 繪圖：每當需要重繪時觸發（類似 GLFW 的 while 循環體）
    void paintGL() override {
        glClear(GL_COLOR_BUFFER_BIT);
        // 在這裡寫你的渲染邏輯，例如：
        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};


#endif // MYWIDGET_H_INCLUDED
