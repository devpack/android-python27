export PYVERSION="2.7.2"

export ANDROID_PLATFORM="android-9"

# android ndk base dir (eg. containing the ndk-build script)
export NDK=${NDK:=/home/tsheasha/Downloads/android-ndk-r8}
export SDK=${SDK:=/home/tsheasha/Downloads/android-sdk-linux}
export NDKPLATFORM=$NDK/platforms/android-9/arch-arm
export PATH=$NDK/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/:$NDK:$SDK/tools:$PATH
