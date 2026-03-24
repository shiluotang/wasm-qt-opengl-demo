#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QWidget>

#include "mywindow.h"

class MainWindow
    : public QMainWindow {
public:
    MainWindow() {
        // 1. 創建 OpenGL 視窗實例
        MyGLWindow *glWindow = new MyGLWindow();

        // 2. 使用 createWindowContainer 將其轉換為 Widget
        // 第一個參數是 window 指針，第二個是父組件
        QWidget *container = QWidget::createWindowContainer(glWindow);

        // 設定容器的最小尺寸，防止佈局塌陷
        container->setMinimumSize(400, 300);

        // 3. 設置 UI 佈局 (例如加入菜單欄)
        // 如果这里用中文，界面上会变成方框，可能是字体的问题
        QMenu *fileMenu = menuBar()->addMenu("File");
        fileMenu->addAction("Open");

        // 4. 將容器放入中心部件
        QWidget *centralWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        // 像普通 Widget 一樣添加
        layout->addWidget(container);
        setCentralWidget(centralWidget);
    }
};

#endif // MAINWINDOW_H_INCLUDED
