#!/usr/bin/env sh

cd output
mkdir pydroid
cp -r python/ pydroid/ 
cp -r extras/python/* pydroid/python/lib/python2.7/
zip -r ../python_27.zip pydroid
cd ..
