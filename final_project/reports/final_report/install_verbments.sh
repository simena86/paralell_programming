#!/bin/bash

# install verbments with dependencies
echo "Installing Verbments"

mkdir -p ~/texmf/tex/latex/verbments
cd ~/texmf/tex/latex/verbments
wget http://www.math.washington.edu/tex-archive/macros/latex/contrib/verbments/verbments.sty
apt-get install python-pygments
texhash ~/texmf

echo "Verbments installed succesfully"

