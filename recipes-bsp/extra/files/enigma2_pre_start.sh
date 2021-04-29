#!/bin/sh

ln -s /dev/dvb/adapter0/ca0  /dev/dvb/adapter0/ca1

/usr/bin/evremote2
/usr/bin/hisiproxy

sleep 5

exit 0
