# malloc-draughts 👑
 
> Uma releitura do clássico jogo de damas — com identidade própria.
 
**malloc-draughts** recria o jogo de Damas combinando mecânicas tradicionais com elementos contemporâneos: sistema de Rainha reformulado, áudio integrado e uma experiência visual renovada. Desenvolvido em C com [Raylib](https://www.raylib.com/), como projeto da disciplina PIF.
 
----
 
## Demonstração
 
> 🎥 [Game play no youtube](https://youtu.be/W_5xzeyKk9E)
 
----
 
## Funcionalidades
 
-  Movimentação responsiva e validada por direção
-  Sistema de Rainha funcional
-  Sistema de captura com alcance controlado
-  Áudio integrado
-  Tabuleiro renderizado com Raylib
----
 
## Pré-requisitos
 
> ⚠️ **O jogo roda somente em Linux** (ou WSL no Windows).
 
Instale as dependências necessárias:
 
```bash
sudo apt update
sudo apt install -y build-essential git cmake
sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
```
 
----
 
## Instalação
 
**1. Clone o repositório:**
 
```bash
git clone https://github.com/Joseefreitas/malloc-draughts.git
cd malloc-draughts
```
 
**2. Adicione o Raylib dentro da pasta do projeto :**
  **Somente para WSL**
 Primeiro, acesse o site de Raylib: https://www.raylib.com/
 
 Nele, vá para área que está escrito "Download"

 <img width="1053" height="262" alt="image" src="https://github.com/user-attachments/assets/77c16966-df46-460f-970e-3cb15a6a20d3" />

Aperte Download, e siga o processo de instalação

Depois de terminar o download, é necessário mover a pasta baixada para dentro da pasta do jogo

Depois de colocar a pasta do raylib dentro da pasta do jogo precisa instalar as dependencias novamente

"
sudo apt update
sudo apt install -y build-essential git cmake
sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
 "
para garantir que não tenha falhas
 
----
 
## Como compilar e rodar
 
**Via Makefile (recomendado):**
 dentro da pasta do jogo
```bash
make run
```
 pode demorar um pouco para compilar

 ----
