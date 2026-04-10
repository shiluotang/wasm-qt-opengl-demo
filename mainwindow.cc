// #include <functional>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QWidget>
#include <QFileDialog>
#include <QIcon>

#include "mywindow.h"
#include "logger.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LOGD(__PRETTY_FUNCTION__);
    this->setWindowIcon(QIcon(":/images/frieren.png"));
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
    QMenu *fileMenu = menuBar()->addMenu("文件");
    QObject::connect(
            fileMenu->addAction("打开"),
            &QAction::triggered,
            this,
            &MainWindow::HandleOpen);
    QObject::connect(
            fileMenu->addAction("关闭"),
            &QAction::triggered,
            this,
            &MainWindow::HandleClose);
    QObject::connect(
            fileMenu->addAction("退出"),
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
    LOGD(__PRETTY_FUNCTION__);
    // it MUST be a heap object to prevent immediate destroy after
    // QFileDialog::open()
    QFileDialog *dlg_ptr = new QFileDialog(this);
    dlg_ptr->setModal(true);
    // // in wasm no file exists!!!
    // dlg_ptr->setFileMode(QFileDialog::ExistingFile);
    // // QFileDialog::openFileContent() will load all content into memory which is
    // // really bad idea for loading large file
    // auto h = std::bind(
    //         &MainWindow::HandleOpenFileContent,
    //         this,
    //         std::placeholders::_1,
    //         std::placeholders::_2);
    QObject::connect(dlg_ptr, &QFileDialog::accepted, [this, dlg_ptr]() {
                if (!!dlg_ptr) {
                    this->HandleFileDialogAccepted(*dlg_ptr);
                    dlg_ptr->deleteLater();
                }
            });
    // You WILL NOT see the local filesystem in wasm!!!
    dlg_ptr->open();
}

void MainWindow::HandleOpenFileContent(
        QString const &filename,
        QByteArray const &ba) {
    LOGD(__PRETTY_FUNCTION__);
    LOGD("file " << filename.toLocal8Bit().constData() << " content is ready");
    QWidget *w = this->centralWidget();
    LOGD("this->centralWidget() = " << w);
    if (!w)
        initRenderPart();
}

void MainWindow::HandleClose() {
    LOGD(__PRETTY_FUNCTION__);
    QWidget *w = this->takeCentralWidget();
    if (!!w)
        w->deleteLater();
}

void MainWindow::HandleQuit() {
    LOGD(__PRETTY_FUNCTION__);
    this->close();
}

void MainWindow::HandleFileDialogAccepted(QFileDialog const &dlg) {
    LOGD(__PRETTY_FUNCTION__);
    QStringList const &files = dlg.selectedFiles();
    for (int i = 0, n = files.size(); i < n; ++i) {
        std::string filename = files.at(i).toLocal8Bit().toStdString();
        LOGD("selected file #" << i << " " << filename);
        char const *mode = "rb";
        FILE *file = std::fopen(filename.c_str(), mode);
        LOGD("fopen(" << filename << ", " << mode << ") = " << file);
        if (!!file) {
            std::fseek(file, 0, SEEK_END);
            int fsize = std::ftell(file);
            LOGD("std::ftell(file = " << file << ") = " << fsize);
            fsize = std::fmin(fsize, 20);
            std::fseek(file, 0, SEEK_SET);
            std::vector<char> buffer(fsize + 1);
            std::fread(&buffer[0], buffer.size() - 1, 1, file);
            LOGD("buffer = " << std::string(&buffer[0], fsize));
            std::fclose(file);
        }
    }
    QWidget *w = this->centralWidget();
    LOGD("this->centralWidget() = " << w);
    if (!w)
        initRenderPart();
}
