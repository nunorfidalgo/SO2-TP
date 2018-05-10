# TP-SO2

## Trabalho Prático de Sistema Operativos 2 2017/2018 - ISEC
* Desenvolvido em Visual Studio 2017 Community Edition;
* Comentários e código em PT-PT;

## Breve descrição:
Implementação de um jogo estilo Phoniex, Galaxians ou Invaders com suporte a vários utilizadores devido ao uso de um servidor(GUI), 
com várias opções de jogo configuráveis, e uma app cliente(GUI) onde mostra o jogo e recebe os comandos do jogador.
A comunicação entre o servidor e cliente será feita por uma app gateway(CMD), que por sua vez faz uso de uma livraria bridge(DLL) com 
recurso a memória partilhada e named pipes.
O jogo terá naves invasores e defensoras, tiros, bombas e powerups, assim como um modo gráfico para visualizar o jogo e para configuração.

## Para Fazer
- [x] Criação inicial da solução em Visual Studio 2017 Community Edition;
- [x] Criação do project servidor(GUI)
- [x] Criação do project cliente(GUI)
- [x] Criação do projecto gateway(DMD)
- [x] Criação do project bridge(DLL)
- [x] Criação inicial do projecto para o GitHub;
- [x] Adicionei colaborador;
- [x] Definir tarefas iniciais;
- [x] Colocar as opções Debug/Release, x86/x64 a funcionar;
	- [x] Correções nos projectos

# Entregas
- [ ] Entrega meta1 em modo release em x86 e x64
- [ ] Entrega final em modo release em x86 e x64

# Modulos

# Servidor
- [x] Código inicial da servidor(GUI):
	- [x] DLL implicita
	- [ ] Estrutura de dados; -> Em progresso!!
	- [x] iniciar as naves;
    - [ ] Threads por cada tipo de invasor(ou por cada nave invasora);
    - [ ] Thread para os tiros dos defensores, bombas dos invasores e powerups;
	- [ ] Thread para gerir a temporização e efeitos dos powerups;
	- [ ] Thread para gerir os jogadores;
	- [ ] Algoritmos de jogo;

# Cliente
- [x] Código inicial da cliente(GUI):
	- [ ] GUI e interface com o utilizador;
    - [ ] Recolhe as teclas do jogador e envia-as ao jogo;
    - [ ] Suporte a named pipes;

# Gateway
- [x] Criação do projecto gateway(CMD):
	- [x] DLL implicita
	- [x] App de consola;
	- [ ] Interage com o cliente e o servidor;
    - [ ] Suporte a memória partilhada;
    - [ ] Suporte a named pipes;

# Bridge
- [ ] Código inicial da bridge(DDL):
	- [x] Livraria DLL;
	- [ ] Zonas de memoria partilhada;
    - [ ] Zona de mensagens;
    - [ ] Zona de dados do jogo;

# Outros
- [x] Criacão de um script para iniciar todas as aplicações em cada linha de comandos
	- [x] suporta apenas x86
	- [ ] adiconar suporte para x64 através de argumentos