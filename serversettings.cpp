#include "serversettings.h"

ServerSettings::ServerSettings(int drawInterval) :
        drawInterval(drawInterval)
{
}

void ServerSettings::setDrawInterval(int drawInterval) {
    this->drawInterval = drawInterval;
}

int ServerSettings::getDrawInterval() const {
    return this->drawInterval;
}
