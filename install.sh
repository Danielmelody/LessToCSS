#! /bin/bash
if env | grep -q ^LESS_TO_CSS=
then
    echo 'export LESS_TO_CSS='$(pwd) >> ~/.bash_profile
    echo 'export PATH=$LESS_TO_CSS/bin:$PATH' >> ~/.bash_profile
else
    echo 'LessToCSS has already installed.'
fi
