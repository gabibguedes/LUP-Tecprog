# Manual de Compilação

### Instalação
  Para rodar o jogo, primeiro é necessário instalar a biblioteca SDL2. Para isso rode o comando:
* Archlinux
```
$ sudo pacman -S sdl2
```

Tambem é necessário instalar as bibliotecas SDL_image, SDL_ttf e SDL_mixer:

* Archlinux
```
$ sudo pacman -S sdl2_image
$ sudo pacman -S sdl2_mixer
$ sudo pacman -S sdl2_ttf
```

Verifique onde as bibliotecas foram instaladas e coloque-as na pasta /usr/include/SDL2 junto com as outras bibliotecas do SDL. Provavelmente elas foram instaladas na pasta /usr/include.

### Configurações da IDE
  Para compilar e rodar o programa utilizamos a IDE do Eclipse para C++. Para instalar rode o comando:

* Archlinux
```
$ sudo pacman -S eclipse-cpp
```
 1. Abra o projeto pelo eclipse, por files > Open project from file system. Abra o browser e selecione a pasta do projeto LUP.  
 2. Selecione o projeto e vá em Project > Build Configurations > Set Active e selecione a opção Realease.  
 3. Vá em Project > Properties > C/C++ Build   
    * Vá em Tool Chain Editor e em Current toolchain selecione Linux GCC.  
    * Vá em Settings e
      - Entre em GCC C++ Compiler > Miscellaneous e em other flags acrescente -std=c++11  
      - Ainda em GCC C++ Compiler, entre em Includes e em Include paths (-I) adicione o caminho da pasta SDL2 /usr/include/SDL2  
      - Em GCC C++ Linker > Libraries adicione em Libraries (-l) as bibliotecas SDL2, SDL2_image, SDL2_mixer e SDL2_ttf  
      - Feche a janela do Properties clicando em Apply and Close  

### Compilar e rodar

Após essas configurações podemos compilar o programa, para isso vá em Project > Build Project.

Agora só falta rodar o programa, para isso clique em Run.

### Possiveis problemas:

* __Binary not found:__
Caso ao clicar em Run o programa dê um problema como Binary not found. Vá em Run > Run Configurations e clique duas vezes em C/C++ Aplication para abrir uma nova configuração. No campo C/C++ Aplication da nova configuração selecione Browse... e va na pasta do projeto, veja que foi criado uma pasta Realease, dentro desta pasta estará o exeutável, selecione ele, clique em Aply e em Run.
