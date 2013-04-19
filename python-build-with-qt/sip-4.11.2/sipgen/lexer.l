/*
 * The SIP lexer.
 *
 * Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
 *
 * This file is part of SIP.
 *
 * This copy of SIP is licensed for use under the terms of the SIP License
 * Agreement.  See the file LICENSE for more details.
 *
 * This copy of SIP may also used under the terms of the GNU General Public
 * License v2 or v3 as published by the Free Software Foundation which can be
 * found in the files LICENSE-GPL2 and LICENSE-GPL3 included in this package.
 *
 * SIP is supplied WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "sip.h"
#include "parser.h"


#ifndef FLEX_SCANNER
#error "Only flex is supported at the moment"
#endif


#define YY_NO_UNISTD_H
#define YY_FATAL_ERROR(s)       fatallex(s)

#define MAX_INCLUDE_DEPTH       10
#define MAX_CODE_LINE_LENGTH    1000


static struct inputFile {
    int lineno;                         /* The line number. */
    YY_BUFFER_STATE bs;                 /* The flex buffer state handle. */
    char *name;                         /* The file name. */
    char *cwd;                          /* The path part of the file name. */
    parserContext pc;                   /* The parser context. */
} inputFileStack[MAX_INCLUDE_DEPTH];

static int currentFile = -1;            /* Index of the current input file. */
static char codeLine[MAX_CODE_LINE_LENGTH + 2]; /* The current code line. */
static int codeIdx = -1;                /* Index of next code character. */

static FILE *openFile(const char *);
static void fatallex(char *);
%}

%x code
%x ccomment

%%

^[ \t]*%API                 {return TK_API;}
^[ \t]*%DefaultEncoding     {return TK_DEFENCODING;}
^[ \t]*%Plugin              {return TK_PLUGIN;}
^[ \t]*%Include             {return TK_INCLUDE;}
^[ \t]*%OptionalInclude     {return TK_OPTINCLUDE;}
^[ \t]*%Import              {return TK_IMPORT;}
^[ \t]*%Module              {return TK_MODULE;}
^[ \t]*%CModule             {return TK_CMODULE;}
^[ \t]*%ConsolidatedModule  {return TK_CONSMODULE;}
^[ \t]*%CompositeModule     {return TK_COMPOMODULE;}
^[ \t]*%Timeline            {return TK_TIMELINE;}
^[ \t]*%Platforms           {return TK_PLATFORMS;}
^[ \t]*%Feature             {return TK_FEATURE;}
^[ \t]*%License             {return TK_LICENSE;}
^[ \t]*%MappedType          {return TK_MAPPEDTYPE;}
^[ \t]*%Exception           {return TK_EXCEPTION;}
^[ \t]*%If                  {return TK_IF;}
^[ \t]*%DefaultMetatype     {return TK_DEFMETATYPE;}
^[ \t]*%DefaultSupertype    {return TK_DEFSUPERTYPE;}
<INITIAL>^[ \t]*%End        {return TK_END;}
class                       {return TK_CLASS;}
struct                      {return TK_STRUCT;}
public                      {return TK_PUBLIC;}
protected                   {return TK_PROTECTED;}
private                     {return TK_PRIVATE;}
signals                     {return TK_SIGNALS;}
Q_SIGNALS                   {return TK_SIGNALS;}
Q_SIGNAL                    {return TK_SIGNAL_METHOD;}
slots                       {return TK_SLOTS;}
Q_SLOTS                     {return TK_SLOTS;}
Q_SLOT                      {return TK_SLOT_METHOD;}
char                        {return TK_CHAR;}
wchar_t                     {return TK_WCHAR_T;}
bool                        {return TK_BOOL;}
short                       {return TK_SHORT;}
int                         {return TK_INT;}
long                        {return TK_LONG;}
float                       {return TK_FLOAT;}
double                      {return TK_DOUBLE;}
void                        {return TK_VOID;}
virtual                     {return TK_VIRTUAL;}
enum                        {return TK_ENUM;}
signed                      {return TK_SIGNED;}
unsigned                    {return TK_UNSIGNED;}
const                       {return TK_CONST;}
static                      {return TK_STATIC;}
true                        {return TK_TRUE;}
false                       {return TK_FALSE;}
NULL                        {return TK_NULL;}
typedef                     {return TK_TYPEDEF;}
namespace                   {return TK_NAMESPACE;}
operator                    {return TK_OPERATOR;}
throw                       {return TK_THROW;}
explicit                    {return TK_EXPLICIT;}
template                    {return TK_TEMPLATE;}
::                          {return TK_SCOPE;}
\|\|                        {return TK_LOGICAL_OR;}
SIP_PYOBJECT                {return TK_PYOBJECT;}
SIP_PYTUPLE                 {return TK_PYTUPLE;}
SIP_PYLIST                  {return TK_PYLIST;}
SIP_PYDICT                  {return TK_PYDICT;}
SIP_PYCALLABLE              {return TK_PYCALLABLE;}
SIP_PYSLICE                 {return TK_PYSLICE;}
SIP_PYTYPE                  {return TK_PYTYPE;}
SIP_SIGNAL                  {return TK_SIPSIGNAL;}
SIP_SLOT                    {return TK_SIPSLOT;}
SIP_ANYSLOT                 {return TK_SIPANYSLOT;}
SIP_RXOBJ_CON               {return TK_SIPRXCON;}
SIP_RXOBJ_DIS               {return TK_SIPRXDIS;}
SIP_SLOT_CON                {return TK_SIPSLOTCON;}
SIP_SLOT_DIS                {return TK_SIPSLOTDIS;}
SIP_QOBJECT                 {return TK_QOBJECT;}
\.\.\.                      {return TK_ELLIPSIS;}


