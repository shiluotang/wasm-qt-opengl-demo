#include <QtWidgets/QApplication>

#include "mainwindow.h"

#include "logger.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.resize(800, 600);
    w.show();

    // Qt 的事件循環會自動處理 Wasm 的渲染請求
    int rc = QApplication::exec();
    LOGD("after application execute");
    return rc;
}
