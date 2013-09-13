#!/bin/bash
echo "--- Pulling from repo"
git pull
echo "--- Copying files to public_html"
rm -rf ~/public_html
cp -R cs184/site/_site ~/public_html

echo "--- Changing public_html permissions" 
chmod -R 0755 ~/public_html

echo "--- Done"
