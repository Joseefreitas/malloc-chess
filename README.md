# malloc-chess



gcc pif_game.c -o pif_game -I include/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  && ./pif_game

depeendencias: 
sudo apt install -y build-essential git cmake
sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev



pra compilar com tudo ajustado:

gcc pif_game.c functions/utilis.c functions/math_game.c functions/constants.c -o pif_game -I ./functions -I./raylib/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  && ./pif_game


