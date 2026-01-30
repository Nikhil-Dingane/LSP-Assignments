#!/bin/bash

LIBDIR="$PWD"

echo "=============================================="
echo "Running program WITHOUT LD_LIBRARY_PATH"
echo "=============================================="
echo ""

./client
STATUS=$?

if [ $STATUS -ne 0 ]; then
    echo
    echo ">>> Explanation:"
    echo "The loader only searches standard system directories."
    echo "The custom library directory is not known:"
    echo "  $LIBDIR"
fi

echo
echo "=============================================="
echo "Exporting LD_LIBRARY_PATH and running again"
echo "=============================================="
echo ""

export LD_LIBRARY_PATH="$LIBDIR"

echo "LD_LIBRARY_PATH set to:"
echo "  $LD_LIBRARY_PATH"

echo

./client
STATUS=$?

if [ $STATUS -eq 0 ]; then
    echo
    echo ">>> Explanation:"
    echo "Now the loader checks LD_LIBRARY_PATH first."
    echo "It finds libdemo.so in the custom directory."
    echo "Loading succeeds."
fi

echo
echo "=============================================="
echo "Test complete"
echo "=============================================="

