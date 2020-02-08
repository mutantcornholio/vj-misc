#include <QImage>
#include "ofApp.h"

void ofApp::setup() {
//    ofSetupOpenGL(1920, 1080, OF_WINDOW);
}

void ofApp::update() {

}
void ofApp::draw() {

}

ofAppSilent::ofAppSilent() {
    this->mainOutputSyphonServer = ofxSyphonServer();
    this->mainOutputSyphonServer.setName("FONT OUTPUT");

//    auto events = this->events();
    ofAddListener(this->events().draw, this, &ofAppSilent::drawHandler);
}

ofAppSilent::~ofAppSilent() {

}

//void ofAppSilent::setup() {
//    ofSetupOpenGL(1920, 1080, OF_WINDOW);

//    this->mainOutputSyphonServer = ofxSyphonServer();
//    this->mainOutputSyphonServer.setName("FONT OUTPUT");
//}

//void ofAppSilent::setTexture(ofTexture *texture) {
//    this->texture = texture;
//}

void ofAppSilent::setImage(ofImage *oimg) {
    this->oimg = oimg;
}

void ofAppSilent::drawHandler(ofEventArgs&) {
//    ofClear(0, 0, 0, 0);
//    if (this->texture) {
//        this->texture->draw(0, 0);
//    }
//    this->oimg->draw(0, 0);
    ofClear(0, 0, 0, 255);
//    this->mainOutputSyphonServer.publishScreen();
    //this->mainOutputSyphonServer.publishTexture(this->texture);
}

void ofAppSilent::setupApp(ofEventArgs&)
{

}

void ofAppSilentWrapper::setup(QObject *parent)
{
    this->setParent(parent);

    this->app1 = new ofApp();
    this->app = new ofAppSilent();
    ofGLFWWindowSettings* windowSettings = new ofGLFWWindowSettings();
    windowSettings->setSize(1920, 1080);
    ofSetupOpenGL(this->app, 1920, 1080, OF_WINDOW);
//    this->app->setup(*windowSettings);
//    this->app->setup();





    texture = new ofTexture();
    texture->allocate(1920, 1080, GL_RGBA);

//    this->app->setTexture(texture);


}
ofAppSilentWrapper::~ofAppSilentWrapper()
{
//    this->app->exitApp();
}

void ofAppSilentWrapper::updateApp()
{
    this->app->toggleFullscreen();
    this->app->makeCurrent();
    this->app->update();
    this->app->draw();
    this->app->pollEvents();
//    ofGetMainLoop()->loopOnce();
}

void ofAppSilentWrapper::drawImage(QImage *img)
{
    QImage img2 = img->convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);
    this->texture->clear();
    this->texture->allocate(1920, 1080, GL_RGBA);
//    this->texture->loadData(img2.bits(), img2.width(), img2.height(), GL_RGBA);
//    this->texture->draw(0, 0);
    ofPixels pix;
    pix.allocate(img2.width(), img2.height(), OF_PIXELS_RGBA);
    auto bits = img2.bits();
    size_t i = 0;
    while( i < pix.size()) {
        pix[i] = bits[i];
        i++;
    }

    ofImage oimg;
    oimg.allocate(img2.width(), img2.height(), OF_IMAGE_COLOR_ALPHA);
    oimg.setFromPixels(pix);
    this->texture->loadData(pix, GL_RGBA);
    this->app->setImage(&oimg);

//    oimg->draw(0, 0);
//    this->app->draw();
//    this->app->mainOutputSyphonServer.publishScreen();
//    this->app->mainOutputSyphonServer.publishTexture(this->texture);
//    this->app->draw();
}

void ofAppSilentWrapper::publishTexture(GLuint texId)
{
//    this->app->mainOutputSyphonServer.publishTexture(texId, QOpenGLTexture::Target2D, 1920, 1080, false);
}
