emcc --pre-js tools.js -o woni.html main.cpp 
mkdir exp
mv woni.html exp
mv woni.js exp
mv woni.wasm exp
cp tools.js exp
cp test.txt exp
sudo rm -r /srv/http/exp
sudo mv exp /srv/http