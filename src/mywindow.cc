#include <vector>

#include <QOpenGLWindow>
// 提供 OpenGL API 支持
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QMenu>

#include <logger.h>

#include "mywindow.h"

MyGLWindow::MyGLWindow(QWidget *parent)
    : QOpenGLWindow()
    , _M_vertices()
    , _M_vao()
    , _M_vbo(QOpenGLBuffer::VertexBuffer)
    , _M_prog(0)
    , _M_angle(0.0)
{
    LOGD(__PRETTY_FUNCTION__);
}

MyGLWindow::~MyGLWindow() {
    LOGD(__PRETTY_FUNCTION__);
    makeCurrent();
    if (_M_vao.isCreated())
        _M_vao.destroy();
    if (_M_vbo.isCreated())
        _M_vbo.destroy();
    if (_M_prog)
        delete _M_prog;
    _M_prog = 0;
    doneCurrent();
}

void MyGLWindow::initializeGL() {
    LOGD(__PRETTY_FUNCTION__);
    QObject::connect(this, &QOpenGLWindow::frameSwapped, this, [this]() {
                this->update();
            });
    // 初始化封裝好的 OpenGL 函數
    initializeOpenGLFunctions();
    // 設定背景色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    _M_prog = new QOpenGLShaderProgram();
    _M_prog->addShaderFromSourceCode(
            QOpenGLShader::Vertex,
#ifdef __EMSCRIPTEN__
            "#version 300 es\n"
#else
            "#version 430 core\n"
#endif
            "layout(location = 0) in vec3 aPos;\n"
            // layout on uniform may cause problem
            "uniform mat4 aMat;"
            "void main() {\n"
            " gl_Position = aMat * vec4(aPos, 1.0);\n"
            "}\n"
            );
    _M_prog->addShaderFromSourceCode(
            QOpenGLShader::Fragment,
#ifdef __EMSCRIPTEN__
            "#version 300 es\n"
            "precision mediump float;\n"
#else
            "#version 430 core\n"
#endif
            "out vec4 FragColor;\n"
            "void main() {\n"
            " FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
            "}\n"
            );
    _M_prog->link();
    std::vector<GLfloat> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    vertices.swap(_M_vertices);
    _M_vbo.create();
    _M_vbo.bind();
    _M_vbo.allocate(&_M_vertices[0], sizeof(_M_vertices[0]) * _M_vertices.size());
    _M_vao.create();
    _M_vao.bind();
    // 将vbo与当前vao关联
    _M_vbo.bind();
    _M_prog->enableAttributeArray(0);
    _M_prog->setAttributeBuffer(0, GL_FLOAT, 0, 3);
    _M_vao.release();
    _M_vbo.release();
    _M_prog->release();
}

// 2. 視窗縮放：當網頁窗口大小改變時觸發
void MyGLWindow::resizeGL(int w, int h) {
    LOGD(__PRETTY_FUNCTION__);
    glViewport(0, 0, w, h);
}

// 3. 繪圖：每當需要重繪時觸發（類似 GLFW 的 while 循環體）
void MyGLWindow::paintGL() {
    // LOGD(__PRETTY_FUNCTION__);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _M_prog->bind();
    QMatrix4x4 matrix;
    // 繞 Z 軸旋轉
    matrix.rotate(_M_angle, 0, 0, 1);
    _M_prog->setUniformValue("aMat", matrix);
    _M_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    _M_vao.release();
    _M_prog->release();
    _M_angle += 0.1;
}

void MyGLWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QMenu *menu = new QMenu();
        QObject::connect(menu, &QMenu::aboutToHide, menu, &QObject::deleteLater);
        menu->addAction("啊啊", this, []() { LOGD("xyz"); })
            ->setWhatsThis("xyz");
        menu->addAction("嗯嗯", this, []() { LOGD("uvw"); })
            ->setWhatsThis("uvw");
        // 直接使用 event->globalPos()，无需手动转换
        menu->popup(event->globalPosition().toPoint());
    } else {
        // call super type handle
        QOpenGLWindow::mousePressEvent(event);
    }
}
