#include <QFile>
#include <QLibraryInfo>
#include <QTextStream>

int main(int, char **)
{
    QFile outf("qtdirs.out");

    if (!outf.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
        return 1;

    QTextStream out(&outf);

    out << QLibraryInfo::location(QLibraryInfo::PrefixPath) << '\n';
    out << QLibraryInfo::location(QLibraryInfo::HeadersPath) << '\n';
    out << QLibraryInfo::location(QLibraryInfo::LibrariesPath) << '\n';
    out << QLibraryInfo::location(QLibraryInfo::BinariesPath) << '\n';
    out << QLibraryInfo::location(QLibraryInfo::DataPath) << '\n';
    out << QLibraryInfo::location(QLibraryInfo::PluginsPath) << '\n';

    out << QT_VERSION << '\n';
    out << QT_EDITION << '\n';

    out << QLibraryInfo::licensee() << '\n';

#if defined(QT_SHARED) || defined(QT_DLL)
    out << "shared\n";
#else
    out << "\n";
#endif

    // Determine which features should be disabled.

#if defined(QT_NO_ACCESSIBILITY)
    out << "PyQt_Accessibility\n";
#endif

#if defined(QT_NO_BIGCODECS)
    out << "PyQt_BigCodecs\n";
#endif

#if defined(QT_NO_BUTTONGROUP)
    out << "PyQt_ButtonGroup\n";
#endif

#if defined(QT_NO_CLIPBOARD)
    out << "PyQt_Clipboard\n";
#endif

#if defined(QT_NO_CODECS)
    out << "PyQt_Codecs\n";
#endif

#if defined(QT_NO_COLORDIALOG)
    out << "PyQt_ColorDialog\n";
#endif

#if defined(QT_NO_COLORNAMES)
    out << "PyQt_ColorNames\n";
#endif

#if defined(QT_NO_CONTEXTMENU)
    out << "PyQt_ContextMenu\n";
#endif

#if defined(QT_NO_CURSOR)
    out << "PyQt_Cursor\n";
#endif

#if defined(QT_NO_DIAL)
    out << "PyQt_Dial\n";
#endif

#if defined(QT_NO_DIRECTPAINTER)
    out << "PyQt_DirectPainter\n";
#endif

#if defined(QT_NO_DIRMODEL)
    out << "PyQt_DirModel\n";
#endif

#if defined(QT_NO_DOCKWIDGET)
    out << "PyQt_DockWidget\n";
#endif

#if defined(QT_NO_DOM)
    out << "PyQt_DOMClasses\n";
#endif

#if defined(QT_NO_DRAGANDDROP)
    out << "PyQt_DragAndDrop\n";
#endif

#if defined(QT_NO_ERRORMESSAGE)
    out << "PyQt_ErrorMessage\n";
#endif

#if defined(QT_NO_FILEDIALOG)
    out << "PyQt_FileDialog\n";
#endif

#if defined(QT_NO_FONTDIALOG)
    out << "PyQt_FontDialog\n";
#endif

#if defined(QT_NO_IMAGEFORMATPLUGIN)
    out << "PyQt_ImageFormatPlugin\n";
#endif

#if defined(QT_NO_IMAGEFORMAT_PPM)
    out << "PyQt_ImageFormat_PPM\n";
#endif

#if defined(QT_NO_IMAGE_HEURISTIC_MASK)
    out << "PyQt_Image_Heuristic_Mask\n";
#endif

#if defined(QT_NO_INPUTDIALOG)
    out << "PyQt_InputDialog\n";
#endif

#if defined(QT_NO_IMAGE_TEXT)
    out << "PyQt_Image_Text\n";
#endif

#if defined(QT_NO_ITEMVIEWS)
    out << "PyQt_ItemViews\n";
#endif

#if defined(QT_NO_LCDNUMBER)
    out << "PyQt_LCDNumber\n";
#endif

#if defined(QT_NO_LINEEDITMENU)
    out << "PyQt_LineEditMenu\n";
#endif

#if defined(QT_NO_LISTVIEW)
    out << "PyQt_ListView\n";
#endif

#if defined(QT_NO_LISTWIDGET)
    out << "PyQt_ListWidget\n";
#endif

#if defined(QT_NO_MAINWINDOW)
    out << "PyQt_MainWindow\n";
#endif

#if defined(QT_NO_MENU)
    out << "PyQt_Menu\n";
#endif

#if defined(QT_NO_MENUBAR)
    out << "PyQt_MenuBar\n";
#endif

#if defined(QT_NO_MESSAGEBOX)
    out << "PyQt_MessageBox\n";
#endif

#if defined(QT_NO_NETWORKPROXY)
    out << "PyQt_NetworkProxy\n";
#endif

#if defined(QT_NO_OPENSSL)
    out << "PyQt_OpenSSL\n";
#endif

#if defined(QT_NO_PICTURE)
    out << "PyQt_Picture\n";
#endif

#if defined(QT_NO_PRINTDIALOG)
    out << "PyQt_PrintDialog\n";
#endif

#if defined(QT_NO_PRINTPREVIEWDIALOG)
    out << "PyQt_PrintPreviewDialog\n";
#endif

#if defined(QT_NO_PRINTPREVIEWWIDGET)
    out << "PyQt_PrintPreviewWidget\n";
#endif

#if defined(QT_NO_PRINTER)
    out << "PyQt_Printer\n";
#endif

#if defined(QT_NO_PROGRESSDIALOG)
    out << "PyQt_ProgressDialog\n";
#endif

#if defined(QT_NO_PROXYMODEL)
    out << "PyQt_ProxyModel\n";
#endif

#if defined(QT_NO_RUBBERBAND)
    out << "PyQt_RubberBand\n";
#endif

#if defined(QT_NO_PROCESS)
    out << "PyQt_Process\n";
#endif

#if defined(QT_NO_QWS_ALPHA_CURSOR)
    out << "PyQt_QWS_Alpha_Cursor\n";
#endif

#if defined(QT_NO_QWS_CURSOR)
    out << "PyQt_QWS_Cursor\n";
#endif

#if defined(QT_NO_QWS_DECORATION_WINDOWS)
    out << "PyQt_QWS_Decoration_Windows\n";
#endif

#if defined(QT_NO_QWS_MOUSE)
    out << "PyQt_QWS_Mouse\n";
#endif

#if defined(QT_NO_QWS_MOUSE_AUTO)
    out << "PyQt_QWS_Mouse_Auto\n";
#endif

#if defined(QT_NO_QWS_MOUSE_MANUAL)
    out << "PyQt_QWS_Mouse_Manual\n";
#endif

#if defined(QT_NO_RUBBERBAND)
    out << "PyQt_RubberBand\n";
#endif

#if defined(QT_NO_SCROLLBAR)
    out << "PyQt_ScrollBar\n";
#endif

#if defined(QT_NO_SESSIONMANAGER)
    out << "PyQt_SessionManager\n";
#endif

#if defined(QT_NO_SIZEGRIP)
    out << "PyQt_SizeGrip\n";
#endif

#if defined(QT_NO_SOCKS5)
    out << "PyQt_Socks5\n";
#endif

#if defined(QT_NO_SORTFILTERPROXYMODEL)
    out << "PyQt_SortFilterProxyModel\n";
#endif

#if defined(QT_NO_SPLASHSCREEN)
    out << "PyQt_SplashScreen\n";
#endif

#if defined(QT_NO_SPLITTER)
    out << "PyQt_Splitter\n";
#endif

#if defined(QT_NO_STANDARDITEMMODEL)
    out << "PyQt_StandardItemModel\n";
#endif

#if defined(QT_NO_STATUSBAR)
    out << "PyQt_StatusBar\n";
#endif

#if defined(QT_NO_STATUSTIP)
    out << "PyQt_StatusTip\n";
#endif

#if defined(QT_NO_STRINGLISTMODEL)
    out << "PyQt_StringListModel\n";
#endif

#if defined(QT_NO_STYLE_CDE)
    out << "PyQt_Style_CDE\n";
#endif

#if defined(QT_NO_STYLE_MOTIF)
    out << "PyQt_Style_Motif\n";
#endif

#if defined(QT_NO_STYLE_PLASTIQUE)
    out << "PyQt_Style_Plastique\n";
#endif

#if defined(QT_NO_STYLE_WINDOWSXP)
    out << "PyQt_Style_WindowsXP\n";
#endif

#if defined(QT_NO_SYNTAXHIGHLIGHTER)
    out << "PyQt_SyntaxHighlighter\n";
#endif

#if defined(QT_NO_SYSTEMTRAYICON)
    out << "PyQt_SystemTrayIcon\n";
#endif

#if defined(QT_NO_TABBAR)
    out << "PyQt_TabBar\n";
#endif

#if defined(QT_NO_TABDIALOG)
    out << "PyQt_TabDialog\n";
#endif

#if defined(QT_NO_TABWIDGET)
    out << "PyQt_TabWidget\n";
#endif

#if defined(QT_NO_TABLEVIEW)
    out << "PyQt_TableView\n";
#endif

#if defined(QT_NO_TEXTEDITMENU)
    out << "PyQt_TextEditMenu\n";
#endif

#if defined(QT_NO_THREAD)
    out << "PyQt_Thread\n";
#endif

#if defined(QT_NO_TOOLBAR)
    out << "PyQt_ToolBar\n";
#endif

#if defined(QT_NO_TOOLBOX)
    out << "PyQt_ToolBox\n";
#endif

#if defined(QT_NO_TOOLBUTTON)
    out << "PyQt_ToolButton\n";
#endif

#if defined(QT_NO_TOOLTIP)
    out << "PyQt_ToolTip\n";
#endif

#if defined(QT_NO_TRANSLATION)
    out << "PyQt_Translator\n";
#endif

#if defined(QT_NO_WHATSTHIS)
    out << "PyQt_WhatsThis\n";
#endif

#if defined(QT_NO_WHEELEVENT)
    out << "PyQt_WheelEvent\n";
#endif

#if defined(QT_NO_WORKSPACE)
    out << "PyQt_Workspace\n";
#endif

#if !defined(QT3_SUPPORT) || QT_VERSION >= 0x040200
    out << "PyQt_NoPrintRangeBug\n";
#endif

#if defined(QT_OPENGL_ES)
    out << "PyQt_NoOpenGLES\n";
#endif

    if (sizeof (qreal) != sizeof (double))
        out << "PyQt_qreal_double\n";

    return 0;
}
