
if [[ ! -d "build/linux" ]];
then
    mkdir -p "build/linux"
fi

gcc -ggdb src/*.c -o build/linux/LD47.o -lSDL2 -lSDL2_mixer -lGL -lm
