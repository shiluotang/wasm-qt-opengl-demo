#ifndef MYWINDOW_H_INCLUDED
#define MYWINDOW_H_INCLUDED

#include <vector>

#include <QOpenGLWindow>
// 提供 OpenGL API 支持
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class MyGLWindow
    : public QOpenGLWindow
    , protected QOpenGLFunctions
{
    Q_OBJECT
public:
    MyGLWindow(QWidget *parent = nullptr);
    virtual ~MyGLWindow();

protected:
    // 1. 初始化：只運行一次（設定著色器、緩衝區等）
    void initializeGL() override;

    // 2. 視窗縮放：當網頁窗口大小改變時觸發
    void resizeGL(int w, int h) override;

    // 3. 繪圖：每當需要重繪時觸發（類似 GLFW 的 while 循環體）
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
private:
    std::vector<GLfloat> _M_vertices;
    QOpenGLVertexArrayObject _M_vao;
    QOpenGLBuffer _M_vbo;
    QOpenGLShaderProgram *_M_prog;
    double _M_angle;
};

#endif // MYWINDOW_H_INCLUDED