[ \t\r] {           /* Ignore whitespace. */
    ;
}

\n {                /* Maintain the line number. */
    ++inputFileStack[currentFile].lineno;

    if (codeIdx == 0)
    {
        BEGIN code;
    }
}

\/\/.* {            /* Ignore C++ style comments. */
    ;
}


-?[0-9]+ {          /* A signed decimal number. */
    yylval.number = strtol(yytext,NULL,0);
    return TK_NUMBER;
}


-?(([0-9]+)|([0-9]*\.[0-9]*)([eE][-+]?[0-9]+)?)[fF]? {/* A floating point number. */
    yylval.real = strtod(yytext,NULL);
    return TK_REAL;
}


0x[0-9a-fA-F]+ {        /* An unsigned hexadecimal number. */
    yylval.number = strtol(yytext,NULL,16);
    return TK_NUMBER;
}


[_A-Za-z][_A-Za-z0-9]* {    /* An identifier name. */
    yylval.text = sipStrdup(yytext);
    return TK_NAME;
}


[._A-Za-z][._/A-Za-z0-9\-]*[._A-Za-z0-9] {  /* A relative pathname. */
    yylval.text = sipStrdup(yytext);
    return TK_PATHNAME;
}


\"[^"\n]*["\n] {        /* A double-quoted string. */
    char *dp, *sp;

    /* Copy the string without the quotes. */

    yylval.text = sipMalloc(strlen(yytext) + 1);

    dp = yylval.text;
    sp = yytext;

    while (*sp != '\0')
    {
        if (*sp != '"')
            *dp++ = *sp;

        ++sp;
    }

    *dp = '\0';

    return TK_STRING;
}


\'[^'\n]*['\n] {        /* A single-quoted character. */
    if (strlen(yytext) != 3)
        fatallex("Exactly one character expected between single quotes");

    yylval.qchar = yytext[1];

    return TK_QCHAR;
}


\/\* {              /* Ignore C-style comments. */
    BEGIN ccomment;
}
<ccomment>\n {
    ++inputFileStack[currentFile].lineno;
}
<ccomment>\*\/ {
    BEGIN INITIAL;
}
<ccomment>. {
    ;
}


^%Copying {         /* The software license. */
    codeIdx = 0;
    return TK_COPYING;
}

^%ConvertFromTypeCode {     /* The start of a from-type code block. */
    codeIdx = 0;
    return TK_FROMTYPE;
}

^%ConvertToTypeCode {       /* The start of a to-type code block. */
    codeIdx = 0;
    return TK_TOTYPE;
}

^%ConvertToSubClassCode {   /* The start of a to-sub-class code block. */
    codeIdx = 0;
    return TK_TOSUBCLASS;
}

^%ExportedHeaderCode {      /* The start of an exported header code block. */
    codeIdx = 0;
    return TK_EXPHEADERCODE;
}

^%ModuleHeaderCode {        /* The start of a module header code block. */
    codeIdx = 0;
    return TK_MODHEADERCODE;
}

^%TypeHeaderCode {      /* The start of a type header code block. */
    codeIdx = 0;
    return TK_TYPEHEADERCODE;
}

^%PreInitialisationCode {   /* The start of a pre-initialisation code block. */
    codeIdx = 0;
    return TK_PREINITCODE;
}

