#include <QDebug>
#include <QScrollBar>
#include <QTimer>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QUrl>
#include <exception>

#include "mainwindow.h"
#include "commons.h"
#include "ui_mainwindow.h"
#include "initApp.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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

    connect(
                ui->refreshFilesList, SIGNAL(clicked()),
                this, SLOT(refreshFileList())
    );

    connect(
                ui->textFilesList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                this, SLOT(fileSelected(QListWidgetItem*, QListWidgetItem*))
    );

    connect(
                ui->saveFile, SIGNAL(clicked()),
                this, SLOT(saveFileClicked())
    );

    connect(
                ui->openInFinder, SIGNAL(clicked()),
                this, SLOT(openInFinderClicked())
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
        this->refreshFileList();
    } catch (std::exception& e) {
        this->showException(e, true);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateFont(const QFont& newFont) {
    ui->textGLWidget->setFont(newFont);
}

void MainWindow::updateLineSpacing(int lineSpacing) {
    ui->textGLWidget->setLineSpacing(lineSpacing);
}

void MainWindow::updateText() {
    auto text = ui->plainTextEdit->toPlainText();
    ui->textGLWidget->setText(text);
}

void MainWindow::updateZoom(int value) {
    ui->textGLWidget->setZoom(qreal(value) * 4 / 100);
    auto widgetSize = ui->textGLWidget->size();
    auto scrollAreaSize = ui->scrollArea->size();
    ui->scrollAreaWidgetContents->setFixedSize(widgetSize);

    int xpos = (widgetSize.width() - scrollAreaSize.width()) / 2;
    int ypos = (widgetSize.height() - scrollAreaSize.height()) / 2;
    ui->scrollArea->horizontalScrollBar()->setSliderPosition(xpos);
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ypos);
}

void MainWindow::subscribe(StatusSenderBearer *sender) {
    connect(sender->s, &StatusSender::newStatus, this, &MainWindow::drawStatus);
}

void MainWindow::drawStatus(QString &status) {
    this->ui->statusbar->showMessage(status);
}

void MainWindow::showError(QString &err, bool fatal) {
    this->errorMessage->showMessage(err);
    this->errorMessage->exec();
    if (fatal) {
        this->scheduleQuit(1);
    }
}

void MainWindow::showException(std::exception &err, bool fatal) {
    QString* message = new QString(err.what());
    this->showError(*message, fatal);
    delete message;
}

void MainWindow::scheduleQuit(int returnCode) {
    QTimer::singleShot(100, this, [returnCode]() {qApp->exit(returnCode);});
}

void MainWindow::refreshFileList() {
    QStringList fileList = getTextFileList();
    int currentRow = this->ui->textFilesList->currentRow();

    QString currentFileName;
    if (currentRow != -1) {
        currentFileName = this->ui->textFilesList->currentItem()->text();
    }
    this->ui->textFilesList->clear();
    this->ui->textFilesList->update();

    if (fileList.length() > 0) {
        this->ui->textFilesList->addItems(fileList);

        if (currentRow == -1) {
            this->ui->textFilesList->setCurrentRow(0);
        } else {
            this->trySelectFileByName(currentFileName);
        }
    }
}

void MainWindow::trySelectFileByName(const QString &filename) {
    if (this->ui->textFilesList->count() == 0) {
        return;
    }
    auto itemsList = this->ui->textFilesList->findItems(filename, Qt::MatchExactly);

    if (itemsList.length() == 0) {
        this->ui->textFilesList->setCurrentRow(0);
    } else {
        int itemRow = this->ui->textFilesList->row(itemsList[0]);
        this->ui->textFilesList->setCurrentRow(itemRow);
    }
}

void MainWindow::fileSelected(QListWidgetItem *current, QListWidgetItem*) {
    if (current == nullptr) {
        return;
    }

    QString fileName = current->text();
    this->ui->currentFileName->setText(fileName);

    QString fileContent = readTextFile(fileName);
    this->ui->plainTextEdit->setPlainText(fileContent);
}

void MainWindow::saveFileClicked() {
    QString fileName = ui->currentFileName->text();
    QString oldFileName = this->ui->textFilesList->currentItem()->text();

    QString fileContent = ui->plainTextEdit->toPlainText();

    saveTextFile(fileName, fileContent);

    this->refreshFileList();

    if (fileName != oldFileName) {
        this->trySelectFileByName(fileName);
    }
}

void MainWindow::openInFinderClicked() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(textsDirectory().c_str()));
}
