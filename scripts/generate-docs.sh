#!/usr/bin/env bash

#
# File: generate-docs.sh
# Author: Tamer Aly
# Purpose: Generate doxygen PDF document from sources and put it into the doc/ source folder.
#
# This script is called by CMake on Unix and Mac platforms to generate doxygen documents from sources.
# Note that this script has the following requirements:
#
# 1) the 'doxygen' command is on the shell's PATH.
# 2) the script must accept a doxygen config file as its sole argument.
# 3) the doxygen config file must have the folllowing configs properly set:
#   a. LATEX_OUTPUT
#   b. OUTPUT_DIRECTORY
#   c. PROJECT_VER
#
# These values from the doxygen config are used to determine where the output PDF will be installed.
#

if [ ! "command -v doxygen" > /dev/null 2>&1 ]; then
    echo "Doxygen command is not on your PATH! Please ensure doxygen is installed in the PATH."
    exit 1
fi

if [ "$#" -ne "1" && ! -f "$1" ]; then
    echo "Need arguments: <doxygen config file>"
    exit 1
fi

DOXYGEN_CONFIG_FILE="${1}"

# Extract the required doxygen configs

LATEX_DIR=$(grep 'LATEX_OUTPUT' "${DOXYGEN_CONFIG_FILE}" | tr -d '=' | awk '{print $2}')
if [ -z LATEX_DIR ]; then
    echo "LATEX_DIR was not specified in doxygen config '${DOXYGEN_CONFIG_FILE}' when it is required!"
    exit 1
fi

DOC_DIR=$(grep 'OUTPUT_DIRECTORY' "${DOXYGEN_CONFIG_FILE}" | tr -d '=' | awk '{print $2}')
if [ -z DOC_DIR ]; then
    echo "OUTPUT_DIRECTORY was not specified in doxygen config '${DOXYGEN_CONFIG_FILE}' when it is required!"
    exit 1
fi

PROJECT_VER=$(grep 'PROJECT_NUMBER' "${DOXYGEN_CONFIG_FILE}" | tr -d '=' | awk '{print $2}')
if [ -z PROJECT_VER ]; then
    echo "PROJECT_NUMBER was not specified in doxygen config '${DOXYGEN_CONFIG_FILE}' when it is required!"
    exit 1
fi

echo "Parsed latex directory: ${LATEX_DIR} , doc directory: '$DOC_DIR' , project version: '$PROJECT_VER' "

OUTPUT_DIR="${DOC_DIR}/${LATEX_DIR}"
OUTFILE_NAME="${DOC_DIR}/csc-${PROJECT_VER}.pdf"

# Generate the documentation.
doxygen "${DOXYGEN_CONFIG_FILE}"

cd "${OUTPUT_DIR}"

# Create the PDF.
make

# Rename the file and move it to the right location.
mv 'refman.pdf' "${OUTFILE_NAME}"

# Clean up other stuff not needed in the directory.
rm -rf "${OUTPUT_DIR}"