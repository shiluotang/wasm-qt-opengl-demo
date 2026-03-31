#include <QtWidgets/QApplication>

#include "mainwindow.h"

#include "logger.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
            Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    LOGD("QApplication app(argc, argv);");
    QApplication app(argc, argv);

    LOGD("MainWindow w;");
    MainWindow w;
    LOGD("pos.x = " << w.pos().x());
    // w.resize(800, 600);
    // w.ensurePolished();
    LOGD("w.show();");
    w.show();

    // Qt 的事件循環會自動處理 Wasm 的渲染請求
    LOGD("QApplication::exec();");
    int rc = QApplication::exec();
    LOGD("after application execute");
    return rc;
}
