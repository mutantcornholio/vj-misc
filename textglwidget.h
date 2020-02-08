#ifndef TEXTGLWIDGET_H
#define TEXTGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLTexture>

#include "qsyphonserver.h"
#include "statussender.h"
#include "vjtextdocument.h"

class TextGLWidget : public QOpenGLWidget, public StatusSenderBearer
{
public:
    TextGLWidget(QWidget *parent);
    void setFont(const QFont&);
    void setText(QString);
    void setZoom(qreal);
    void setBoundingSize(int, int);
    ~TextGLWidget();
    GLuint textureId();
    QImage *img;
    QTransform *transform;

    VJTextDocument *doc;

protected:
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int, int) override;

private:

    void renderImage();
    void updateCopyRect();

    QSyphonServer *syphonServer;
    QString text;
    QFont font;
    QOpenGLTexture *texture;
    QColor background;
    QColor foreground;
    QTextOption *textOpts;

    QPoint *imgCopyPosition;
    QImage *tempImg;

    qreal zoom;
    qreal minZoom;
    QRect *widgetViewport;
};

#endif // TEXTGLWIDGET_H
