#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H
#include "message.h"
#include <QTcpSocket>

namespace MessageUtils {
    inline void sendMessage(QTcpSocket &socket, Message::Type messageType,const QByteArray &data, bool forceFlush = false)
    {
        Message message(messageType, data);
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << message;
        socket.write(byteArray);
        if(forceFlush)
            socket.flush();
    }

    inline std::unique_ptr<std::vector<std::shared_ptr<Message>>>readMessages(QDataStream& stream)
    {
        auto messages = std::make_unique<std::vector<std::shared_ptr<Message>>>();
        bool commitTransaction = true;
        while (commitTransaction && stream.device()->bytesAvailable() > 0) {
            stream.startTransaction();
            auto message = std::make_shared<Message>();
            stream >> *message;
            commitTransaction = stream.commitTransaction();
            if (commitTransaction) {
                messages->push_back(std::move(message));
            }
        }

    return messages;
    }
}
#endif // MESSAGEUTILS_H
