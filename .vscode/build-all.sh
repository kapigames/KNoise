clear

echo Preparing compile...
rmdir --ignore-fail-on-non-empty -p bin

./.vscode/build-linux64.sh
./.vscode/build-windows64.sh