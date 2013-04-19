
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_API = 258,
     TK_DEFENCODING = 259,
     TK_PLUGIN = 260,
     TK_DOCSTRING = 261,
     TK_DOC = 262,
     TK_EXPORTEDDOC = 263,
     TK_MAKEFILE = 264,
     TK_ACCESSCODE = 265,
     TK_GETCODE = 266,
     TK_SETCODE = 267,
     TK_PREINITCODE = 268,
     TK_INITCODE = 269,
     TK_POSTINITCODE = 270,
     TK_UNITCODE = 271,
     TK_UNITPOSTINCLUDECODE = 272,
     TK_MODCODE = 273,
     TK_TYPECODE = 274,
     TK_PREPYCODE = 275,
     TK_COPYING = 276,
     TK_MAPPEDTYPE = 277,
     TK_CODELINE = 278,
     TK_IF = 279,
     TK_END = 280,
     TK_NAME = 281,
     TK_PATHNAME = 282,
     TK_STRING = 283,
     TK_VIRTUALCATCHERCODE = 284,
     TK_TRAVERSECODE = 285,
     TK_CLEARCODE = 286,
     TK_GETBUFFERCODE = 287,
     TK_RELEASEBUFFERCODE = 288,
     TK_READBUFFERCODE = 289,
     TK_WRITEBUFFERCODE = 290,
     TK_SEGCOUNTCODE = 291,
     TK_CHARBUFFERCODE = 292,
     TK_PICKLECODE = 293,
     TK_METHODCODE = 294,
     TK_FROMTYPE = 295,
     TK_TOTYPE = 296,
     TK_TOSUBCLASS = 297,
     TK_INCLUDE = 298,
     TK_OPTINCLUDE = 299,
     TK_IMPORT = 300,
     TK_EXPHEADERCODE = 301,
     TK_MODHEADERCODE = 302,
     TK_TYPEHEADERCODE = 303,
     TK_MODULE = 304,
     TK_CMODULE = 305,
     TK_CONSMODULE = 306,
     TK_COMPOMODULE = 307,
     TK_CLASS = 308,
     TK_STRUCT = 309,
     TK_PUBLIC = 310,
     TK_PROTECTED = 311,
     TK_PRIVATE = 312,
     TK_SIGNALS = 313,
     TK_SIGNAL_METHOD = 314,
     TK_SLOTS = 315,
     TK_SLOT_METHOD = 316,
     TK_BOOL = 317,
     TK_SHORT = 318,
     TK_INT = 319,
     TK_LONG = 320,
     TK_FLOAT = 321,
     TK_DOUBLE = 322,
     TK_CHAR = 323,
     TK_WCHAR_T = 324,
     TK_VOID = 325,
     TK_PYOBJECT = 326,
     TK_PYTUPLE = 327,
     TK_PYLIST = 328,
     TK_PYDICT = 329,
     TK_PYCALLABLE = 330,
     TK_PYSLICE = 331,
     TK_PYTYPE = 332,
     TK_VIRTUAL = 333,
     TK_ENUM = 334,
     TK_SIGNED = 335,
     TK_UNSIGNED = 336,
     TK_SCOPE = 337,
     TK_LOGICAL_OR = 338,
     TK_CONST = 339,
     TK_STATIC = 340,
     TK_SIPSIGNAL = 341,
     TK_SIPSLOT = 342,
     TK_SIPANYSLOT = 343,
     TK_SIPRXCON = 344,
     TK_SIPRXDIS = 345,
     TK_SIPSLOTCON = 346,
     TK_SIPSLOTDIS = 347,
     TK_NUMBER = 348,
     TK_REAL = 349,
     TK_TYPEDEF = 350,
     TK_NAMESPACE = 351,
     TK_TIMELINE = 352,
     TK_PLATFORMS = 353,
     TK_FEATURE = 354,
     TK_LICENSE = 355,
     TK_QCHAR = 356,
     TK_TRUE = 357,
     TK_FALSE = 358,
     TK_NULL = 359,
     TK_OPERATOR = 360,
     TK_THROW = 361,
     TK_QOBJECT = 362,
     TK_EXCEPTION = 363,
     TK_RAISECODE = 364,
     TK_EXPLICIT = 365,
     TK_TEMPLATE = 366,
     TK_ELLIPSIS = 367,
     TK_DEFMETATYPE = 368,
     TK_DEFSUPERTYPE = 369
   };
