#ifndef Peer_h
#define Peer_h

#include <string>

struct Peer
{
    std::string hostname;
    int port;

    Peer(){};

    Peer(std::string hn, int p)
    {
        hostname = hn;
        port = p;
    };
};

#endif