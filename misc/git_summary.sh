#!/bin/bash

cd src/
find . -type d -name '.git' | while read dir ; do sh -c "cd $dir/../ && echo \"\n\033[1;36m----> ${dir//\.git/}\033[0m\" && git --no-pager branch && git status -s" ; done
