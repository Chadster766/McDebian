#!/bin/bash

LOGFILE=/var/lib/dibbler/client-notify.log

# uncomment this to get full list of available variables
#set >> $LOGFILE

echo "-----------" >> $LOGFILE

if [ "$OPTION_NEXT_HOP" != "" ]; then

    ip -6 route del default > /dev/null 2>&1
    ip -6 route add default via ${OPTION_NEXT_HOP} dev $IFACE
    echo "Added default route via ${OPTION_NEXT_HOP} on interface $IFACE/$IFINDEX" >> $LOGFILE

fi

if [ "$OPTION_NEXT_HOP_RTPREFIX" != "" ]; then

    NEXT_HOP=`echo ${OPTION_NEXT_HOP_RTPREFIX} | awk '{print $1}'`
    NETWORK=`echo ${OPTION_NEXT_HOP_RTPREFIX} | awk '{print $2}'`
    #LIFETIME=`echo ${OPTION_NEXT_HOP_RTPREFIX} | awk '{print $3}'`
    METRIC=`echo ${OPTION_NEXT_HOP_RTPREFIX} | awk '{print $4}'`

    if [ "$NETWORK" == "::/0" ]; then

        ip -6 route del default > /dev/null 2>&1
        ip -6 route add default via ${OPTION_NEXT_HOP} dev $IFACE
        echo "Added default route via  ${OPTION_NEXT_HOP} on interface $IFACE/$IFINDEX" >> $LOGFILE

    else

        ip -6 route add ${NETWORK} nexthop via ${NEXT_HOP} dev $IFACE weight ${METRIC}
        echo "Added nexthop to network ${NETWORK} via ${NEXT_HOP} on interface $IFACE/$IFINDEX, metric ${METRIC}" >> $LOGFILE

    fi

fi

if [ "$OPTION_RTPREFIX" != "" ]; then

    ONLINK=`echo ${OPTION_RTPREFIX} | awk '{print $1}'`
    METRIC=`echo ${OPTION_RTPREFIX} | awk '{print $3}'`
    ip -6 route add ${ONLINK} dev $IFACE onlink metric ${METRIC}
    echo "Added route to network ${ONLINK} on interface $IFACE/$IFINDEX onlink, metric ${METRIC}" >> $LOGFILE

fi

#Add radvd configs not included in dibbler radvd.conf creation
if ! grep -q AdvLinkMTU /etc/dibbler/radvd.conf; then
        sed -i "s/AdvSendAdvert on;/AdvSendAdvert on;\\n\\tAdvLinkMTU 1280;\\n\\tAdvManagedFlag off;\\n\\tAdvOtherConfigFlag on;/" /etc/dibbler/radvd.conf
fi

if [ "$ADDR1" != "" ]; then
    	echo "Address ${ADDR1} (operation $1) to client $REMOTE_ADDR on inteface $IFACE/$IFINDEX" >> $LOGFILE
    	if [ "$1" == "add" ]; then
		pkill radvd
		systemctl stop dibbler-server
    		ip -6 addr add ${ADDR1} dev ${IFACE}
		radvd -n -C /etc/dibbler/radvd.conf &
		systemctl start dibbler-server
	fi
	if [ "$1" == "update" ]; then
		pkill radvd
                systemctl stop dibbler-server
                ip -6 addr change ${ADDR1} dev ${IFACE}
		radvd -n -C /etc/dibbler/radvd.conf &
                systemctl start dibbler-server
        fi
        if [ "$1" == "delete" ]; then
		pkill radvd
                systemctl stop dibbler-server
                ip -6 addr del ${ADDR1} dev ${IFACE}
        fi
fi

if [ "$PREFIX1" != "" ]; then
	echo "Prefix ${PREFIX1}/${PREFIX1LEN} (operation $1) to client $REMOTE_ADDR on inteface $IFACE/$IFINDEX" >> $LOGFILE
        if [ "$1" == "add" ]; then
		pkill radvd
                systemctl stop dibbler-server
		ip -6 addr add ${PREFIX1}1/${PREFIX1LEN} dev br0
		radvd -n -C /etc/dibbler/radvd.conf &
                systemctl start dibbler-server
        fi
        if [ "$1" == "update" ]; then
		pkill radvd
                systemctl stop dibbler-server
		ip -6 addr change ${PREFIX1}1/${PREFIX1LEN} dev br0
		radvd -n -C /etc/dibbler/radvd.conf &
                systemctl start dibbler-server
        fi
        if [ "$1" == "delete" ]; then
		pkill radvd
                systemctl stop dibbler-server
		ip -6 addr del ${PREFIX1}1/${PREFIX1LEN} dev br0
        fi
fi

# sample return code. Dibbler will just print it out.
exit 3

