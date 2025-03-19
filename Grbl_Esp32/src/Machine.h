#pragma once

// Este arquivo é onde você escolhe o tipo de máquina, incluindo
// um ou mais arquivos de definição de máquina conforme descrito abaixo.

#ifndef MACHINE_FILENAME

// !!! Para testes iniciais, comece com test_drive.h, que desativa
// todos os pinos de E/S
#include "Machines/laser_cutter.h"
//#    include "Machines/test_drive.h"

// !!! Para uso real, altere a linha acima para selecionar uma placa
// de Machines/, por exemplo:
// #include "Machines/3axis_v4.h"

// === Opção de Configuração de Arquivo Único para OEM
// Fabricantes (OEMs) que desejam publicar o código-fonte configurado
// para uma máquina específica podem colocar todas as definições de configuração
// diretamente neste arquivo, sem incluir nenhum outro arquivo acima.

#else

// Usando o ambiente externo para definir MACHINE_FILENAME,
// uma configuração pode ser escolhida sem editar este arquivo.
// Isso é útil para scripts de testes automatizados.
//
// Por exemplo, ao usar o ambiente de compilação platformio
// no Linux, você poderia executar o seguinte comando:
//   PLATFORMIO_BUILD_FLAGS=-DMACHINE_FILENAME=3axis_v4.h platformio run
//
// No Windows, usando PowerShell, o comando seria:
//   $env:PLATFORMIO_BUILD_FLAGS='-DMACHINE_FILENAME=3axis_v4.h'; platformio run
//
// Ao usar o Arduino IDE, não há uma maneira fácil de passar variáveis
// para o compilador, então esse recurso não é útil para Arduino.
//
// MACHINE_FILENAME não deve incluir o prefixo do caminho Machines/;
// ele é fornecido automaticamente.
//
// MACHINE_PATHNAME_QUOTED constrói um caminho adequado para
//#include
#    define MACHINE_PATHNAME_QUOTED(name) <src/Machines/name>

#    include MACHINE_PATHNAME_QUOTED(MACHINE_FILENAME)

#endif  // MACHINE_FILENAME
