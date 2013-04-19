
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 19 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sip.h"


#define MAX_NESTED_IF       10
#define MAX_NESTED_SCOPE    10

#define inMainModule()      (currentSpec->module == currentModule || currentModule->container != NULL)


static sipSpec *currentSpec;            /* The current spec being parsed. */
static stringList *neededQualifiers;    /* The list of required qualifiers. */
static stringList *excludedQualifiers;  /* The list of excluded qualifiers. */
static moduleDef *currentModule;        /* The current module being parsed. */
static mappedTypeDef *currentMappedType;    /* The current mapped type. */
static enumDef *currentEnum;            /* The current enum being parsed. */
static int sectionFlags;                /* The current section flags. */
static int currentOverIsVirt;           /* Set if the overload is virtual. */
static int currentCtorIsExplicit;       /* Set if the ctor is explicit. */
static int currentIsStatic;             /* Set if the current is static. */
static int currentIsSignal;             /* Set if the current is Q_SIGNAL. */
static int currentIsSlot;               /* Set if the current is Q_SLOT. */
static int currentIsTemplate;           /* Set if the current is a template. */
static char *previousFile;              /* The file just parsed. */
static parserContext currentContext;    /* The current context. */
static int skipStackPtr;                /* The skip stack pointer. */
static int skipStack[MAX_NESTED_IF];    /* Stack of skip flags. */
static classDef *scopeStack[MAX_NESTED_SCOPE];  /* The scope stack. */
static int sectFlagsStack[MAX_NESTED_SCOPE];    /* The section flags stack. */
static int currentScopeIdx;             /* The scope stack index. */
static int currentTimelineOrder;        /* The current timeline order. */
static classList *currentSupers;        /* The current super-class list. */
static int defaultKwdArgs;              /* Support keyword arguments by default. */
static int makeProtPublic;              /* Treat protected items as public. */


static const char *getPythonName(optFlags *optflgs, const char *cname);
static classDef *findClass(sipSpec *pt, ifaceFileType iftype,
        apiVersionRangeDef *api_range, scopedNameDef *fqname);
static classDef *findClassWithInterface(sipSpec *pt, ifaceFileDef *iff);
static classDef *newClass(sipSpec *pt, ifaceFileType iftype,
        apiVersionRangeDef *api_range, scopedNameDef *snd);
static void finishClass(sipSpec *, moduleDef *, classDef *, optFlags *);
static exceptionDef *findException(sipSpec *pt, scopedNameDef *fqname, int new);
static mappedTypeDef *newMappedType(sipSpec *,argDef *, optFlags *);
static enumDef *newEnum(sipSpec *pt, moduleDef *mod, mappedTypeDef *mt_scope,
        char *name, optFlags *of, int flags);
static void instantiateClassTemplate(sipSpec *pt, moduleDef *mod, classDef *scope, scopedNameDef *fqname, classTmplDef *tcd, templateDef *td);
static void newTypedef(sipSpec *, moduleDef *, char *, argDef *, optFlags *);
static void newVar(sipSpec *, moduleDef *, char *, int, argDef *, optFlags *,
        codeBlock *, codeBlock *, codeBlock *);
static void newCtor(char *, int, signatureDef *, optFlags *, codeBlock *,
        throwArgs *, signatureDef *, int, codeBlock *);
static void newFunction(sipSpec *, moduleDef *, classDef *, mappedTypeDef *,
        int, int, int, int, int, char *, signatureDef *, int, int, optFlags *,
        codeBlock *, codeBlock *, throwArgs *, signatureDef *, codeBlock *);
static optFlag *findOptFlag(optFlags *,char *,flagType);
static memberDef *findFunction(sipSpec *, moduleDef *, classDef *,
        mappedTypeDef *, const char *, int, int, int);
static void checkAttributes(sipSpec *, moduleDef *, classDef *,
        mappedTypeDef *, const char *, int);
static void newModule(FILE *fp, char *filename);
static moduleDef *allocModule();
static void parseFile(FILE *fp, char *name, moduleDef *prevmod, int optional);
static void handleEOF(void);
static void handleEOM(void);
static qualDef *findQualifier(const char *name);
static scopedNameDef *text2scopedName(ifaceFileDef *scope, char *text);
static scopedNameDef *scopeScopedName(ifaceFileDef *scope,
        scopedNameDef *name);
static void pushScope(classDef *);
static void popScope(void);
static classDef *currentScope(void);
static void newQualifier(moduleDef *,int,int,char *,qualType);
static void newImport(char *filename);
static int timePeriod(char *,char *);
static int platOrFeature(char *,int);
static int isNeeded(qualDef *);
static int notSkipping(void);
static void getHooks(optFlags *,char **,char **);
static int getTransfer(optFlags *optflgs);
static int getReleaseGIL(optFlags *optflgs);
static int getHoldGIL(optFlags *optflgs);
static int getDeprecated(optFlags *optflgs);
static int getAllowNone(optFlags *optflgs);
static const char *getDocType(optFlags *optflgs);
static const char *getDocValue(optFlags *optflgs);
static void templateSignature(signatureDef *sd, int result, classTmplDef *tcd, templateDef *td, classDef *ncd);
static void templateType(argDef *ad, classTmplDef *tcd, templateDef *td, classDef *ncd);
static int search_back(const char *end, const char *start, const char *target);
static char *type2string(argDef *ad);
static char *scopedNameToString(scopedNameDef *name);
static void addUsedFromCode(sipSpec *pt, ifaceFileList **used, const char *sname);
static int sameName(scopedNameDef *snd, const char *sname);
static int stringFind(stringList *sl, const char *s);
static void setModuleName(sipSpec *pt, moduleDef *mod, const char *fullname);
static int foundInScope(scopedNameDef *fq_name, scopedNameDef *rel_name);
static void defineClass(scopedNameDef *snd, classList *supers, optFlags *of);
static classDef *completeClass(scopedNameDef *snd, optFlags *of, int has_def);
static memberDef *instantiateTemplateMethods(memberDef *tmd, moduleDef *mod);
static void instantiateTemplateEnums(sipSpec *pt, classTmplDef *tcd,
        templateDef *td, classDef *cd, ifaceFileList **used,
        scopedNameDef *type_names, scopedNameDef *type_values);
static void instantiateTemplateVars(sipSpec *pt, classTmplDef *tcd,
        templateDef *td, classDef *cd, ifaceFileList **used,
        scopedNameDef *type_names, scopedNameDef *type_values);
static overDef *instantiateTemplateOverloads(sipSpec *pt, overDef *tod,
        memberDef *tmethods, memberDef *methods, classTmplDef *tcd,
        templateDef *td, classDef *cd, ifaceFileList **used,
        scopedNameDef *type_names, scopedNameDef *type_values);
static void resolveAnyTypedef(sipSpec *pt, argDef *ad);
static void addVariable(sipSpec *pt, varDef *vd);
static void applyTypeFlags(moduleDef *mod, argDef *ad, optFlags *flags);
static argType convertEncoding(const char *encoding);
static apiVersionRangeDef *getAPIRange(optFlags *optflgs);
static apiVersionRangeDef *convertAPIRange(moduleDef *mod, nameDef *name,
        int from, int to);
static char *convertFeaturedString(char *fs);
static scopedNameDef *text2scopePart(char *text);
static int usesKeywordArgs(optFlags *optflgs, signatureDef *sd);
static char *strip(char *s);
static int isEnabledFeature(const char *name);