^%InitialisationCode {      /* The start of an initialisation code block. */
    codeIdx = 0;
    return TK_INITCODE;
}

^%PostInitialisationCode {  /* The start of a post-initialisation code block. */
    codeIdx = 0;
    return TK_POSTINITCODE;
}

^%UnitCode {            /* The start of a unit code block. */
    codeIdx = 0;
    return TK_UNITCODE;
}

^%UnitPostIncludeCode { /* The start of a unit post-include code block. */
    codeIdx = 0;
    return TK_UNITPOSTINCLUDECODE;
}

^%ModuleCode {          /* The start of a module code block. */
    codeIdx = 0;
    return TK_MODCODE;
}

^%TypeCode {            /* The start of a type code block. */
    codeIdx = 0;
    return TK_TYPECODE;
}

^%MethodCode {          /* The start of a C++ method code block. */
    codeIdx = 0;
    return TK_METHODCODE;
}

^%VirtualCatcherCode {      /* The start of a C++ virtual code block. */
    codeIdx = 0;
    return TK_VIRTUALCATCHERCODE;
}

^%GCTraverseCode {      /* The start of a traverse code block. */
    codeIdx = 0;
    return TK_TRAVERSECODE;
}

^%GCClearCode {         /* The start of a clear code block. */
    codeIdx = 0;
    return TK_CLEARCODE;
}

^%BIGetBufferCode {     /* The start of a get buffer code block. */
    codeIdx = 0;
    return TK_GETBUFFERCODE;
}

^%BIReleaseBufferCode {     /* The start of a release buffer code block. */
    codeIdx = 0;
    return TK_RELEASEBUFFERCODE;
}

^%BIGetReadBufferCode {     /* The start of a read buffer code block. */
    codeIdx = 0;
    return TK_READBUFFERCODE;
}

^%BIGetWriteBufferCode {    /* The start of a write buffer code block. */
    codeIdx = 0;
    return TK_WRITEBUFFERCODE;
}

^%BIGetSegCountCode {       /* The start of a segment count code block. */
    codeIdx = 0;
    return TK_SEGCOUNTCODE;
}

^%BIGetCharBufferCode {     /* The start of a char buffer code block. */
    codeIdx = 0;
    return TK_CHARBUFFERCODE;
}

^%PickleCode {         /* The start of a pickle code block. */
    codeIdx = 0;
    return TK_PICKLECODE;
}

^%PrePythonCode {       /* The start of a pre-Python code block. */
    codeIdx = 0;
    return TK_PREPYCODE;
}

^%RaiseCode {           /* The start of a raise exception code block. */
    codeIdx = 0;
    return TK_RAISECODE;
}

^%Docstring {           /* The start of a docstring block. */
    codeIdx = 0;
    return TK_DOCSTRING;
}

^%Doc {             /* The start of a documentation block. */
    codeIdx = 0;
    return TK_DOC;
}

^%ExportedDoc {         /* The start of an exported documentation block. */
    codeIdx = 0;
    return TK_EXPORTEDDOC;
}

^%Makefile {            /* The start of a Makefile code block. */
    codeIdx = 0;
    return TK_MAKEFILE;
}

^%AccessCode {          /* The start of an access code block. */
    codeIdx = 0;
    return TK_ACCESSCODE;
}

^%GetCode {         /* The start of a get code block. */
    codeIdx = 0;
    return TK_GETCODE;
}

^%SetCode {         /* The start of a set code block. */
    codeIdx = 0;
    return TK_SETCODE;
}

<code>^%End {           /* The end of a code block. */
    BEGIN INITIAL;
    codeIdx = -1;
    return TK_END;
}

<code>\n {          /* The end of a code line . */
    struct inputFile *ifp;

    codeLine[codeIdx] = '\n';
    codeLine[codeIdx + 1] = '\0';
    codeIdx = 0;

    ifp = &inputFileStack[currentFile];

    yylval.codeb = sipMalloc(sizeof (codeBlock));

    yylval.codeb -> frag = sipStrdup(codeLine);
    yylval.codeb -> linenr = ifp -> lineno++;
    yylval.codeb -> filename = sipStrdup(ifp -> name);
    yylval.codeb -> next = NULL;

    return TK_CODELINE;
}

<code>. {           /* The contents of a code line. */
    if (codeIdx == MAX_CODE_LINE_LENGTH)
        fatallex("Line is too long");

    codeLine[codeIdx++] = yytext[0];
}

. {             /* Anything else is returned as is. */
    return yytext[0];
}

%%

