#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void updateText();

    void updateZoom(int value);
    void drawStatus(QString &);

private:
    Ui::MainWindow *ui;
    void subscribe(StatusSenderBearer *);
};
#endif // MAINWINDOW_H
