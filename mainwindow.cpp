#include <QDebug>
#include <QScrollBar>
#include <QTimer>
#include <exception>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initApp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->scrollArea->setAlignment(Qt::AlignVCenter);

    connect(
                ui->fontTuner, SIGNAL(fontUpdated(const QFont&)),
                this, SLOT(updateFont(const QFont&))
    );

    connect(
                ui->fontTuner, SIGNAL(lineSpacingUpdated(int)),
                this, SLOT(updateLineSpacing(int))
    );

    connect(
                ui->plainTextEdit, SIGNAL(textChanged()),
                this, SLOT(updateText())
    );

    connect(
                ui->fontZoom, SIGNAL(valueChanged(int)),
                this, SLOT(updateZoom(int))
    );

    ui->textGLWidget->setBoundingSize(ui->scrollArea->width(), ui->scrollArea->height());
    this->updateFont(ui->fontTuner->currentFont());
    this->updateZoom(ui->fontZoom->value());

    subscribe(this->ui->textGLWidget);
    subscribe(this->ui->fontTuner);

    this->updateText();
    this->errorMessage = new QErrorMessage(this);

    try {
        ensureDirs();
    }
    catch (std::exception& e) {
        this->showException(e, true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFont(const QFont& newFont)
{
    ui->textGLWidget->setFont(newFont);
}

void MainWindow::updateLineSpacing(int lineSpacing)
{
    ui->textGLWidget->setLineSpacing(lineSpacing);
}

void MainWindow::updateText()
{
    auto text = ui->plainTextEdit->toPlainText();
    ui->textGLWidget->setText(text);
}

void MainWindow::updateZoom(int value)
{
    ui->textGLWidget->setZoom(qreal(value) * 4 / 100);
    auto widgetSize = ui->textGLWidget->size();
    auto scrollAreaSize = ui->scrollArea->size();
    ui->scrollAreaWidgetContents->setFixedSize(widgetSize);

    int xpos = (widgetSize.width() - scrollAreaSize.width()) / 2;
    int ypos = (widgetSize.height() - scrollAreaSize.height()) / 2;
    ui->scrollArea->horizontalScrollBar()->setSliderPosition(xpos);
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ypos);
}

void MainWindow::subscribe(StatusSenderBearer *sender)
{
    connect(sender->s, &StatusSender::newStatus, this, &MainWindow::drawStatus);
}

void MainWindow::drawStatus(QString &status)
{
    this->ui->statusbar->showMessage(status);
}

void MainWindow::showError(QString &err, bool fatal)
{
    this->errorMessage->showMessage(err);
    this->errorMessage->exec();
    if (fatal) {
        this->scheduleQuit(1);
    }
}

void MainWindow::showException(std::exception &err, bool fatal)
{
    QString* message = new QString(err.what());
    this->showError(*message, fatal);
    delete message;
}

void MainWindow::scheduleQuit(int returnCode)
{
    QTimer::singleShot(100, this, [returnCode]() {qApp->exit(returnCode);});
}
