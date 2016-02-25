#!/bin/bash
cd ./prog
rm -f Hisots_cpp.so TreeVar_cpp.so Qvectors_cpp.so Event_cpp.so
root.exe -b -l <<EOF1
.L Histos.cpp+
.L TreeVar.cpp+
.L Qvectors.cpp+
.L Event.cpp+
.q
EOF1

root.exe -b -l <<EOF
.x QA.cpp(313305);
.q
EOF
