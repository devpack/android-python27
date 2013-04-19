#!/usr/bin/env sh
set -e
npath() { python -c "import sys, os; print os.path.normpath(os.path.abspath(os.path.join(*sys.argv[1:])))" $@; }

# ROOTDIR is the directory holding all the scripts configs, BUILDDIR is the current working dir (stage)
export ROOTDIR=$( npath "$0" ".." )
export BUILDDIR=$( pwd )
. "$ROOTDIR/functions.sh" && readconfig "$ROOTDIR/config.sh" "$BUILDDIR/config.sh"


info "Bootstrapping python $PYVERSION for android with data from $ROOTDIR"

if [ ! -e "$BUILDDIR/Python-2.7.2.tgz" ]; then
    set_downloader
    downloader http://www.python.org/ftp/python/2.7.2/Python-2.7.2.tgz
fi

if [ ! -e "$BUILDDIR/Python-host" ]; then
    tar zxvf Python-2.7.2.tgz
    mv Python-2.7.2 Python-host
fi

if [ ! -e "$BUILDDIR/Python" ]; then
    tar zxvf Python-2.7.2.tgz
    mv Python-2.7.2 Python
    cd "$BUILDDIR/Python"
    
    patch -p1 < "$ROOTDIR/patch/Python-2.7.2-xcompile.patch"
    patch -p1 < "$ROOTDIR/patch/Python-2.7.2-android.patch"
    #patch -p1 -i "$ROOTDIR/patch/Python-2.7.2-getplatform.patch"
    patch -p1 -i "$ROOTDIR/patch/Python-2.7.2-site-relax-include-config.patch"
    patch -p1 -i "$ROOTDIR/patch/Python-2.7.2-enable_ipv6.patch"
    patch -p1 -i "$ROOTDIR/patch/Python-2.7.2-filesystemdefaultencoding.patch"
fi


if [ ! -e "$BUILDDIR/hostpython" -a ! -e "$BUILDDIR/hostpgen" ]; then
    cd "$BUILDDIR/Python-host"
    ./configure --prefix="$BUILDDIR/prebuilt"
    make -j4
    make install
    mv python "$BUILDDIR/hostpython"
    mv Parser/pgen "$BUILDDIR/hostpgen"
    make distclean
fi

if [ ! -e "$BUILDDIR/openssl" ]; then
    cd "$BUILDDIR"
    git clone https://github.com/guardianproject/openssl-android.git openssl
fi

if [ ! -e "$BUILDDIR/pycrypto-2.6" ]; then
    cd "$BUILDDIR"
    set_downloader
    downloader http://pypi.python.org/packages/source/p/pycrypto/pycrypto-2.6.tar.gz
    tar zxvf pycrypto-2.6.tar.gz
    cd "$BUILDDIR/pycrypto-2.6"
    patch -p1 -i "$ROOTDIR/patch/pycrypto-2.6-customize_compiler.patch"
fi

if [ ! -e "$BUILDDIR/psutil-0.6.1" ]; then
    cd "$BUILDDIR"
    set_downloader
    downloader http://psutil.googlecode.com/files/psutil-0.6.1.tar.gz
    tar zxvf psutil-0.6.1.tar.gz
    cd "$BUILDDIR/psutil-0.6.1"
    patch -p1 -i "$ROOTDIR/patch/psutil-0.6.1-android.patch"
fi

if [ ! -d "$BUILDDIR/toolchain" ]; then
    [ ! -f "$NDK/build/tools/make-standalone-toolchain.sh" ] && error "missing \$NDK/build/tools/make-standalone-toolchain.sh"
    "$NDK/build/tools/make-standalone-toolchain.sh" --platform=${ANDROID_PLATFORM} --install-dir="${BUILDDIR}/toolchain"
fi
