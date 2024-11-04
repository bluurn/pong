#!/bin/sh

set +ex

CLANGD_FILE=".clangd"

[ -f $CLANGD_FILE ] && echo "file $CLANGD_FILE exists. skipping" && exit

printf "CompileFlags:\n  Add: %s" "$(pkg-config --cflags raylib)" > "$CLANGD_FILE"
echo "file $CLANGD_FILE created."

