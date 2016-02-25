#!/bin/bash
cd ./prog

root.exe -b -l <<EOF
.x GetQAtoffset.cpp();
.q
EOF
