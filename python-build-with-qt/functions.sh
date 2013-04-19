info() { 
    echo "+ $@" >&2
}

warning() {
    echo "! $@" >&2
}

error() {
    echo "* $@" >&2
    exit 1
}

npath() {
    python -c "import sys, os; print os.path.normpath(os.path.abspath(os.path.join(*sys.argv[1:])))" $@
}

set_downloader() {
    downloader=""
    [ "$downloader" == "" ] && which curl >&/dev/null && downloader="curl"
    [ "$downloader" == "" ] && which wget >&/dev/null && downloader="wget"
    case $downloader in
        curl)
            function downloader { curl -LO "$1"; }
            ;;
        wget)
            function downloader { wget "$1"; }
            ;;
        *)
            error "no downloader found (either curl or wget)"
            ;;
    esac
}

readconfig() {
    local x
    for x in $@
    do
        [ -f "$x" ] && { info "loading config from $x"; . "$x" ; }
    done
}
