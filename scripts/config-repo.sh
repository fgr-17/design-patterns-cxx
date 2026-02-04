#!/bin/bash

# run this script from inside the folder:
# cd scripts
# git config commit.template $PWD/../.gitmessage
cp pre-commit $PWD/../.git/hooks/pre-commit
chmod +x $PWD/../.git/hooks/pre-commit
