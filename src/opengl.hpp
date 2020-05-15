#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <GLES2/gl2.h>

void _glPrintErrors(const char *file, int line, bool printOk);
#define glPrintErrors() _glPrintErrors(__FILE__, __LINE__, false)
#define glPrintErrorsOk(printOk) _glPrintErrors(__FILE__, __LINE__, true)

#endif
