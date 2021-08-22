clear

echo Preparing compile...
rmdir --ignore-fail-on-non-empty -p bin

./.vscode/build-linux.sh
./.vscode/build-windows64.sh