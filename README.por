MDFOnda
=======

MDFonda é uma aplicação para a visualização de uma onda em função do tempo (onda calculada pelo Método das Diferenças Finitas), desenvolvido em Matlab e C++ com QT e OpenGL.


------------------
Instruções para Linux
------------------

Primeiro, execute o arquivo do Matlab 'MDFOnda.m' para gerar o arquivo 'wave_data.txt'. Use este arquivo como entrada para o MDFonda. O diretório 'release' tem um binário compilado para Debian 7.6.0 amd64 (release/MDFonda_linux). Para executá-lo, você precisa instalar os pacotes OpenGL Utility Toolkit (freeglut3) e QT 4 OpenGL Libraries (libqt4-opengl).

Compilando MDFonda: você precisa instalar os pacotes OpenGL Utility Toolkit develompent files (freeglut3-dev) e QT 4 Develompent Libraries. No diretório raiz, rode o comando 'make'. Você também pode importar o arquivo do projeto 'MDFonda.pro' no seu QTCreator.

