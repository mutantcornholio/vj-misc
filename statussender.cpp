#include "statussender.h"

void StatusSender::status(QString &sta) {
    emit(this->newStatus(sta));
}


void StatusSender::status(QString sta) {
    emit(this->newStatus(sta));
}

StatusSenderBearer::StatusSenderBearer() {
    this->s = new StatusSender();
}

StatusSenderBearer::~StatusSenderBearer() {
    delete this->s;
}
