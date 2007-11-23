#!/bin/sh

rm -f WeiCommonLib.ncb
rm -f WeiCommonLib.suo

rm -rf `find . -name "Debug" -or -name "Release" -or -name "debug" -or -name "release"`
rm -rf `find . -name "*.user"`
