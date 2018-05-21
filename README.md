# TP-SO2

# Trabalho Prático de Sistema Operativos 2 2017/2018 - ISEC
* Nome do trabalho Phoenix Multipler;
* Desenvolvido em Visual Studio 2017 Community Edition;
* Comentários e código em PT-PT;

## Breve descrição:
Implementação de um jogo estilo Phoniex, Galaxians ou Invaders com suporte a vários utilizadores devido ao uso de um servidor(GUI), 
com várias opções de jogo configuráveis, e uma app cliente(GUI) onde mostra o jogo e recebe os comandos do jogador.
A comunicação entre o servidor e cliente será feita por uma app gateway(CMD), que por sua vez faz uso de uma livraria bridge(DLL) com 
recurso a memória partilhada e named pipes.
O jogo terá naves invasores e defensoras, tiros, bombas e powerups, assim como um modo gráfico para visualizar o jogo e para configuração, pontuação.

## Tecnologias
* Threads;
* Mutex, Events, Semáforos;
* Named Pipes;
* WinAPI
* Windows GUI;

# Entregas
- [x] Entrega meta1, com código retirado do github (desta forma o projecto fica o mais limpo possível e sem o "lixo" dos projetos compilados);
- [ ] Entrega final em modo release em x86 e x64 e código retirado do github;

# Para Fazer

## Meta1
- [x] Criação inicial da solução em Visual Studio 2017 Community Edition;
- [x] Criação do project servidor(GUI)
- [x] Criação do project cliente(GUI)
- [x] Criação do projecto gateway(DMD)
- [x] Criação do project bridge(DLL)
- [x] Criação inicial do projecto para o GitHub;
- [x] Adicionei colaborador;
- [x] Definir tarefas iniciais;
- [x] Colocar as opções Debug/Release, x86/x64 a funcionar;
	- [x] Correções nos projectos;

## Versão final
- [x] Correção dos projectos para C e devidas correções;
- [ ] Diagramas de arquitectura; 

## Extras
- [x] Obstáculos;
- [ ] Guardar lista das melhoras pontuações de jogadores (guardar em ficheiro) (High Score);
- [ ] Mais ideias?

# Outros
- [x] Criacão de um script para iniciar todas as aplicações em cada linha de comandos
	- [x] suporta argumentos;
	- [x] suporta x86/x64;
	- [x] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [ ] Código inicial da bridge(DDL):
	- [x] Livraria DLL;
	- [ ] Funções para zonas de memoria partilhada;
		- [ ] Dados de jogo;
		- [ ] Mensagens;
	- [ ] Funções para zona de dados do jogo;
    - [ ] Funções para zona de mensagens;

## Modulo "Servidor"
- [x] Código inicial da servidor(consola);
- [x] Interligação DLL implícita;
- [ ] Estrutura de dados; -> Em progresso!!;
	- [x] Estrutura de Jogo;
	- [ ] Estutura de Mensagens;
- [x] iniciar as naves, tiros, bombas, etc com posições (x,y) random;
	- [x] Definir limites para naves invasoras, defensores e para os tires/bombas/etc;
	- [x] Sem sobreposição das posições;
	- [ ] limite inferior, em %, das naves invasoras;
- [x] Modo debug, activar por argumentos;
- [x] Mostrar os dados, inicialemente em consola, mais tarde mudar para a GUI (especie de "debug");
- [x] Criação de zona de memória partilhada para o jogo (não usar variáveis globais);
- [x] Suporte a threads;
	- [x] Threads naves invasoras;
		- [ ] movimento inicial das naves
	- [ ] Thread para os tiros dos defensores, bombas dos invasores e powerups;
	- [ ] Thread para gerir a temporização e efeitos dos powerups;
	- [ ] Thread para gerir os jogadores(?) -> isto vai passar para o "gateway";
- [ ] Algoritmos de jogo;
	- [ ] Movimento naves;
	- [ ] detectar colisões, tiros, bombas, obstaculos, etc...
	- [ ] Pontuações;
- [ ] Extras: 
	- [ ] Obstáculos;
	- [ ] "High Score", guardar em ficheiro;
	- [ ] Guardar dados da memoria partilhada em ficheiro (não é importante, fazer se houver tempo!!);
- [ ] GUI, interface com o utilizador;

## Modulo "Gateway"
- [x] Criação do projecto gateway(consola):
	- [x] Interligação DLL implícita;
	- [x] App de consola;
	- [x] Modo debug, activar por argumentos;
		- [x] mostra os posições iniciais de novo jogo, dimensões da consola (com recurso a gotoxy());
    - [x] Suporte a memória partilhada e verificação se o servidor está em execução;
		- [ ] Falta verificação de quando o servidor termina;
	- [ ] Suporte a named pipes;
	- [ ] Suporte a threads;
		- [ ] nova ligação;
		- [ ] novo jogador;
	- [ ] Suporte a envio de login, nome de utiliazador(jogador);
	- [ ] Suporte ao input do jogador;
 	- [ ] Suporte a mensagens;
    
## Modulo "Cliente"
- [x] Código inicial da cliente(consola);
	- [ ] Suporte a named pipes;
	- [ ] Suporte a threads;
		- [ ] leitura;
		- [ ] escrita;
	- [ ] Recolhe as teclas do jogador e envia-as ao jogo;
	- [ ] Enviar e receber mensagens;
	- [ ] Primeiro teste em modo de consola (uma vez que a matéria de GUI gráfica ainda não foi lecionada nas aulas);
	- [ ] GUI, interface com o utilizador;

# Como jogar?
* Executar o sctipt "inicar_jogo.bat" de forma a iniciar o "servidor" e "gateway";
* Executar cliente(s);
