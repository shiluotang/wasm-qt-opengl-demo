#include <QtWidgets/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(800, 600);
    w.show();

    // Qt 的事件循環會自動處理 Wasm 的渲染請求
    return a.exec();
}
