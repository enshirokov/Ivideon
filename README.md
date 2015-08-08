git clone https://github.com/enshirokov/ivideon.git

cd ivideon
cmake -DCMAKE_PREFIX_PATH=<QTPATH> build/

(For example: cmake -DCMAKE_PREFIX_PATH=/home/eugene/Qt5/5.5/gcc_64/  build/)

make
