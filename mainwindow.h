#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QMainWindow>

class MainWindow
    : public QMainWindow {
public:
    MainWindow();

    void setVSync(bool enabled);

    void initMenu();

    void initRenderPart();

    virtual ~MainWindow();
protected:
    void HandleOpen();

    void HandleOpenFileContent(QString const &filename, QByteArray const &ba);

    void HandleClose();

    void HandleQuit();
private:
};

#endif // MAINWINDOW_H_INCLUDED
