#include <QFile>
#include <QTextStream>
#include <qgl.h>

int main(int, char **)
{
    QFile outf("./sip/QtOpenGL/opengl_types.sip");

    if (!outf.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
        return 1;

    QTextStream out(&outf);

    if (sizeof (long) == sizeof (GLint))
        out << "typedef long GLint;\n";
    else
        out << "typedef int GLint;\n";

    if (sizeof (unsigned long) == sizeof (GLuint))
        out << "typedef unsigned long GLuint;\n";
    else
        out << "typedef unsigned GLuint;\n";

    if (sizeof (unsigned long) == sizeof (GLenum))
        out << "typedef unsigned long GLenum;\n";
    else
        out << "typedef unsigned GLenum;\n";

    if (sizeof (unsigned long) == sizeof (GLbitfield))
        out << "typedef unsigned long GLbitfield;\n";
    else
        out << "typedef unsigned GLbitfield;\n";

    out << "typedef float GLfloat;\n";

    return 0;
}
