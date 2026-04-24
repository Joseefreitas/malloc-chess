# malloc-chess



gcc pif_game.c -o pif_game -I include/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  && ./pif_game





gcc -c functions/utilis.c -Iutilis -o utilis.o && gcc pif_game.c utilis.o -o pif_game -Iinclude/raylib/src -Iutilis -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./pif_game