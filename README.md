# malloc-draughts 👑
 
> Uma releitura do clássico jogo de Damas — com identidade própria.
 
**malloc-draughts** recria o jogo de Damas combinando mecânicas tradicionais com elementos contemporâneos: sistema de Rainha reformulado, áudio integrado e uma experiência visual renovada. Desenvolvido em C com [Raylib](https://www.raylib.com/), como projeto da disciplina PIF.
 
---
 
## Demonstração
 
> 🎥 [Game play no youtube](#)
 
---
 
## Funcionalidades
 
-  Movimentação responsiva e validada por direção
-  Sistema de Rainha funcional
-  Sistema de captura com alcance controlado
-  Áudio integrado
-  Tabuleiro renderizado com Raylib
---
 
## Pré-requisitos
 
> ⚠️ **O jogo roda apenas em Linux** (ou WSL no Windows).
 
Instale as dependências necessárias:
 
```bash
sudo apt update
sudo apt install -y build-essential git cmake
sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
```
 
---
 
## Instalação
 
**1. Clone o repositório:**
 
```bash
git clone https://github.com/Joseefreitas/malloc-draughts.git
cd malloc-draughts
```
 
**2. Adicione o Raylib dentro da pasta do projeto:**
 
```bash
git clone https://github.com/educ8s/Intro-To-raylib-Tutorial.git
```
 
---
 
## Como compilar e rodar
 
**Via Makefile (recomendado):**
 
```bash
make run
```
 
**Ou manualmente com GCC:**
 
```bash
gcc pif_game.c functions/utilis.c functions/math_game.c functions/tabuleiro.c functions/constants.c functions/funcoes_placar.c functions/funcoes_salvar_pontuacao.c functions/hud.c -o pif_game -I ./functions -I./raylib/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  && ./pif_game
```
 
---
