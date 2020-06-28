#include "qsyphonserver.h"
#import <Syphon/Syphon.h>

QSyphonServer::QSyphonServer() {
    mSyphon = nil;
}

QSyphonServer::~QSyphonServer() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    [(SyphonServer *)mSyphon stop];
    [(SyphonServer *)mSyphon release];

    [pool drain];
}

void QSyphonServer::setName(std::string n) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    NSString *title = [NSString stringWithCString:n.c_str()
                                         encoding:[NSString defaultCStringEncoding]];

    if (!mSyphon) {
        mSyphon = [[SyphonServer alloc] initWithName:title context:CGLGetCurrentContext() options:nil];
    } else {
        [(SyphonServer *)mSyphon setName:title];
    }

    [pool drain];
}


void QSyphonServer::publishTexture(GLuint id, GLenum target, GLsizei width, GLsizei height, bool isFlipped) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    if (!mSyphon) {
        mSyphon = [[SyphonServer alloc] initWithName:@"Untitled" context:CGLGetCurrentContext() options:nil];
    }

    [(SyphonServer *)mSyphon publishFrameTexture:id textureTarget:target imageRegion:NSMakeRect(0, 0, width, height) textureDimensions:NSMakeSize(width, height) flipped:!isFlipped];
    [pool drain];

}
