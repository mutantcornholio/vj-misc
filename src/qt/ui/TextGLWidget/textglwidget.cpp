#include <QPainter>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QTextDocument>
#include <QTextOption>
#include <QString>
#include <QFlags>
#include <QAbstractTextDocumentLayout>


#include "src/qt/ui/TextGLWidget/textglwidget.h"
#include "src/qt/defines.cpp"

QPoint zeroPoint = QPoint(0, 0);
QRect renderRect = QRect(0, 0, RENDERSIZE_X, RENDERSIZE_Y);

QString getCSSForColor(QColor color) {
    QString css = "* {color: rgb(%1,%2,%3)}";
    css = css.arg(color.red()).arg(color.green()).arg(color.blue());

    return css;
}

TextGLWidget::TextGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    auto font = new QFont();
    this->font = *font;
    this->text = QStringLiteral("");
    this->zoom = 0.5;
    this->minZoom = 0.3;
    this->transform = new QTransform();
    this->background = QColor(0, 0, 0);
    this->foreground = QColor(255, 255, 255);
    this->doc = new VJTextDocument();
    this->doc->setDefaultStyleSheet(getCSSForColor(this->foreground));
    this->imgCopyPosition = new QPoint(0, 0);
    this->widgetViewport = new QRect(0, 0, this->width(), this->height());
}

void TextGLWidget::setBoundingSize(int x, int y) {
    this->minZoom = qMin(
        qreal(x) / qreal(RENDERSIZE_X),
        qreal(y) / qreal(RENDERSIZE_Y)
    );
}

void TextGLWidget::initializeGL() {
    this->syphonServer = new QSyphonServer();
    this->syphonServer->setName("FONT OUTPUT");

    this->img = new QImage(RENDERSIZE_X, RENDERSIZE_Y, QImage::Format_ARGB32);
    this->tempImg = new QImage(RENDERSIZE_X, RENDERSIZE_Y, QImage::Format_ARGB32);
}

void TextGLWidget::resizeGL(int, int) {
}

void TextGLWidget::paintGL() {
    this->renderImage();

    QPainter painter;
    painter.begin(this);
    painter.drawImage(*this->widgetViewport, *this->img);
    painter.end();

    delete this->texture;
    this->texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    this->texture->setData(*this->img);
    this->syphonServer->publishTexture(this->texture->textureId(), QOpenGLTexture::Target2D, RENDERSIZE_X, RENDERSIZE_Y, false);
}

void TextGLWidget::renderImage() {
    QPainter tempPainter;
    tempPainter.begin(this->tempImg);

    delete this->textOpts;
    this->textOpts = new QTextOption(Qt::AlignCenter);
    this->textOpts->setAlignment(Qt::AlignVCenter);
    this->textOpts->setWrapMode(QTextOption::ManualWrap);

    auto view = tempPainter.viewport();

    tempPainter.setPen(this->foreground);
    tempPainter.fillRect(view, this->background);

    this->doc->setDefaultTextOption(*this->textOpts);
    this->doc->setPlainText(this->text);
    this->doc->setDefaultFont(this->font);

    this->doc->drawContents(&tempPainter, renderRect);

    tempPainter.setViewTransformEnabled(true);
    tempPainter.end();

    this->updateCopyRect();

    QPainter painter;
    painter.begin(this->img);
    painter.setPen(this->foreground);

    painter.fillRect(renderRect, this->background);

    painter.drawImage(*this->imgCopyPosition, *this->tempImg, renderRect);
    painter.end();
}

void TextGLWidget::setFont(const QFont& font) {
    this->font = font;
    this->update();
}

void TextGLWidget::setLineSpacing(int lineSpacing) {
    this->doc->setLineSpacing(lineSpacing);
    this->update();
}

void TextGLWidget::setAlignment(FontPreset::Alignment alignment) {
    this->doc->setAlignment(alignment);
    this->update();
}

void TextGLWidget::setText(QString text) {
    this->text = text;
    this->update();
}

TextGLWidget::~TextGLWidget() {
    delete this->transform;
    delete this->doc;
    delete this->syphonServer;
    delete this->img;
    delete this->tempImg;
}

void TextGLWidget::setZoom(qreal val) {
    if (val < this->minZoom) {
        this->zoom = this->minZoom;
    } else {
        this->zoom = val;
    }

    int x = int(this->zoom * RENDERSIZE_X);
    auto y = int(this->zoom * RENDERSIZE_Y);

    this->setFixedSize(x, y);
    this->widgetViewport->setWidth(x);
    this->widgetViewport->setHeight(y);
    this->update();
}

void TextGLWidget::updateCopyRect() {
    QAbstractTextDocumentLayout *layout = this->doc->documentLayout();
    QSizeF docSize = layout->documentSize();

    auto w = docSize.width();
    qreal x = 0;
    if (w < RENDERSIZE_X) {
        x = (RENDERSIZE_X - w) / 2;
    }

    auto h = docSize.height();
    qreal y = 0;
    if (h < RENDERSIZE_Y) {
        y = (RENDERSIZE_Y - h) / 2;
    }

    this->imgCopyPosition->setX(x);
    this->imgCopyPosition->setY(y);
}

