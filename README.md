android-python27
================

*Embed Python 2.7 (3.2 and others) interpreter and your scripts into an Android APK:*

The objective of this project is to help people embed a Python for Android interpreter along with their scripts into a single APK that will not require the interpreter to be downloaded separately. A custom version of Python can also be used.

We hope to add more interpreters, and welcome contributors who have experience with different interpreters.

News:

4 April 2013 - Added template for Python 3: https://github.com/devpack/android-python27/tree/master/apk_python32

----
*Overview:* 
_(Check the Wiki tutorials for more detailed instructions)_

*apk*: This is the Python project template that will embed a Python interpreter and your Python scripts into an APK.

  * To use this template project in Eclipse, just go to `File->Import` and select the apk template folder. It's recommended that you then run `Project->clean` to generate `R.java`

  * Your Python scripts should be collected and zipped into an archive, and then placed inside the `res/raw` directory. An example zip archive containing a main Python script (`hello.py`) is already in the `res/raw` directory, which can be replaced with a zip archive with the same name, or a different name (see the second to last bullet point below in this section about naming).

  * The Python interpreter, including all binaries and modules, should be zipped into an archive and also placed inside the `res/raw` directory. The template already has a zip archive containing the Python interpreter in this directory, so you don't need to change this if your APK runs fine. You can add modules that are needed for your scripts or remove them just by editing the files in this zip archive, or you can use your own Python build by replacing this zip archive with one containing your Python build (see the last bullet point below in this section about naming).

  * If you change the name of the main Python script (`hello.py`) or the name of the zip archive containing your Python scripts, then in `src/GlobalConstants.java` change the values for: `Python_MAIN_SCRIPT_NAME` and `PYTHON_PROJECT_ZIP_NAME` respectively.

  * If you change the name of the zip archive containing the Python interpreter and the Python extras, then in `src/GlobalConstants.java` change the values for: `PYTHON_NICE_NAME`, `PYTHON_ZIP_NAME`, and `PYTHON_EXTRAS_ZIP_NAME` respectively.

*python-build*: 

  * Currently the `apk` project template above contains Python version 2.7.2 already built and included inside the `apk/res/raw` directory, so there's no need to build Python yourself. 

  * If you wish to build Python 2.7.2 however, you'll find the source code in `python-build` (see README). This will build Python and create the `python_27.zip` and `python_extras_27.zip` archives to replace the ones located inside the `apk/res/raw` directory.

*python-build-with-qt*: 

  * If you wish to use Python 2.7.2 with PyQT, pre-built binaries are located inside `python-build-with-qt/binaries`, named `python_27.zip` and `python_extras_27.zip`. Just replace the archives of the same name inside `apk/res/raw` with these.

  * If you wish to build Python 2.7.2 with PyQT yourself, you'll find the source code in `python-build-with-qt` (see README_MOD). This will build Python with PyQT and create the `python_27.zip` and `python_extras_27.zip` archives to replace the ones with the same name inside `apk/res/raw`.

----

Based on:

- https://github.com/nonameentername

- https://code.google.com/p/python-for-android/

- https://code.google.com/p/android-scripting/

- https://seattle.cs.washington.edu/browser/seattle/trunk/dist/android/SeattleOnAndroid
