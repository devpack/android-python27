# this script adds additional python2.7.2 modules that are needed for running kalite on Android. 
cur=`pwd`
root="$(dirname "$cur")"

# add unittest to python_extras_27
addon_1_target=$root"/apk/res/raw/python_extras_27.zip"
addon_1_destination=$root"/apk/res/raw"
unzip $addon_1_target -d $cur
cp -r unittest python
zip -r python_extras_27.zip python
rm -rf python
mv python_extras_27.zip $addon_1_destination

# add other addons below ...