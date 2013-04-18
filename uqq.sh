#!/bin/sh

cd plugin
qmake && make
cd ..
qmlscene -I plugin uqq.qml
