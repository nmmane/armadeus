#!/bin/sh

#
# Script to test Armadeus Software release
#
#  Copyright (C) 2008 The Armadeus Project
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#

source ./test_helpers.sh
source ./test_env.sh


WTIME=0
RTIME=0
#DEBUG=True

test_ethernet()
{
	show_test_banner "Ethernet"

	# Check if interface is up
	ifconfig eth0
	if [ "$?" != 0 ]; then
		echo "No Ethernet interface found"
		exit 1
	fi
	# To autoconfigure Internet access
	udhcpc -q -i eth0

	cd $TEMP_DIR
	# Create temp bench file
	echo "Creating random data file"
	if [ ! -f "$TEMP_FILE" ]; then
		dd if=/dev/urandom of=$TEMP_FILE bs=1024 count=$TEMP_FILE_SIZE 2>/dev/null & pid=$!
		# Show a kind of progress bar
		echo -en "[                          ]\r["
		while [ $? == 0 ]; do
			echo -n "."
			sleep 1
			kill -USR1 $pid 2>/dev/null
		done
		echo
	fi

	for it in 1 2 3; do
		echo "--- Test iteration n°$it ---"
		echo "  Uploading"
		time tftp -p -l $TEMP_FILE $SERVER_IP 2>/tmp/writetime
		if [ "$?" == 0 ]; then
			rm $TEMP_FILE
		fi
		echo "  Downloading"
		time tftp -g -r $TEMP_FILE $SERVER_IP 2>/tmp/readtime
		# Update writing mean time
		get_time_in_ms_from_file /tmp/writetime
		if [ $it == "1" ]; then
			WTOTIME=$WTIME
		else
			WTOTIME=`expr $WTIME + $WTOTIME`
			WTOTIME=`expr $WTOTIME / 2`
		fi
		debug "Mean write time: $WTOTIME ms"
		# Update reading mean time
		get_time_in_ms_from_file /tmp/readtime
		if [ $it == "1" ]; then
			RTOTIME=$RTIME
		else
			RTOTIME=`expr $RTIME + $RTOTIME`
			RTOTIME=`expr $RTOTIME / 2`
		fi
		debug "Mean reading time: $RTOTIME ms"
	done
	rm -f $TEMP_FILE
	WSPEED=`expr $TEMP_FILE_SIZE \* 1000 / $WTOTIME`
	RSPEED=`expr $TEMP_FILE_SIZE \* 1000 / $RTOTIME`
	echo "--- Test result (mean values):"
	echo "  read  -> $RSPEED kBytes/sec"
	echo "  write -> $WSPEED kBytes/sec"
	echo_test_ok
}

test_ethernet