/* Line 189 of yacc.c  */
#line 202 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 489 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 501 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  137
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  152
/* YYNRULES -- Number of rules.  */
#define YYNRULES  375
/* YYNRULES -- Number of states.  */
#define YYNSTATES  641

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   369

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   120,     2,     2,     2,   135,   127,     2,
     118,   119,   125,   124,   122,   121,     2,   126,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   132,   117,
     130,   123,   131,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   133,     2,   134,   136,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   115,   128,   116,   129,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    36,    38,
      40,    42,    44,    46,    48,    50,    52,    54,    56,    58,
      60,    62,    64,    66,    68,    70,    72,    74,    76,    78,
      80,    82,    84,    86,    88,    90,    92,    94,    96,    98,
     101,   104,   108,   118,   119,   123,   126,   127,   133,   134,
     141,   146,   148,   151,   153,   155,   158,   161,   163,   165,
     179,   180,   188,   190,   193,   194,   200,   202,   205,   207,
     210,   211,   217,   219,   222,   224,   229,   231,   234,   238,
     243,   245,   249,   251,   254,   257,   260,   263,   266,   270,
     272,   274,   276,   278,   279,   281,   284,   287,   290,   291,
     294,   295,   298,   299,   302,   305,   308,   311,   314,   315,
     317,   320,   323,   326,   329,   332,   335,   338,   341,   344,
     347,   350,   353,   356,   359,   362,   365,   368,   371,   374,
     379,   382,   384,   387,   388,   397,   398,   400,   401,   403,
     404,   406,   408,   411,   413,   415,   420,   421,   423,   424,
     427,   428,   431,   433,   437,   439,   441,   443,   445,   447,
     449,   450,   452,   454,   456,   458,   461,   463,   467,   469,
     471,   476,   478,   480,   482,   484,   486,   488,   490,   491,
     493,   497,   503,   515,   516,   517,   526,   527,   531,   536,
     537,   538,   547,   548,   551,   553,   557,   559,   560,   564,
     566,   569,   571,   573,   575,   577,   579,   581,   583,   585,
     587,   589,   591,   593,   595,   597,   599,   601,   603,   605,
     607,   609,   611,   613,   615,   618,   621,   625,   629,   633,
     636,   637,   639,   651,   652,   656,   658,   669,   670,   676,
     677,   684,   685,   687,   702,   710,   725,   739,   741,   743,
     745,   747,   749,   751,   753,   755,   758,   761,   764,   767,
     770,   773,   776,   779,   782,   785,   789,   793,   795,   798,
     801,   803,   806,   809,   812,   814,   817,   818,   820,   821,
     824,   825,   829,   831,   835,   837,   841,   843,   849,   851,
     853,   856,   857,   859,   860,   863,   864,   867,   869,   870,
     872,   876,   881,   886,   891,   895,   899,   906,   913,   917,
     920,   921,   925,   926,   930,   932,   933,   937,   939,   941,
     943,   944,   948,   950,   958,   963,   967,   971,   972,   974,
     975,   978,   980,   985,   988,   991,   993,   995,   998,  1000,
    1002,  1005,  1008,  1012,  1014,  1016,  1018,  1021,  1024,  1026,
    1028,  1030,  1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,
    1048,  1052,  1053,  1058,  1059,  1061
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     138,     0,    -1,   139,    -1,   138,   139,    -1,    -1,   140,
     141,    -1,   178,    -1,   176,    -1,   177,    -1,   144,    -1,
     188,    -1,   182,    -1,   183,    -1,   184,    -1,   145,    -1,
     165,    -1,   160,    -1,   164,    -1,   173,    -1,   143,    -1,
     174,    -1,   175,    -1,   189,    -1,   190,    -1,   202,    -1,
     204,    -1,   205,    -1,   206,    -1,   207,    -1,   208,    -1,
     209,    -1,   210,    -1,   211,    -1,   212,    -1,   149,    -1,
     151,    -1,   142,    -1,   169,    -1,   172,    -1,   157,    -1,
     234,    -1,   240,    -1,   237,    -1,   146,    -1,   233,    -1,
     215,    -1,   257,    -1,   280,    -1,   191,    -1,     4,    28,
      -1,     5,    26,    -1,     3,    26,    93,    -1,   108,   229,
     147,   261,   115,   192,   148,   116,   117,    -1,    -1,   118,
     229,   119,    -1,   109,   213,    -1,    -1,    22,   285,   261,
     150,   153,    -1,    -1,   239,    22,   285,   261,   152,   153,
      -1,   115,   154,   116,   117,    -1,   155,    -1,   154,   155,
      -1,   191,    -1,   203,    -1,    40,   213,    -1,    41,   213,
      -1,   215,    -1,   156,    -1,    85,   281,    26,   118,   269,
     119,   259,   287,   261,   255,   117,   266,   267,    -1,    -1,
      96,    26,   158,   115,   159,   116,   117,    -1,   142,    -1,
     159,   142,    -1,    -1,    98,   161,   115,   162,   116,    -1,
     163,    -1,   162,   163,    -1,    26,    -1,    99,    26,    -1,
      -1,    97,   166,   115,   167,   116,    -1,   168,    -1,   167,
     168,    -1,    26,    -1,    24,   118,   171,   119,    -1,    26,
      -1,   120,    26,    -1,   170,    83,    26,    -1,   170,    83,
     120,    26,    -1,   170,    -1,   218,   121,   218,    -1,    25,
      -1,   100,   261,    -1,   113,   180,    -1,   114,   180,    -1,
      51,   180,    -1,    52,   180,    -1,   179,   180,   181,    -1,
      49,    -1,    50,    -1,    26,    -1,    27,    -1,    -1,    93,
      -1,    43,    27,    -1,    44,    27,    -1,    45,    27,    -1,
      -1,    10,   213,    -1,    -1,    11,   213,    -1,    -1,    12,
     213,    -1,    21,   213,    -1,    46,   213,    -1,    47,   213,
      -1,    48,   213,    -1,    -1,   191,    -1,    30,   213,    -1,
      31,   213,    -1,    32,   213,    -1,    33,   213,    -1,    34,
     213,    -1,    35,   213,    -1,    36,   213,    -1,    37,   213,
      -1,    38,   213,    -1,    18,   213,    -1,    19,   213,    -1,
      13,   213,    -1,    14,   213,    -1,    15,   213,    -1,    16,
     213,    -1,    17,   213,    -1,    20,   213,    -1,     7,   213,
      -1,     8,   213,    -1,     9,    27,   217,   213,    -1,   214,
      25,    -1,    23,    -1,   214,    23,    -1,    -1,    79,   218,
     261,   216,   115,   219,   116,   117,    -1,    -1,    27,    -1,
      -1,    26,    -1,    -1,   220,    -1,   221,    -1,   220,   221,
      -1,   169,    -1,   172,    -1,    26,   223,   261,   222,    -1,
      -1,   122,    -1,    -1,   123,   228,    -1,    -1,   123,   225,
      -1,   228,    -1,   225,   226,   228,    -1,   121,    -1,   124,
      -1,   125,    -1,   126,    -1,   127,    -1,   128,    -1,    -1,
     120,    -1,   129,    -1,   121,    -1,   124,    -1,   227,   231,
      -1,   230,    -1,   229,    82,   230,    -1,    26,    -1,   229,
      -1,   285,   118,   232,   119,    -1,    94,    -1,    93,    -1,
     102,    -1,   103,    -1,   104,    -1,    28,    -1,   101,    -1,
      -1,   225,    -1,   232,   122,   225,    -1,    95,   281,    26,
     261,   117,    -1,    95,   281,   118,   284,    26,   119,   118,
     286,   119,   261,   117,    -1,    -1,    -1,    54,   229,   235,
     243,   261,   236,   246,   117,    -1,    -1,   239,   238,   240,
      -1,   111,   130,   286,   131,    -1,    -1,    -1,    53,   229,
     241,   243,   261,   242,   246,   117,    -1,    -1,   132,   244,
      -1,   245,    -1,   244,   122,   245,    -1,   229,    -1,    -1,
     115,   247,   116,    -1,   248,    -1,   247,   248,    -1,   169,
      -1,   172,    -1,   157,    -1,   234,    -1,   240,    -1,   146,
      -1,   233,    -1,   215,    -1,   265,    -1,   203,    -1,   191,
      -1,   193,    -1,   194,    -1,   195,    -1,   196,    -1,   197,
      -1,   198,    -1,   199,    -1,   200,    -1,   201,    -1,   251,
      -1,   250,    -1,   272,    -1,    42,   213,    -1,    41,   213,
      -1,    55,   249,   132,    -1,    56,   249,   132,    -1,    57,
     249,   132,    -1,    58,   132,    -1,    -1,    60,    -1,   256,
     129,    26,   118,   119,   287,   260,   261,   117,   267,   268,
      -1,    -1,   110,   252,   253,    -1,   253,    -1,    26,   118,
     269,   119,   287,   261,   254,   117,   266,   267,    -1,    -1,
     133,   118,   269,   119,   134,    -1,    -1,   133,   281,   118,
     269,   119,   134,    -1,    -1,    78,    -1,   281,    26,   118,
     269,   119,   259,   287,   260,   261,   255,   117,   266,   267,
     268,    -1,   281,   105,   123,   118,   281,   119,   117,    -1,
     281,   105,   258,   118,   269,   119,   259,   287,   260,   261,
     255,   117,   267,   268,    -1,   105,   281,   118,   269,   119,
     259,   287,   260,   261,   255,   117,   267,   268,    -1,   124,
      -1,   121,    -1,   125,    -1,   126,    -1,   135,    -1,   127,
      -1,   128,    -1,   136,    -1,   130,   130,    -1,   131,   131,
      -1,   124,   123,    -1,   121,   123,    -1,   125,   123,    -1,
     126,   123,    -1,   135,   123,    -1,   127,   123,    -1,   128,
     123,    -1,   136,   123,    -1,   130,   130,   123,    -1,   131,
     131,   123,    -1,   129,    -1,   118,   119,    -1,   133,   134,
      -1,   130,    -1,   130,   123,    -1,   123,   123,    -1,   120,
     123,    -1,   131,    -1,   131,   123,    -1,    -1,    84,    -1,
      -1,   123,    93,    -1,    -1,   126,   262,   126,    -1,   263,
      -1,   262,   122,   263,    -1,    26,    -1,    26,   123,   264,
      -1,   180,    -1,    26,   132,   181,   121,   181,    -1,    28,
      -1,    93,    -1,     6,   213,    -1,    -1,   265,    -1,    -1,
      39,   213,    -1,    -1,    29,   213,    -1,   270,    -1,    -1,
     271,    -1,   270,   122,   271,    -1,    86,   218,   261,   224,
      -1,    87,   218,   261,   224,    -1,    88,   218,   261,   224,
      -1,    89,   218,   261,    -1,    90,   218,   261,    -1,    91,
     118,   269,   119,   218,   261,    -1,    92,   118,   269,   119,
     218,   261,    -1,   107,   218,   261,    -1,   282,   224,    -1,
      -1,    59,   273,   275,    -1,    -1,    61,   274,   275,    -1,
     275,    -1,    -1,    85,   276,   277,    -1,   277,    -1,   278,
      -1,   280,    -1,    -1,    78,   279,   257,    -1,   257,    -1,
     281,    26,   261,   117,   185,   186,   187,    -1,    84,   285,
     284,   283,    -1,   285,   284,   283,    -1,   281,   218,   261,
      -1,    -1,   127,    -1,    -1,   284,   125,    -1,   229,    -1,
     229,   130,   286,   131,    -1,    54,   229,    -1,    81,    63,
      -1,    63,    -1,    81,    -1,    81,    64,    -1,    64,    -1,
      65,    -1,    81,    65,    -1,    65,    65,    -1,    81,    65,
      65,    -1,    66,    -1,    67,    -1,    62,    -1,    80,    68,
      -1,    81,    68,    -1,    68,    -1,    69,    -1,    70,    -1,
      71,    -1,    72,    -1,    73,    -1,    74,    -1,    75,    -1,
      76,    -1,    77,    -1,   112,    -1,   281,    -1,   286,   122,
     281,    -1,    -1,   106,   118,   288,   119,    -1,    -1,   229,
      -1,   288,   122,   229,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   351,   351,   352,   355,   355,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   394,   398,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   440,
     449,   454,   480,   519,   523,   597,   602,   602,   608,   608,
     658,   672,   673,   676,   680,   684,   693,   702,   703,   706,
     720,   720,   757,   758,   761,   761,   788,   789,   792,   797,
     802,   802,   827,   828,   831,   836,   849,   852,   855,   858,
     863,   864,   869,   875,   902,   913,   924,   937,   950,   983,
     986,   991,   992,  1008,  1011,  1014,  1019,  1024,  1029,  1032,
    1037,  1040,  1045,  1048,  1053,  1058,  1063,  1068,  1073,  1076,
    1079,  1084,  1089,  1094,  1099,  1104,  1109,  1114,  1119,  1124,
    1129,  1134,  1140,  1146,  1152,  1158,  1164,  1173,  1179,  1184,
    1190,  1193,  1194,  1205,  1205,  1217,  1220,  1225,  1228,  1233,
    1234,  1237,  1238,  1241,  1242,  1243,  1271,  1272,  1275,  1276,
    1279,  1282,  1287,  1288,  1306,  1309,  1312,  1315,  1318,  1321,
    1326,  1329,  1332,  1335,  1338,  1343,  1361,  1362,  1370,  1375,
    1384,  1394,  1398,  1402,  1406,  1410,  1414,  1418,  1424,  1429,
    1435,  1453,  1460,  1485,  1491,  1485,  1506,  1506,  1532,  1537,
    1543,  1537,  1555,  1556,  1559,  1560,  1563,  1602,  1605,  1610,
    1611,  1614,  1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,
    1632,  1636,  1640,  1651,  1662,  1673,  1684,  1695,  1706,  1717,
    1728,  1739,  1740,  1741,  1742,  1753,  1764,  1771,  1778,  1785,
    1794,  1797,  1802,  1856,  1856,  1857,  1860,  1887,  1890,  1897,
    1900,  1908,  1911,  1916,  1934,  1954,  1990,  2068,  2069,  2070,
    2071,  2072,  2073,  2074,  2075,  2076,  2077,  2078,  2079,  2080,
    2081,  2082,  2083,  2084,  2085,  2086,  2087,  2088,  2089,  2090,
    2091,  2092,  2093,  2094,  2095,  2096,  2099,  2102,  2107,  2110,
    2118,  2121,  2127,  2131,  2143,  2147,  2153,  2157,  2180,  2184,
    2190,  2195,  2198,  2201,  2204,  2209,  2212,  2217,  2265,  2270,
    2276,  2303,  2312,  2321,  2330,  2341,  2349,  2363,  2377,  2383,
    2390,  2390,  2391,  2391,  2392,  2396,  2396,  2397,  2401,  2402,
    2406,  2406,  2407,  2410,  2445,  2450,  2457,  2537,  2540,  2548,
    2551,  2556,  2564,  2575,  2590,  2594,  2598,  2602,  2606,  2610,
    2614,  2618,  2622,  2626,  2630,  2634,  2638,  2642,  2646,  2650,
    2654,  2658,  2662,  2666,  2670,  2674,  2678,  2682,  2686,  2692,
    2698,  2714,  2717,  2725,  2731,  2738
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_API", "TK_DEFENCODING", "TK_PLUGIN",
  "TK_DOCSTRING", "TK_DOC", "TK_EXPORTEDDOC", "TK_MAKEFILE",
  "TK_ACCESSCODE", "TK_GETCODE", "TK_SETCODE", "TK_PREINITCODE",
  "TK_INITCODE", "TK_POSTINITCODE", "TK_UNITCODE",
  "TK_UNITPOSTINCLUDECODE", "TK_MODCODE", "TK_TYPECODE", "TK_PREPYCODE",
  "TK_COPYING", "TK_MAPPEDTYPE", "TK_CODELINE", "TK_IF", "TK_END",
  "TK_NAME", "TK_PATHNAME", "TK_STRING", "TK_VIRTUALCATCHERCODE",
  "TK_TRAVERSECODE", "TK_CLEARCODE", "TK_GETBUFFERCODE",
  "TK_RELEASEBUFFERCODE", "TK_READBUFFERCODE", "TK_WRITEBUFFERCODE",
  "TK_SEGCOUNTCODE", "TK_CHARBUFFERCODE", "TK_PICKLECODE", "TK_METHODCODE",
  "TK_FROMTYPE", "TK_TOTYPE", "TK_TOSUBCLASS", "TK_INCLUDE",
  "TK_OPTINCLUDE", "TK_IMPORT", "TK_EXPHEADERCODE", "TK_MODHEADERCODE",
  "TK_TYPEHEADERCODE", "TK_MODULE", "TK_CMODULE", "TK_CONSMODULE",
  "TK_COMPOMODULE", "TK_CLASS", "TK_STRUCT", "TK_PUBLIC", "TK_PROTECTED",
  "TK_PRIVATE", "TK_SIGNALS", "TK_SIGNAL_METHOD", "TK_SLOTS",
  "TK_SLOT_METHOD", "TK_BOOL", "TK_SHORT", "TK_INT", "TK_LONG", "TK_FLOAT",
  "TK_DOUBLE", "TK_CHAR", "TK_WCHAR_T", "TK_VOID", "TK_PYOBJECT",
  "TK_PYTUPLE", "TK_PYLIST", "TK_PYDICT", "TK_PYCALLABLE", "TK_PYSLICE",
  "TK_PYTYPE", "TK_VIRTUAL", "TK_ENUM", "TK_SIGNED", "TK_UNSIGNED",
  "TK_SCOPE", "TK_LOGICAL_OR", "TK_CONST", "TK_STATIC", "TK_SIPSIGNAL",
  "TK_SIPSLOT", "TK_SIPANYSLOT", "TK_SIPRXCON", "TK_SIPRXDIS",
  "TK_SIPSLOTCON", "TK_SIPSLOTDIS", "TK_NUMBER", "TK_REAL", "TK_TYPEDEF",
  "TK_NAMESPACE", "TK_TIMELINE", "TK_PLATFORMS", "TK_FEATURE",
  "TK_LICENSE", "TK_QCHAR", "TK_TRUE", "TK_FALSE", "TK_NULL",
  "TK_OPERATOR", "TK_THROW", "TK_QOBJECT", "TK_EXCEPTION", "TK_RAISECODE",
  "TK_EXPLICIT", "TK_TEMPLATE", "TK_ELLIPSIS", "TK_DEFMETATYPE",
  "TK_DEFSUPERTYPE", "'{'", "'}'", "';'", "'('", "')'", "'!'", "'-'",
  "','", "'='", "'+'", "'*'", "'/'", "'&'", "'|'", "'~'", "'<'", "'>'",
  "':'", "'['", "']'", "'%'", "'^'", "$accept", "specification",
  "statement", "$@1", "modstatement", "nsstatement", "defencoding",
  "plugin", "api", "exception", "baseexception", "raisecode", "mappedtype",
  "$@2", "mappedtypetmpl", "$@3", "mtdefinition", "mtbody", "mtline",
  "mtfunction", "namespace", "$@4", "nsbody", "platforms", "$@5",
  "platformlist", "platform", "feature", "timeline", "$@6",
  "qualifierlist", "qualifiername", "ifstart", "oredqualifiers",
  "qualifiers", "ifend", "license", "defmetatype", "defsupertype",
  "consmodule", "compmodule", "module", "modlang", "dottedname",
  "optnumber", "include", "optinclude", "import", "optaccesscode",
  "optgetcode", "optsetcode", "copying", "exphdrcode", "modhdrcode",
  "typehdrcode", "opttypehdrcode", "travcode", "clearcode", "getbufcode",
  "releasebufcode", "readbufcode", "writebufcode", "segcountcode",
  "charbufcode", "picklecode", "modcode", "typecode", "preinitcode",
  "initcode", "postinitcode", "unitcode", "unitpostinccode", "prepycode",
  "doc", "exporteddoc", "makefile", "codeblock", "codelines", "enum",
  "$@7", "optfilename", "optname", "optenumbody", "enumbody", "enumline",
  "optcomma", "optenumassign", "optassign", "expr", "binop", "optunop",
  "value", "scopedname", "scopepart", "simplevalue", "exprlist", "typedef",
  "struct", "$@8", "$@9", "classtmpl", "$@10", "template", "class", "$@11",
  "$@12", "superclasses", "superlist", "superclass", "optclassbody",
  "classbody", "classline", "optslot", "dtor", "ctor", "$@13",
  "simplector", "optctorsig", "optsig", "optvirtual", "function",
  "operatorname", "optconst", "optabstract", "optflags", "flaglist",
  "flag", "flagvalue", "docstring", "optdocstring", "methodcode",
  "virtualcatchercode", "arglist", "rawarglist", "argvalue", "varmember",
  "$@14", "$@15", "simple_varmem", "$@16", "varmem", "member", "$@17",
  "variable", "cpptype", "argtype", "optref", "deref", "basetype",
  "cpptypelist", "optexceptions", "exceptionlist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   123,   125,    59,    40,    41,
      33,    45,    44,    61,    43,    42,    47,    38,   124,   126,
      60,    62,    58,    91,    93,    37,    94
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   137,   138,   138,   140,   139,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   143,
     144,   145,   146,   147,   147,   148,   150,   149,   152,   151,
     153,   154,   154,   155,   155,   155,   155,   155,   155,   156,
     158,   157,   159,   159,   161,   160,   162,   162,   163,   164,
     166,   165,   167,   167,   168,   169,   170,   170,   170,   170,
     171,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     179,   180,   180,   181,   181,   182,   183,   184,   185,   185,
     186,   186,   187,   187,   188,   189,   190,   191,   192,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   214,   216,   215,   217,   217,   218,   218,   219,
     219,   220,   220,   221,   221,   221,   222,   222,   223,   223,
     224,   224,   225,   225,   226,   226,   226,   226,   226,   226,
     227,   227,   227,   227,   227,   228,   229,   229,   230,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   232,   232,
     232,   233,   233,   235,   236,   234,   238,   237,   239,   241,
     242,   240,   243,   243,   244,   244,   245,   246,   246,   247,
     247,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     249,   249,   250,   252,   251,   251,   253,   254,   254,   255,
     255,   256,   256,   257,   257,   257,   257,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   264,   264,   264,
     265,   266,   266,   267,   267,   268,   268,   269,   270,   270,
     270,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     273,   272,   274,   272,   272,   276,   275,   275,   277,   277,
     279,   278,   278,   280,   281,   281,   282,   283,   283,   284,
     284,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   286,
     286,   287,   287,   288,   288,   288
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     9,     0,     3,     2,     0,     5,     0,     6,
       4,     1,     2,     1,     1,     2,     2,     1,     1,    13,
       0,     7,     1,     2,     0,     5,     1,     2,     1,     2,
       0,     5,     1,     2,     1,     4,     1,     2,     3,     4,
       1,     3,     1,     2,     2,     2,     2,     2,     3,     1,
       1,     1,     1,     0,     1,     2,     2,     2,     0,     2,
       0,     2,     0,     2,     2,     2,     2,     2,     0,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     1,     2,     0,     8,     0,     1,     0,     1,     0,
       1,     1,     2,     1,     1,     4,     0,     1,     0,     2,
       0,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     1,     1,     1,     1,     2,     1,     3,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       3,     5,    11,     0,     0,     8,     0,     3,     4,     0,
       0,     8,     0,     2,     1,     3,     1,     0,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     3,     2,
       0,     1,    11,     0,     3,     1,    10,     0,     5,     0,
       6,     0,     1,    14,     7,    14,    13,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     1,     2,     2,
       1,     2,     2,     2,     1,     2,     0,     1,     0,     2,
       0,     3,     1,     3,     1,     3,     1,     5,     1,     1,
       2,     0,     1,     0,     2,     0,     2,     1,     0,     1,
       3,     4,     4,     4,     3,     3,     6,     6,     3,     2,
       0,     3,     0,     3,     1,     0,     3,     1,     1,     1,
       0,     3,     1,     7,     4,     3,     3,     0,     1,     0,
       2,     1,     4,     2,     2,     1,     1,     2,     1,     1,
       2,     2,     3,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     4,     2,     0,     1,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,   178,     0,     0,     0,     0,     0,     0,
      99,   100,     0,     0,     0,     0,   355,   345,   348,   349,
     353,   354,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   147,     0,   346,     0,     0,     0,    80,    74,
       0,   290,     0,     0,     0,   368,     0,     0,     5,    36,
      19,     9,    14,    43,    34,    35,    39,    16,    17,    15,
      37,    38,    18,    20,    21,     7,     8,     6,     0,    11,
      12,    13,    10,    22,    23,    48,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    45,   341,   176,    44,
      40,    42,   196,    41,    46,    47,     0,   339,     0,    49,
      50,   141,   137,     0,   138,   145,   131,   132,   133,   134,
     135,   129,   136,   114,     0,   290,   147,   105,   106,   107,
     115,   116,   117,   101,   102,    96,    97,   199,   193,   351,
     148,   290,   356,   344,   347,   350,   357,   339,     0,    70,
       0,     0,    79,     0,    93,     0,    53,     0,    94,    95,
     103,     0,     0,     0,     0,   290,     0,   337,    51,   142,
     140,   146,     0,   343,    56,    86,     0,    90,     0,     0,
     202,   202,   143,   352,   337,   290,   339,     0,     0,     0,
     294,     0,   292,   308,     0,   290,   369,     0,   104,    98,
     177,     0,   290,   197,   308,     0,     0,     0,   258,     0,
     257,   259,   260,   262,   263,   277,   280,   284,     0,   261,
     264,     0,   340,   338,   335,   139,     0,    87,     0,    85,
     147,     0,   290,   290,     0,   334,     0,     0,     0,    84,
       0,    82,    78,     0,    76,     0,     0,   291,   147,   147,
     147,   147,   147,     0,     0,   147,     0,   307,   309,   147,
     160,     0,     0,     0,   198,   342,    58,     0,   108,   278,
     283,   268,     0,   282,   267,   269,   270,   272,   273,   281,
     265,   285,   266,   279,   271,   274,   308,     0,    57,    88,
       0,    91,   206,   203,   204,   200,   194,   149,   191,     0,
      72,     0,   196,    81,    83,    75,    77,   101,   298,   299,
     296,   295,   293,   290,   290,   290,   290,   290,   308,   308,
     290,   286,     0,   290,   170,   319,    54,   118,   370,     0,
     286,     0,   110,     0,   275,   276,     0,     0,     0,     0,
       0,     0,    61,    68,    63,    64,    67,    89,     0,   207,
     207,   158,   153,   154,     0,   150,   151,     0,     0,    73,
     103,   160,   160,   160,   314,   315,     0,     0,   318,   287,
     371,   310,   336,   171,   173,   174,   172,   161,     0,   162,
     119,     0,    59,   371,   109,     0,   112,     0,   286,   130,
      65,    66,     0,     0,    62,   205,   251,     0,     0,   170,
     290,     0,   152,     0,    71,     0,   311,   312,   313,   147,
     147,     0,   288,   164,   165,   166,   167,   168,   169,   170,
     186,   182,   181,   187,   183,   184,   185,   179,   175,     0,
       0,     0,   288,   111,     0,   333,   254,   371,     0,    60,
       0,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   240,   240,   240,     0,   320,   322,   330,
     325,   243,   216,   213,   211,   212,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   220,   218,   217,   214,
     215,   251,   209,   232,   231,   245,     0,   332,   219,   233,
     324,   327,   328,   329,   201,   195,   159,   156,   144,     0,
     103,   290,   290,   373,     0,   290,   163,   170,    55,     0,
     290,   113,   288,   308,   300,   308,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   235,   234,   241,     0,     0,
       0,   239,     0,     0,     0,     0,     0,   208,   210,     0,
     157,   155,   290,   297,   316,   317,   374,     0,   289,   249,
     189,     0,    52,   249,   290,     0,     0,   236,   237,   238,
     330,   321,   323,   331,     0,   326,     0,   244,     0,     0,
     372,     0,     0,     0,   180,   170,     0,   249,   286,   371,
       0,     0,   192,   375,     0,   303,   190,   301,     0,   371,
     290,   371,   308,     0,   305,   302,   303,   303,   290,   247,
     288,     0,   304,     0,   256,   305,   305,   249,     0,     0,
     290,     0,   306,   253,   255,     0,   308,   301,     0,   250,
     301,     0,   303,   303,   303,     0,   246,   305,    69,   248,
     242
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    68,    69,    70,    71,    72,    73,
     205,   441,    74,   236,    75,   339,   298,   351,   352,   353,
      76,   197,   311,    77,   161,   253,   254,    78,    79,   160,
     250,   251,    80,   187,   188,    81,    82,    83,    84,    85,
      86,    87,    88,   145,   209,    89,    90,    91,   342,   396,
     445,    92,    93,    94,    95,   391,   477,   478,   479,   480,
     481,   482,   483,   484,   485,    96,   355,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   122,   123,   106,   244,
     182,   151,   364,   365,   366,   551,   410,   335,   387,   429,
     388,   389,   107,   108,   438,   561,   109,   110,   191,   360,
     111,   174,   312,   113,   190,   359,   242,   303,   304,   407,
     491,   492,   538,   493,   494,   546,   495,   619,   583,   496,
     497,   231,   380,   515,   164,   201,   202,   321,   605,   606,
     604,   614,   266,   267,   268,   499,   542,   543,   500,   545,
     501,   502,   544,   503,   269,   270,   234,   177,   117,   207,
     422,   557
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -531
static const yytype_int16 yypact[] =
{
    -531,    70,  -531,   561,  -531,  -531,    32,    47,    86,    94,
      94,   133,    94,    94,    94,    94,    94,    94,    94,    94,
    1055,     3,  -531,  -531,   139,   155,   227,    94,    94,    94,
    -531,  -531,   164,   164,   238,   238,  -531,  -531,  -531,   203,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,   244,   204,   188,  1055,  1031,   247,  -531,  -531,
     248,   149,  1031,   238,   147,  -531,   164,   164,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,   164,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,   -32,  -531,  -531,
    -531,  -531,   268,  -531,  -531,  -531,     9,  -531,   199,  -531,
    -531,  -531,  -531,    74,  -531,   269,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,   238,   149,    13,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,   213,    21,  -531,
    -531,   149,  -531,  -531,  -531,   232,  -531,  -531,     6,  -531,
     183,   186,  -531,   276,  -531,   185,   -31,  1031,  -531,  -531,
     211,   238,  1031,  1055,   252,   -17,   158,   118,  -531,  -531,
    -531,  -531,    94,   213,  -531,   187,   280,   224,   191,   193,
     180,   180,  -531,  -531,   118,   149,  -531,   200,   290,   291,
     196,    89,  -531,   287,   238,   149,  -531,    28,  -531,  -531,
    -531,    33,   149,  -531,   287,   206,   201,   198,   202,   -49,
     207,   210,   217,   219,   220,  -531,    -8,    48,   192,   221,
     222,   209,  -531,  -531,  -531,  -531,   214,  -531,    15,  -531,
     244,   238,   149,   149,   231,  -531,   230,     5,   814,  -531,
      18,  -531,  -531,    31,  -531,    63,   276,  -531,   244,   244,
     244,   244,   244,   216,   218,   244,   250,   258,  -531,   244,
     243,   -39,   255,  1031,  -531,  -531,  -531,   253,   371,  -531,
    -531,  -531,  1031,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
     260,  -531,   261,  -531,  -531,  -531,   287,   144,  -531,  -531,
     360,  -531,   213,   265,  -531,  -531,  -531,   233,  -531,   270,
    -531,   407,  -531,  -531,  -531,  -531,  -531,   256,  -531,  -531,
    -531,  -531,  -531,   149,   149,   149,   149,   149,   287,   287,
     149,   306,   287,   149,   -65,  -531,  -531,   343,  -531,   214,
     306,    94,   381,   274,  -531,  -531,   277,    94,    94,    94,
    1031,    52,  -531,  -531,  -531,  -531,  -531,  -531,   238,   282,
     282,   272,  -531,  -531,   284,   233,  -531,   285,   281,  -531,
     211,   243,   243,   243,  -531,  -531,   283,   286,  -531,  -531,
     300,  -531,  -531,  -531,  -531,  -531,  -531,   114,   873,  -531,
    -531,   298,  -531,   300,  -531,    94,   396,   292,   306,  -531,
    -531,  -531,   384,   297,  -531,  -531,   751,   301,   302,   -65,
     149,   303,  -531,  1031,  -531,   294,  -531,  -531,  -531,   244,
     244,   299,   304,  -531,  -531,  -531,  -531,  -531,  -531,   -65,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,   -36,  -531,   305,
      94,   308,   304,  -531,    94,  -531,  -531,   300,   310,  -531,
      94,   311,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,   362,   362,   362,   307,  -531,  -531,   309,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,   657,  -531,  -531,  -531,  -531,   312,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,   313,  -531,    35,
     211,   149,   149,   238,   333,   149,  -531,    54,  -531,   319,
     149,  -531,   304,   287,  -531,   287,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,   322,   324,
     325,  -531,   925,   925,   132,   978,   411,  -531,  -531,   432,
    -531,  -531,   149,  -531,  -531,  -531,   213,    58,  -531,   326,
     114,   100,  -531,   326,   149,   344,   345,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,    11,  -531,   311,  -531,   348,   350,
    -531,   238,  1031,   351,  -531,   -65,   368,   326,   306,   300,
     374,   375,  -531,   213,   377,   423,   114,   487,   379,   300,
     149,   300,   287,    94,   468,  -531,   423,   423,   149,   365,
     304,   380,  -531,    94,  -531,   468,   468,   326,   382,   387,
     149,   372,  -531,  -531,  -531,   388,   287,   487,   390,  -531,
     487,   389,   423,   423,   423,   376,  -531,   468,  -531,  -531,
    -531
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -531,  -531,   510,  -531,  -531,  -203,  -531,  -531,  -531,  -373,
    -531,  -531,  -531,  -531,  -531,  -531,   174,  -531,   163,  -531,
    -372,  -531,  -531,  -531,  -531,  -531,   263,  -531,  -531,  -531,
    -531,   267,  -281,  -531,  -531,  -277,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,    -5,  -341,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -274,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -368,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,   -10,  -531,  -270,  -531,
    -531,  -120,  -531,  -531,   157,  -531,  -531,  -111,  -475,  -531,
    -531,  -356,   -23,   349,  -531,  -531,  -340,  -339,  -531,  -531,
    -531,  -531,   521,  -159,  -531,  -531,   334,  -531,   168,   167,
    -531,    37,  -216,  -531,  -531,  -531,   -16,  -531,  -515,  -531,
       7,  -531,  -319,  -417,   -99,  -531,   273,  -531,  -338,  -394,
    -445,  -530,  -201,  -531,   205,  -531,  -531,  -531,  -276,  -531,
     -14,  -531,  -531,    17,    -2,  -531,   338,   -92,    -6,  -150,
    -369,  -531
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -344
static const yytype_int16 yytable[] =
{
     124,   116,   126,   127,   128,   129,   130,   131,   132,   133,
     114,   147,   148,   277,   135,   213,   189,   140,   141,   142,
     115,   393,   211,   354,   442,   520,   362,   356,   146,   415,
     363,   309,   195,   472,   473,   175,   184,   590,   486,   185,
     166,   299,   560,   171,   249,   310,   171,  -343,   586,   157,
     171,   171,   192,   506,   158,   383,   384,   252,   118,   385,
     165,   168,   169,   390,   386,   194,   488,   489,   498,   282,
       4,   347,   598,   516,   283,   119,   215,   354,   522,   447,
     336,   356,  -341,   170,   362,   623,   624,   204,   363,   317,
     144,   318,   348,   349,   172,   346,   246,   179,   172,   180,
      29,   214,   625,   171,   247,   564,   272,   640,   369,   163,
     596,   183,   120,   276,   176,   289,   176,   121,   472,   473,
     301,   136,   290,   486,   196,   474,  -343,   376,   377,   475,
     232,    52,   476,   186,   313,   300,   487,   350,   323,   324,
     325,   326,   327,   305,   306,   330,  -343,   315,  -343,   333,
     273,   488,   489,   498,   552,   273,   319,   273,    23,   274,
     125,   615,   616,   347,   275,   206,   137,   212,   403,   553,
     206,   291,   235,  -188,   383,   384,  -188,   580,   385,   292,
     581,   271,   138,   386,   348,   349,   134,   636,   637,   638,
     143,   144,    29,   620,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
     474,   256,    53,    54,   475,   257,    55,   476,   302,   584,
     600,   487,   585,    52,   371,   372,   373,   374,   375,   350,
     608,   378,   610,   632,   382,   423,   634,    62,   424,   425,
     426,   427,   428,   232,    65,   233,   116,   490,   539,   540,
     320,   153,   154,   155,   139,   114,   156,    21,    22,   361,
     416,   417,   418,   509,    23,   115,   571,   572,   149,   599,
     150,   338,   152,   159,   162,   163,   216,   167,   217,   218,
     343,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     173,   228,   178,   229,   230,   171,   181,   193,   198,   511,
     512,   199,   200,   203,   208,    34,   237,   238,  -148,   116,
     239,   507,   241,    23,   240,   248,   249,   252,   114,   255,
     279,   280,   565,   278,   566,   281,   293,   296,   115,   297,
     284,   394,   490,   285,   328,   302,   329,   399,   400,   401,
     286,   134,   287,   288,   294,   295,   307,   308,   402,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,   437,   334,    53,    54,   331,
     337,    55,   340,   258,   259,   260,   261,   262,   263,   264,
     332,   341,   439,   344,   345,   443,   357,   358,   370,   367,
     379,    29,   395,   397,   265,   409,   398,   406,   414,    65,
     411,   611,   419,   413,   116,   420,   421,   440,   444,   446,
     448,   206,   554,   555,   449,   510,   559,   513,   504,   505,
     508,   563,   537,   517,   519,   631,   558,   514,   523,   525,
     518,    21,    22,    23,   521,   550,   562,   576,  -252,   541,
     524,   549,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   579,   567,    29,   568,   569,   578,   582,
      34,    35,   603,   588,   589,   587,   591,   592,   595,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,   597,    52,    53,    54,   116,
     556,    55,   214,   450,   601,   602,   607,   613,   618,   621,
     626,   609,    56,    57,   627,   630,   629,   633,   635,   617,
     639,     5,    62,   392,   404,    63,   316,   314,    64,    65,
     210,   628,   412,   368,   112,   243,   405,   408,   548,   322,
     577,   575,   245,     0,     0,     0,     0,   381,     0,     0,
     116,   116,   574,   116,     0,     0,     0,     0,     0,     0,
       0,   573,     0,     0,     0,     0,     0,     0,   593,     0,
       0,     0,     0,     0,     6,     7,     8,     0,     9,    10,
      11,     0,     0,     0,    12,    13,    14,    15,    16,    17,
     594,    18,    19,    20,     0,    21,    22,    23,     0,     0,
       0,     0,     0,   612,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   622,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,     0,
      52,    53,    54,     0,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,     0,   450,     0,     0,    62,     0,     0,    63,
       0,     0,    64,    65,    66,    67,   347,     0,     0,     0,
       0,    21,    22,   451,     0,     0,     0,   452,   453,   454,
     455,   456,   457,   458,   459,   460,     0,     0,   461,   462,
       0,     0,     0,     0,     0,    29,     0,     0,     0,     0,
      34,    35,   463,   464,   465,   466,   467,     0,   468,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,   469,    52,    53,    54,     0,
       0,    55,   470,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    56,    57,     0,     0,     0,   450,     0,     0,
       0,     0,    62,     0,     0,    63,     0,   471,     0,    65,
     347,     0,     0,   547,     0,    21,    22,   451,     0,     0,
       0,   452,   453,   454,   455,   456,   457,   458,   459,   460,
       0,     0,   461,   462,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,    34,    35,   463,   464,   465,   466,
     467,     0,   468,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,   469,
      52,    53,    54,     0,     0,    55,   470,     0,    21,    22,
      23,     0,     0,     0,     0,     0,    56,    57,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,    63,
       0,   471,    29,    65,     0,     0,     0,    34,    35,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,     0,    52,    53,    54,     0,     0,    55,    23,
       0,   430,     0,     0,     0,     0,     0,     0,     0,    56,
      57,     0,     0,     0,     0,     0,     0,     0,     0,    62,
       0,     0,    63,     0,     0,    64,    65,   134,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    23,     0,    53,    54,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   431,   432,     0,     0,
       0,     0,     0,     0,   433,   434,   435,   436,     0,   134,
       0,     0,     0,     0,     0,    65,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,   570,    23,    53,    54,     0,     0,    55,
     470,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,   134,     0,     0,     0,     0,    65,     0,     0,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,   570,    23,    53,    54,
       0,     0,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,     0,    62,     0,   134,     0,     0,     0,     0,
      65,     0,     0,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,   134,
       0,    53,    54,     0,     0,    55,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,     0,     0,    53,    54,     0,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65
};

static const yytype_int16 yycheck[] =
{
      10,     3,    12,    13,    14,    15,    16,    17,    18,    19,
       3,    34,    35,   214,    20,   174,   136,    27,    28,    29,
       3,   340,   172,   297,   393,   442,   307,   297,    33,   370,
     307,    26,    26,   406,   406,    26,   135,    26,   406,    26,
      63,    26,   517,    82,    26,   248,    82,    26,   563,    55,
      82,    82,   151,   409,    56,   120,   121,    26,    26,   124,
      62,    66,    67,   337,   129,   157,   406,   406,   406,   118,
       0,    19,   587,   429,   123,    28,   175,   351,   447,   398,
     119,   351,   118,    88,   365,   615,   616,   118,   365,    26,
      27,    28,    40,    41,   130,   296,   195,    23,   130,    25,
      48,   118,   617,    82,   196,   522,   205,   637,   311,   126,
     585,   134,    26,   212,   105,   123,   105,    23,   491,   491,
     240,   118,   130,   491,   118,   406,   105,   328,   329,   406,
     125,    79,   406,   120,   116,   120,   406,    85,   258,   259,
     260,   261,   262,   242,   243,   265,   125,   116,   127,   269,
     122,   491,   491,   491,   119,   122,    93,   122,    26,   131,
      27,   606,   607,    19,   131,   167,    27,   173,   116,   510,
     172,   123,   182,   119,   120,   121,   122,   119,   124,   131,
     122,   204,    27,   129,    40,    41,    54,   632,   633,   634,
      26,    27,    48,   610,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     491,   122,    80,    81,   491,   126,    84,   491,   241,   119,
     589,   491,   122,    79,   323,   324,   325,   326,   327,    85,
     599,   330,   601,   627,   333,   121,   630,   105,   124,   125,
     126,   127,   128,   125,   112,   127,   248,   406,   464,   465,
     255,    63,    64,    65,    27,   248,    68,    24,    25,    26,
     371,   372,   373,   413,    26,   248,   542,   543,    65,   588,
      26,   273,    68,    26,    26,   126,   118,   130,   120,   121,
     282,   123,   124,   125,   126,   127,   128,   129,   130,   131,
      22,   133,    93,   135,   136,    82,    27,    65,   115,   419,
     420,   115,    26,   118,    93,    53,    26,    83,   121,   311,
     119,   410,   132,    26,   121,   115,    26,    26,   311,   123,
     119,   123,   523,   117,   525,   123,   134,   118,   311,   115,
     123,   341,   491,   123,   118,   358,   118,   347,   348,   349,
     123,    54,   123,   123,   123,   123,   115,   117,   350,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   388,   123,    80,    81,   119,
     115,    84,   119,    86,    87,    88,    89,    90,    91,    92,
     122,    10,   388,   123,   123,   395,    26,   122,   132,   119,
      84,    48,    11,   119,   107,   123,   119,   115,   117,   112,
     116,   602,   119,   118,   406,   119,   106,   109,    12,   117,
      26,   413,   511,   512,   117,   121,   515,   118,   117,   117,
     117,   520,    60,   118,   116,   626,    93,   123,   118,   118,
     440,    24,    25,    26,   444,   122,   117,    26,   129,   132,
     450,   129,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   552,   132,    48,   132,   132,    26,   133,
      53,    54,    39,   119,   119,   564,   118,   117,   117,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   117,    79,    80,    81,   491,
     513,    84,   118,     6,   119,   118,   117,    29,   133,   119,
     118,   600,    95,    96,   117,   117,   134,   117,   119,   608,
     134,     1,   105,   339,   351,   108,   253,   250,   111,   112,
     171,   620,   365,   116,     3,   191,   358,   360,   491,   256,
     546,   545,   194,    -1,    -1,    -1,    -1,   332,    -1,    -1,
     542,   543,   544,   545,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   544,    -1,    -1,    -1,    -1,    -1,    -1,   581,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,     8,
       9,    -1,    -1,    -1,    13,    14,    15,    16,    17,    18,
     582,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,   603,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   613,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    98,
      99,   100,    -1,     6,    -1,    -1,   105,    -1,    -1,   108,
      -1,    -1,   111,   112,   113,   114,    19,    -1,    -1,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    -1,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    96,    -1,    -1,    -1,     6,    -1,    -1,
      -1,    -1,   105,    -1,    -1,   108,    -1,   110,    -1,   112,
      19,    -1,    -1,   116,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    -1,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    -1,    -1,    84,    85,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    95,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,   108,
      -1,   110,    48,   112,    -1,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    79,    80,    81,    -1,    -1,    84,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,   108,    -1,    -1,   111,   112,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    26,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,   101,   102,   103,   104,    -1,    54,
      -1,    -1,    -1,    -1,    -1,   112,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    26,    80,    81,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    -1,    54,    -1,    -1,    -1,    -1,   112,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    26,    80,    81,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    -1,   105,    -1,    54,    -1,    -1,    -1,    -1,
     112,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    54,
      -1,    80,    81,    -1,    -1,    84,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   138,   139,   140,     0,   139,     3,     4,     5,     7,
       8,     9,    13,    14,    15,    16,    17,    18,    20,    21,
      22,    24,    25,    26,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    79,    80,    81,    84,    95,    96,    97,    98,
      99,   100,   105,   108,   111,   112,   113,   114,   141,   142,
     143,   144,   145,   146,   149,   151,   157,   160,   164,   165,
     169,   172,   173,   174,   175,   176,   177,   178,   179,   182,
     183,   184,   188,   189,   190,   191,   202,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   215,   229,   230,   233,
     234,   237,   239,   240,   257,   280,   281,   285,    26,    28,
      26,    23,   213,   214,   213,    27,   213,   213,   213,   213,
     213,   213,   213,   213,    54,   285,   118,    27,    27,    27,
     213,   213,   213,    26,    27,   180,   180,   229,   229,    65,
      26,   218,    68,    63,    64,    65,    68,   285,   281,    26,
     166,   161,    26,   126,   261,   281,   229,   130,   180,   180,
     180,    82,   130,    22,   238,    26,   105,   284,    93,    23,
      25,    27,   217,   229,   261,    26,   120,   170,   171,   218,
     241,   235,   261,    65,   284,    26,   118,   158,   115,   115,
      26,   262,   263,   118,   118,   147,   281,   286,    93,   181,
     230,   286,   285,   240,   118,   261,   118,   120,   121,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   133,   135,
     136,   258,   125,   127,   283,   213,   150,    26,    83,   119,
     121,   132,   243,   243,   216,   283,   261,   284,   115,    26,
     167,   168,    26,   162,   163,   123,   122,   126,    86,    87,
      88,    89,    90,    91,    92,   107,   269,   270,   271,   281,
     282,   229,   261,   122,   131,   131,   261,   269,   117,   119,
     123,   123,   118,   123,   123,   123,   123,   123,   123,   123,
     130,   123,   131,   134,   123,   123,   118,   115,   153,    26,
     120,   218,   229,   244,   245,   261,   261,   115,   117,    26,
     142,   159,   239,   116,   168,   116,   163,    26,    28,    93,
     180,   264,   263,   218,   218,   218,   218,   218,   118,   118,
     218,   119,   122,   218,   123,   224,   119,   115,   281,   152,
     119,    10,   185,   281,   123,   123,   269,    19,    40,    41,
      85,   154,   155,   156,   191,   203,   215,    26,   122,   242,
     236,    26,   169,   172,   219,   220,   221,   119,   116,   142,
     132,   261,   261,   261,   261,   261,   269,   269,   261,    84,
     259,   271,   261,   120,   121,   124,   129,   225,   227,   228,
     191,   192,   153,   259,   213,    11,   186,   119,   119,   213,
     213,   213,   281,   116,   155,   245,   115,   246,   246,   123,
     223,   116,   221,   118,   117,   181,   224,   224,   224,   119,
     119,   106,   287,   121,   124,   125,   126,   127,   128,   226,
      28,    93,    94,   101,   102,   103,   104,   229,   231,   285,
     109,   148,   287,   213,    12,   187,   117,   259,    26,   117,
       6,    26,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    41,    42,    55,    56,    57,    58,    59,    61,    78,
      85,   110,   146,   157,   169,   172,   191,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   203,   215,   233,   234,
     240,   247,   248,   250,   251,   253,   256,   257,   265,   272,
     275,   277,   278,   280,   117,   117,   228,   261,   117,   286,
     121,   218,   218,   118,   123,   260,   228,   118,   213,   116,
     260,   213,   287,   118,   213,   118,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,    60,   249,   249,
     249,   132,   273,   274,   279,   276,   252,   116,   248,   129,
     122,   222,   119,   181,   261,   261,   229,   288,    93,   261,
     225,   232,   117,   261,   260,   269,   269,   132,   132,   132,
      78,   275,   275,   257,   281,   277,    26,   253,    26,   261,
     119,   122,   133,   255,   119,   122,   255,   261,   119,   119,
      26,   118,   117,   229,   281,   117,   225,   117,   255,   259,
     287,   119,   118,    39,   267,   265,   266,   117,   287,   261,
     287,   269,   213,    29,   268,   267,   267,   261,   133,   254,
     260,   119,   213,   268,   268,   255,   118,   117,   261,   134,
     117,   269,   266,   117,   266,   119,   267,   267,   267,   134,
     268
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1455 of yacc.c  */
#line 355 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /*
             * We don't do these in parserEOF() because the parser is reading
             * ahead and that would be too early.
             */

            if (previousFile != NULL)
            {
                handleEOF();

                if (currentContext.prevmod != NULL)
                    handleEOM();

                free(previousFile);
                previousFile = NULL;
            }
    }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 390 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentSpec->exphdrcode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 394 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->hdrcode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 398 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->cppcode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 427 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope == NULL)
                    yyerror("%TypeHeaderCode can only be used in a namespace, class or mapped type");

                appendCodeBlock(&scope->iff->hdrcode, (yyvsp[(1) - (1)].codeb));
            }
        }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 440 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if ((currentModule->encoding = convertEncoding((yyvsp[(2) - (2)].text))) == no_type)
                    yyerror("The value of %DefaultEncoding must be one of \"ASCII\", \"Latin-1\", \"UTF-8\" or \"None\"");
            }
        }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 449 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            appendString(&currentSpec->plugins, (yyvsp[(2) - (2)].text));
        }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 454 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                apiVersionRangeDef *avd;

                if (findAPI(currentSpec, (yyvsp[(2) - (3)].text)) != NULL)
                    yyerror("The API name in the %API directive has already been defined");

                if ((yyvsp[(3) - (3)].number) < 1)
                    yyerror("The version number in the %API directive must be greater than or equal to 1");

                avd = sipMalloc(sizeof (apiVersionRangeDef));

                avd->api_name = cacheName(currentSpec, (yyvsp[(2) - (3)].text));
                avd->from = (yyvsp[(3) - (3)].number);
                avd->to = -1;

                avd->next = currentModule->api_versions;
                currentModule->api_versions = avd;

                if (inMainModule())
                    setIsUsedName(avd->api_name);
            }
        }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 480 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                exceptionDef *xd;
                const char *pyname;

                if (currentSpec->genc)
                    yyerror("%Exception not allowed in a C module");

                pyname = getPythonName(&(yyvsp[(4) - (9)].optflags), scopedNameTail((yyvsp[(2) - (9)].scpvalp)));

                checkAttributes(currentSpec, currentModule, NULL, NULL,
                        pyname, FALSE);

                xd = findException(currentSpec, (yyvsp[(2) - (9)].scpvalp), TRUE);

                if (xd->cd != NULL)
                    yyerror("%Exception name has already been seen as a class name - it must be defined before being used");

                if (xd->iff->module != NULL)
                    yyerror("The %Exception has already been defined");

                /* Complete the definition. */
                xd->iff->module = currentModule;
                xd->iff->hdrcode = (yyvsp[(6) - (9)].codeb);
                xd->pyname = pyname;
                xd->bibase = (yyvsp[(3) - (9)].exceptionbase).bibase;
                xd->base = (yyvsp[(3) - (9)].exceptionbase).base;
                xd->raisecode = (yyvsp[(7) - (9)].codeb);

                if (findOptFlag(&(yyvsp[(4) - (9)].optflags), "Default", bool_flag) != NULL)
                    currentModule->defexception = xd;

                if (xd->bibase != NULL || xd->base != NULL)
                    xd->exceptionnr = currentModule->nrexceptions++;
            }
        }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 519 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.exceptionbase).bibase = NULL;
            (yyval.exceptionbase).base = NULL;
        }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 523 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            exceptionDef *xd;

            (yyval.exceptionbase).bibase = NULL;
            (yyval.exceptionbase).base = NULL;

            /* See if it is a defined exception. */
            for (xd = currentSpec->exceptions; xd != NULL; xd = xd->next)
                if (compareScopedNames(xd->iff->fqcname, (yyvsp[(2) - (3)].scpvalp)) == 0)
                {
                    (yyval.exceptionbase).base = xd;
                    break;
                }

            if (xd == NULL && (yyvsp[(2) - (3)].scpvalp)->next == NULL && strncmp((yyvsp[(2) - (3)].scpvalp)->name, "SIP_", 4) == 0)
            {
                /* See if it is a builtin exception. */

                static char *builtins[] = {
                    "Exception",
                    "StopIteration",
                    "StandardError",
                    "ArithmeticError",
                    "LookupError",
                    "AssertionError",
                    "AttributeError",
                    "EOFError",
                    "FloatingPointError",
                    "EnvironmentError",
                    "IOError",
                    "OSError",
                    "ImportError",
                    "IndexError",
                    "KeyError",
                    "KeyboardInterrupt",
                    "MemoryError",
                    "NameError",
                    "OverflowError",
                    "RuntimeError",
                    "NotImplementedError",
                    "SyntaxError",
                    "IndentationError",
                    "TabError",
                    "ReferenceError",
                    "SystemError",
                    "SystemExit",
                    "TypeError",
                    "UnboundLocalError",
                    "UnicodeError",
                    "UnicodeEncodeError",
                    "UnicodeDecodeError",
                    "UnicodeTranslateError",
                    "ValueError",
                    "ZeroDivisionError",
                    "WindowsError",
                    "VMSError",
                    NULL
                };

                char **cp;

                for (cp = builtins; *cp != NULL; ++cp)
                    if (strcmp((yyvsp[(2) - (3)].scpvalp)->name + 4, *cp) == 0)
                    {
                        (yyval.exceptionbase).bibase = *cp;
                        break;
                    }
            }

            if ((yyval.exceptionbase).bibase == NULL && (yyval.exceptionbase).base == NULL)
                yyerror("Unknown exception base type");
        }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 597 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 602 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                currentMappedType = newMappedType(currentSpec, &(yyvsp[(2) - (3)].memArg), &(yyvsp[(3) - (3)].optflags));
        }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 608 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            int a;

            if (currentSpec->genc)
                yyerror("%MappedType templates not allowed in a C module");

            /* Check the template arguments are basic types or simple names. */
            for (a = 0; a < (yyvsp[(1) - (4)].signature).nrArgs; ++a)
            {
                argDef *ad = &(yyvsp[(1) - (4)].signature).args[a];

                if (ad->atype == defined_type && ad->u.snd->next != NULL)
                    yyerror("%MappedType template arguments must be simple names");
            }

            if ((yyvsp[(3) - (4)].memArg).atype != template_type)
                yyerror("%MappedType template must map a template type");

            if (notSkipping())
            {
                mappedTypeTmplDef *mtt;
                ifaceFileDef *iff;

                /* Check a template hasn't already been provided. */
                for (mtt = currentSpec->mappedtypetemplates; mtt != NULL; mtt = mtt->next)
                    if (compareScopedNames(mtt->mt->type.u.td->fqname, (yyvsp[(3) - (4)].memArg).u.td->fqname) == 0 && sameTemplateSignature(&mtt->mt->type.u.td->types, &(yyvsp[(3) - (4)].memArg).u.td->types, TRUE))
                        yyerror("%MappedType template for this type has already been defined");

                (yyvsp[(3) - (4)].memArg).nrderefs = 0;
                (yyvsp[(3) - (4)].memArg).argflags = 0;

                mtt = sipMalloc(sizeof (mappedTypeTmplDef));

                mtt->sig = (yyvsp[(1) - (4)].signature);
                mtt->mt = allocMappedType(currentSpec, &(yyvsp[(3) - (4)].memArg));
                mtt->mt->doctype = getDocType(&(yyvsp[(4) - (4)].optflags));
                mtt->next = currentSpec->mappedtypetemplates;

                currentSpec->mappedtypetemplates = mtt;

                currentMappedType = mtt->mt;

                /* Create a dummy interface file. */
                iff = sipMalloc(sizeof (ifaceFileDef));
                iff->hdrcode = NULL;
                mtt->mt->iff = iff;
            }
        }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 658 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (currentMappedType->convfromcode == NULL)
                    yyerror("%MappedType must have a %ConvertFromTypeCode directive");

                if (currentMappedType->convtocode == NULL)
                    yyerror("%MappedType must have a %ConvertToTypeCode directive");

                currentMappedType = NULL;
            }
        }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 676 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentMappedType->iff->hdrcode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 680 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentMappedType->typecode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 684 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (currentMappedType -> convfromcode != NULL)
                    yyerror("%MappedType has more than one %ConvertFromTypeCode directive");

                currentMappedType -> convfromcode = (yyvsp[(2) - (2)].codeb);
            }
        }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 693 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (currentMappedType -> convtocode != NULL)
                    yyerror("%MappedType has more than one %ConvertToTypeCode directive");

                currentMappedType -> convtocode = (yyvsp[(2) - (2)].codeb);
            }
        }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 706 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                applyTypeFlags(currentModule, &(yyvsp[(2) - (13)].memArg), &(yyvsp[(9) - (13)].optflags));

                (yyvsp[(5) - (13)].signature).result = (yyvsp[(2) - (13)].memArg);

                newFunction(currentSpec, currentModule, NULL,
                        currentMappedType, 0, TRUE, FALSE, FALSE, FALSE, (yyvsp[(3) - (13)].text),
                        &(yyvsp[(5) - (13)].signature), (yyvsp[(7) - (13)].number), FALSE, &(yyvsp[(9) - (13)].optflags), (yyvsp[(13) - (13)].codeb), NULL, (yyvsp[(8) - (13)].throwlist), (yyvsp[(10) - (13)].optsignature), (yyvsp[(12) - (13)].codeb));
            }
        }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 720 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("namespace definition not allowed in a C module");

            if (notSkipping())
            {
                classDef *ns, *c_scope;
                ifaceFileDef *scope;

                if ((c_scope = currentScope()) != NULL)
                    scope = c_scope->iff;
                else
                    scope = NULL;

                ns = newClass(currentSpec, namespace_iface, NULL,
                        text2scopedName(scope, (yyvsp[(2) - (2)].text)));

                pushScope(ns);

                sectionFlags = 0;
            }
        }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 741 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (inMainModule())
                {
                    classDef *ns = currentScope();

                    setIsUsedName(ns->iff->name);
                    setIsUsedName(ns->pyname);
                }

                popScope();
            }
        }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 761 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            qualDef *qd;

            for (qd = currentModule -> qualifiers; qd != NULL; qd = qd -> next)
                if (qd -> qtype == platform_qualifier)
                    yyerror("%Platforms has already been defined for this module");
        }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 768 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            qualDef *qd;
            int nrneeded;

            /*
             * Check that exactly one platform in the set was
             * requested.
             */

            nrneeded = 0;

            for (qd = currentModule -> qualifiers; qd != NULL; qd = qd -> next)
                if (qd -> qtype == platform_qualifier && isNeeded(qd))
                    ++nrneeded;

            if (nrneeded > 1)
                yyerror("No more than one of these %Platforms must be specified with the -t flag");
        }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 792 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            newQualifier(currentModule,-1,-1,(yyvsp[(1) - (1)].text),platform_qualifier);
        }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 797 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            newQualifier(currentModule,-1,-1,(yyvsp[(2) - (2)].text),feature_qualifier);
        }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 802 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            currentTimelineOrder = 0;
        }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 805 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            qualDef *qd;
            int nrneeded;

            /*
             * Check that exactly one time slot in the set was
             * requested.
             */

            nrneeded = 0;

            for (qd = currentModule -> qualifiers; qd != NULL; qd = qd -> next)
                if (qd -> qtype == time_qualifier && isNeeded(qd))
                    ++nrneeded;

            if (nrneeded > 1)
                yyerror("At most one of this %Timeline must be specified with the -t flag");

            currentModule -> nrtimelines++;
        }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 831 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            newQualifier(currentModule,currentModule -> nrtimelines,currentTimelineOrder++,(yyvsp[(1) - (1)].text),time_qualifier);
        }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 836 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (skipStackPtr >= MAX_NESTED_IF)
                yyerror("Internal error: increase the value of MAX_NESTED_IF");

            /* Nested %Ifs are implicit logical ands. */

            if (skipStackPtr > 0)
                (yyvsp[(3) - (4)].boolean) = ((yyvsp[(3) - (4)].boolean) && skipStack[skipStackPtr - 1]);

            skipStack[skipStackPtr++] = (yyvsp[(3) - (4)].boolean);
        }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 849 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = platOrFeature((yyvsp[(1) - (1)].text),FALSE);
        }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 852 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = platOrFeature((yyvsp[(2) - (2)].text),TRUE);
        }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 855 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = (platOrFeature((yyvsp[(3) - (3)].text),FALSE) || (yyvsp[(1) - (3)].boolean));
        }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 858 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = (platOrFeature((yyvsp[(4) - (4)].text),TRUE) || (yyvsp[(1) - (4)].boolean));
        }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 864 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = timePeriod((yyvsp[(1) - (3)].text),(yyvsp[(3) - (3)].text));
        }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 869 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (skipStackPtr-- <= 0)
                yyerror("Too many %End directives");
        }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 875 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            optFlag *of;

            if ((yyvsp[(2) - (2)].optflags).nrFlags == 0)
                yyerror("%License details not specified");

            if ((of = findOptFlag(&(yyvsp[(2) - (2)].optflags),"Type",string_flag)) == NULL)
                yyerror("%License type not specified");

            currentModule -> license = sipMalloc(sizeof (licenseDef));

            currentModule -> license -> type = of -> fvalue.sval;

            currentModule -> license -> licensee = 
                ((of = findOptFlag(&(yyvsp[(2) - (2)].optflags),"Licensee",string_flag)) != NULL)
                    ? of -> fvalue.sval : NULL;

            currentModule -> license -> timestamp = 
                ((of = findOptFlag(&(yyvsp[(2) - (2)].optflags),"Timestamp",string_flag)) != NULL)
                    ? of -> fvalue.sval : NULL;

            currentModule -> license -> sig = 
                ((of = findOptFlag(&(yyvsp[(2) - (2)].optflags),"Signature",string_flag)) != NULL)
                    ? of -> fvalue.sval : NULL;
        }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 902 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (currentModule->defmetatype != NULL)
                    yyerror("%DefaultMetatype has already been defined for this module");

                currentModule->defmetatype = cacheName(currentSpec, (yyvsp[(2) - (2)].text));
            }
        }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 913 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (currentModule->defsupertype != NULL)
                    yyerror("%DefaultSupertype has already been defined for this module");

                currentModule->defsupertype = cacheName(currentSpec, (yyvsp[(2) - (2)].text));
            }
        }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 924 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Make sure this is the first mention of a module. */
            if (currentSpec->module != currentModule)
                yyerror("A %ConsolidatedModule cannot be %Imported");

            if (currentModule->fullname != NULL)
                yyerror("%ConsolidatedModule must appear before any %Module or %CModule directive");

            setModuleName(currentSpec, currentModule, (yyvsp[(2) - (2)].text));
            setIsConsolidated(currentModule);
        }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 937 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Make sure this is the first mention of a module. */
            if (currentSpec->module != currentModule)
                yyerror("A %CompositeModule cannot be %Imported");

            if (currentModule->fullname != NULL)
                yyerror("%CompositeModule must appear before any %Module or %CModule directive");

            setModuleName(currentSpec, currentModule, (yyvsp[(2) - (2)].text));
            setIsComposite(currentModule);
        }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 950 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Check the module hasn't already been defined. */

            moduleDef *mod;

            for (mod = currentSpec->modules; mod != NULL; mod = mod->next)
                if (mod->fullname != NULL && strcmp(mod->fullname->text, (yyvsp[(2) - (3)].text)) == 0)
                    yyerror("Module is already defined");

            /*
             * If we are in a container module then create a component module
             * and make it current.
             */
            if (isContainer(currentModule) || currentModule->container != NULL)
            {
                mod = allocModule();

                mod->file = currentContext.filename;
                mod->container = (isContainer(currentModule) ? currentModule : currentModule->container);

                currentModule = mod;
            }

            setModuleName(currentSpec, currentModule, (yyvsp[(2) - (3)].text));
            currentModule->version = (yyvsp[(3) - (3)].number);

            if (currentSpec->genc < 0)
                currentSpec->genc = (yyvsp[(1) - (3)].boolean);
            else if (currentSpec->genc != (yyvsp[(1) - (3)].boolean))
                yyerror("Cannot mix C and C++ modules");
        }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 983 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = FALSE;
        }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 986 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = TRUE;
        }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 992 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /*
             * The grammar design is a bit broken and this is the easiest way
             * to allow periods in names.
             */

            char *cp;

            for (cp = (yyvsp[(1) - (1)].text); *cp != '\0'; ++cp)
                if (*cp != '.' && *cp != '_' && !isalnum(*cp))
                    yyerror("Invalid character in name");

            (yyval.text) = (yyvsp[(1) - (1)].text);
        }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1008 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = -1;
        }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1014 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            parseFile(NULL, (yyvsp[(2) - (2)].text), NULL, FALSE);
        }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1019 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            parseFile(NULL, (yyvsp[(2) - (2)].text), NULL, TRUE);
        }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1024 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            newImport((yyvsp[(2) - (2)].text));
        }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1029 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1032 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1037 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1040 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1045 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1048 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1053 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            appendCodeBlock(&currentModule->copying, (yyvsp[(2) - (2)].codeb));
        }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1058 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1063 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1068 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1073 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1079 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1084 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1089 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1094 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1099 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1104 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1109 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1114 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1119 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1124 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1129 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1134 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->preinitcode, (yyvsp[(2) - (2)].codeb));
        }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1140 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->initcode, (yyvsp[(2) - (2)].codeb));
        }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1146 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->postinitcode, (yyvsp[(2) - (2)].codeb));
        }
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1152 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->unitcode, (yyvsp[(2) - (2)].codeb));
        }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1158 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentModule->unitpostinccode, (yyvsp[(2) - (2)].codeb));
        }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1164 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /*
             * This is a no-op and is retained for compatibility
             * until the last use of it (by SIP v3) can be removed
             * from PyQt.
             */
        }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1173 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (inMainModule())
                appendCodeBlock(&currentSpec -> docs,(yyvsp[(2) - (2)].codeb));
        }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1179 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            appendCodeBlock(&currentSpec -> docs,(yyvsp[(2) - (2)].codeb));
        }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1184 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (inMainModule())
                yywarning("%Makefile is ignored, please use the -b flag instead");
        }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1194 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(1) - (2)].codeb);

            append(&(yyval.codeb)->frag, (yyvsp[(2) - (2)].codeb)->frag);

            free((yyvsp[(2) - (2)].codeb)->frag);
            free((char *)(yyvsp[(2) - (2)].codeb)->filename);
            free((yyvsp[(2) - (2)].codeb));
        }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1205 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (sectionFlags != 0 && (sectionFlags & ~(SECT_IS_PUBLIC | SECT_IS_PROT)) != 0)
                    yyerror("Class enums must be in the public or protected sections");

                currentEnum = newEnum(currentSpec, currentModule,
                        currentMappedType, (yyvsp[(2) - (3)].text), &(yyvsp[(3) - (3)].optflags), sectionFlags);
            }
        }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1217 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.text) = NULL;
        }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1220 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.text) = (yyvsp[(1) - (1)].text);
        }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1225 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.text) = NULL;
        }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1228 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.text) = (yyvsp[(1) - (1)].text);
        }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1243 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                enumMemberDef *emd, **tail;

                /* Note that we don't use the assigned value. */
                emd = sipMalloc(sizeof (enumMemberDef));

                emd -> pyname = cacheName(currentSpec, getPythonName(&(yyvsp[(3) - (4)].optflags), (yyvsp[(1) - (4)].text)));
                emd -> cname = (yyvsp[(1) - (4)].text);
                emd -> ed = currentEnum;
                emd -> next = NULL;

                checkAttributes(currentSpec, currentModule, emd->ed->ecd,
                        emd->ed->emtd, emd->pyname->text, FALSE);

                /* Append to preserve the order. */
                for (tail = &currentEnum->members; *tail != NULL; tail = &(*tail)->next)
                    ;

                *tail = emd;

                if (inMainModule())
                    setIsUsedName(emd -> pyname);
            }
        }
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1279 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.valp) = NULL;
        }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1282 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.valp) = (yyvsp[(2) - (2)].valp);
        }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1288 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            valueDef *vd;
 
            if ((yyvsp[(1) - (3)].valp) -> vtype == string_value || (yyvsp[(3) - (3)].valp) -> vtype == string_value)
                yyerror("Invalid binary operator for string");
 
            /* Find the last value in the existing expression. */
 
            for (vd = (yyvsp[(1) - (3)].valp); vd -> next != NULL; vd = vd -> next)
                ;
 
            vd -> vbinop = (yyvsp[(2) - (3)].qchar);
            vd -> next = (yyvsp[(3) - (3)].valp);

            (yyval.valp) = (yyvsp[(1) - (3)].valp);
        }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1306 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '-';
        }
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1309 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '+';
        }
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1312 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '*';
        }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1315 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '/';
        }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1318 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '&';
        }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1321 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '|';
        }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1326 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '\0';
        }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1329 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '!';
        }
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1332 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '~';
        }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1335 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '-';
        }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1338 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.qchar) = '+';
        }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1343 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if ((yyvsp[(1) - (2)].qchar) != '\0' && (yyvsp[(2) - (2)].value).vtype == string_value)
                yyerror("Invalid unary operator for string");
 
            /*
             * Convert the value to a simple expression on the
             * heap.
             */
 
            (yyval.valp) = sipMalloc(sizeof (valueDef));
 
            *(yyval.valp) = (yyvsp[(2) - (2)].value);
            (yyval.valp) -> vunop = (yyvsp[(1) - (2)].qchar);
            (yyval.valp) -> vbinop = '\0';
            (yyval.valp) -> next = NULL;
        }
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1362 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("Scoped names are not allowed in a C module");

            appendScopedName(&(yyvsp[(1) - (3)].scpvalp),(yyvsp[(3) - (3)].scpvalp));
        }
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1370 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.scpvalp) = text2scopePart((yyvsp[(1) - (1)].text));
        }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1375 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /*
             * We let the C++ compiler decide if the value is a valid one - no
             * point in building a full C++ parser here.
             */

            (yyval.value).vtype = scoped_value;
            (yyval.value).u.vscp = (yyvsp[(1) - (1)].scpvalp);
        }
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1384 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            fcallDef *fcd;

            fcd = sipMalloc(sizeof (fcallDef));
            *fcd = (yyvsp[(3) - (4)].fcall);
            fcd -> type = (yyvsp[(1) - (4)].memArg);

            (yyval.value).vtype = fcall_value;
            (yyval.value).u.fcd = fcd;
        }
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1394 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = real_value;
            (yyval.value).u.vreal = (yyvsp[(1) - (1)].real);
        }
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1398 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = numeric_value;
            (yyval.value).u.vnum = (yyvsp[(1) - (1)].number);
        }
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1402 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = numeric_value;
            (yyval.value).u.vnum = 1;
        }
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1406 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = numeric_value;
            (yyval.value).u.vnum = 0;
        }
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1410 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = numeric_value;
            (yyval.value).u.vnum = 0;
        }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1414 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = string_value;
            (yyval.value).u.vstr = (yyvsp[(1) - (1)].text);
        }
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1418 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.value).vtype = qchar_value;
            (yyval.value).u.vqchar = (yyvsp[(1) - (1)].qchar);
        }
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1424 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* No values. */

            (yyval.fcall).nrArgs = 0;
        }
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1429 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* The single or first expression. */

            (yyval.fcall).args[0] = (yyvsp[(1) - (1)].valp);
            (yyval.fcall).nrArgs = 1;
        }
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1435 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Check that it wasn't ...(,expression...). */

            if ((yyval.fcall).nrArgs == 0)
                yyerror("First argument to function call is missing");

            /* Check there is room. */

            if ((yyvsp[(1) - (3)].fcall).nrArgs == MAX_NR_ARGS)
                yyerror("Too many arguments to function call");

            (yyval.fcall) = (yyvsp[(1) - (3)].fcall);

            (yyval.fcall).args[(yyval.fcall).nrArgs] = (yyvsp[(3) - (3)].valp);
            (yyval.fcall).nrArgs++;
        }
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1453 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                applyTypeFlags(currentModule, &(yyvsp[(2) - (5)].memArg), &(yyvsp[(4) - (5)].optflags));
                newTypedef(currentSpec, currentModule, (yyvsp[(3) - (5)].text), &(yyvsp[(2) - (5)].memArg), &(yyvsp[(4) - (5)].optflags));
            }
        }
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1460 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                signatureDef *sig;
                argDef ftype;

                applyTypeFlags(currentModule, &(yyvsp[(2) - (11)].memArg), &(yyvsp[(10) - (11)].optflags));

                memset(&ftype, 0, sizeof (argDef));

                /* Create the full signature on the heap. */
                sig = sipMalloc(sizeof (signatureDef));
                *sig = (yyvsp[(8) - (11)].signature);
                sig->result = (yyvsp[(2) - (11)].memArg);

                /* Create the full type. */
                ftype.atype = function_type;
                ftype.nrderefs = (yyvsp[(4) - (11)].number);
                ftype.u.sa = sig;

                newTypedef(currentSpec, currentModule, (yyvsp[(5) - (11)].text), &ftype, &(yyvsp[(10) - (11)].optflags));
            }
        }
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1485 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc && (yyvsp[(2) - (2)].scpvalp)->next != NULL)
                yyerror("Namespaces not allowed in a C module");

            if (notSkipping())
                currentSupers = NULL;
        }
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1491 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                if (currentSpec->genc && currentSupers != NULL)
                    yyerror("Super-classes not allowed in a C module struct");

                defineClass((yyvsp[(2) - (5)].scpvalp), currentSupers, &(yyvsp[(5) - (5)].optflags));
                sectionFlags = SECT_IS_PUBLIC;
            }
        }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1500 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                completeClass((yyvsp[(2) - (8)].scpvalp), &(yyvsp[(5) - (8)].optflags), (yyvsp[(7) - (8)].boolean));
        }
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1506 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {currentIsTemplate = TRUE;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1506 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec->genc)
                yyerror("Class templates not allowed in a C module");

            if (notSkipping())
            {
                classTmplDef *tcd;

                /*
                 * Make sure there is room for the extra class name argument.
                 */
                if ((yyvsp[(1) - (3)].signature).nrArgs == MAX_NR_ARGS)
                    yyerror("Internal error - increase the value of MAX_NR_ARGS");

                tcd = sipMalloc(sizeof (classTmplDef));
                tcd->sig = (yyvsp[(1) - (3)].signature);
                tcd->cd = (yyvsp[(3) - (3)].klass);
                tcd->next = currentSpec->classtemplates;

                currentSpec->classtemplates = tcd;
            }

            currentIsTemplate = FALSE;
        }
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1532 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.signature) = (yyvsp[(3) - (4)].signature);
        }
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1537 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec->genc)
                yyerror("Class definition not allowed in a C module");

            if (notSkipping())
                currentSupers = NULL;
        }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1543 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                defineClass((yyvsp[(2) - (5)].scpvalp), currentSupers, &(yyvsp[(5) - (5)].optflags));
                sectionFlags = SECT_IS_PRIVATE;
            }
        }
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1549 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                (yyval.klass) = completeClass((yyvsp[(2) - (8)].scpvalp), &(yyvsp[(5) - (8)].optflags), (yyvsp[(7) - (8)].boolean));
        }
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1563 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                argDef ad;
                classDef *super;
                scopedNameDef *snd = (yyvsp[(1) - (1)].scpvalp);

                /*
                 * This is a hack to allow typedef'ed classes to be used before
                 * we have resolved the typedef definitions.  Unlike elsewhere,
                 * we require that the typedef is defined before being used.
                 */
                for (;;)
                {
                    ad.atype = no_type;
                    ad.argflags = 0;
                    ad.nrderefs = 0;
                    ad.original_type = NULL;

                    searchTypedefs(currentSpec, snd, &ad);

                    if (ad.atype != defined_type)
                        break;

                    if (ad.nrderefs != 0 || isConstArg(&ad) || isReference(&ad))
                        break;

                    snd = ad.u.snd;
                }

                if (ad.atype != no_type)
                    yyerror("Super-class list contains an invalid type");

                super = findClass(currentSpec, class_iface, NULL, snd);
                appendToClassList(&currentSupers, super);
            }
        }
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1602 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = FALSE;
        }
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1605 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.boolean) = TRUE;
        }
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1622 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                /* Make sure this is before any ctor docstrings. */
                (yyvsp[(1) - (1)].codeb)->next = scope->docstring;
                scope->docstring = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1632 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentScope()->cppcode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1636 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
                appendCodeBlock(&currentScope()->iff->hdrcode, (yyvsp[(1) - (1)].codeb));
        }
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1640 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->travcode != NULL)
                    yyerror("%GCTraverseCode already given for class");

                scope->travcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1651 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->clearcode != NULL)
                    yyerror("%GCClearCode already given for class");

                scope->clearcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1662 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->getbufcode != NULL)
                    yyerror("%BIGetBufferCode already given for class");

                scope->getbufcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1673 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->releasebufcode != NULL)
                    yyerror("%BIReleaseBufferCode already given for class");

                scope->releasebufcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1684 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->readbufcode != NULL)
                    yyerror("%BIGetReadBufferCode already given for class");

                scope->readbufcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1695 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->writebufcode != NULL)
                    yyerror("%BIGetWriteBufferCode already given for class");

                scope->writebufcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1706 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->segcountcode != NULL)
                    yyerror("%BIGetSegCountCode already given for class");

                scope->segcountcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1717 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->charbufcode != NULL)
                    yyerror("%BIGetCharBufferCode already given for class");

                scope->charbufcode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1728 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->picklecode != NULL)
                    yyerror("%PickleCode already given for class");

                scope->picklecode = (yyvsp[(1) - (1)].codeb);
            }
        }
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1742 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->convtosubcode != NULL)
                    yyerror("Class has more than one %ConvertToSubClassCode directive");

                scope->convtosubcode = (yyvsp[(2) - (2)].codeb);
            }
        }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1753 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *scope = currentScope();

                if (scope->convtocode != NULL)
                    yyerror("Class has more than one %ConvertToTypeCode directive");

                scope->convtocode = (yyvsp[(2) - (2)].codeb);
            }
        }
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1764 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("public section not allowed in a C module");

            if (notSkipping())
                sectionFlags = SECT_IS_PUBLIC | (yyvsp[(2) - (3)].number);
        }
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1771 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("protected section not allowed in a C module");

            if (notSkipping())
                sectionFlags = SECT_IS_PROT | (yyvsp[(2) - (3)].number);
        }
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1778 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("private section not allowed in a C module");

            if (notSkipping())
                sectionFlags = SECT_IS_PRIVATE | (yyvsp[(2) - (3)].number);
        }
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1785 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("signals section not allowed in a C module");

            if (notSkipping())
                sectionFlags = SECT_IS_SIGNAL;
        }
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1794 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = 0;
        }
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1797 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = SECT_IS_SLOT;
        }
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1802 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Note that we allow non-virtual dtors in C modules. */

            if (notSkipping())
            {
                classDef *cd = currentScope();

                if (strcmp(classBaseName(cd),(yyvsp[(3) - (11)].text)) != 0)
                    yyerror("Destructor doesn't have the same name as its class");

                if (isDtor(cd))
                    yyerror("Destructor has already been defined");

                if (currentSpec -> genc && (yyvsp[(10) - (11)].codeb) == NULL)
                    yyerror("Destructor in C modules must include %MethodCode");

                cd -> dealloccode = (yyvsp[(10) - (11)].codeb);
                cd -> dtorcode = (yyvsp[(11) - (11)].codeb);
                cd -> dtorexceptions = (yyvsp[(6) - (11)].throwlist);

                /*
                 * Note that we don't apply the protected/public hack to dtors
                 * as it (I think) may change the behaviour of the wrapped API.
                 */
                cd->classflags |= sectionFlags;

                if ((yyvsp[(7) - (11)].number))
                {
                    if (!(yyvsp[(1) - (11)].number))
                        yyerror("Abstract destructor must be virtual");

                    setIsAbstractClass(cd);
                }

                /*
                 * The class has a shadow if we have a virtual dtor or some
                 * dtor code.
                 */
                if ((yyvsp[(1) - (11)].number) || (yyvsp[(11) - (11)].codeb) != NULL)
                {
                    if (currentSpec -> genc)
                        yyerror("Virtual destructor or %VirtualCatcherCode not allowed in a C module");

                    setHasShadow(cd);
                }

                if (getReleaseGIL(&(yyvsp[(8) - (11)].optflags)))
                    setIsReleaseGILDtor(cd);
                else if (getHoldGIL(&(yyvsp[(8) - (11)].optflags)))
                    setIsHoldGILDtor(cd);
            }
        }
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1856 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {currentCtorIsExplicit = TRUE;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1860 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Note that we allow ctors in C modules. */

            if (notSkipping())
            {
                if (currentSpec -> genc)
                {
                    if ((yyvsp[(10) - (10)].codeb) == NULL && (yyvsp[(3) - (10)].signature).nrArgs != 0)
                        yyerror("Constructors with arguments in C modules must include %MethodCode");

                    if (currentCtorIsExplicit)
                        yyerror("Explicit constructors not allowed in a C module");
                }

                if ((sectionFlags & (SECT_IS_PUBLIC | SECT_IS_PROT | SECT_IS_PRIVATE)) == 0)
                    yyerror("Constructor must be in the public, private or protected sections");

                newCtor((yyvsp[(1) - (10)].text), sectionFlags, &(yyvsp[(3) - (10)].signature), &(yyvsp[(6) - (10)].optflags), (yyvsp[(10) - (10)].codeb), (yyvsp[(5) - (10)].throwlist), (yyvsp[(7) - (10)].optsignature),
                        currentCtorIsExplicit, (yyvsp[(9) - (10)].codeb));
            }

            free((yyvsp[(1) - (10)].text));

            currentCtorIsExplicit = FALSE;
        }
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1887 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optsignature) = NULL;
        }
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1890 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optsignature) = sipMalloc(sizeof (signatureDef));

            *(yyval.optsignature) = (yyvsp[(3) - (5)].signature);
        }
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1897 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optsignature) = NULL;
        }
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1900 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optsignature) = sipMalloc(sizeof (signatureDef));

            *(yyval.optsignature) = (yyvsp[(4) - (6)].signature);
            (yyval.optsignature) -> result = (yyvsp[(2) - (6)].memArg);
        }
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1908 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = FALSE;
        }
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1911 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = TRUE;
        }
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1916 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                applyTypeFlags(currentModule, &(yyvsp[(1) - (14)].memArg), &(yyvsp[(9) - (14)].optflags));

                (yyvsp[(4) - (14)].signature).result = (yyvsp[(1) - (14)].memArg);

                newFunction(currentSpec, currentModule, currentScope(), NULL,
                        sectionFlags, currentIsStatic, currentIsSignal,
                        currentIsSlot, currentOverIsVirt, (yyvsp[(2) - (14)].text), &(yyvsp[(4) - (14)].signature), (yyvsp[(6) - (14)].number), (yyvsp[(8) - (14)].number), &(yyvsp[(9) - (14)].optflags),
                        (yyvsp[(13) - (14)].codeb), (yyvsp[(14) - (14)].codeb), (yyvsp[(7) - (14)].throwlist), (yyvsp[(10) - (14)].optsignature), (yyvsp[(12) - (14)].codeb));
            }

            currentIsStatic = FALSE;
            currentIsSignal = FALSE;
            currentIsSlot = FALSE;
            currentOverIsVirt = FALSE;
        }
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1934 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /*
             * It looks like an assignment operator (though we don't bother to
             * check the types) so make sure it is private.
             */
            if (notSkipping())
            {
                classDef *cd = currentScope();

                if (cd == NULL || !(sectionFlags & SECT_IS_PRIVATE))
                    yyerror("Assignment operators may only be defined as private");

                setCannotAssign(cd);
            }

            currentIsStatic = FALSE;
            currentIsSignal = FALSE;
            currentIsSlot = FALSE;
            currentOverIsVirt = FALSE;
        }
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1954 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                classDef *cd = currentScope();

                /*
                 * If the scope is a namespace then make sure the operator is
                 * handled as a global.
                 */
                if (cd != NULL && cd->iff->type == namespace_iface)
                    cd = NULL;

                applyTypeFlags(currentModule, &(yyvsp[(1) - (14)].memArg), &(yyvsp[(10) - (14)].optflags));

                /* Handle the unary '+' and '-' operators. */
                if ((cd != NULL && (yyvsp[(5) - (14)].signature).nrArgs == 0) || (cd == NULL && (yyvsp[(5) - (14)].signature).nrArgs == 1))
                {
                    if (strcmp((yyvsp[(3) - (14)].text), "__add__") == 0)
                        (yyvsp[(3) - (14)].text) = "__pos__";
                    else if (strcmp((yyvsp[(3) - (14)].text), "__sub__") == 0)
                        (yyvsp[(3) - (14)].text) = "__neg__";
                }

                (yyvsp[(5) - (14)].signature).result = (yyvsp[(1) - (14)].memArg);

                newFunction(currentSpec, currentModule, cd, NULL,
                        sectionFlags, currentIsStatic, currentIsSignal,
                        currentIsSlot, currentOverIsVirt, (yyvsp[(3) - (14)].text), &(yyvsp[(5) - (14)].signature), (yyvsp[(7) - (14)].number), (yyvsp[(9) - (14)].number),
                        &(yyvsp[(10) - (14)].optflags), (yyvsp[(13) - (14)].codeb), (yyvsp[(14) - (14)].codeb), (yyvsp[(8) - (14)].throwlist), (yyvsp[(11) - (14)].optsignature), NULL);
            }

            currentIsStatic = FALSE;
            currentIsSignal = FALSE;
            currentIsSlot = FALSE;
            currentOverIsVirt = FALSE;
        }
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1990 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                char *sname;
                classDef *scope = currentScope();

                if (scope == NULL || (yyvsp[(4) - (13)].signature).nrArgs != 0)
                    yyerror("Operator casts must be specified in a class and have no arguments");

                applyTypeFlags(currentModule, &(yyvsp[(2) - (13)].memArg), &(yyvsp[(9) - (13)].optflags));

                switch ((yyvsp[(2) - (13)].memArg).atype)
                {
                case defined_type:
                    sname = NULL;
                    break;

                case bool_type:
                case cbool_type:
                case short_type:
                case ushort_type:
                case int_type:
                case cint_type:
                case uint_type:
                    sname = "__int__";
                    break;

                case long_type:
                case ulong_type:
                case longlong_type:
                case ulonglong_type:
                    sname = "__long__";
                    break;

                case float_type:
                case cfloat_type:
                case double_type:
                case cdouble_type:
                    sname = "__float__";
                    break;

                default:
                    yyerror("Unsupported operator cast");
                }

                if (sname != NULL)
                {
                    (yyvsp[(4) - (13)].signature).result = (yyvsp[(2) - (13)].memArg);

                    newFunction(currentSpec, currentModule, scope, NULL,
                            sectionFlags, currentIsStatic, currentIsSignal,
                            currentIsSlot, currentOverIsVirt, sname, &(yyvsp[(4) - (13)].signature), (yyvsp[(6) - (13)].number),
                            (yyvsp[(8) - (13)].number), &(yyvsp[(9) - (13)].optflags), (yyvsp[(12) - (13)].codeb), (yyvsp[(13) - (13)].codeb), (yyvsp[(7) - (13)].throwlist), (yyvsp[(10) - (13)].optsignature), NULL);
                }
                else
                {
                    argList *al;

                    /* Check it doesn't already exist. */
                    for (al = scope->casts; al != NULL; al = al->next)
                        if (compareScopedNames((yyvsp[(2) - (13)].memArg).u.snd, al->arg.u.snd) == 0)
                            yyerror("This operator cast has already been specified in this class");

                    al = sipMalloc(sizeof (argList));
                    al->arg = (yyvsp[(2) - (13)].memArg);
                    al->next = scope->casts;

                    scope->casts = al;
                }
            }

            currentIsStatic = FALSE;
            currentIsSignal = FALSE;
            currentIsSlot = FALSE;
            currentOverIsVirt = FALSE;
        }
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 2068 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__add__";}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 2069 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__sub__";}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 2070 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__mul__";}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 2071 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__div__";}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 2072 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__mod__";}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 2073 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__and__";}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 2074 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__or__";}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 2075 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__xor__";}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2076 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__lshift__";}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2077 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__rshift__";}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2078 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__iadd__";}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 2079 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__isub__";}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 2080 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__imul__";}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 2081 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__idiv__";}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2082 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__imod__";}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2083 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__iand__";}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 2084 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__ior__";}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2085 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__ixor__";}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2086 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__ilshift__";}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2087 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__irshift__";}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 2088 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__invert__";}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 2089 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__call__";}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 2090 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__getitem__";}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 2091 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__lt__";}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2092 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__le__";}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2093 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__eq__";}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 2094 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__ne__";}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 2095 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__gt__";}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 2096 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {(yyval.text) = "__ge__";}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 2099 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = FALSE;
        }
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 2102 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = TRUE;
        }
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 2107 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = 0;
        }
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 2110 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if ((yyvsp[(2) - (2)].number) != 0)
                yyerror("Abstract virtual function '= 0' expected");

            (yyval.number) = TRUE;
        }
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 2118 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optflags).nrFlags = 0;
        }
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2121 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optflags) = (yyvsp[(2) - (3)].optflags);
        }
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2127 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.optflags).flags[0] = (yyvsp[(1) - (1)].flag);
            (yyval.optflags).nrFlags = 1;
        }
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2131 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Check there is room. */

            if ((yyvsp[(1) - (3)].optflags).nrFlags == MAX_NR_FLAGS)
                yyerror("Too many optional flags");

            (yyval.optflags) = (yyvsp[(1) - (3)].optflags);

            (yyval.optflags).flags[(yyval.optflags).nrFlags++] = (yyvsp[(3) - (3)].flag);
        }
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2143 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.flag).ftype = bool_flag;
            (yyval.flag).fname = (yyvsp[(1) - (1)].text);
        }
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2147 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.flag) = (yyvsp[(3) - (3)].flag);
            (yyval.flag).fname = (yyvsp[(1) - (3)].text);
        }
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2153 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.flag).ftype = (strchr((yyvsp[(1) - (1)].text), '.') != NULL) ? dotted_name_flag : name_flag;
            (yyval.flag).fvalue.sval = (yyvsp[(1) - (1)].text);
        }
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2157 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            apiVersionRangeDef *avd;
            int from, to;

            (yyval.flag).ftype = api_range_flag;

            /* Check that the API is known. */
            if ((avd = findAPI(currentSpec, (yyvsp[(1) - (5)].text))) == NULL)
                yyerror("unknown API name in API annotation");

            if (inMainModule())
                setIsUsedName(avd->api_name);

            /* Unbounded values are represented by 0. */
            if ((from = (yyvsp[(3) - (5)].number)) < 0)
                from = 0;

            if ((to = (yyvsp[(5) - (5)].number)) < 0)
                to = 0;

            (yyval.flag).fvalue.aval = convertAPIRange(currentModule, avd->api_name,
                    from, to);
        }
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2180 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.flag).ftype = string_flag;
            (yyval.flag).fvalue.sval = convertFeaturedString((yyvsp[(1) - (1)].text));
        }
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2184 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.flag).ftype = integer_flag;
            (yyval.flag).fvalue.ival = (yyvsp[(1) - (1)].number);
        }
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2190 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2195 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2201 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2204 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2209 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = NULL;
        }
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2212 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.codeb) = (yyvsp[(2) - (2)].codeb);
        }
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2217 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            int a, nrrxcon, nrrxdis, nrslotcon, nrslotdis, nrarray, nrarraysize;

            nrrxcon = nrrxdis = nrslotcon = nrslotdis = nrarray = nrarraysize = 0;

            for (a = 0; a < (yyvsp[(1) - (1)].signature).nrArgs; ++a)
            {
                argDef *ad = &(yyvsp[(1) - (1)].signature).args[a];

                switch (ad -> atype)
                {
                case rxcon_type:
                    ++nrrxcon;
                    break;

                case rxdis_type:
                    ++nrrxdis;
                    break;

                case slotcon_type:
                    ++nrslotcon;
                    break;

                case slotdis_type:
                    ++nrslotdis;
                    break;
                }

                if (isArray(ad))
                    ++nrarray;

                if (isArraySize(ad))
                    ++nrarraysize;
            }

            if (nrrxcon != nrslotcon || nrrxcon > 1)
                yyerror("SIP_RXOBJ_CON and SIP_SLOT_CON must both be given and at most once");

            if (nrrxdis != nrslotdis || nrrxdis > 1)
                yyerror("SIP_RXOBJ_DIS and SIP_SLOT_DIS must both be given and at most once");

            if (nrarray != nrarraysize || nrarray > 1)
                yyerror("/Array/ and /ArraySize/ must both be given and at most once");

            (yyval.signature) = (yyvsp[(1) - (1)].signature);
        }
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2265 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* No arguments. */

            (yyval.signature).nrArgs = 0;
        }
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2270 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* The single or first argument. */

            (yyval.signature).args[0] = (yyvsp[(1) - (1)].memArg);
            (yyval.signature).nrArgs = 1;
        }
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2276 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Check that it wasn't ...(,arg...). */
            if ((yyvsp[(1) - (3)].signature).nrArgs == 0)
                yyerror("First argument of the list is missing");

            /* Check there is nothing after an ellipsis. */
            if ((yyvsp[(1) - (3)].signature).args[(yyvsp[(1) - (3)].signature).nrArgs - 1].atype == ellipsis_type)
                yyerror("An ellipsis must be at the end of the argument list");

            /*
             * If this argument has no default value, then the
             * previous one mustn't either.
             */
            if ((yyvsp[(3) - (3)].memArg).defval == NULL && (yyvsp[(1) - (3)].signature).args[(yyvsp[(1) - (3)].signature).nrArgs - 1].defval != NULL)
                yyerror("Compulsory argument given after optional argument");

            /* Check there is room. */
            if ((yyvsp[(1) - (3)].signature).nrArgs == MAX_NR_ARGS)
                yyerror("Internal error - increase the value of MAX_NR_ARGS");

            (yyval.signature) = (yyvsp[(1) - (3)].signature);

            (yyval.signature).args[(yyval.signature).nrArgs] = (yyvsp[(3) - (3)].memArg);
            (yyval.signature).nrArgs++;
        }
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2303 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = signal_type;
            (yyval.memArg).argflags = ARG_IS_CONST;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (4)].text));
            (yyval.memArg).defval = (yyvsp[(4) - (4)].valp);

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2312 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = slot_type;
            (yyval.memArg).argflags = ARG_IS_CONST;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (4)].text));
            (yyval.memArg).defval = (yyvsp[(4) - (4)].valp);

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2321 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = anyslot_type;
            (yyval.memArg).argflags = ARG_IS_CONST;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (4)].text));
            (yyval.memArg).defval = (yyvsp[(4) - (4)].valp);

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2330 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = rxcon_type;
            (yyval.memArg).argflags = 0;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (3)].text));

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags), "SingleShot", bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_SINGLE_SHOT;

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2341 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = rxdis_type;
            (yyval.memArg).argflags = 0;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (3)].text));

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2349 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = slotcon_type;
            (yyval.memArg).argflags = ARG_IS_CONST;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(5) - (6)].text));

            memset(&(yyvsp[(3) - (6)].signature).result, 0, sizeof (argDef));
            (yyvsp[(3) - (6)].signature).result.atype = void_type;

            (yyval.memArg).u.sa = sipMalloc(sizeof (signatureDef));
            *(yyval.memArg).u.sa = (yyvsp[(3) - (6)].signature);

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2363 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = slotdis_type;
            (yyval.memArg).argflags = ARG_IS_CONST;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(5) - (6)].text));

            memset(&(yyvsp[(3) - (6)].signature).result, 0, sizeof (argDef));
            (yyvsp[(3) - (6)].signature).result.atype = void_type;

            (yyval.memArg).u.sa = sipMalloc(sizeof (signatureDef));
            *(yyval.memArg).u.sa = (yyvsp[(3) - (6)].signature);

            currentSpec -> sigslots = TRUE;
        }
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2377 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg).atype = qobject_type;
            (yyval.memArg).argflags = 0;
            (yyval.memArg).nrderefs = 0;
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (3)].text));
        }
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2383 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg) = (yyvsp[(1) - (2)].memArg);
            (yyval.memArg).defval = (yyvsp[(2) - (2)].valp);
        }
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2390 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {currentIsSignal = TRUE;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2391 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {currentIsSlot = TRUE;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2396 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {currentIsStatic = TRUE;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2406 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {currentOverIsVirt = TRUE;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2410 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (notSkipping())
            {
                /* Check the section. */

                if (sectionFlags != 0)
                {
                    if ((sectionFlags & SECT_IS_PUBLIC) == 0)
                        yyerror("Class variables must be in the public section");

                    if (!currentIsStatic && (yyvsp[(5) - (7)].codeb) != NULL)
                        yyerror("%AccessCode cannot be specified for non-static class variables");
                }

                if (currentIsStatic && currentSpec -> genc)
                    yyerror("Cannot have static members in a C structure");

                applyTypeFlags(currentModule, &(yyvsp[(1) - (7)].memArg), &(yyvsp[(3) - (7)].optflags));

                if ((yyvsp[(6) - (7)].codeb) != NULL || (yyvsp[(7) - (7)].codeb) != NULL)
                {
                    if ((yyvsp[(5) - (7)].codeb) != NULL)
                        yyerror("Cannot mix %AccessCode and %GetCode or %SetCode");

                    if (currentScope() == NULL)
                        yyerror("Cannot specify %GetCode or %SetCode for global variables");
                }

                newVar(currentSpec,currentModule,(yyvsp[(2) - (7)].text),currentIsStatic,&(yyvsp[(1) - (7)].memArg),&(yyvsp[(3) - (7)].optflags),(yyvsp[(5) - (7)].codeb),(yyvsp[(6) - (7)].codeb),(yyvsp[(7) - (7)].codeb));
            }

            currentIsStatic = FALSE;
        }
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2445 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg) = (yyvsp[(2) - (4)].memArg);
            (yyval.memArg).nrderefs += (yyvsp[(3) - (4)].number);
            (yyval.memArg).argflags |= ARG_IS_CONST | (yyvsp[(4) - (4)].number);
        }
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2450 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.memArg) = (yyvsp[(1) - (3)].memArg);
            (yyval.memArg).nrderefs += (yyvsp[(2) - (3)].number);
            (yyval.memArg).argflags |= (yyvsp[(3) - (3)].number);
        }
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2457 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            optFlag *of;

            (yyval.memArg) = (yyvsp[(1) - (3)].memArg);
            (yyval.memArg).name = cacheName(currentSpec, (yyvsp[(2) - (3)].text));

            if (getAllowNone(&(yyvsp[(3) - (3)].optflags)))
                (yyval.memArg).argflags |= ARG_ALLOW_NONE;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"GetWrapper",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_GET_WRAPPER;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"Array",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_ARRAY;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"ArraySize",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_ARRAY_SIZE;

            if (getTransfer(&(yyvsp[(3) - (3)].optflags)))
                (yyval.memArg).argflags |= ARG_XFERRED;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"TransferThis",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_THIS_XFERRED;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"TransferBack",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_XFERRED_BACK;

            if ((of = findOptFlag(&(yyvsp[(3) - (3)].optflags), "KeepReference", opt_integer_flag)) != NULL)
            {
                (yyval.memArg).argflags |= ARG_KEEP_REF;

                if (((yyval.memArg).key = of->fvalue.ival) < -1)
                    yyerror("/KeepReference/ key cannot be negative");

                /* If there was no explicit key then auto-allocate one. */
                if ((yyval.memArg).key == -1)
                    (yyval.memArg).key = currentModule->next_key--;
            }

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"In",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_IN;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"Out",bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_OUT;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags), "ResultSize", bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_RESULT_SIZE;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags), "NoCopy", bool_flag) != NULL)
                (yyval.memArg).argflags |= ARG_NO_COPY;

            if (findOptFlag(&(yyvsp[(3) - (3)].optflags),"Constrained",bool_flag) != NULL)
            {
                (yyval.memArg).argflags |= ARG_CONSTRAINED;

                switch ((yyval.memArg).atype)
                {
                case bool_type:
                    (yyval.memArg).atype = cbool_type;
                    break;

                case int_type:
                    (yyval.memArg).atype = cint_type;
                    break;

                case float_type:
                    (yyval.memArg).atype = cfloat_type;
                    break;

                case double_type:
                    (yyval.memArg).atype = cdouble_type;
                    break;
                }
            }

            applyTypeFlags(currentModule, &(yyval.memArg), &(yyvsp[(3) - (3)].optflags));
            (yyval.memArg).docval = getDocValue(&(yyvsp[(3) - (3)].optflags));
        }
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2537 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = 0;
        }
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2540 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec -> genc)
                yyerror("References not allowed in a C module");

            (yyval.number) = ARG_IS_REF;
        }
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2548 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = 0;
        }
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2551 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.number) = (yyvsp[(1) - (2)].number) + 1;
        }
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2556 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = defined_type;
            (yyval.memArg).u.snd = (yyvsp[(1) - (1)].scpvalp);

            /* Try and resolve typedefs as early as possible. */
            resolveAnyTypedef(currentSpec, &(yyval.memArg));
        }
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2564 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            templateDef *td;

            td = sipMalloc(sizeof(templateDef));
            td->fqname = (yyvsp[(1) - (4)].scpvalp);
            td->types = (yyvsp[(3) - (4)].signature);

            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = template_type;
            (yyval.memArg).u.td = td;
        }
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2575 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));

            /* In a C module all structures must be defined. */
            if (currentSpec -> genc)
            {
                (yyval.memArg).atype = defined_type;
                (yyval.memArg).u.snd = (yyvsp[(2) - (2)].scpvalp);
            }
            else
            {
                (yyval.memArg).atype = struct_type;
                (yyval.memArg).u.sname = (yyvsp[(2) - (2)].scpvalp);
            }
        }
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2590 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = ushort_type;
        }
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2594 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = short_type;
        }
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2598 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = uint_type;
        }
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2602 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = uint_type;
        }
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2606 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = int_type;
        }
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2610 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = long_type;
        }
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 2614 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = ulong_type;
        }
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2618 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = longlong_type;
        }
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 2622 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = ulonglong_type;
        }
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2626 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = float_type;
        }
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2630 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = double_type;
        }
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2634 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = bool_type;
        }
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2638 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = sstring_type;
        }
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 2642 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = ustring_type;
        }
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2646 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = string_type;
        }
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2650 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = wstring_type;
        }
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2654 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = void_type;
        }
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2658 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pyobject_type;
        }
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 2662 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pytuple_type;
        }
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 2666 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pylist_type;
        }
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2670 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pydict_type;
        }
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2674 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pycallable_type;
        }
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2678 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pyslice_type;
        }
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2682 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = pytype_type;
        }
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2686 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            memset(&(yyval.memArg), 0, sizeof (argDef));
            (yyval.memArg).atype = ellipsis_type;
        }
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2692 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* The single or first type. */

            (yyval.signature).args[0] = (yyvsp[(1) - (1)].memArg);
            (yyval.signature).nrArgs = 1;
        }
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2698 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Check there is nothing after an ellipsis. */
            if ((yyvsp[(1) - (3)].signature).args[(yyvsp[(1) - (3)].signature).nrArgs - 1].atype == ellipsis_type)
                yyerror("An ellipsis must be at the end of the argument list");

            /* Check there is room. */
            if ((yyvsp[(1) - (3)].signature).nrArgs == MAX_NR_ARGS)
                yyerror("Internal error - increase the value of MAX_NR_ARGS");

            (yyval.signature) = (yyvsp[(1) - (3)].signature);

            (yyval.signature).args[(yyval.signature).nrArgs] = (yyvsp[(3) - (3)].memArg);
            (yyval.signature).nrArgs++;
        }
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2714 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            (yyval.throwlist) = NULL;
        }
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2717 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            if (currentSpec->genc)
                yyerror("Exceptions not allowed in a C module");

            (yyval.throwlist) = (yyvsp[(3) - (4)].throwlist);
        }
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2725 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Empty list so use a blank. */

            (yyval.throwlist) = sipMalloc(sizeof (throwArgs));
            (yyval.throwlist) -> nrArgs = 0;
        }
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2731 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* The only or first exception. */

            (yyval.throwlist) = sipMalloc(sizeof (throwArgs));
            (yyval.throwlist) -> nrArgs = 1;
            (yyval.throwlist) -> args[0] = findException(currentSpec, (yyvsp[(1) - (1)].scpvalp), FALSE);
        }
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2738 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"
    {
            /* Check that it wasn't ...(,arg...). */

            if ((yyvsp[(1) - (3)].throwlist) -> nrArgs == 0)
                yyerror("First exception of throw specifier is missing");

            /* Check there is room. */

            if ((yyvsp[(1) - (3)].throwlist) -> nrArgs == MAX_NR_ARGS)
                yyerror("Internal error - increase the value of MAX_NR_ARGS");

            (yyval.throwlist) = (yyvsp[(1) - (3)].throwlist);
            (yyval.throwlist) -> args[(yyval.throwlist) -> nrArgs++] = findException(currentSpec, (yyvsp[(3) - (3)].scpvalp), FALSE);
        }
    break;



