#!/usr/bin/env bash

if [ ! "command -v doxygen" > /dev/null 2>&1 ]; then
    echo "Doxygen command is not on your PATH! Please ensure doxygen is installed in the PATH."
    exit 1
fi

if [ "$#" -ne "1" ]; then
    echo "Missing the required Doxygen configuration argument!"
    exit 1
fi

doxygen "$1"