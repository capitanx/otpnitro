#!/bin/bash

MANIFEST=$1
VERSION=$(grep VERSION Makefile | head -1 | awk '{print $3}')
RELEASE=$(lsb_release -c -s)

MACHINE=$(uname -m)

[[ "$MACHINE" = *"86"   ]] && ARCH="i386"
[[ "$MACHINE" = *"arm"* ]] && ARCH="armhf"
[[ "$MACHINE" = *"_64"  ]] && ARCH="amd64"

[[ "$1" = "--all"     ]] && echo "${VERSION}-1${RELEASE}0_${ARCH}" && exit 0
[[ "$1" = "--version" ]] && echo "$VERSION" && exit 0
[[ "$1" = "--release" ]] && echo "$VERSION" && exit 0
[[ "$1" = "--arch"    ]] && echo "$ARCH"    && exit 0

cp -f $MANIFEST $MANIFEST.orig

BUFFER="$(sed -e s,#ARCH#,$ARCH,g -e s,#VERSION#,$VERSION,g -e s,#RELEASE#,$RELEASE,g $MANIFEST)"
echo "${BUFFER}" > $MANIFEST
