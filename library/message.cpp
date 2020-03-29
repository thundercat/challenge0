#include "message.h"

Message::Message(const Message::Type type, const QByteArray &data) : type(type), data(data)
{

}

Message::~Message()
{

}