/* Line 1455 of yacc.c  */
#line 6140 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 2754 "/home/phil/hg/sip/sip-4.11.2/sipgen/parser.y"



/*
 * Parse the specification.
 */
void parse(sipSpec *spec, FILE *fp, char *filename, stringList *tsl,
        stringList *xfl, int kwdArgs, int protHack)
{
    classTmplDef *tcd;

    /* Initialise the spec. */
 
    spec->modules = NULL;
    spec->namecache = NULL;
    spec->ifacefiles = NULL;
    spec->classes = NULL;
    spec->classtemplates = NULL;
    spec->exceptions = NULL;
    spec->mappedtypes = NULL;
    spec->mappedtypetemplates = NULL;
    spec->enums = NULL;
    spec->vars = NULL;
    spec->typedefs = NULL;
    spec->exphdrcode = NULL;
    spec->docs = NULL;
    spec->sigslots = FALSE;
    spec->genc = -1;
    spec->plugins = NULL;

    currentSpec = spec;
    neededQualifiers = tsl;
    excludedQualifiers = xfl;
    currentModule = NULL;
    currentMappedType = NULL;
    currentOverIsVirt = FALSE;
    currentCtorIsExplicit = FALSE;
    currentIsStatic = FALSE;
    currentIsSignal = FALSE;
    currentIsSlot = FALSE;
    currentIsTemplate = FALSE;
    previousFile = NULL;
    skipStackPtr = 0;
    currentScopeIdx = 0;
    sectionFlags = 0;
    defaultKwdArgs = kwdArgs;
    makeProtPublic = protHack;

    newModule(fp, filename);
    spec->module = currentModule;

    yyparse();

    handleEOF();
    handleEOM();

    /*
     * Go through each template class and remove it from the list of classes.
     */
    for (tcd = spec->classtemplates; tcd != NULL; tcd = tcd->next)
    {
        classDef **cdp;

        for (cdp = &spec->classes; *cdp != NULL; cdp = &(*cdp)->next)
            if (*cdp == tcd->cd)
            {
                ifaceFileDef **ifdp;

                /* Remove the interface file as well. */
                for (ifdp = &spec->ifacefiles; *ifdp != NULL; ifdp = &(*ifdp)->next)
                    if (*ifdp == tcd->cd->iff)
                    {
                        *ifdp = (*ifdp)->next;
                        break;
                    }

                *cdp = (*cdp)->next;
                break;
            }
    }
}


