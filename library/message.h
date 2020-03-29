#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QDataStream>

class Message
{
public:
    enum class Type {
        CLIENT_REGISTER,
        CLIENT_UNREGISTER,
        ADD_EVENT,
        GET_EVENTS,
        UPDATED
    };

    Message(const Type type = Type::CLIENT_REGISTER, const QByteArray & data = QByteArray());

    ~Message();
    Type type;
    QByteArray data;
};


inline QDataStream &operator<<(QDataStream & out, const Message & message)
{
    out << static_cast<qint8>(message.type) << message.data;
    return out;
}

inline QDataStream &operator>>(QDataStream & in, Message & message)
{
    qint8 type;
    in >> type;
    in >> message.data;

    message.type = static_cast<Message::Type>(type);
    return in;
}


#endif // MESSAGE_H
