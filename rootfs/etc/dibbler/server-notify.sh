#!/bin/bash

# this is example notify script that can be invoked on a server side
# This script will be called by dibbler-server with a single parameter
# describing operation (add, update, delete, expire)
#
# Many parameters will be passed as environment variables

LOGFILE=/var/lib/dibbler/server-notify.log

echo "---$1--------" >> $LOGFILE
date >> $LOGFILE

# uncomment this to get full list of available variables
#set >> $LOGFILE

if [ "$ADDR1" != "" ]; then
    echo "Address ${ADDR1} (operation $1) to client $REMOTE_ADDR on inteface $IFACE/$IFINDEX" >> $LOGFILE
fi

if [ "$PREFIX1" != "" ]; then
    echo "Prefix ${PREFIX1} (operation $1) to client $REMOTE_ADDR on inteface $IFACE/$IFINDEX" >> $LOGFILE
fi

# sample return code. Dibbler will just print it out.
exit 3

