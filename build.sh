#!/bin/bash

# emscripten binaries need to be in your $PATH, run "source ./emsdk_env.sh" in the emscripten installation directory to do that

emcc jh.c hash.c -O3 -o dist/jh.js -s MODULARIZE=1 -s 'EXPORT_NAME="createJHModule"' -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -s EXPORTED_FUNCTIONS="['_malloc', '_free']" -s WASM=1

if [ $? == 0 ]; then
  cat dist/jh.js wrapper/wrapper.js > dist/jh-wasm.js ;
  rm dist/jh.js
fi

