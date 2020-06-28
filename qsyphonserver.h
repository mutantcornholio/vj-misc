#ifndef SYPHONSERVER_H
#define SYPHONSERVER_H

#include <QObject>
#include <QOpenGLFunctions>

class QSyphonServer: public QObject {
    Q_OBJECT
public:
    QSyphonServer();
    ~QSyphonServer();
    void setName (std::string);
    void publishTexture(GLuint id, GLenum target, GLsizei width, GLsizei height, bool isFlipped);

protected:
    void *mSyphon;
};

#endif // SYPHONSERVER_H
