#!/bin/bash

BASE_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd)
INSTALL_DIR=${BASE_DIR}"/install/"
for d in $(find ${INSTALL_DIR} -type d)
do
    DIR_NAME=${d##*/}
    if [ "${DIR_NAME}" = "bin" ];then
        export PATH=${d}:$PATH
    fi
done