/*
 * Tell the parser that a complete file has now been read.
 */
void parserEOF(char *name, parserContext *pc)
{
    previousFile = sipStrdup(name);
    currentContext = *pc;
}


/*
 * Append a class definition to a class list if it doesn't already appear.
 * Append is needed specifically for the list of super-classes because the
 * order is important to Python.
 */
void appendToClassList(classList **clp,classDef *cd)
{
    classList *new;

    /* Find the end of the list. */

    while (*clp != NULL)
    {
        if ((*clp) -> cd == cd)
            return;

        clp = &(*clp) -> next;
    }

    new = sipMalloc(sizeof (classList));

    new -> cd = cd;
    new -> next = NULL;

    *clp = new;
}


/*
 * Create a new module for the current specification and make it current.
 */
static void newModule(FILE *fp, char *filename)
{
    moduleDef *mod;

    parseFile(fp, filename, currentModule, FALSE);

    mod = allocModule();
    mod->file = filename;

    if (currentModule != NULL)
        mod->defexception = currentModule->defexception;

    currentModule = mod;
}


/*
 * Allocate and initialise the memory for a new module.
 */
static moduleDef *allocModule()
{
    moduleDef *newmod, **tailp;

    newmod = sipMalloc(sizeof (moduleDef));

    newmod->version = -1;
    newmod->encoding = no_type;
    newmod->qobjclass = -1;
    newmod->nrvirthandlers = -1;
    newmod->next_key = -2;

    /*
     * The consolidated module support needs these to be in order that they
     * appeared.
     */
    for (tailp = &currentSpec->modules; *tailp != NULL; tailp = &(*tailp)->next)
        ;

    *tailp = newmod;

    return newmod;
}


