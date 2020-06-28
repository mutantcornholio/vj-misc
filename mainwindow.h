#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QErrorMessage>
#include "fonttuner.h"
#include "statussender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFont(const QFont&);
    void updateLineSpacing(int);
    void updateText();

    void updateZoom(int value);
    void drawStatus(QString &);
    void showException(std::exception &err, bool fatal = false);
    void showError(QString &err, bool fatal = false);
    void scheduleQuit(int returnCode);

private:
    Ui::MainWindow *ui;
    void subscribe(StatusSenderBearer *);
    QErrorMessage *errorMessage;
};
#endif // MAINWINDOW_H
