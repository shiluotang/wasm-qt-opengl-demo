#include <QtWidgets/QApplication>
#include <QFontDatabase>

#include "mainwindow.h"

#include "logger.h"

void initDefaultFont() {
    int fontId = QFontDatabase::addApplicationFont(":/fonts/wqy-zenhei.ttc");
    if (fontId != -1) {
        // 2. 獲取該字體文件對應的字體族名稱
        // 一個字體文件可能包含多個字體族，通常取第一個
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // 3. 創建 QFont 對象並設置為應用程序默認字體
        QFont defaultFont(family);
        // 您也可以在這裡設置默認大小，例如 12px
        defaultFont.setPixelSize(12);
        QApplication::setFont(defaultFont);
    } else {
        LOGD("無法加載字體文件！");
    }
}

void prepareFiles() {
    LOGD("home path = " << QDir::homePath().toStdString());
    QString filename = QDir::homePath() + "/" + "file-write-by-prog.txt";
    QFile file(filename);
    if (!file.open(QFile::WriteOnly))
        LOGD("can't open file for write");
    file.write("hahahaokokok");
    file.close();
    QFile::copy(":/data/test.dat", QDir::homePath() + "/" + "file-copy-from-qrc.txt");
}

int main(int argc, char *argv[]) {
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
            Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    LOGD("QApplication app(argc, argv);");
    QApplication app(argc, argv);
#ifdef __EMSCRIPTEN__
    initDefaultFont();
    prepareFiles();
#endif
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