/*
 * Switch to parsing a new file.
 */
static void parseFile(FILE *fp, char *name, moduleDef *prevmod, int optional)
{
    parserContext pc;

    pc.filename = name;
    pc.ifdepth = skipStackPtr;
    pc.prevmod = prevmod;

    if (setInputFile(fp, &pc, optional))
        currentContext = pc;
}


/*
 * Find an interface file, or create a new one.
 */
ifaceFileDef *findIfaceFile(sipSpec *pt, moduleDef *mod, scopedNameDef *fqname,
        ifaceFileType iftype, apiVersionRangeDef *api_range, argDef *ad)
{
    ifaceFileDef *iff, *first_alt = NULL;

    /* See if the name is already used. */

    for (iff = pt->ifacefiles; iff != NULL; iff = iff->next)
    {
        if (compareScopedNames(iff->fqcname, fqname) != 0)
            continue;

        /*
         * If they are both versioned then assume the user knows what they are
         * doing.
         */
        if (iff->api_range != NULL && api_range != NULL && iff->module == mod)
        {
            /* Remember the first of the alternate APIs. */
            if ((first_alt = iff->first_alt) == NULL)
                first_alt = iff;

            break;
        }

        /*
         * They must be the same type except that we allow a class if we want
         * an exception.  This is because we allow classes to be used before
         * they are defined.
         */
        if (iff->type != iftype)
            if (iftype != exception_iface || iff->type != class_iface)
                yyerror("A class, exception, namespace or mapped type has already been defined with the same name");

        /* Ignore an external class declared in another module. */
        if (iftype == class_iface && iff->module != mod)
        {
            classDef *cd;

            for (cd = pt->classes; cd != NULL; cd = cd->next)
                if (cd->iff == iff)
                    break;

            if (cd != NULL && iff->module != NULL && isExternal(cd))
                continue;
        }

        /*
         * If this is a mapped type with the same name defined in a different
         * module, then check that this type isn't the same as any of the
         * mapped types defined in that module.
         */
        if (iftype == mappedtype_iface && iff->module != mod)
        {
            mappedTypeDef *mtd;

            /*
             * This is a bit of a cheat.  With consolidated modules it's
             * possible to have two implementations of a mapped type in
             * different branches of the module hierarchy.  We assume that, if
             * there really are multiple implementations in the same branch,
             * then it will be picked up in a non-consolidated build.
             */
            if (isConsolidated(pt->module))
                continue;

            for (mtd = pt->mappedtypes; mtd != NULL; mtd = mtd->next)
            {
                if (mtd->iff != iff)
                    continue;

                if (ad->atype != template_type ||
                    mtd->type.atype != template_type ||
                    sameBaseType(ad, &mtd->type))
                    yyerror("Mapped type has already been defined in another module");
            }

            /*
             * If we got here then we have a mapped type based on an existing
             * template, but with unique parameters.  We don't want to use
             * interface files from other modules, so skip this one.
             */

            continue;
        }

        /* Ignore a namespace defined in another module. */
        if (iftype == namespace_iface && iff->module != mod)
            continue;

        return iff;
    }

    iff = sipMalloc(sizeof (ifaceFileDef));

    iff->name = cacheName(pt, scopedNameToString(fqname));
    iff->api_range = api_range;

    if (first_alt != NULL)
    {
        iff->first_alt = first_alt;
        iff->next_alt = first_alt->next_alt;

        first_alt->next_alt = iff;
    }
    else
    {
        /* This is the first alternate so point to itself. */
        iff->first_alt = iff;
    }

    iff->type = iftype;
    iff->ifacenr = -1;
    iff->fqcname = fqname;
    iff->module = NULL;
    iff->hdrcode = NULL;
    iff->used = NULL;
    iff->next = pt->ifacefiles;

    pt->ifacefiles = iff;

    return iff;
}


/*
 * Find a class definition in a parse tree.
 */
static classDef *findClass(sipSpec *pt, ifaceFileType iftype,
        apiVersionRangeDef *api_range, scopedNameDef *fqname)
{
    return findClassWithInterface(pt, findIfaceFile(pt, currentModule, fqname, iftype, api_range, NULL));
}


/*
 * Find a class definition given an existing interface file.
 */
static classDef *findClassWithInterface(sipSpec *pt, ifaceFileDef *iff)
{
    classDef *cd;

    for (cd = pt -> classes; cd != NULL; cd = cd -> next)
        if (cd -> iff == iff)
            return cd;

    /* Create a new one. */
    cd = sipMalloc(sizeof (classDef));

    cd->iff = iff;
    cd->pyname = cacheName(pt, classBaseName(cd));
    cd->next = pt->classes;

    pt->classes = cd;

    return cd;
}


/*
 * Add an interface file to an interface file list if it isn't already there.
 */
void addToUsedList(ifaceFileList **ifflp, ifaceFileDef *iff)
{
    /* Make sure we don't try to add an interface file to its own list. */
    if (&iff->used != ifflp)
    {
        ifaceFileList *iffl;

        while ((iffl = *ifflp) != NULL)
        {
            /* Don't bother if it is already there. */
            if (iffl->iff == iff)
                return;

            ifflp = &iffl -> next;
        }

        iffl = sipMalloc(sizeof (ifaceFileList));

        iffl->iff = iff;
        iffl->next = NULL;

        *ifflp = iffl;
    }
}


/*
 * Find an undefined (or create a new) exception definition in a parse tree.
 */
static exceptionDef *findException(sipSpec *pt, scopedNameDef *fqname, int new)
{
    exceptionDef *xd, **tail;
    ifaceFileDef *iff;
    classDef *cd;

    iff = findIfaceFile(pt, currentModule, fqname, exception_iface, NULL, NULL);

    /* See if it is an existing one. */
    for (xd = pt->exceptions; xd != NULL; xd = xd->next)
        if (xd->iff == iff)
            return xd;

    /*
     * If it is an exception interface file then we have never seen this
     * name before.  We require that exceptions are defined before being
     * used, but don't make the same requirement of classes (for reasons of
     * backwards compatibility).  Therefore the name must be reinterpreted
     * as a (as yet undefined) class.
     */
    if (new)
    {
        if (iff->type == exception_iface)
            cd = NULL;
        else
            yyerror("There is already a class with the same name or the exception has been used before being defined");
    }
    else
    {
        if (iff->type == exception_iface)
            iff->type = class_iface;

        cd = findClassWithInterface(pt, iff);
    }

    /* Create a new one. */
    xd = sipMalloc(sizeof (exceptionDef));

    xd->exceptionnr = -1;
    xd->iff = iff;
    xd->pyname = NULL;
    xd->cd = cd;
    xd->bibase = NULL;
    xd->base = NULL;
    xd->raisecode = NULL;
    xd->next = NULL;

    /* Append it to the list. */
    for (tail = &pt->exceptions; *tail != NULL; tail = &(*tail)->next)
        ;

    *tail = xd;

    return xd;
}


/*
 * Find an undefined (or create a new) class definition in a parse tree.
 */
static classDef *newClass(sipSpec *pt, ifaceFileType iftype,
        apiVersionRangeDef *api_range, scopedNameDef *fqname)
{
    int flags;
    classDef *cd, *scope;
    codeBlock *hdrcode;

    if (sectionFlags & SECT_IS_PRIVATE)
        yyerror("Classes, structs and namespaces must be in the public or protected sections");

    flags = 0;

    if ((scope = currentScope()) != NULL)
    {
        if (sectionFlags & SECT_IS_PROT && !makeProtPublic)
        {
            flags = CLASS_IS_PROTECTED;

            if (scope->iff->type == class_iface)
                setHasShadow(scope);
        }

        /* Header code from outer scopes is also included. */
        hdrcode = scope->iff->hdrcode;
    }
    else
        hdrcode = NULL;

    if (pt -> genc)
    {
        /* C structs are always global types. */
        while (fqname -> next != NULL)
            fqname = fqname -> next;

        scope = NULL;
    }

    cd = findClass(pt, iftype, api_range, fqname);

    /* Check it hasn't already been defined. */
    if (iftype != namespace_iface && cd->iff->module != NULL)
        yyerror("The struct/class has already been defined");

    /* Complete the initialisation. */
    cd->classflags |= flags;
    cd->ecd = scope;
    cd->iff->module = currentModule;

    if (currentIsTemplate)
        setIsTemplateClass(cd);

    appendCodeBlock(&cd->iff->hdrcode, hdrcode);

    /* See if it is a namespace extender. */
    if (iftype == namespace_iface)
    {
        classDef *ns;

        for (ns = pt->classes; ns != NULL; ns = ns->next)
        {
            if (ns == cd)
                continue;

            if (ns->iff->type != namespace_iface)
                continue;

            if (compareScopedNames(ns->iff->fqcname, fqname) != 0)
                continue;

            cd->real = ns;
            break;
        }
    }

    return cd;
}


/*
 * Tidy up after finishing a class definition.
 */
