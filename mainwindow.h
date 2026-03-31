#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QMainWindow>
#include <QFileDialog>

class MainWindow
    : public QMainWindow {
public:
    MainWindow(QWidget *parent = 0);

    void setVSync(bool enabled);

    void initMenu();

    void initRenderPart();

    virtual ~MainWindow();
protected:
    void HandleOpen();

    void HandleOpenFileContent(QString const &filename, QByteArray const &ba);

    void HandleFileDialogAccepted(QFileDialog const &dlg);

    void HandleClose();

    void HandleQuit();
private:
};

#endif // MAINWINDOW_H_INCLUDED
