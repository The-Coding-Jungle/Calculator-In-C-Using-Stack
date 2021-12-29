if [ ! -d "build" ] ; then
    mkdir build;
fi

if [ ! -d "data" ] ; then
    mkdir data;
fi

gcc src/main.c -o build/main.out -lm 
./build/main.out