/*
 * Hook into EOF handling.  Return 0 if there is more to process.
 */

int yywrap()
{
    char *cwd;
    struct inputFile *ifp;

    if ((cwd = inputFileStack[currentFile].cwd) != NULL)
        free(cwd);

    ifp = &inputFileStack[currentFile--];

    /* Tell the parser if this is the end of a file. */

    parserEOF(ifp -> name, &ifp -> pc);

    /* Tidy up this file. */

    fclose(yyin);
    free(ifp -> name);

    /* See if this was the original file. */

    if (currentFile < 0)
        return 1;

    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(ifp -> bs);

    return 0;
}


/*
 * Set up an input file to be read by the lexer, opening it if necessary.  TRUE
 * is returned if the file has not already been read.
 */
int setInputFile(FILE *open_fp, parserContext *pc, int optional)
{
    static stringList *all = NULL;
    char *cwd, *fullname = NULL;
    FILE *fp = open_fp;

    if (currentFile >= MAX_INCLUDE_DEPTH - 1)
        fatal("Too many nested %%Include, %%OptionalInclude or %%Import statements\n");

    if (fp != NULL || (fp = openFile(pc->filename)) != NULL)
        fullname = sipStrdup(pc->filename);
    else
    {
        char *cwd;

        /* Try the directory that contains the current file. */
        if (currentFile >= 0 && (cwd = inputFileStack[currentFile].cwd) != NULL)
        {
            fullname = concat(cwd, "/", pc->filename, NULL);

            if ((fp = openFile(fullname)) == NULL)
            {
                free(fullname);
                fullname = NULL;
            }
        }
    }

    /* Try the include path if we haven't found anything yet. */
    if (fullname == NULL)
    {
        stringList *sl;

        fullname = NULL;

        for (sl = includeDirList; sl != NULL; sl = sl -> next)
        {
            if (fullname != NULL)
                free(fullname);

            fullname = concat(sl->s, "/", pc->filename, NULL);

            if ((fp = openFile(fullname)) != NULL)
                break;
        }

        if (fp == NULL)
        {
            if (optional)
                return FALSE;

            fatal("Unable to find file \"%s\"\n", pc->filename);
        }
    }

    /*
     * If we have just opened the file, make sure that we haven't already read
     * it.  While it should never happen with normal modules (if the user
     * doesn't specify recursive %Imports or %Includes) it is likely to happen
     * with consolidated modules.
     */
    if (open_fp == NULL)
    {
        stringList *sl;

        for (sl = all; sl != NULL; sl = sl->next)
            if (strcmp(sl->s, fullname) == 0)
            {
                fclose(fp);
                return FALSE;
            }
    }

    /* Remember the filename. */
    appendString(&all, sipStrdup(fullname));

    yyin = fp;

    ++currentFile;

    /* Remember the directory containing the new file and make it "current". */
    if ((cwd = strchr(fullname, '/')) != NULL)
    {
        cwd = sipStrdup(fullname);
        *strrchr(cwd,'/') = '\0';
    }

    inputFileStack[currentFile].lineno = 1;
    inputFileStack[currentFile].name = fullname;
    inputFileStack[currentFile].pc = *pc;
    inputFileStack[currentFile].cwd = cwd;

    if (currentFile > 0)
    {
        inputFileStack[currentFile].bs = YY_CURRENT_BUFFER;
        yy_switch_to_buffer(yy_create_buffer(yyin,YY_BUF_SIZE));
    }

    return TRUE;
}


/*
 * Open a file for reading or return NULL if it doesn't exist.  Any other error
 * is fatal.
 */
static FILE *openFile(const char *name)
{
    FILE *fp;

    if ((fp = fopen(name,"r")) == NULL && errno != ENOENT)
        fatal("Error in opening file %s\n",name);

    return fp;
}


/*
 * Handle fatal yacc errors.
 */
void yyerror(char *s)
{
    if (currentFile < 0)
        fatal("%s\n", s);

    fatal("%s:%d: %s\n",
        inputFileStack[currentFile].name,
        inputFileStack[currentFile].lineno,
        s);
}


/*
 * Handle warnings while parsing.
 */
void yywarning(char *s)
{
    warning("%s:%d: %s\n",
        inputFileStack[currentFile].name,
        inputFileStack[currentFile].lineno,
        s);
}


/*
 * Handle fatal lex errors.
 */
static void fatallex(char *s)
{
    fatal("%s:%d: Lexical analyser error: %s\n",
        inputFileStack[currentFile].name,
        inputFileStack[currentFile].lineno,
        s);
}
