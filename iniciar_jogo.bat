@echo off
REM 
REM Script para iniciar o jogo, servidor e gateway em simultâneo nas várias arquitecturas.
REM

if "%1"=="" if "%2"=="" goto ajuda
if "%1"=="?" if "%2"=="" goto ajuda

if "%1"=="x86" if "%2"=="" goto x86
if "%1"=="x86" if "%2"=="debug" goto x86_debug

if "%1"=="x64" if "%2"=="" goto x64
if "%1"=="x64" if "%2"=="debug" goto x64_debug

:x86
	start Release\servidor.exe
	timeout /t 1
	start Release\gateway.exe
	goto :eof

:x86_debug
	start Debug\servidor.exe debug
	timeout /t 1
	start Debug\gateway.exe debug
	goto :eof

:x64
	start x64\Release\servirdor.exe
	timeout /t 1
	start x64\Release\gateway.exe
	goto :eof

:x64_debug
	start x64\Debug\servidor.exe debug
	timeout /t 1
	start x64\Debug\gateway.exe debug
	goto :eof

:ajuda
	echo Iniciar Jogo ^(Servidor^&Gateway^)
	echo uso: %0 ^<x86/x64^> ^<debug^>
	goto :eof