static void finishClass(sipSpec *pt, moduleDef *mod, classDef *cd,
        optFlags *of)
{
    const char *pyname;
    optFlag *flg;

    /* Get the Python name and see if it is different to the C++ name. */
    pyname = getPythonName(of, classBaseName(cd));

    cd->pyname = NULL;
    checkAttributes(pt, mod, cd->ecd, NULL, pyname, FALSE);
    cd->pyname = cacheName(pt, pyname);

    if ((flg = findOptFlag(of, "Metatype", dotted_name_flag)) != NULL)
        cd->metatype = cacheName(pt, flg->fvalue.sval);

    if ((flg = findOptFlag(of, "Supertype", dotted_name_flag)) != NULL)
        cd->supertype = cacheName(pt, flg->fvalue.sval);

    if ((flg = findOptFlag(of, "PyQt4Flags", integer_flag)) != NULL)
        cd->pyqt4_flags = flg->fvalue.ival;

    if (findOptFlag(of, "PyQt4NoQMetaObject", bool_flag) != NULL)
        setPyQt4NoQMetaObject(cd);

    if (isOpaque(cd))
    {
        if (findOptFlag(of, "External", bool_flag) != NULL)
            setIsExternal(cd);
    }
    else
    {
        int seq_might, seq_not;
        memberDef *md;

        if (findOptFlag(of, "NoDefaultCtors", bool_flag) != NULL)
            setNoDefaultCtors(cd);

        if (cd -> ctors == NULL)
        {
            if (!noDefaultCtors(cd))
            {
                /* Provide a default ctor. */

                cd->ctors = sipMalloc(sizeof (ctorDef));
 
                cd->ctors->ctorflags = SECT_IS_PUBLIC;
                cd->ctors->pysig.result.atype = void_type;
                cd->ctors->cppsig = &cd->ctors->pysig;

                cd->defctor = cd->ctors;

                setCanCreate(cd);
            }
        }
        else if (cd -> defctor == NULL)
        {
            ctorDef *ct, *last = NULL;

            for (ct = cd -> ctors; ct != NULL; ct = ct -> next)
            {
                if (!isPublicCtor(ct))
                    continue;

                if (ct -> pysig.nrArgs == 0 || ct -> pysig.args[0].defval != NULL)
                {
                    cd -> defctor = ct;
                    break;
                }

                if (last == NULL)
                    last = ct;
            }

            /* The last resort is the first public ctor. */
            if (cd->defctor == NULL)
                cd->defctor = last;
        }

        if (getDeprecated(of))
            setIsDeprecatedClass(cd);

        if (cd->convtocode != NULL && getAllowNone(of))
            setClassHandlesNone(cd);

        if (findOptFlag(of,"Abstract",bool_flag) != NULL)
        {
            setIsAbstractClass(cd);
            setIsIncomplete(cd);
            resetCanCreate(cd);
        }

        /* We assume a public dtor if nothing specific was provided. */
        if (!isDtor(cd))
            setIsPublicDtor(cd);

        if (findOptFlag(of, "DelayDtor", bool_flag) != NULL)
        {
            setIsDelayedDtor(cd);
            setHasDelayedDtors(mod);
        }

        /*
         * There are subtle differences between the add and concat methods and
         * the multiply and repeat methods.  The number versions can have their
         * operands swapped and may return NotImplemented.  If the user has
         * used the /Numeric/ annotation or there are other numeric operators
         * then we use add/multiply.  Otherwise, if there are indexing
         * operators then we use concat/repeat.
         */
        seq_might = seq_not = FALSE;

        for (md = cd -> members; md != NULL; md = md -> next)
            switch (md -> slot)
            {
            case getitem_slot:
            case setitem_slot:
            case delitem_slot:
                /* This might be a sequence. */
                seq_might = TRUE;
                break;

            case sub_slot:
            case isub_slot:
            case div_slot:
            case idiv_slot:
            case mod_slot:
            case imod_slot:
            case floordiv_slot:
            case ifloordiv_slot:
            case truediv_slot:
            case itruediv_slot:
            case pos_slot:
            case neg_slot:
                /* This is definately not a sequence. */
                seq_not = TRUE;
                break;
            }

        if (!seq_not && seq_might)
            for (md = cd -> members; md != NULL; md = md -> next)
            {
                /* Ignore if the user has been explicit. */
                if (isNumeric(md))
                    continue;

                switch (md -> slot)
                {
                case add_slot:
                    md -> slot = concat_slot;
                    break;

                case iadd_slot:
                    md -> slot = iconcat_slot;
                    break;

                case mul_slot:
                    md -> slot = repeat_slot;
                    break;

                case imul_slot:
                    md -> slot = irepeat_slot;
                    break;
                }
            }
    }

    if (inMainModule())
    {
        setIsUsedName(cd->iff->name);
        setIsUsedName(cd->pyname);
    }
}


/*
 * Return the encoded name of a template (ie. including its argument types) as
 * a scoped name.
 */
scopedNameDef *encodedTemplateName(templateDef *td)
{
    int a;
    scopedNameDef *snd;

    snd = copyScopedName(td->fqname);

    for (a = 0; a < td->types.nrArgs; ++a)
    {
        char buf[50];
        int flgs;
        scopedNameDef *arg_snd;
        argDef *ad = &td->types.args[a];

        flgs = 0;

        if (isConstArg(ad))
            flgs += 1;

        if (isReference(ad))
            flgs += 2;

        /* We use numbers so they don't conflict with names. */
        sprintf(buf, "%02d%d%d", ad->atype, flgs, ad->nrderefs);

        switch (ad->atype)
        {
        case defined_type:
            arg_snd = copyScopedName(ad->u.snd);
            break;

        case template_type:
            arg_snd = encodedTemplateName(ad->u.td);
            break;

        case struct_type:
            arg_snd = copyScopedName(ad->u.sname);
            break;

        default:
            arg_snd = NULL;
        }

        /*
         * Replace the first element of the argument name with a copy with the
         * encoding prepended.
         */
        if (arg_snd != NULL)
            arg_snd->name = concat(buf, arg_snd->name, NULL);
        else
            arg_snd = text2scopePart(sipStrdup(buf));

        appendScopedName(&snd, arg_snd);
    }

    return snd;
}


/*
 * Create a new mapped type.
 */
static mappedTypeDef *newMappedType(sipSpec *pt, argDef *ad, optFlags *of)
{
    mappedTypeDef *mtd;
    scopedNameDef *snd;
    ifaceFileDef *iff;
    const char *cname;

    /* Check that the type is one we want to map. */
    switch (ad->atype)
    {
    case defined_type:
        snd = ad->u.snd;
        cname = scopedNameTail(snd);
        break;

    case template_type:
        snd = encodedTemplateName(ad->u.td);
        cname = NULL;
        break;

    case struct_type:
        snd = ad->u.sname;
        cname = scopedNameTail(snd);
        break;

    default:
        yyerror("Invalid type for %MappedType");
    }

    iff = findIfaceFile(pt, currentModule, snd, mappedtype_iface,
            getAPIRange(of), ad);

    /* Check it hasn't already been defined. */
    for (mtd = pt->mappedtypes; mtd != NULL; mtd = mtd->next)
        if (mtd->iff == iff)
        {
            /*
             * We allow types based on the same template but with different
             * arguments.
             */
            if (ad->atype != template_type || sameBaseType(ad, &mtd->type))
                yyerror("Mapped type has already been defined in this module");
        }

    /* The module may not have been set yet. */
    iff->module = currentModule;

    /* Create a new mapped type. */
    mtd = allocMappedType(pt, ad);

    if (cname != NULL)
        mtd->pyname = cacheName(pt, getPythonName(of, cname));

    if (findOptFlag(of, "NoRelease", bool_flag) != NULL)
        setNoRelease(mtd);

    if (getAllowNone(of))
        setHandlesNone(mtd);

    mtd->doctype = getDocType(of);

    mtd->iff = iff;
    mtd->next = pt->mappedtypes;

    pt->mappedtypes = mtd;

    if (inMainModule())
    {
        setIsUsedName(mtd->cname);

        if (mtd->pyname)
            setIsUsedName(mtd->pyname);
    }

    return mtd;
}


/*
 * Allocate, intialise and return a mapped type structure.
 */
mappedTypeDef *allocMappedType(sipSpec *pt, argDef *type)
{
    mappedTypeDef *mtd;

    mtd = sipMalloc(sizeof (mappedTypeDef));

    mtd->type = *type;
    mtd->type.argflags = 0;
    mtd->type.nrderefs = 0;

    mtd->cname = cacheName(pt, type2string(&mtd->type));

    return mtd;
}


/*
 * Create a new enum.
 */
static enumDef *newEnum(sipSpec *pt, moduleDef *mod, mappedTypeDef *mt_scope,
        char *name, optFlags *of, int flags)
{
    enumDef *ed, *first_alt, *next_alt;
    classDef *c_scope;
    ifaceFileDef *scope;

    if (mt_scope != NULL)
    {
        scope = mt_scope->iff;
        c_scope = NULL;
    }
    else
    {
        if ((c_scope = currentScope()) != NULL)
            scope = c_scope->iff;
        else
            scope = NULL;
    }

    ed = sipMalloc(sizeof (enumDef));

    /* Assume the enum isn't versioned. */
    first_alt = ed;
    next_alt = NULL;

    if (name != NULL)
    {
        ed->pyname = cacheName(pt, getPythonName(of, name));
        checkAttributes(pt, mod, c_scope, mt_scope, ed->pyname->text, FALSE);

        ed->fqcname = text2scopedName(scope, name);
        ed->cname = cacheName(pt, scopedNameToString(ed->fqcname));

        if (inMainModule())
        {
            setIsUsedName(ed->pyname);
            setIsUsedName(ed->cname);
        }

        /* If the scope is versioned then look for any alternate. */
        if (scope != NULL && scope->api_range != NULL)
        {
            enumDef *alt;

            for (alt = pt->enums; alt != NULL; alt = alt->next)
            {
                if (alt->module != mod || alt->fqcname == NULL)
                    continue;

                if (compareScopedNames(alt->fqcname, ed->fqcname) == 0)
                {
                    first_alt = alt->first_alt;
                    next_alt = first_alt->next_alt;
                    first_alt->next_alt = ed;

                    break;
                }
            }
        }
    }
    else
    {
        ed->pyname = NULL;
        ed->fqcname = NULL;
        ed->cname = NULL;
    }

    if (flags & SECT_IS_PROT)
    {
        if (makeProtPublic)
        {
            flags &= ~SECT_IS_PROT;
            flags |= SECT_IS_PUBLIC;
        }
        else if (c_scope != NULL)
        {
            setHasShadow(c_scope);
        }
    }

    ed->enumflags = flags;
    ed->enumnr = -1;
    ed->ecd = c_scope;
    ed->emtd = mt_scope;
    ed->first_alt = first_alt;
    ed->next_alt = next_alt;
    ed->module = mod;
    ed->members = NULL;
    ed->slots = NULL;
    ed->overs = NULL;
    ed->next = pt -> enums;

    pt->enums = ed;

    return ed;
}


/*
 * Get the type values and (optionally) the type names for substitution in
 * handwritten code.
 */
void appendTypeStrings(scopedNameDef *ename, signatureDef *patt, signatureDef *src, signatureDef *known, scopedNameDef **names, scopedNameDef **values)
{
    int a;

    for (a = 0; a < patt->nrArgs; ++a)
    {
        argDef *pad = &patt->args[a];

        if (pad->atype == defined_type)
        {
            char *nam = NULL, *val;
            argDef *sad;

            /*
             * If the type names are already known then check that this is one
             * of them.
             */
            if (known == NULL)
                nam = scopedNameTail(pad->u.snd);
            else if (pad->u.snd->next == NULL)
            {
                int k;

                for (k = 0; k < known->nrArgs; ++k)
                {
                    /* Skip base types. */
                    if (known->args[k].atype != defined_type)
                        continue;

                    if (strcmp(pad->u.snd->name, known->args[k].u.snd->name) == 0)
                    {
                        nam = pad->u.snd->name;
                        break;
                    }
                }
            }

            if (nam == NULL)
                continue;

            /* Add the name. */
            appendScopedName(names, text2scopePart(nam));

            /*
             * Add the corresponding value.  For defined types we don't want 
             * any indirection or references.
             */
            sad = &src->args[a];

            if (sad->atype == defined_type)
                val = scopedNameToString(sad->u.snd);
            else
                val = type2string(sad);

            appendScopedName(values, text2scopePart(val));
        }
        else if (pad->atype == template_type)
        {
            argDef *sad = &src->args[a];

            /* These checks shouldn't be necessary, but... */
            if (sad->atype == template_type && pad->u.td->types.nrArgs == sad->u.td->types.nrArgs)
                appendTypeStrings(ename, &pad->u.td->types, &sad->u.td->types, known, names, values);
        }
    }
}


/*
 * Convert a type to a string on the heap.  The string will use the minimum
 * whitespace while still remaining valid C++.
 */
static char *type2string(argDef *ad)
{
    int i, on_heap = FALSE;
    int nr_derefs = ad->nrderefs;
    int is_reference = isReference(ad);
    char *s;

    /* Use the original type if possible. */
    if (ad->original_type != NULL && !noTypeName(ad->original_type))
    {
        s = scopedNameToString(ad->original_type->fqname);
        on_heap = TRUE;

        nr_derefs -= ad->original_type->type.nrderefs;

        if (isReference(&ad->original_type->type))
            is_reference = FALSE;
    }
    else
        switch (ad->atype)
        {
        case template_type:
            {
                templateDef *td = ad->u.td;

                s = scopedNameToString(td->fqname);
                append(&s, "<");

                for (i = 0; i < td->types.nrArgs; ++i)
                {
                    char *sub_type = type2string(&td->types.args[i]);

                    if (i > 0)
                        append(&s, ",");

                    append(&s, sub_type);
                    free(sub_type);
                }

                if (s[strlen(s) - 1] == '>')
                    append(&s, " >");
                else
                    append(&s, ">");

                on_heap = TRUE;
                break;
            }

        case struct_type:
            s = scopedNameToString(ad->u.sname);
            on_heap = TRUE;
            break;

        case defined_type:
            s = scopedNameToString(ad->u.snd);
            on_heap = TRUE;
            break;

        case ustring_type:
            s = "unsigned char";
            break;

        case ascii_string_type:
        case latin1_string_type:
        case utf8_string_type:
        case string_type:
            s = "char";
            break;

        case sstring_type:
            s = "signed char";
            break;

        case wstring_type:
            s = "wchar_t";
            break;

        case ushort_type:
            s = "unsigned short";
            break;

        case short_type:
            s = "short";
            break;

        case uint_type:
            s = "uint";
            break;

        case int_type:
        case cint_type:
            s = "int";
            break;

        case ulong_type:
            s = "unsigned long";
            break;

        case long_type:
            s = "long";
            break;

        case ulonglong_type:
            s = "unsigned long long";
            break;

        case longlong_type:
            s = "long long";
            break;

        case float_type:
        case cfloat_type:
            s = "float";
            break;

        case double_type:
        case cdouble_type:
            s = "double";
            break;

        case bool_type:
        case cbool_type:
            s = "bool";
            break;

        default:
            fatal("Unsupported type argument to type2string(): %d\n", ad->atype);
        }

    /* Make sure the string is on the heap. */
    if (!on_heap)
        s = sipStrdup(s);

    while (nr_derefs-- > 0)
        append(&s, "*");

    if (is_reference)
        append(&s, "&");

    return s;
}


/*
 * Convert a scoped name to a string on the heap.
 */
static char *scopedNameToString(scopedNameDef *name)
{
    static const char scope_string[] = "::";
    size_t len;
    scopedNameDef *snd;
    char *s, *dp;

    /* Work out the length of buffer needed. */
    len = 0;

    for (snd = name; snd != NULL; snd = snd->next)
    {
        len += strlen(snd->name);

        if (snd->next != NULL)
        {
            /* Ignore the encoded part of template names. */
            if (isdigit(snd->next->name[0]))
                break;

            len += strlen(scope_string);
        }
    }

    /* Allocate and populate the buffer. */
    dp = s = sipMalloc(len + 1);

    for (snd = name; snd != NULL; snd = snd->next)
    {
        strcpy(dp, snd->name);
        dp += strlen(snd->name);

        if (snd->next != NULL)
        {
            /* Ignore the encoded part of template names. */
            if (isdigit(snd->next->name[0]))
                break;

            strcpy(dp, scope_string);
            dp += strlen(scope_string);
        }
    }

    return s;
}


/*
 * Instantiate a class template.
 */
static void instantiateClassTemplate(sipSpec *pt, moduleDef *mod,
        classDef *scope, scopedNameDef *fqname, classTmplDef *tcd,
        templateDef *td)
{
    scopedNameDef *type_names, *type_values;
    classDef *cd;
    ctorDef *oct, **cttail;
    argDef *ad;
    ifaceFileList *iffl, **used;

    type_names = type_values = NULL;
    appendTypeStrings(classFQCName(tcd->cd), &tcd->sig, &td->types, NULL, &type_names, &type_values);

    /*
     * Add a mapping from the template name to the instantiated name.  If we
     * have got this far we know there is room for it.
     */
    ad = &tcd->sig.args[tcd->sig.nrArgs++];
    memset(ad, 0, sizeof (argDef));
    ad->atype = defined_type;
    ad->u.snd = classFQCName(tcd->cd);

    appendScopedName(&type_names, text2scopePart(scopedNameTail(classFQCName(tcd->cd))));
    appendScopedName(&type_values, text2scopePart(scopedNameToString(fqname)));

    /* Create the new class. */
    cd = sipMalloc(sizeof (classDef));

    /* Start with a shallow copy. */
    *cd = *tcd->cd;

    resetIsTemplateClass(cd);
    cd->pyname = cacheName(pt, scopedNameTail(fqname));
    cd->td = td;

    /* Handle the interface file. */
    cd->iff = findIfaceFile(pt, mod, fqname, class_iface,
            (scope != NULL ? scope->iff->api_range : NULL), NULL);
    cd->iff->module = mod;

    /* Make a copy of the used list and add the enclosing scope. */
    used = &cd->iff->used;

    for (iffl = tcd->cd->iff->used; iffl != NULL; iffl = iffl->next)
        addToUsedList(used, iffl->iff);

    /* Include any scope header code. */
    if (scope != NULL)
        appendCodeBlock(&cd->iff->hdrcode, scope->iff->hdrcode);

    if (inMainModule())
    {
        setIsUsedName(cd->iff->name);
        setIsUsedName(cd->pyname);
    }

    cd->ecd = currentScope();

    /* Handle the enums. */
    instantiateTemplateEnums(pt, tcd, td, cd, used, type_names, type_values);

    /* Handle the variables. */
    instantiateTemplateVars(pt, tcd, td, cd, used, type_names, type_values);

    /* Handle the ctors. */
    cd->ctors = NULL;
    cttail = &cd->ctors;

    for (oct = tcd->cd->ctors; oct != NULL; oct = oct->next)
    {
        ctorDef *nct = sipMalloc(sizeof (ctorDef));

        /* Start with a shallow copy. */
        *nct = *oct;

        templateSignature(&nct->pysig, FALSE, tcd, td, cd);

        if (oct->cppsig == NULL)
            nct->cppsig = NULL;
        else if (oct->cppsig == &oct->pysig)
            nct->cppsig = &nct->pysig;
        else
        {
            nct->cppsig = sipMalloc(sizeof (signatureDef));

            *nct->cppsig = *oct->cppsig;

            templateSignature(nct->cppsig, FALSE, tcd, td, cd);
        }

        nct->methodcode = templateCode(pt, used, nct->methodcode, type_names, type_values);

        nct->next = NULL;
        *cttail = nct;
        cttail = &nct->next;

        /* Handle the default ctor. */
        if (tcd->cd->defctor == oct)
            cd->defctor = nct;
    }

    cd->dealloccode = templateCode(pt, used, cd->dealloccode, type_names, type_values);
    cd->dtorcode = templateCode(pt, used, cd->dtorcode, type_names, type_values);

    /* Handle the methods. */
    cd->members = instantiateTemplateMethods(tcd->cd->members, mod);
    cd->overs = instantiateTemplateOverloads(pt, tcd->cd->overs,
            tcd->cd->members, cd->members, tcd, td, cd, used, type_names,
            type_values);

    cd->cppcode = templateCode(pt, used, cd->cppcode, type_names, type_values);
    cd->iff->hdrcode = templateCode(pt, used, cd->iff->hdrcode, type_names, type_values);
    cd->convtosubcode = templateCode(pt, used, cd->convtosubcode, type_names, type_values);
    cd->convtocode = templateCode(pt, used, cd->convtocode, type_names, type_values);
    cd->travcode = templateCode(pt, used, cd->travcode, type_names, type_values);
    cd->clearcode = templateCode(pt, used, cd->clearcode, type_names, type_values);
    cd->getbufcode = templateCode(pt, used, cd->getbufcode, type_names, type_values);
    cd->releasebufcode = templateCode(pt, used, cd->releasebufcode, type_names, type_values);
    cd->readbufcode = templateCode(pt, used, cd->readbufcode, type_names, type_values);
    cd->writebufcode = templateCode(pt, used, cd->writebufcode, type_names, type_values);
    cd->segcountcode = templateCode(pt, used, cd->segcountcode, type_names, type_values);
    cd->charbufcode = templateCode(pt, used, cd->charbufcode, type_names, type_values);
    cd->picklecode = templateCode(pt, used, cd->picklecode, type_names, type_values);
    cd->next = pt->classes;

    pt->classes = cd;

    tcd->sig.nrArgs--;

    freeScopedName(type_names);
    freeScopedName(type_values);
}


/*
 * Instantiate the methods of a template class.
 */
static memberDef *instantiateTemplateMethods(memberDef *tmd, moduleDef *mod)
{
    memberDef *md, *methods, **mdtail;

    methods = NULL;
    mdtail = &methods;

    for (md = tmd; md != NULL; md = md->next)
    {
        memberDef *nmd = sipMalloc(sizeof (memberDef));

        /* Start with a shallow copy. */
        *nmd = *md;

        nmd->module = mod;

        if (inMainModule())
            setIsUsedName(nmd->pyname);

        nmd->next = NULL;
        *mdtail = nmd;
        mdtail = &nmd->next;
    }

    return methods;
}


/*
 * Instantiate the overloads of a template class.
 */
static overDef *instantiateTemplateOverloads(sipSpec *pt, overDef *tod,
        memberDef *tmethods, memberDef *methods, classTmplDef *tcd,
        templateDef *td, classDef *cd, ifaceFileList **used,
        scopedNameDef *type_names, scopedNameDef *type_values)
{
    overDef *od, *overloads, **odtail;

    overloads = NULL;
    odtail = &overloads;

    for (od = tod; od != NULL; od = od->next)
    {
        overDef *nod = sipMalloc(sizeof (overDef));
        memberDef *nmd, *omd;

        /* Start with a shallow copy. */
        *nod = *od;

        for (nmd = methods, omd = tmethods; omd != NULL; omd = omd->next, nmd = nmd->next)
            if (omd == od->common)
            {
                nod->common = nmd;
                break;
            }

        templateSignature(&nod->pysig, TRUE, tcd, td, cd);

        if (od->cppsig == &od->pysig)
            nod->cppsig = &nod->pysig;
        else
        {
            nod->cppsig = sipMalloc(sizeof (signatureDef));

            *nod->cppsig = *od->cppsig;

            templateSignature(nod->cppsig, TRUE, tcd, td, cd);
        }

        nod->methodcode = templateCode(pt, used, nod->methodcode, type_names, type_values);

        /* Handle any virtual handler. */
        if (od->virthandler != NULL)
        {
            moduleDef *mod = cd->iff->module;

            nod->virthandler = sipMalloc(sizeof (virtHandlerDef));

            /* Start with a shallow copy. */
            *nod->virthandler = *od->virthandler;

            if (od->virthandler->cppsig == &od->pysig)
                nod->virthandler->cppsig = &nod->pysig;
            else
            {
                nod->virthandler->cppsig = sipMalloc(sizeof (signatureDef));

                *nod->virthandler->cppsig = *od->virthandler->cppsig;

                templateSignature(nod->virthandler->cppsig, TRUE, tcd, td, cd);
            }

            nod->virthandler->module = mod;
            nod->virthandler->virtcode = templateCode(pt, used, nod->virthandler->virtcode, type_names, type_values);
            nod->virthandler->next = mod->virthandlers;

            mod->virthandlers = nod->virthandler;
        }

        nod->next = NULL;
        *odtail = nod;
        odtail = &nod->next;
    }

    return overloads;
}


/*
 * Instantiate the enums of a template class.
 */
static void instantiateTemplateEnums(sipSpec *pt, classTmplDef *tcd,
        templateDef *td, classDef *cd, ifaceFileList **used,
        scopedNameDef *type_names, scopedNameDef *type_values)
{
    enumDef *ted;
    moduleDef *mod = cd->iff->module;

    for (ted = pt->enums; ted != NULL; ted = ted->next)
        if (ted->ecd == tcd->cd)
        {
            enumDef *ed;
            enumMemberDef *temd;

            ed = sipMalloc(sizeof (enumDef));

            /* Start with a shallow copy. */
            *ed = *ted;

            if (ed->fqcname != NULL)
            {
                ed->fqcname = text2scopedName(cd->iff,
                        scopedNameTail(ed->fqcname));
                ed->cname = cacheName(pt, scopedNameToString(ed->fqcname));
            }

            if (inMainModule())
            {
                if (ed->pyname != NULL)
                    setIsUsedName(ed->pyname);

                if (ed->cname != NULL)
                    setIsUsedName(ed->cname);
            }

            ed->ecd = cd;
            ed->first_alt = ed;
            ed->module = mod;
            ed->members = NULL;

            for (temd = ted->members; temd != NULL; temd = temd->next)
            {
                enumMemberDef *emd;

                emd = sipMalloc(sizeof (enumMemberDef));

                /* Start with a shallow copy. */
                *emd = *temd;
                emd->ed = ed;

                emd->next = ed->members;
                ed->members = emd;
            }

            ed->slots = instantiateTemplateMethods(ted->slots, mod);
            ed->overs = instantiateTemplateOverloads(pt, ted->overs,
                    ted->slots, ed->slots, tcd, td, cd, used, type_names,
                    type_values);

            ed->next = pt->enums;
            pt->enums = ed;
        }
}


/*
 * Instantiate the variables of a template class.
 */
static void instantiateTemplateVars(sipSpec *pt, classTmplDef *tcd,
        templateDef *td, classDef *cd, ifaceFileList **used,
        scopedNameDef *type_names, scopedNameDef *type_values)
{
    varDef *tvd;

    for (tvd = pt->vars; tvd != NULL; tvd = tvd->next)
        if (tvd->ecd == tcd->cd)
        {
            varDef *vd;

            vd = sipMalloc(sizeof (varDef));

            /* Start with a shallow copy. */
            *vd = *tvd;

            if (inMainModule())
                setIsUsedName(vd->pyname);

            vd->fqcname = text2scopedName(cd->iff,
                    scopedNameTail(vd->fqcname));
            vd->ecd = cd;
            vd->module = cd->iff->module;

            templateType(&vd->type, tcd, td, cd);

            vd->accessfunc = templateCode(pt, used, vd->accessfunc, type_names, type_values);
            vd->getcode = templateCode(pt, used, vd->getcode, type_names, type_values);
            vd->setcode = templateCode(pt, used, vd->setcode, type_names, type_values);

            addVariable(pt, vd);
        }
}


/*
 * Replace any template arguments in a signature.
 */
static void templateSignature(signatureDef *sd, int result, classTmplDef *tcd, templateDef *td, classDef *ncd)
{
    int a;

    if (result)
        templateType(&sd->result, tcd, td, ncd);

    for (a = 0; a < sd->nrArgs; ++a)
        templateType(&sd->args[a], tcd, td, ncd);
}


/*
 * Replace any template arguments in a type.
 */
