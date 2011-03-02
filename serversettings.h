#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

// Stores game settings received from server. At this moment it is only drawInterval, but it is supposed
// to be bigger in the future.

class ServerSettings
{
    int drawInterval;
public:
    ServerSettings(int drawInterval = 0);
    void setDrawInterval(int);
    int getDrawInterval() const;
};

#endif // SERVERSETTINGS_H
