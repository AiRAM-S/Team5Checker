#ifndef ROOM_H
#define ROOM_H
#include<QStringList>
#include<QString>
#include<QTcpSocket>

class Player{
private:
    QString ID;
    bool isReady;
    QTcpSocket* pSocket;
    char place;
public:
    Player(QString _ID,QTcpSocket* _client):ID(_ID),pSocket(_client){
        isReady = false;
    }
    QString getID() const{
        return ID;
    }
    bool ifReady() const{
        return isReady;
    }
    QTcpSocket* getSocket() const{
        return pSocket;
    }
    void setReady(){
        isReady = true;
    }
};

class Room
{
private:
    int roomID;
    QList<Player> playerList;
    bool gameOn;
    int playerNumber;
public:
    Room(int _id):roomID(_id){
        gameOn = false;
        playerNumber=0;
    }
    void addPl(QString _name,QTcpSocket* _client);
    int getID() const{
        return roomID;
    }
    QList<Player> getPl() const{
        return playerList;
    }
    bool ifON() const{
        return gameOn;
    }
    int getPlnum() const{
        return playerNumber;
    }
};

#endif // ROOM_H
