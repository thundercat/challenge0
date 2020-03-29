TEMPLATE = subdirs

SUBDIRS += \
    client \
    library \
    server

server.depends = library
client.depends = library