static void templateType(argDef *ad, classTmplDef *tcd, templateDef *td, classDef *ncd)
{
    int a;
    char *name;

    /* Descend into any sub-templates. */
    if (ad->atype == template_type)
    {
        templateDef *new_td = sipMalloc(sizeof (templateDef));

        /* Make a deep copy of the template definition. */
        *new_td = *ad->u.td;
        ad->u.td = new_td;

        templateSignature(&ad->u.td->types, FALSE, tcd, td, ncd);

        return;
    }

    /* Ignore if it isn't an unscoped name. */
    if (ad->atype != defined_type || ad->u.snd->next != NULL)
        return;

    name = ad->u.snd->name;

    for (a = 0; a < tcd->sig.nrArgs - 1; ++a)
        if (strcmp(name, scopedNameTail(tcd->sig.args[a].u.snd)) == 0)
        {
            argDef *tad = &td->types.args[a];

            ad->atype = tad->atype;

            /* We take the constrained flag from the real type. */
            resetIsConstrained(ad);

            if (isConstrained(tad))
                setIsConstrained(ad);

            ad->u = tad->u;

            return;
        }

    /* Handle the class name itself. */
    if (strcmp(name, scopedNameTail(classFQCName(tcd->cd))) == 0)
    {
        ad->atype = class_type;
        ad->u.cd = ncd;
        ad->original_type = NULL;
    }
}


/*
 * Replace any template arguments in a literal code block.
 */
codeBlock *templateCode(sipSpec *pt, ifaceFileList **used, codeBlock *ocb,
        scopedNameDef *names, scopedNameDef *values)
{
    codeBlock *ncb = NULL, **tail = &ncb;

    while (ocb != NULL)
    {
        char *at = ocb->frag;

        do
        {
            char *first = NULL;
            codeBlock *cb;
            scopedNameDef *nam, *val, *nam_first, *val_first;

            /*
             * Go through the rest of this fragment looking for each of the
             * types and the name of the class itself.
             */
            nam = names;
            val = values;

            while (nam != NULL && val != NULL)
            {
                char *cp;

                if ((cp = strstr(at, nam->name)) != NULL)
                    if (first == NULL || first > cp)
                    {
                        nam_first = nam;
                        val_first = val;
                        first = cp;
                    }

                nam = nam->next;
                val = val->next;
            }

            /* Create the new fragment. */
            cb = sipMalloc(sizeof (codeBlock));

            if (at == ocb->frag)
            {
                cb->filename = ocb->filename;
                cb->linenr = ocb->linenr;
            }
            else
                cb->filename = NULL;

            cb->next = NULL;
            *tail = cb;
            tail = &cb->next;

            /* See if anything was found. */
            if (first == NULL)
            {
                /* We can just point to this. */
                cb->frag = at;

                /* All done with this one. */
                at = NULL;
            }
            else
            {
                static char *gen_names[] = {
                    "sipType_",
                    "sipClass_",
                    "sipEnum_",
                    "sipException_",
                    NULL
                };

                char *dp, *sp, **gn;
                int genname = FALSE;

                /*
                 * If the context in which the text is used is in the name of a
                 * SIP generated object then translate any "::" scoping to "_".
                 */
                for (gn = gen_names; *gn != NULL; ++gn)
                    if (search_back(first, at, *gn))
                    {
                        addUsedFromCode(pt, used, val_first->name);
                        genname = TRUE;
                        break;
                    }

                /* Fragment the fragment. */
                cb->frag = sipMalloc(first - at + strlen(val_first->name) + 1);

                strncpy(cb->frag, at, first - at);

                dp = &cb->frag[first - at];
                sp = val_first->name;

                if (genname)
                {
                    char gch;

                    while ((gch = *sp++) != '\0')
                        if (gch == ':' && *sp == ':')
                        {
                            *dp++ = '_';
                            ++sp;
                        }
                        else
                            *dp++ = gch;

                    *dp = '\0';
                }
                else
                    strcpy(dp, sp);

                /* Move past the replaced text. */
                at = first + strlen(nam_first->name);
            }
        }
        while (at != NULL && *at != '\0');

        ocb = ocb->next;
    }

    return ncb;
}


/*
 * Return TRUE if the text at the end of a string matches the target string.
 */
static int search_back(const char *end, const char *start, const char *target)
{
    size_t tlen = strlen(target);

    if (start + tlen >= end)
        return FALSE;

    return (strncmp(end - tlen, target, tlen) == 0);
}


/*
 * Add any needed interface files based on handwritten code.
 */
static void addUsedFromCode(sipSpec *pt, ifaceFileList **used, const char *sname)
{
    ifaceFileDef *iff;
    enumDef *ed;

    for (iff = pt->ifacefiles; iff != NULL; iff = iff->next)
    {
        if (iff->type != class_iface && iff->type != exception_iface)
            continue;

        if (sameName(iff->fqcname, sname))
        {
            addToUsedList(used, iff);
            return;
        }
    }

    for (ed = pt->enums; ed != NULL; ed = ed->next)
    {
        if (ed->ecd == NULL)
            continue;

        if (sameName(ed->fqcname, sname))
        {
            addToUsedList(used, ed->ecd->iff);
            return;
        }
    }
}


/*
 * Compare a scoped name with its string equivalent.
 */
static int sameName(scopedNameDef *snd, const char *sname)
{
    while (snd != NULL && *sname != '\0')
    {
        const char *sp = snd->name;

        while (*sp != '\0' && *sname != ':' && *sname != '\0')
            if (*sp++ != *sname++)
                return FALSE;

        if (*sp != '\0' || (*sname != ':' && *sname != '\0'))
            return FALSE;

        snd = snd->next;

        if (*sname == ':')
            sname += 2;
    }

    return (snd == NULL && *sname == '\0');
}


/*
 * Compare a (possibly) relative scoped name with a fully qualified scoped name
 * while taking the current scope into account.
 */
static int foundInScope(scopedNameDef *fq_name, scopedNameDef *rel_name)
{
    classDef *scope;

    for (scope = currentScope(); scope != NULL; scope = scope->ecd)
    {
        scopedNameDef *snd;
        int found;

        snd = copyScopedName(classFQCName(scope));
        appendScopedName(&snd, copyScopedName(rel_name));

        found = (compareScopedNames(fq_name, snd) == 0);

        freeScopedName(snd);

        if (found)
            return TRUE;
    }

    return compareScopedNames(fq_name, rel_name) == 0;
}


/*
 * Create a new typedef.
 */
static void newTypedef(sipSpec *pt, moduleDef *mod, char *name, argDef *type,
        optFlags *optflgs)
{
    typedefDef *td, **tdp;
    scopedNameDef *fqname;
    classDef *scope;

    scope = currentScope();
    fqname = text2scopedName((scope != NULL ? scope->iff : NULL), name);

    /* See if we are instantiating a template class. */
    if (type->atype == template_type)
    {
        classTmplDef *tcd;
        templateDef *td = type->u.td;

        for (tcd = pt->classtemplates; tcd != NULL; tcd = tcd->next)
            if (foundInScope(tcd->cd->iff->fqcname, td->fqname) &&
                sameTemplateSignature(&tcd->sig, &td->types, FALSE))
            {
                instantiateClassTemplate(pt, mod, scope, fqname, tcd, td);

                /* All done. */
                return;
            }
    }

    /*
     * Check it doesn't already exist and find the position in the sorted list
     * where it should be put.
     */
    for (tdp = &pt->typedefs; *tdp != NULL; tdp = &(*tdp)->next)
    {
        int res = compareScopedNames((*tdp)->fqname, fqname);

        if (res == 0)
        {
            fatalScopedName(fqname);
            fatal(" already defined\n");
        }

        if (res > 0)
            break;
    }

    td = sipMalloc(sizeof (typedefDef));

    td->tdflags = 0;
    td->fqname = fqname;
    td->ecd = scope;
    td->module = mod;
    td->type = *type;

    td->next = *tdp;
    *tdp = td;

    if (findOptFlag(optflgs, "NoTypeName", bool_flag) != NULL)
        setNoTypeName(td);

    mod->nrtypedefs++;
}


/*
 * Speculatively try and resolve any typedefs.  In some cases (eg. when
 * comparing template signatures) it helps to use the real type if it is known.
 * Note that this wouldn't be necessary if we required that all types be known
 * before they are used.
 */
static void resolveAnyTypedef(sipSpec *pt, argDef *ad)
{
    argDef orig = *ad;

    while (ad->atype == defined_type)
    {
        ad->atype = no_type;
        searchTypedefs(pt, ad->u.snd, ad);

        /*
         * Don't resolve to a template type as it may be superceded later on
         * by a more specific mapped type.
         */
        if (ad->atype == no_type || ad->atype == template_type)
        {
            *ad = orig;
            break;
        }
    }
}


/*
 * Return TRUE if the template signatures are the same.  A deep comparison is
 * used for mapped type templates where we want to recurse into any nested
 * templates.
 */
int sameTemplateSignature(signatureDef *tmpl_sd, signatureDef *args_sd,
        int deep)
{
    int a;

    if (tmpl_sd->nrArgs != args_sd->nrArgs)
        return FALSE;

    for (a = 0; a < tmpl_sd->nrArgs; ++a)
    {
        argDef *tmpl_ad = &tmpl_sd->args[a];
        argDef *args_ad = &args_sd->args[a];

        /*
         * If we are doing a shallow comparision (ie. for class templates) then
         * a type name in the template signature matches anything in the
         * argument signature.
         */
        if (tmpl_ad->atype == defined_type && !deep)
            continue;

        /*
         * For type names only compare the references and pointers, and do the
         * same for any nested templates.
         */
        if (tmpl_ad->atype == defined_type && args_ad->atype == defined_type)
        {
            if (isReference(tmpl_ad) != isReference(args_ad) || tmpl_ad->nrderefs != args_ad->nrderefs)
                return FALSE;
        }
        else if (tmpl_ad->atype == template_type && args_ad->atype == template_type)
        {
            if (!sameTemplateSignature(&tmpl_ad->u.td->types, &args_ad->u.td->types, deep))
                return FALSE;
        }
        else if (!sameBaseType(tmpl_ad, args_ad))
            return FALSE;
    }

    return TRUE;
}


/*
 * Create a new variable.
 */
static void newVar(sipSpec *pt,moduleDef *mod,char *name,int isstatic,
           argDef *type,optFlags *of,codeBlock *acode,codeBlock *gcode,
           codeBlock *scode)
{
    varDef *var;
    classDef *escope = currentScope();
    nameDef *nd = cacheName(pt,getPythonName(of,name));

    if (inMainModule())
        setIsUsedName(nd);

    checkAttributes(pt, mod, escope, NULL, nd->text, FALSE);

    var = sipMalloc(sizeof (varDef));

    var->pyname = nd;
    var->fqcname = text2scopedName((escope != NULL ? escope->iff : NULL),
            name);
    var->ecd = escope;
    var->module = mod;
    var->varflags = 0;
    var->type = *type;
    var->accessfunc = acode;
    var->getcode = gcode;
    var->setcode = scode;

    if (isstatic || (escope != NULL && escope->iff->type == namespace_iface))
        setIsStaticVar(var);

    addVariable(pt, var);
}


/*
 * Create a new ctor.
 */
static void newCtor(char *name, int sectFlags, signatureDef *args,
        optFlags *optflgs, codeBlock *methodcode, throwArgs *exceptions,
        signatureDef *cppsig, int explicit, codeBlock *docstring)
{
    ctorDef *ct, **ctp;
    classDef *cd = currentScope();

    /* Check the name of the constructor. */
    if (strcmp(classBaseName(cd), name) != 0)
        yyerror("Constructor doesn't have the same name as its class");

    if (docstring != NULL)
        appendCodeBlock(&cd->docstring, docstring);

    /* Add to the list of constructors. */
    ct = sipMalloc(sizeof (ctorDef));

    if (sectFlags & SECT_IS_PROT && makeProtPublic)
    {
        sectFlags &= ~SECT_IS_PROT;
        sectFlags |= SECT_IS_PUBLIC;
    }

    /* Allow the signature to be used like an function signature. */
    memset(&args->result, 0, sizeof (argDef));
    args->result.atype = void_type;

    ct->ctorflags = sectFlags;
    ct->api_range = getAPIRange(optflgs);
    ct->pysig = *args;
    ct->cppsig = (cppsig != NULL ? cppsig : &ct->pysig);
    ct->exceptions = exceptions;
    ct->methodcode = methodcode;

    if (!isPrivateCtor(ct))
        setCanCreate(cd);

    if (isProtectedCtor(ct))
        setHasShadow(cd);

    if (explicit)
        setIsExplicitCtor(ct);

    getHooks(optflgs, &ct->prehook, &ct->posthook);

    if (getReleaseGIL(optflgs))
        setIsReleaseGILCtor(ct);
    else if (getHoldGIL(optflgs))
        setIsHoldGILCtor(ct);

    if (getTransfer(optflgs))
        setIsResultTransferredCtor(ct);

    if (getDeprecated(optflgs))
        setIsDeprecatedCtor(ct);

    if (!isPrivateCtor(ct) && usesKeywordArgs(optflgs, &ct->pysig))
        setUseKeywordArgsCtor(ct);

    if (findOptFlag(optflgs, "NoDerived", bool_flag) != NULL)
    {
        if (cppsig != NULL)
            yyerror("The /NoDerived/ annotation cannot be used with a C++ signature");

        if (methodcode == NULL)
            yyerror("The /NoDerived/ annotation must be used with %MethodCode");

        ct->cppsig = NULL;
    }

    if (findOptFlag(optflgs, "Default", bool_flag) != NULL)
    {
        if (cd->defctor != NULL)
            yyerror("A constructor with the /Default/ annotation has already been defined");

        cd->defctor = ct;
    }

    /* Append to the list. */
    for (ctp = &cd->ctors; *ctp != NULL; ctp = &(*ctp)->next)
        ;

    *ctp = ct;
}


/*
 * Create a new function.
 */
static void newFunction(sipSpec *pt, moduleDef *mod, classDef *c_scope,
        mappedTypeDef *mt_scope, int sflags, int isstatic, int issignal,
        int isslot, int isvirt, char *name, signatureDef *sig, int isconst,
        int isabstract, optFlags *optflgs, codeBlock *methodcode,
        codeBlock *vcode, throwArgs *exceptions, signatureDef *cppsig,
        codeBlock *docstring)
{
    int factory, xferback, no_arg_parser;
    overDef *od, **odp, **headp;
    optFlag *of;
    virtHandlerDef *vhd;

    /* Extra checks for a C module. */
    if (pt->genc)
    {
        if (c_scope != NULL)
            yyerror("Function declaration not allowed in a struct in a C module");

        if (isstatic)
            yyerror("Static functions not allowed in a C module");

        if (exceptions != NULL)
            yyerror("Exceptions not allowed in a C module");
    }

    if (mt_scope != NULL)
        headp = &mt_scope->overs;
    else if (c_scope != NULL)
        headp = &c_scope->overs;
    else
        headp = &mod->overs;

    /*
     * See if the function has a non-lazy method.  These are methods that
     * Python expects to see defined in the type before any instance of the
     * type is created.
     */
    if (c_scope != NULL)
    {
        if (strcmp(name, "__enter__") == 0 || strcmp(name, "__exit__") == 0)
            setHasNonlazyMethod(c_scope);
    }

    /* See if it is a factory method. */
    if (findOptFlag(optflgs, "Factory", bool_flag) != NULL)
        factory = TRUE;
    else
    {
        int a;

        factory = FALSE;

        /* Check /TransferThis/ wasn't specified. */
        if (c_scope == NULL || isstatic)
            for (a = 0; a < sig->nrArgs; ++a)
                if (isThisTransferred(&sig->args[a]))
                    yyerror("/TransferThis/ may only be specified in constructors and class methods");
    }

    /* See if the result is to be returned to Python ownership. */
    xferback = (findOptFlag(optflgs, "TransferBack", bool_flag) != NULL);

    if (factory && xferback)
        yyerror("/TransferBack/ and /Factory/ cannot both be specified");

    /* Create a new overload definition. */

    od = sipMalloc(sizeof (overDef));

    /* Set the overload flags. */

    if ((sflags & SECT_IS_PROT) && makeProtPublic)
    {
        sflags &= ~SECT_IS_PROT;
        sflags |= SECT_IS_PUBLIC | OVER_REALLY_PROT;
    }

    od->overflags = sflags;

    if (issignal)
    {
        resetIsSlot(od);
        setIsSignal(od);
    }
    else if (isslot)
    {
        resetIsSignal(od);
        setIsSlot(od);
    }

    if (factory)
        setIsFactory(od);

    if (xferback)
        setIsResultTransferredBack(od);

    if (getTransfer(optflgs))
        setIsResultTransferred(od);

    if (findOptFlag(optflgs, "TransferThis", bool_flag) != NULL)
        setIsThisTransferredMeth(od);

    if (isProtected(od))
        setHasShadow(c_scope);

    if ((isSlot(od) || isSignal(od)) && !isPrivate(od))
    {
        if (isSignal(od))
            setHasShadow(c_scope);

        pt->sigslots = TRUE;
    }

    if (isSignal(od) && (methodcode != NULL || vcode != NULL))
        yyerror("Cannot provide code for signals");

    if (isstatic)
    {
        if (isSignal(od))
            yyerror("Static functions cannot be signals");

        if (isvirt)
            yyerror("Static functions cannot be virtual");

        setIsStatic(od);
    }

    if (isconst)
        setIsConst(od);

    if (isabstract)
    {
        if (sflags == 0)
            yyerror("Non-class function specified as abstract");

        setIsAbstract(od);
    }

    if ((of = findOptFlag(optflgs, "AutoGen", opt_name_flag)) != NULL)
    {
        if (of->fvalue.sval == NULL || isEnabledFeature(of->fvalue.sval))
            setIsAutoGen(od);
    }

    if (isvirt)
    {
        if (isSignal(od) && pluginPyQt3(pt))
            yyerror("Virtual signals aren't supported");

        setIsVirtual(od);
        setHasShadow(c_scope);

        vhd = sipMalloc(sizeof (virtHandlerDef));

        vhd->virthandlernr = -1;
        vhd->vhflags = 0;
        vhd->pysig = &od->pysig;
        vhd->cppsig = (cppsig != NULL ? cppsig : &od->pysig);
        vhd->virtcode = vcode;

        if (factory || xferback)
            setIsTransferVH(vhd);

        /*
         * Only add it to the module's virtual handlers if we are not in a
         * class template.
         */
        if (!currentIsTemplate)
        {
            vhd->module = mod;

            vhd->next = mod->virthandlers;
            mod->virthandlers = vhd;
        }
    }
    else
    {
        if (vcode != NULL)
            yyerror("%VirtualCatcherCode provided for non-virtual function");

        vhd = NULL;
    }

    od->cppname = name;
    od->pysig = *sig;
    od->cppsig = (cppsig != NULL ? cppsig : &od->pysig);
    od->exceptions = exceptions;
    od->methodcode = methodcode;
    od->virthandler = vhd;

    no_arg_parser = (findOptFlag(optflgs, "NoArgParser", bool_flag) != NULL);

    if (no_arg_parser)
    {
        if (methodcode == NULL)
            yyerror("%MethodCode must be supplied if /NoArgParser/ is specified");
    }

    if (findOptFlag(optflgs, "NoCopy", bool_flag) != NULL)
        setNoCopy(&od->pysig.result);

    od->common = findFunction(pt, mod, c_scope, mt_scope,
            getPythonName(optflgs, name), (methodcode != NULL), sig->nrArgs,
            no_arg_parser);

    if (docstring != NULL)
        appendCodeBlock(&od->common->docstring, docstring);

    od->api_range = getAPIRange(optflgs);

    if (od->api_range == NULL)
        setNotVersioned(od->common);

    if (findOptFlag(optflgs, "Numeric", bool_flag) != NULL)
        setIsNumeric(od->common);

    /* Methods that run in new threads must be virtual. */
    if (findOptFlag(optflgs, "NewThread", bool_flag) != NULL)
    {
        argDef *res;

        if (!isvirt)
            yyerror("/NewThread/ may only be specified for virtual functions");

        /*
         * This is an arbitary limitation to make the code generator slightly
         * easier - laziness on my part.
         */
        res = &od->cppsig->result;

        if (res->atype != void_type || res->nrderefs != 0)
            yyerror("/NewThread/ may only be specified for void functions");

        setIsNewThread(od);
    }

    getHooks(optflgs, &od->prehook, &od->posthook);

    if (getReleaseGIL(optflgs))
        setIsReleaseGIL(od);
    else if (getHoldGIL(optflgs))
        setIsHoldGIL(od);

    if (getDeprecated(optflgs))
        setIsDeprecated(od);

    if (!isPrivate(od) && !isSignal(od) && (od->common->slot == no_slot || od->common->slot == call_slot) && usesKeywordArgs(optflgs, &od->pysig))
    {
        setUseKeywordArgs(od);
        setUseKeywordArgsFunction(od->common);
    }

    /* See if we want to auto-generate a __len__() method. */
    if (findOptFlag(optflgs, "__len__", bool_flag) != NULL)
    {
        overDef *len;

        len = sipMalloc(sizeof (overDef));

        len->cppname = "__len__";
        len->overflags = SECT_IS_PUBLIC;
        len->pysig.result.atype = ssize_type;
        len->pysig.nrArgs = 0;
        len->cppsig = &len->pysig;

        len->common = findFunction(pt, mod, c_scope, mt_scope, len->cppname,
                TRUE, 0, FALSE);

        if ((len->methodcode = od->methodcode) == NULL)
        {
            char *buf = sipStrdup("            sipRes = (SIP_SSIZE_T)sipCpp->");
            codeBlock *code;

            append(&buf, od->cppname);
            append(&buf, "();\n");

            code = sipMalloc(sizeof (codeBlock));

            code->frag = buf;
            code->filename = "Auto-generated";
            code->linenr = 1;
            code->next = NULL;

            len->methodcode = code;
        }

        len->next = NULL;

        od->next = len;
    }
    else
    {
        od->next = NULL;
    }

    /* Append to the list. */
    for (odp = headp; *odp != NULL; odp = &(*odp)->next)
        ;

    *odp = od;
}


/*
 * Return the Python name based on the C/C++ name and any /PyName/ annotation.
 */
static const char *getPythonName(optFlags *optflgs, const char *cname)
{
    const char *pname;
    optFlag *of;

    if ((of = findOptFlag(optflgs, "PyName", name_flag)) != NULL)
        pname = of->fvalue.sval;
    else
        pname = cname;

    return pname;
}


/*
 * Cache a name in a module.  Entries in the cache are stored in order of
 * decreasing length.
 */
nameDef *cacheName(sipSpec *pt, const char *name)
{
    nameDef *nd, **ndp;
    size_t len;

    /* Allow callers to be lazy about checking if there is really a name. */
    if (name == NULL)
        return NULL;

    /* Skip entries that are too large. */
    ndp = &pt->namecache;
    len = strlen(name);

    while (*ndp != NULL && (*ndp)->len > len)
        ndp = &(*ndp)->next;

    /* Check entries that are the right length. */
    for (nd = *ndp; nd != NULL && nd->len == len; nd = nd->next)
        if (memcmp(nd->text, name, len) == 0)
            return nd;

    /* Create a new one. */
    nd = sipMalloc(sizeof (nameDef));

    nd->nameflags = 0;
    nd->text = name;
    nd->len = len;
    nd->next = *ndp;

    *ndp = nd;

    return nd;
}


/*
 * Find (or create) an overloaded function name.
 */
