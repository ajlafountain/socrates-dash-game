#/bin/bash

PROJECT_NAME=$(basename $PWD)

[ -f windows_release.zip ] && rm windows_release.zip
[ -d windows_release_tmp ] && rm -r windows_release_tmp
[ -d windows_release_tmp/bin ] && rm -r windows_release_tmp/bin
mkdir windows_release_tmp
mkdir windows_release_tmp/bin
cp build_windows/*".dll" windows_release_tmp/bin
cp build_windows/*".exe" windows_release_tmp/bin
cp -r assets windows_release_tmp/assets
cat << EOF > windows_release_tmp/app_launcher.bat
start bin/$PROJECT_NAME.exe
exit
EOF
mv windows_release_tmp ${PROJECT_NAME}
zip -rm ${PROJECT_NAME}.zip ${PROJECT_NAME}