#endif
/* Tokens.  */
#define TK_API 258
#define TK_DEFENCODING 259
#define TK_PLUGIN 260
#define TK_DOCSTRING 261
#define TK_DOC 262
#define TK_EXPORTEDDOC 263
#define TK_MAKEFILE 264
#define TK_ACCESSCODE 265
#define TK_GETCODE 266
#define TK_SETCODE 267
#define TK_PREINITCODE 268
#define TK_INITCODE 269
#define TK_POSTINITCODE 270
#define TK_UNITCODE 271
#define TK_UNITPOSTINCLUDECODE 272
#define TK_MODCODE 273
#define TK_TYPECODE 274
#define TK_PREPYCODE 275
#define TK_COPYING 276
#define TK_MAPPEDTYPE 277
#define TK_CODELINE 278
#define TK_IF 279
#define TK_END 280
#define TK_NAME 281
#define TK_PATHNAME 282
#define TK_STRING 283
#define TK_VIRTUALCATCHERCODE 284
#define TK_TRAVERSECODE 285
#define TK_CLEARCODE 286
#define TK_GETBUFFERCODE 287
#define TK_RELEASEBUFFERCODE 288
#define TK_READBUFFERCODE 289
#define TK_WRITEBUFFERCODE 290
#define TK_SEGCOUNTCODE 291
#define TK_CHARBUFFERCODE 292
#define TK_PICKLECODE 293
#define TK_METHODCODE 294
#define TK_FROMTYPE 295
#define TK_TOTYPE 296
#define TK_TOSUBCLASS 297
#define TK_INCLUDE 298
#define TK_OPTINCLUDE 299
#define TK_IMPORT 300
#define TK_EXPHEADERCODE 301
#define TK_MODHEADERCODE 302
#define TK_TYPEHEADERCODE 303
#define TK_MODULE 304
#define TK_CMODULE 305
#define TK_CONSMODULE 306
#define TK_COMPOMODULE 307
#define TK_CLASS 308
#define TK_STRUCT 309
#define TK_PUBLIC 310
#define TK_PROTECTED 311
#define TK_PRIVATE 312
#define TK_SIGNALS 313
#define TK_SIGNAL_METHOD 314
#define TK_SLOTS 315
#define TK_SLOT_METHOD 316
#define TK_BOOL 317
#define TK_SHORT 318
#define TK_INT 319
#define TK_LONG 320
#define TK_FLOAT 321
#define TK_DOUBLE 322
#define TK_CHAR 323
#define TK_WCHAR_T 324
#define TK_VOID 325
#define TK_PYOBJECT 326
#define TK_PYTUPLE 327
#define TK_PYLIST 328
#define TK_PYDICT 329
#define TK_PYCALLABLE 330
#define TK_PYSLICE 331
#define TK_PYTYPE 332
#define TK_VIRTUAL 333
#define TK_ENUM 334
#define TK_SIGNED 335
#define TK_UNSIGNED 336
#define TK_SCOPE 337
#define TK_LOGICAL_OR 338
#define TK_CONST 339
#define TK_STATIC 340
#define TK_SIPSIGNAL 341
#define TK_SIPSLOT 342
#define TK_SIPANYSLOT 343
#define TK_SIPRXCON 344
#define TK_SIPRXDIS 345
#define TK_SIPSLOTCON 346
#define TK_SIPSLOTDIS 347
#define TK_NUMBER 348
#define TK_REAL 349
#define TK_TYPEDEF 350
#define TK_NAMESPACE 351
#define TK_TIMELINE 352
#define TK_PLATFORMS 353
#define TK_FEATURE 354
#define TK_LICENSE 355
#define TK_QCHAR 356
#define TK_TRUE 357
#define TK_FALSE 358
#define TK_NULL 359
#define TK_OPERATOR 360
#define TK_THROW 361
#define TK_QOBJECT 362
#define TK_EXCEPTION 363
#define TK_RAISECODE 364
#define TK_EXPLICIT 365
#define TK_TEMPLATE 366
#define TK_ELLIPSIS 367
#define TK_DEFMETATYPE 368
#define TK_DEFSUPERTYPE 369




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 147 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"

    char            qchar;
    char            *text;
    long            number;
    double          real;
    argDef          memArg;
    signatureDef    signature;
    signatureDef    *optsignature;
    throwArgs       *throwlist;
    codeBlock       *codeb;
    valueDef        value;
    valueDef        *valp;
    optFlags        optflags;
    optFlag         flag;
    scopedNameDef   *scpvalp;
    fcallDef        fcall;
    int             boolean;
    exceptionDef    exceptionbase;
    classDef        *klass;



/* Line 1676 of yacc.c  */
#line 303 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


