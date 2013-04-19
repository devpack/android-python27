#include <Python.h>
#include <QtGui/QApplication>
#include "main.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    setenv("PYTHONHOME", PYTHON_HOME, 1);
    setenv("PYTHONPATH", PYTHON_PATH, 1);
    setenv("LD_LIBRARY_PATH", LD_LIBRARY_PATH, 1);
    setenv("PATH", PATH, 1);

    QApplication app(argc, argv);
    Py_Initialize();
    PySys_SetArgv(argc, argv);
    PySys_SetPath(PYTHON_PATH);
    FILE *fp = fopen(PYQT_MAIN, "r");
    PyRun_SimpleFile(fp, PYQT_MAIN);
    fclose(fp);
    Py_Finalize();
    //app.exec();
}
