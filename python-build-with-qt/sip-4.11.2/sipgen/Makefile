TARGET = sip
OFILES = main.o transform.o gencode.o export.o heap.o parser.o lexer.o
HFILES = sip.h parser.h

CC=/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc 
CXX=/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++
LINK = /opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++
CPPFLAGS = -DNDEBUG -I. -I/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/include -I/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/libs/armeabi/include -I/home/tsheasha/GUC/Bachelors/android-python27/python-build/build/include/python2.7
CFLAGS = -pipe -fpic -g -msoft-float -mthumb -mthumb-interwork  -mtune=xscale -march=armv7-a -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W -Os -pipe -msoft-float -fpic -mthumb-interwork -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums -funwind-tables -DANDROID  -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5TE__ -D__STDC_INT64__ -DQT_NO_QWS_TRANSFORMED  --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/
CXXFLAGS = -pipe --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -fpic -g -msoft-float -mthumb -mthumb-interwork  -mtune=xscale -march=armv7-a -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -msoft-float -mthumb -mthumb-interwork  -mtune=xscale -march=armv7-a -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W -Os -pipe -msoft-float -fpic -mthumb-interwork -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums -funwind-tables -DANDROID  -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5TE__ -D__STDC_INT64__ -DQT_NO_QWS_TRANSFORMED
LFLAGS = --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -L/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/ -Wl,-rpath-link= -Wl,-rpath=/opt/necessitas/Android/Qt/480/qt-src/src/3rdparty/android/precompiled/android-9/arch-arm/lib -Wl,-z,noexecstack -Wl,-rpath=/opt/necessitas/Android/Qt/480/armeabi/lib
LIBS = -L/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/qpy/QtGui -L/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/libs/armeabi/ -L/opt/necessitas/Android/Qt/480/armeabi/lib -lstdc++ -lsupc++ -llog -lz -lm -ldl -lc -lgcc -L/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/lib/ -lpython2.7 -L/opt/necessitas/unstable/Android/Qt/480/build-armeabi/install/lib -L/opt/necessitas/android-ndk-r6b/sources/cxx-stl/gnu-libstdc++/libs/armeabi -L/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm//usr/lib -L/opt/necessitas/unstable/Android/Qt/480/build-armeabi/install/lib -L/opt/necessitas/android-ndk-r6b/sources/cxx-stl/gnu-libstdc++/libs/armeabi -L/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm//usr/lib -lstdc++ -lsupc++ -llog -lz -lm -ldl -lc -lgcc -L/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/lib/ -lpython2.7 -L/opt/necessitas/unstable/Android/Qt/480/build-armeabi/install/lib -L/opt/necessitas/android-ndk-r6b/sources/cxx-stl/gnu-libstdc++/libs/armeabi -L/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm//usr/lib -lstdc++ -lsupc++ -llog -lz -lm -ldl -lc -lgcc -L/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/lib/ -lpython2.7
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
	$(LINK) $(LFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

install: $(TARGET)
	@test -d $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/bin || mkdir -p $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/bin
	cp -f $(TARGET) $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/bin/$(TARGET)

clean:
	-rm -f $(TARGET)
	-rm -f main.o
	-rm -f transform.o
	-rm -f gencode.o
	-rm -f export.o
	-rm -f heap.o
	-rm -f parser.o
	-rm -f lexer.o