static memberDef *findFunction(sipSpec *pt, moduleDef *mod, classDef *c_scope,
        mappedTypeDef *mt_scope, const char *pname, int hwcode, int nrargs,
        int no_arg_parser)
{
    static struct slot_map {
        const char *name;   /* The slot name. */
        slotType type;      /* The corresponding type. */
        int needs_hwcode;   /* Set if handwritten code is required. */
        int nrargs;         /* Nr. of arguments. */
    } slot_table[] = {
        {"__str__", str_slot, TRUE, 0},
        {"__unicode__", unicode_slot, TRUE, 0},
        {"__int__", int_slot, FALSE, 0},
        {"__long__", long_slot, FALSE, 0},
        {"__float__", float_slot, FALSE, 0},
        {"__len__", len_slot, TRUE, 0},
        {"__contains__", contains_slot, TRUE, 1},
        {"__add__", add_slot, FALSE, 1},
        {"__sub__", sub_slot, FALSE, 1},
        {"__mul__", mul_slot, FALSE, 1},
        {"__div__", div_slot, FALSE, 1},
        {"__mod__", mod_slot, FALSE, 1},
        {"__floordiv__", floordiv_slot, TRUE, 1},
        {"__truediv__", truediv_slot, FALSE, 1},
        {"__and__", and_slot, FALSE, 1},
        {"__or__", or_slot, FALSE, 1},
        {"__xor__", xor_slot, FALSE, 1},
        {"__lshift__", lshift_slot, FALSE, 1},
        {"__rshift__", rshift_slot, FALSE, 1},
        {"__iadd__", iadd_slot, FALSE, 1},
        {"__isub__", isub_slot, FALSE, 1},
        {"__imul__", imul_slot, FALSE, 1},
        {"__idiv__", idiv_slot, FALSE, 1},
        {"__imod__", imod_slot, FALSE, 1},
        {"__ifloordiv__", ifloordiv_slot, TRUE, 1},
        {"__itruediv__", itruediv_slot, FALSE, 1},
        {"__iand__", iand_slot, FALSE, 1},
        {"__ior__", ior_slot, FALSE, 1},
        {"__ixor__", ixor_slot, FALSE, 1},
        {"__ilshift__", ilshift_slot, FALSE, 1},
        {"__irshift__", irshift_slot, FALSE, 1},
        {"__invert__", invert_slot, FALSE, 0},
        {"__call__", call_slot, FALSE, -1},
        {"__getitem__", getitem_slot, FALSE, 1},
        {"__setitem__", setitem_slot, TRUE, 2},
        {"__delitem__", delitem_slot, TRUE, 1},
        {"__lt__", lt_slot, FALSE, 1},
        {"__le__", le_slot, FALSE, 1},
        {"__eq__", eq_slot, FALSE, 1},
        {"__ne__", ne_slot, FALSE, 1},
        {"__gt__", gt_slot, FALSE, 1},
        {"__ge__", ge_slot, FALSE, 1},
        {"__cmp__", cmp_slot, FALSE, 1},
        {"__bool__", bool_slot, TRUE, 0},
        {"__nonzero__", bool_slot, TRUE, 0},
        {"__neg__", neg_slot, FALSE, 0},
        {"__pos__", pos_slot, FALSE, 0},
        {"__abs__", abs_slot, TRUE, 0},
        {"__repr__", repr_slot, TRUE, 0},
        {"__hash__", hash_slot, TRUE, 0},
        {"__index__", index_slot, TRUE, 0},
        {"__iter__", iter_slot, TRUE, 0},
        {"__next__", next_slot, TRUE, 0},
        {NULL}
    };

    memberDef *md, **flist;
    struct slot_map *sm;
    slotType st;

    /* Get the slot type. */
    st = no_slot;

    for (sm = slot_table; sm->name != NULL; ++sm)
        if (strcmp(sm->name, pname) == 0)
        {
            if (sm->needs_hwcode && !hwcode)
                yyerror("This Python slot requires %MethodCode");

            if (sm->nrargs >= 0)
            {
                if (mt_scope == NULL && c_scope == NULL)
                {
                    /* Global operators need one extra argument. */
                    if (sm -> nrargs + 1 != nrargs)
                        yyerror("Incorrect number of arguments to global operator");
                }
                else if (sm->nrargs != nrargs)
                    yyerror("Incorrect number of arguments to Python slot");
            }

            st = sm->type;

            break;
        }

    /* Check there is no name clash. */
    checkAttributes(pt, mod, c_scope, mt_scope, pname, TRUE);

    /* See if it already exists. */
    if (mt_scope != NULL)
        flist = &mt_scope->members;
    else if (c_scope != NULL)
        flist = &c_scope->members;
    else
        flist = &mod->othfuncs;

    for (md = *flist; md != NULL; md = md->next)
        if (strcmp(md->pyname->text, pname) == 0 && md->module == mod)
            break;

    if (md == NULL)
    {
        /* Create a new one. */
        md = sipMalloc(sizeof (memberDef));

        md->pyname = cacheName(pt, pname);
        md->memberflags = 0;
        md->slot = st;
        md->module = mod;
        md->next = *flist;

        *flist = md;

        if (inMainModule())
            setIsUsedName(md->pyname);

        if (no_arg_parser)
            setNoArgParser(md);
    }
    else if (noArgParser(md))
        yyerror("Another overload has already been defined that is annotated as /NoArgParser/");

    /* Global operators are a subset. */
    if (mt_scope == NULL && c_scope == NULL && st != no_slot && st != neg_slot && st != pos_slot && !isNumberSlot(md) && !isRichCompareSlot(md))
        yyerror("Global operators must be either numeric or comparison operators");

    return md;
}


/*
 * Search a set of flags for a particular one and check its type.
 */
static optFlag *findOptFlag(optFlags *flgs, char *name, flagType ft)
{
    int f;

    for (f = 0; f < flgs->nrFlags; ++f)
    {
        optFlag *of = &flgs->flags[f];

        if (strcmp(of->fname, name) == 0)
        {
            /* An optional name can look like a boolean or a name. */
            if (ft == opt_name_flag)
            {
                if (of->ftype == bool_flag)
                {
                    of->ftype = opt_name_flag;
                    of->fvalue.sval = NULL;
                }
                else if (of->ftype == name_flag)
                {
                    of->ftype = opt_name_flag;
                }
            }

            /* An optional integer can look like a boolean or an integer. */
            if (ft == opt_integer_flag)
            {
                if (of->ftype == bool_flag)
                {
                    of->ftype = opt_integer_flag;
                    of->fvalue.ival = -1;
                }
                else if (of->ftype == integer_flag)
                {
                    of->ftype = opt_integer_flag;
                }
            }

            if (ft != of->ftype)
                yyerror("Optional flag has a value of the wrong type");

            return of;
        }
    }

    return NULL;
}


/*
 * A name is going to be used as a Python attribute name within a Python scope
 * (ie. a Python dictionary), so check against what we already know is going in
 * the same scope in case there is a clash.
 */
static void checkAttributes(sipSpec *pt, moduleDef *mod, classDef *py_c_scope,
        mappedTypeDef *py_mt_scope, const char *attr, int isfunc)
{
    enumDef *ed;
    varDef *vd;
    classDef *cd;

    /* Check the enums. */

    for (ed = pt->enums; ed != NULL; ed = ed->next)
    {
        enumMemberDef *emd;

        if (ed->pyname == NULL)
            continue;

        if (py_c_scope != NULL)
        {
            if (ed->ecd != py_c_scope)
                continue;
        }
        else if (py_mt_scope != NULL)
        {
            if (ed->emtd != py_mt_scope)
                continue;
        }
        else if (ed->ecd != NULL || ed->emtd != NULL)
        {
            continue;
        }

        if (strcmp(ed->pyname->text, attr) == 0)
            yyerror("There is already an enum in scope with the same Python name");

        for (emd = ed->members; emd != NULL; emd = emd->next)
            if (strcmp(emd->pyname->text, attr) == 0)
                yyerror("There is already an enum member in scope with the same Python name");
    }

    /*
     * Only check the members if this attribute isn't a member because we
     * can handle members with the same name in the same scope.
     */
    if (!isfunc)
    {
        memberDef *md, *membs;
        overDef *overs;

        if (py_mt_scope != NULL)
        {
            membs = py_mt_scope->members;
            overs = py_mt_scope->overs;
        }
        else if (py_c_scope != NULL)
        {
            membs = py_c_scope->members;
            overs = py_c_scope->overs;
        }
        else
        {
            membs = mod->othfuncs;
            overs = mod->overs;
        }

        for (md = membs; md != NULL; md = md->next)
        {
            overDef *od;

            if (strcmp(md->pyname->text, attr) != 0)
                continue;

            /* Check for a conflict with all overloads. */
            for (od = overs; od != NULL; od = od->next)
            {
                if (od->common != md)
                    continue;

                yyerror("There is already a function in scope with the same Python name");
            }
        }
    }

    /* If the scope was a mapped type then that's all we have to check. */
    if (py_mt_scope != NULL)
        return;

    /* Check the variables. */
    for (vd = pt->vars; vd != NULL; vd = vd->next)
    {
        if (vd->ecd != py_c_scope)
            continue;

        if (strcmp(vd->pyname->text,attr) == 0)
            yyerror("There is already a variable in scope with the same Python name");
    }

    /* Check the classes. */
    for (cd = pt->classes; cd != NULL; cd = cd->next)
    {
        if (cd->ecd != py_c_scope || cd->pyname == NULL)
            continue;

        if (strcmp(cd->pyname->text, attr) == 0 && !isExternal(cd))
            yyerror("There is already a class or namespace in scope with the same Python name");
    }

    /* Check the exceptions. */
    if (py_c_scope == NULL)
    {
        exceptionDef *xd;

        for (xd = pt->exceptions; xd != NULL; xd = xd->next)
            if (xd->pyname != NULL && strcmp(xd->pyname, attr) == 0)
                yyerror("There is already an exception with the same Python name");
    }
}


/*
 * Append a code block to a list of them.  Append is needed to give the
 * specifier easy control over the order of the documentation.
 */
void appendCodeBlock(codeBlock **headp, codeBlock *new)
{
    while (*headp != NULL)
        headp = &(*headp)->next;

    *headp = new;
}


/*
 * Handle the end of a fully parsed a file.
 */
static void handleEOF()
{
    /*
     * Check that the number of nested if's is the same as when we started
     * the file.
     */

    if (skipStackPtr > currentContext.ifdepth)
        fatal("Too many %%If statements in %s\n", previousFile);

    if (skipStackPtr < currentContext.ifdepth)
        fatal("Too many %%End statements in %s\n", previousFile);
}


/*
 * Handle the end of a fully parsed a module.
 */
static void handleEOM()
{
    moduleDef *from;

    /* Check it has been named. */
    if (currentModule->name == NULL)
        fatal("No %%Module has been specified for module defined in %s\n",
                previousFile);

    from = currentContext.prevmod;

    if (from != NULL && from->encoding == no_type)
        from->encoding = currentModule->encoding;

    /* The previous module is now current. */
    currentModule = from;
}


/*
 * Find an existing qualifier.
 */
static qualDef *findQualifier(const char *name)
{
    moduleDef *mod;

    for (mod = currentSpec->modules; mod != NULL; mod = mod->next)
    {
        qualDef *qd;

        for (qd = mod->qualifiers; qd != NULL; qd = qd->next)
            if (strcmp(qd->name, name) == 0)
                return qd;
    }

    return NULL;
}


/*
 * Find an existing API.
 */
apiVersionRangeDef *findAPI(sipSpec *pt, const char *name)
{
    moduleDef *mod;

    for (mod = pt->modules; mod != NULL; mod = mod->next)
    {
        apiVersionRangeDef *avd;

        for (avd = mod->api_versions; avd != NULL; avd = avd->next)
            if (strcmp(avd->api_name->text, name) == 0)
                return avd;
    }

    return NULL;
}


/*
 * Return a copy of a scoped name.
 */
scopedNameDef *copyScopedName(scopedNameDef *snd)
{
    scopedNameDef *head;

    head = NULL;

    while (snd != NULL)
    {
        appendScopedName(&head,text2scopePart(snd -> name));
        snd = snd -> next;
    }

    return head;
}


/*
 * Append a name to a list of scopes.
 */
void appendScopedName(scopedNameDef **headp,scopedNameDef *newsnd)
{
    while (*headp != NULL)
        headp = &(*headp) -> next;

    *headp = newsnd;
}


/*
 * Free a scoped name - but not the text itself.
 */
void freeScopedName(scopedNameDef *snd)
{
    while (snd != NULL)
    {
        scopedNameDef *next = snd -> next;

        free(snd);

        snd = next;
    }
}


/*
 * Convert a text string to a scope part structure.
 */
static scopedNameDef *text2scopePart(char *text)
{
    scopedNameDef *snd;

    snd = sipMalloc(sizeof (scopedNameDef));

    snd->name = text;
    snd->next = NULL;

    return snd;
}


/*
 * Convert a text string to a fully scoped name.
 */
static scopedNameDef *text2scopedName(ifaceFileDef *scope, char *text)
{
    return scopeScopedName(scope, text2scopePart(text));
}


/*
 * Prepend any current scope to a scoped name.
 */
static scopedNameDef *scopeScopedName(ifaceFileDef *scope, scopedNameDef *name)
{
    scopedNameDef *snd;

    snd = (scope != NULL ? copyScopedName(scope->fqcname) : NULL);

    appendScopedName(&snd, name);

    return snd;
}


/*
 * Return a pointer to the tail part of a scoped name.
 */
char *scopedNameTail(scopedNameDef *snd)
{
    if (snd == NULL)
        return NULL;

    while (snd -> next != NULL)
        snd = snd -> next;

    return snd -> name;
}


/*
 * Push the given scope onto the scope stack.
 */
static void pushScope(classDef *scope)
{
    if (currentScopeIdx >= MAX_NESTED_SCOPE)
        fatal("Internal error: increase the value of MAX_NESTED_SCOPE\n");

    scopeStack[currentScopeIdx] = scope;
    sectFlagsStack[currentScopeIdx] = sectionFlags;

    ++currentScopeIdx;
}


/*
 * Pop the scope stack.
 */
static void popScope(void)
{
    if (currentScopeIdx > 0)
        sectionFlags = sectFlagsStack[--currentScopeIdx];
}


/*
 * Return non-zero if the current input should be parsed rather than be
 * skipped.
 */
static int notSkipping()
{
    return (skipStackPtr == 0 ? TRUE : skipStack[skipStackPtr - 1]);
}


/*
 * Return the value of an expression involving a time period.
 */
static int timePeriod(char *lname,char *uname)
{
    int this, line;
    qualDef *qd, *lower, *upper;
    moduleDef *mod;

    if (lname == NULL)
        lower = NULL;
    else if ((lower = findQualifier(lname)) == NULL || lower -> qtype != time_qualifier)
        yyerror("Lower bound is not a time version");

    if (uname == NULL)
        upper = NULL;
    else if ((upper = findQualifier(uname)) == NULL || upper -> qtype != time_qualifier)
        yyerror("Upper bound is not a time version");

    /* Sanity checks on the bounds. */

    if (lower == NULL && upper == NULL)
        yyerror("Lower and upper bounds cannot both be omitted");

    if (lower != NULL && upper != NULL)
    {
        if (lower -> module != upper -> module || lower -> line != upper -> line)
            yyerror("Lower and upper bounds are from different timelines");

        if (lower == upper)
            yyerror("Lower and upper bounds must be different");

        if (lower -> order > upper -> order)
            yyerror("Later version specified as lower bound");
    }

    /* Go through each slot in the relevant timeline. */

    if (lower != NULL)
    {
        mod = lower -> module;
        line = lower -> line;
    }
    else
    {
        mod = upper -> module;
        line = upper -> line;
    }

    this = FALSE;

    for (qd = mod -> qualifiers; qd != NULL; qd = qd -> next)
    {
        if (qd -> qtype != time_qualifier || qd -> line != line)
            continue;

        if (lower != NULL && qd -> order < lower -> order)
            continue;

        if (upper != NULL && qd -> order >= upper -> order)
            continue;

        /*
         * This is within the required range so if it is also needed
         * then the expression is true.
         */

        if (isNeeded(qd))
        {
            this = TRUE;
            break;
        }
    }

    return this;
}


/*
 * Return the value of an expression involving a single platform or feature.
 */
static int platOrFeature(char *name,int optnot)
{
    int this;
    qualDef *qd;

    if ((qd = findQualifier(name)) == NULL || qd -> qtype == time_qualifier)
        yyerror("No such platform or feature");

    /* Assume this sub-expression is false. */

    this = FALSE;

    if (qd -> qtype == feature_qualifier)
    {
        if (!excludedFeature(excludedQualifiers,qd))
            this = TRUE;
    }
    else if (isNeeded(qd))
        this = TRUE;

    if (optnot)
        this = !this;

    return this;
}


/*
 * Return TRUE if the given qualifier is excluded.
 */
int excludedFeature(stringList *xsl,qualDef *qd)
{
    while (xsl != NULL)
    {
        if (strcmp(qd -> name,xsl -> s) == 0)
            return TRUE;

        xsl = xsl -> next;
    }

    return FALSE;
}


/*
 * Return TRUE if the given qualifier is needed.
 */
static int isNeeded(qualDef *qd)
{
    stringList *sl;

    for (sl = neededQualifiers; sl != NULL; sl = sl -> next)
        if (strcmp(qd -> name,sl -> s) == 0)
            return TRUE;

    return FALSE;
}


/*
 * Return the current scope.  currentScope() is only valid if notSkipping()
 * returns non-zero.
 */
static classDef *currentScope(void)
{
    return (currentScopeIdx > 0 ? scopeStack[currentScopeIdx - 1] : NULL);
}


/*
 * Create a new qualifier.
 */
static void newQualifier(moduleDef *mod, int line, int order, char *name,
        qualType qt)
{
    qualDef *qd;

    /* Check it doesn't already exist. */

    if (findQualifier(name) != NULL)
        yyerror("Version is already defined");

    qd = sipMalloc(sizeof (qualDef));
    qd->name = name;
    qd->qtype = qt;
    qd->module = mod;
    qd->line = line;
    qd->order = order;
    qd->next = mod -> qualifiers;
    mod->qualifiers = qd;
}


/*
 * Create a new imported module.
 */
static void newImport(char *filename)
{
    moduleDef *from, *mod;
    moduleListDef *mld;

    /* Create a new module if it has not already been defined. */
    for (mod = currentSpec->modules; mod != NULL; mod = mod->next)
        if (strcmp(mod->file, filename) == 0)
            break;

    from = currentModule;

    if (mod == NULL)
    {
        newModule(NULL, filename);
        mod = currentModule;
    }
    else if (from->encoding == no_type)
    {
        /* Import any defaults from the already parsed module. */
        from->encoding = mod->encoding;
    }

    /* Add the new import unless it has already been imported. */
    for (mld = from->imports; mld != NULL; mld = mld->next)
        if (mld->module == mod)
            return;

    mld = sipMalloc(sizeof (moduleListDef));
    mld->module = mod;
    mld->next = from->imports;

    from->imports = mld;
}


/*
 * Set up pointers to hook names.
 */
static void getHooks(optFlags *optflgs,char **pre,char **post)
{
    optFlag *of;

    if ((of = findOptFlag(optflgs,"PreHook",name_flag)) != NULL)
        *pre = of -> fvalue.sval;
    else
        *pre = NULL;

    if ((of = findOptFlag(optflgs,"PostHook",name_flag)) != NULL)
        *post = of -> fvalue.sval;
    else
        *post = NULL;
}


/*
 * Get the /Transfer/ option flag.
 */
static int getTransfer(optFlags *optflgs)
{
    return (findOptFlag(optflgs, "Transfer", bool_flag) != NULL);
}


/*
 * Get the /ReleaseGIL/ option flag.
 */
static int getReleaseGIL(optFlags *optflgs)
{
    return (findOptFlag(optflgs, "ReleaseGIL", bool_flag) != NULL);
}


/*
 * Get the /HoldGIL/ option flag.
 */
static int getHoldGIL(optFlags *optflgs)
{
    return (findOptFlag(optflgs, "HoldGIL", bool_flag) != NULL);
}


/*
 * Get the /Deprecated/ option flag.
 */
static int getDeprecated(optFlags *optflgs)
{
    return (findOptFlag(optflgs, "Deprecated", bool_flag) != NULL);
}


/*
 * Get the /AllowNone/ option flag.
 */
static int getAllowNone(optFlags *optflgs)
{
    return (findOptFlag(optflgs, "AllowNone", bool_flag) != NULL);
}


/*
 * Get the /DocType/ option flag.
 */
static const char *getDocType(optFlags *optflgs)
{
    optFlag *of = findOptFlag(optflgs, "DocType", string_flag);

    if (of == NULL)
        return NULL;

    return of->fvalue.sval;
}


/*
 * Get the /DocValue/ option flag.
 */
static const char *getDocValue(optFlags *optflgs)
{
    optFlag *of = findOptFlag(optflgs, "DocValue", string_flag);

    if (of == NULL)
        return NULL;

    return of->fvalue.sval;
}


/*
 * Return TRUE if the PyQt3 plugin was specified.
 */
int pluginPyQt3(sipSpec *pt)
{
    return stringFind(pt->plugins, "PyQt3");
}


/*
 * Return TRUE if the PyQt4 plugin was specified.
 */
int pluginPyQt4(sipSpec *pt)
{
    return stringFind(pt->plugins, "PyQt4");
}


/*
 * Return TRUE if a list of strings contains a given entry.
 */
static int stringFind(stringList *sl, const char *s)
{
    while (sl != NULL)
    {
        if (strcmp(sl->s, s) == 0)
            return TRUE;

        sl = sl->next;
    }

    return FALSE;
}


/*
 * Set the name of a module.
 */
static void setModuleName(sipSpec *pt, moduleDef *mod, const char *fullname)
{
    mod->fullname = cacheName(pt, fullname);

    if (inMainModule())
        setIsUsedName(mod->fullname);

    if ((mod->name = strrchr(fullname, '.')) != NULL)
        mod->name++;
    else
        mod->name = fullname;
}


/*
 * Define a new class and set its name.
 */
static void defineClass(scopedNameDef *snd, classList *supers, optFlags *of)
{
    classDef *cd, *c_scope = currentScope();

    cd = newClass(currentSpec, class_iface, getAPIRange(of),
            scopeScopedName((c_scope != NULL ? c_scope->iff : NULL), snd));
    cd->supers = supers;

    pushScope(cd);
}


/*
 * Complete the definition of a class.
 */
static classDef *completeClass(scopedNameDef *snd, optFlags *of, int has_def)
{
    classDef *cd = currentScope();

    /* See if the class was defined or just declared. */
    if (has_def)
    {
        if (snd->next != NULL)
            yyerror("A scoped name cannot be given in a class/struct definition");

    }
    else if (cd->supers != NULL)
        yyerror("Class/struct has super-classes but no definition");
    else
        setIsOpaque(cd);

    finishClass(currentSpec, currentModule, cd, of);
    popScope();

    /*
     * Check that external classes have only been declared at the global scope.
     */
    if (isExternal(cd) && currentScope() != NULL)
        yyerror("External classes/structs can only be declared in the global scope");

    return cd;
}


/*
 * Add a variable to the list so that the list remains sorted.
 */
static void addVariable(sipSpec *pt, varDef *vd)
{
    varDef **at = &pt->vars;

    while (*at != NULL)
    {
        if (strcmp(vd->pyname->text, (*at)->pyname->text) < 0)
            break;

        at = &(*at)->next;
    }

    vd->next = *at;
    *at = vd;
}


/*
 * Update a type according to optional flags.
 */
static void applyTypeFlags(moduleDef *mod, argDef *ad, optFlags *flags)
{
    ad->doctype = getDocType(flags);

    if (ad->atype == string_type && !isArray(ad) && !isReference(ad))
    {
        optFlag *of;

        if ((of = findOptFlag(flags, "Encoding", string_flag)) == NULL)
        {
            if (mod->encoding != no_type)
                ad->atype = mod->encoding;
            else
                ad->atype = string_type;
        }
        else if ((ad->atype = convertEncoding(of->fvalue.sval)) == no_type)
            yyerror("The value of the /Encoding/ annotation must be one of \"ASCII\", \"Latin-1\", \"UTF-8\" or \"None\"");
    }
}


/*
 * Return the argument type for a string with the given encoding or no_type if
 * the encoding was invalid.
 */
static argType convertEncoding(const char *encoding)
{
    if (strcmp(encoding, "ASCII") == 0)
        return ascii_string_type;

    if (strcmp(encoding, "Latin-1") == 0)
        return latin1_string_type;

    if (strcmp(encoding, "UTF-8") == 0)
        return utf8_string_type;

    if (strcmp(encoding, "None") == 0)
        return string_type;

    return no_type;
}


/*
 * Get the /API/ option flag.
 */
static apiVersionRangeDef *getAPIRange(optFlags *optflgs)
{
    optFlag *of;

    if ((of = findOptFlag(optflgs, "API", api_range_flag)) == NULL)
        return NULL;

    return of->fvalue.aval;
}


/*
 * Return the API range structure and version number corresponding to the
 * given API range.
 */
static apiVersionRangeDef *convertAPIRange(moduleDef *mod, nameDef *name,
        int from, int to)
{
    int index;
    apiVersionRangeDef *avd, **avdp;

    /* Handle the trivial case. */
    if (from == 0 && to == 0)
        return NULL;

    for (index = 0, avdp = &mod->api_ranges; (*avdp) != NULL; avdp = &(*avdp)->next, ++index)
    {
        avd = *avdp;

        if (avd->api_name == name && avd->from == from && avd->to == to)
            return avd;
    }

    /* The new one must be appended so that version numbers remain valid. */
    avd = sipMalloc(sizeof (apiVersionRangeDef));

    avd->api_name = name;
    avd->from = from;
    avd->to = to;
    avd->index = index;

    avd->next = NULL;
    *avdp = avd;

    return avd;
}


/*
 * Return TRUE if a signature with annotations uses keyword arguments.
 */
static int usesKeywordArgs(optFlags *optflgs, signatureDef *sd)
{
    int kwd_args_anno, no_kwd_args_anno;

    kwd_args_anno = (findOptFlag(optflgs, "KeywordArgs", bool_flag) != NULL);
    no_kwd_args_anno = (findOptFlag(optflgs, "NoKeywordArgs", bool_flag) != NULL);

    /*
     * An ellipsis cannot be used with keyword arguments.  Only complain if it
     * has been explicitly requested.
     */
    if (kwd_args_anno && sd->nrArgs > 0 && sd->args[sd->nrArgs - 1].atype == ellipsis_type)
        yyerror("/KeywordArgs/ cannot be specified for calls with a variable number of arguments");

    if ((defaultKwdArgs || kwd_args_anno) && !no_kwd_args_anno)
    {
        int a, is_name = FALSE;

        /*
         * Mark argument names as being used and check there is at least one.
         */
        for (a = 0; a < sd->nrArgs; ++a)
        {
            nameDef *nd = sd->args[a].name;

            if (sd->args[a].name != NULL)
            {
                setIsUsedName(nd);
                is_name = TRUE;
            }
        }

        return is_name;
    }

    return FALSE;
}


/*
 * Extract the version of a string value optionally associated with a
 * particular feature.
 */
static char *convertFeaturedString(char *fs)
{
    while (fs != NULL)
    {
        char *next, *value;

        /* Individual values are ';' separated. */
        if ((next = strchr(fs, ';')) != NULL)
            *next++ = '\0';

        /* Features and values are ':' separated. */
        if ((value = strchr(fs, ':')) == NULL)
        {
            /* This is an unconditional value so just return it. */
            return strip(fs);
        }

        *value++ = '\0';

        if (isEnabledFeature(strip(fs)))
            return strip(value);

        fs = next;
    }

    /* No value was enabled. */
    return NULL;
}


/*
 * Return the stripped version of a string.
 */
static char *strip(char *s)
{
    while (*s == ' ')
        ++s;

    if (*s != '\0')
    {
        char *cp = &s[strlen(s) - 1];

        while (*cp == ' ')
            *cp-- = '\0';
    }

    return s;
}


/*
 * Return TRUE if the given feature is enabled.
 */
static int isEnabledFeature(const char *name)
{
    qualDef *qd;

    if ((qd = findQualifier(name)) == NULL || qd->qtype != feature_qualifier)
        yyerror("No such feature");

    return !excludedFeature(excludedQualifiers, qd);
}

