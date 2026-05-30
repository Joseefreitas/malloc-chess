# malloc-draughts

Nossa proposta foi recriar- do nosso jeito- o clássico jogo de Damas, com elementos prórpios e algumas coisas novas.
Utilizamos mecânicas e estilos de jogos antigos, misturados com elementos contemporâneos de execução e funcionamento.

## Gameplay:
  -(link)


##### O jogo somente pode ser executado via Linux (Seja Linux/WSL no Windows).
De preferência utilize a distribuição Ubuntu,

##### O primeiro passo para compilar é copiar o repositório git:
        git clone https://github.com/Joseefreitas/malloc-draughts.git

### Adicionar o Raylib na pasta do arquivo (Dentro da pasta do jogo):
     git clone https://github.com/raysan5/raylib.git raylib
     
### Para rodar na máquina Linux, primeiro instale as seguintes dependências:
    sudo apt update
    sudo apt install -y build-essential git cmake
    sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev

### Para Rodar o jogo, em máquina Linux, existem 2 formas que podem ser utilizadas para compilar o jogo: 
    `gcc pif_game.c -o pif_game -I include/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  && ./pif_game`
-  Ou, via MakeFile:
      `make run`
