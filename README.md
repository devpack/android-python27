ka-lite-android-python27
================

The objective of this project is to create an APK for Ka-lite and make it runs on the embeded Python-for-Android interpreter. Therefore, user can use this app as a LAN server to serve open-scoure educational contents, or consume the content within the app's webview, without the access to the Internet.

More details about Ka-lite can be found here:

Wiki: https://github.com/learningequality/ka-lite/wiki

More details about how to use android-python27 can be found here:

Wiki: http://code.google.com/p/android-python27/w/list

----
*Overview:* 

  * Before go with the following instruction, run the `prepare_python27_for_kalite.sh` script on your terminal to add the necessary python modules for Ka-lite

  * To use this project in Eclipse, just go to `File->Import` and select the apk template folder. It's recommended that you then run `Project->clean` to generate `R.java`

  * The whole Ka-lite project is wrapped into the `ka-lite.zip` file under `res/raw`.

  * The Python interpreter, including all binaries and modules, should be zipped into an archive and also placed inside the `res/raw` directory. The template already has a zip archive containing the Python interpreter in this directory, so you don't need to change this if your APK runs fine. You can add modules that are needed for your scripts or remove them just by editing the files in this zip archive, or you can use your own Python build by replacing this zip archive with one containing your Python build (see the last bullet point below in this section about naming).

  * If you change the name of the main Python script (`manage.py`) or the name of the zip archive containing your Python scripts, then in `src/GlobalConstants.java` change the values for: `Python_MAIN_SCRIPT_NAME` and `PYTHON_PROJECT_ZIP_NAME` respectively.

  * If you change the name of the zip archive containing the Python interpreter and the Python extras, then in `src/GlobalConstants.java` change the values for: `PYTHON_NICE_NAME`, `PYTHON_ZIP_NAME`, and `PYTHON_EXTRAS_ZIP_NAME` respectively.

*python-build*: 

  * Currently the `apk` project template above contains Python version 2.7.2 already built and included inside the `apk/res/raw` directory, so there's no need to build Python yourself. 

  * If you wish to build Python 2.7.2 however, you'll find the source code in `python-build` (see README). This will build Python and create the `python_27.zip` and `python_extras_27.zip` archives to replace the ones located inside the `apk/res/raw` directory.

----

Based on:

- https://github.com/nonameentername

- https://code.google.com/p/python-for-android/

- https://code.google.com/p/android-scripting/

- https://seattle.cs.washington.edu/browser/seattle/trunk/dist/android/SeattleOnAndroid
