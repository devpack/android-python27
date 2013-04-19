#!/usr/bin/env sh

yes | rm output
yes | rm python_extras_27.zip
yes | rm python_27.zip

# 1) build python_27.zip
mkdir -p output/python/bin
mkdir -p output/python/lib/python2.7/lib-dynload

cp -r build/bin/python  output/python/bin/python
cp -r build/lib/libpython2.7.so  output/python/lib/libpython2.7.so
cp -r libs/armeabi/libsqlite3.so  output/python/lib/libsqlite3.so
cp -r libs/armeabi/libcrypt.so  output/python/lib/libcrypt.so
cp -r openssl/libs/armeabi/libcrypto.so  output/python/lib/libcrypto.so
cp -r openssl/libs/armeabi/libssl.so  output/python/lib/libssl.so
cp -r build/lib/python2.7/lib-dynload/*  output/python/lib/python2.7/lib-dynload/
cp -r pycrypto-2.6/build/lib*/Crypto output/python/lib/python2.7/lib-dynload/
mv psutil-0.6.1/build/lib*/*.so psutil-0.6.1/build/lib*/psutil
cp -r psutil-0.6.1/build/lib*/psutil output/python/lib/python2.7/lib-dynload/
#find pycrypto-2.6/build/lib* -name "*.so" -exec cp -v {} output/python/lib/python2.7/lib-dynload/ \;

cd output
zip -r ../python_27.zip python
cd ..

# 2) build python_extras_27.zip
mkdir -p output/extras/python

cp -r build/lib/python2.7/* output/extras/python/
#cp -r pycrypto-2.6/build/lib*/* output/extras/python/ # import from site-packages not working

cd output/extras/python
rm -rf config
rm -rf lib-dynload
rm -v `find . | grep "\.so$\|.pyc$\|.egg-info$\|.doc$\|.pyo$\|.txt$"`
rm -r `find . | grep test`
cp ../../../android.py .

cd ..
zip -r ../../python_extras_27.zip python





