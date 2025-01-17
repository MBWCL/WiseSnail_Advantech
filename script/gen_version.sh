#/bin/sh

versiondef=$1
versionh=$2

function writeverion() {
	echo "#/bin/sh" > $versiondef
	echo "major=$1" >> $versiondef
	echo "minor=$2" >> $versiondef
	echo "patch=$3" >> $versiondef
	echo "alpha=$4" >> $versiondef
	echo "model=$5" >> $versiondef

}

tag=`git describe --abbrev=0 --tags`
revision=`git rev-parse HEAD | cut -c1-8`

if [ -f "$versiondef" ];then
	source $versiondef
else
	exit
fi

version=`printf ".%s%s" $revision $alpha 2>/dev/null`
release=`printf ".%d.%d.%02d" $major $minor $patch`

writeverion "$major" "$minor" "$patch" "$alpha" "$model"

echo "#define SNAIL_MODEL \"SNAIL.$model\"" > $versionh
echo "#define SNAIL_RELEASE_VERSION SNAIL_MODEL\"$release\"" >> $versionh
echo "#define SNAIL_FACTORY_VERSION SNAIL_RELEASE_VERSION\"$version\"" >> $versionh
