#!/usr/local/bin/bash

MANIFEST=$1
VERSION=$(grep VERSION Makefile | head -1 | awk '{print $3}')

cp -f $MANIFEST $MANIFEST.orig

for FILE in $(grep SHA256 $MANIFEST | awk -F":" '{print $1":"$2}' | tr -d '"' | tr -d ' ' | tr -d "\t" | awk -F"," '{print $1}'); do
	REPLACE=${FILE##*:}
	RFILE=${FILE%:*}
	RPATH=${MANIFEST%/*}${RFILE}
	SHA256=$(sha256 $RPATH | awk -F"=" '{print $2}' | tr -d ' ')

	BUFFER="$(sed -e s,$REPLACE,$SHA256,g -e s,#VERSION#,$VERSION,g $MANIFEST)"
	echo "${BUFFER}" > $MANIFEST
done
