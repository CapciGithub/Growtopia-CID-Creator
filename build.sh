sudo apt-get install clang
clang++ CPPBot.cpp enet/callbacks.c enet/compress.c enet/host.c enet/list.c enet/packet.c enet/peer.c enet/protocol.c enet/unix.c -pthread -std=c++11 -fpermissive -o gtbot -w #Build source code into executable
sudo apt-get install boxes
echo -e "Tool succesfuly builded, you can start creating ID by typing ./gtbot \n\tCreated by github.com/CapciGithub"| boxes -d parchment -a c
