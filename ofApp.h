#pragma once

#include <QObject>
#include <QOpenGLTexture>

//class ofAppSilent : public ofAppGLFWWindow
//{
//public:
//    void setup(const ofGLWindowSettings &);
//    void setup();
//    void draw();
//    void setTexture(ofTexture *);
//    void setImage(ofImage *);
//    ofxSyphonServer mainOutputSyphonServer;

//private:
//    ofTexture *texture = nullptr;
//    ofImage *oimg = nullptr;
//};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
};

class ofAppSilent : public ofAppGLFWWindow
{
public:
    ofAppSilent();
    ~ofAppSilent();
    void drawHandler(ofEventArgs&);
    void setupApp(ofEventArgs&);
    void setImage(ofImage *);
    ofxSyphonServer mainOutputSyphonServer;

private:
    ofImage *oimg = nullptr;
};

class ofAppSilentWrapper: public QObject
{
    Q_OBJECT

public:
    void setup(QObject *parent);
    ~ofAppSilentWrapper();

private slots:
    void updateApp();
    void drawImage(QImage *);
    void publishTexture(GLuint texId);

private:
    ofAppSilent *app = nullptr;
    ofApp *app1 = nullptr;
    ofTexture *texture = nullptr;
};
