#include <QCoreApplication>

#include <QString>
#include <QDebug>
#include "qt-raw-udp/rawudp.h"
#include <QUdpSocket>
const int SRC_PORT=20000;
const int DST_PORT=SRC_PORT+1;
const QString srcAddr=QString("10.211.55.9");
//const QString dstAddr=QString("192.168.0.1");
//const QString dstAddr=QString("10.100.100.100");
const QString dstAddr=QString(srcAddr);
const QString senderIfname="eth0";
bool runProgram(){
    RawUDP sendSocket;

    int res=sendSocket.openSocket(srcAddr,dstAddr,SRC_PORT,DST_PORT,senderIfname);
    if (res==EXIT_FAILURE){
        qCritical()<<"Fail to openSocket!";
        return false;
    }
    const char* OPROBOVANIE="oprobovanie";
    res=sendSocket.writeDatagram(QByteArray(OPROBOVANIE));
    if (res<=0)
    {
        qCritical()<<"Failure to write, res="<<res;
        return false;
    }
    qDebug()<<"write success";
    return true;
}

const int BUF_SIZE=1024;
bool listenSocket(){
    QUdpSocket listenSock;
    bool res=listenSock.bind(QHostAddress(dstAddr),DST_PORT);
    if (!res)
    {
        qCritical()<<"cant bind!";
        return false;
    }
    while(true)
    {
    listenSock.waitForReadyRead(999999999);
    char  buf[BUF_SIZE];
    int read=listenSock.readDatagram(buf,BUF_SIZE);
    qDebug()<<"read "<<buf;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (argc!=2){
        qDebug()<<"w - write, r - read";
        return 0;
    }
    char ch;
    sscanf(argv[1],"%c",&ch);
    qDebug()<<"get ch="<<ch;
    switch(ch)
    {
        case 'w':
        runProgram();
        break;
    case 'r':
       listenSocket();
        break;
    }

    //return a.exec();
return 0;
}


