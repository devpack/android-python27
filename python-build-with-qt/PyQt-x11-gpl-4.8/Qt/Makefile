TARGET = Qt.so
OFILES = sipQtcmodule.o
HFILES =  

CC = /opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc
CXX = /opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++
LINK = /opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++
CPPFLAGS = -DNDEBUG -I. -I/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/include -I/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/libs/armeabi/include -I/opt/necessitas/Android/Qt/480/qt-src/src/3rdparty/phonon -I/home/tsheasha/GUC/Bachelors/android-python27/python-build/build/include/python2.7
CFLAGS = -pipe -DQT_NO_QWS_TRANSFORMED -DQ_WS_QWS -Dprotected=public -DSIP_PROTECTED_IS_PUBLIC --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -pipe -DQT_NO_QWS_TRANSFORMED -DQ_WS_QWS -Dprotected=public -DSIP_PROTECTED_IS_PUBLIC --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -fpic -g -msoft-float -mthumb -mthumb-interwork -mtune=xscale -march=armv5te -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -msoft-float -mthumb -mthumb-interwork  -mtune=xscale -march=armv5te -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W -Os -pipe -msoft-float -fpic -mthumb-interwork -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums -funwind-tables -DANDROID  -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5TE__ -D__STDC_INT64__ -DQT_NO_QWS_TRANSFORMED -fPIC -g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W -pipe -fPIC -g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W
CXXFLAGS = -pipe -DQT_NO_QWS_TRANSFORMED -DQ_WS_QWS -Dprotected=public -DSIP_PROTECTED_IS_PUBLIC --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -pipe -DQT_NO_QWS_TRANSFORMED -DQ_WS_QWS -Dprotected=public -DSIP_PROTECTED_IS_PUBLIC --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -fpic -g -msoft-float -mthumb -mthumb-interwork -mtune=xscale -march=armv5te -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -msoft-float -mthumb -mthumb-interwork  -mtune=xscale -march=armv5te -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W -Os -pipe -msoft-float -fpic -mthumb-interwork -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums -funwind-tables -DANDROID  -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5TE__ -D__STDC_INT64__ -DQT_NO_QWS_TRANSFORMED -fPIC -g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W
LFLAGS = --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -L/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/ -Wl,-rpath-link= -Wl,-rpath=/opt/necessitas/Android/Qt/480/qt-src/src/3rdparty/android/precompiled/android-9/arch-arm/lib -Wl,-z,noexecstack -Wl,-O1  -Wl,-z,noexecstack -shared -Wl,-shared,-Bsymbolic -Wl,--no-whole-archive -Wl,--no-undefined -Wl,-z,noexecstack -shared -Wl,-z,noexecstack -Wl,-O1  -Wl,-z,noexecstack -shared -Wl,-shared,-Bsymbolic -Wl,--no-whole-archive   -Wl,--version-script=Qt.exp
LIBS = -L/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/libs/armeabi/ -lstdc++ -lsupc++ -llog -lz -lm -ldl -lc -lgcc -L/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/lib/ -lpython2.7
.SUFFIXES: .c .o .cpp .cc .cxx .C


.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

all: $(TARGET)

$(OFILES): $(HFILES)

$(TARGET): $(OFILES)
	@echo '{ global: initQt; local: *; };' > Qt.exp
	$(LINK) $(LFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

install: $(TARGET)
	@test -d $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/PyQt4 || mkdir $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/PyQt4
	cp -f $(TARGET) $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/PyQt4/$(TARGET)
	/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-strip $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/PyQt4/$(TARGET)

clean:
	-del /q 2> NUL $(TARGET)
	-del /q 2> NUL sipQtcmodule.o
	-del /q 2> NUL Qt.exp
