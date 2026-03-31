#include <functional>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QWidget>
#include <QFileDialog>

#include "mywindow.h"
#include "logger.h"
#include "mainwindow.h"

MainWindow::MainWindow() {
    LOGD(__PRETTY_FUNCTION__);
    setVSync(true);
    initMenu();
    initRenderPart();
}

void MainWindow::setVSync(bool enabled) {
    QSurfaceFormat format;
    // 1 表示開啟 VSync，0 表示關閉
    format.setSwapInterval(enabled ? 1 : 0);
    QSurfaceFormat::setDefaultFormat(format);
}

void MainWindow::initMenu() {
    // 3. 設置 UI 佈局 (例如加入菜單欄)
    // 如果这里用中文，界面上会变成方框，可能是字体的问题
    QMenu *fileMenu = menuBar()->addMenu("File");
    QObject::connect(
            fileMenu->addAction("Open"),
            &QAction::triggered,
            this,
            &MainWindow::HandleOpen);
    QObject::connect(
            fileMenu->addAction("Close"),
            &QAction::triggered,
            this,
            &MainWindow::HandleClose);
    QObject::connect(
            fileMenu->addAction("Quit"),
            &QAction::triggered,
            this,
            &MainWindow::HandleQuit);
}

void MainWindow::initRenderPart() {
    LOGD(__PRETTY_FUNCTION__);
    // 1. 創建 OpenGL 視窗實例
    MyGLWindow *glWindow = new MyGLWindow();

    // 2. 使用 createWindowContainer 將其轉換為 Widget
    // 第一個參數是 window 指針，第二個是父組件
    QWidget *container = QWidget::createWindowContainer(glWindow, this);
    // 設定容器的最小尺寸，防止佈局塌陷
    container->setMinimumSize(400, 300);
    // 4. 將容器放入中心部件
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    // 像普通 Widget 一樣添加
    layout->addWidget(container);
    LOGD("this->setCentralWidget(centralWidget = " << centralWidget << ")");
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
    LOGD(__PRETTY_FUNCTION__);
}

void MainWindow::HandleOpen() {
    LOGD("clicked open action");
    QFileDialog dlg;
    dlg.setModal(true);
    auto h = std::bind(
            &MainWindow::HandleOpenFileContent,
            this,
            std::placeholders::_1,
            std::placeholders::_2);
    dlg.getOpenFileContent("Files (*.*)", h);
}

void MainWindow::HandleOpenFileContent(
        QString const &filename,
        QByteArray const &ba) {
    LOGD("file " << filename.toLocal8Bit().constData() << " content is ready");
    QWidget *w = this->centralWidget();
    LOGD("this->centralWidget() = " << w);
    if (!w)
        initRenderPart();
}

void MainWindow::HandleClose() {
    LOGD("clicked close action");
    QWidget *w = this->takeCentralWidget();
    if (!!w)
        w->deleteLater();
}

void MainWindow::HandleQuit() {
    LOGD("clicked quit action");
    this->close();
}
