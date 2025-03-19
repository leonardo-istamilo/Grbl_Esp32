#pragma once
// clang-format off

/*
    test_drive.h
    Parte do Grbl_ESP32

    Atribuições de pinos (ou a ausência delas) para testar o Grbl_ESP32.

    Ele cria uma máquina básica de 3 eixos sem realmente acionar 
    os pinos de E/S. O Grbl irá relatar que os eixos estão se movendo, 
    mas nenhum movimento físico do motor ocorrerá.

    Isso pode ser carregado em um ESP32 não conectado ou conectado 
    a um hardware desconhecido, sem risco de os pinos tentarem 
    emitir sinais que possam causar um curto-circuito ou outros danos ao ESP32.

    Também pode ser usado para executar o programa básico, permitindo
    o carregamento de firmware OTA (over-the-air).

    2018    - Bart Dring
    2020    - Mitch Bradley

    O Grbl_ESP32 é um software livre: você pode redistribuí-lo e/ou modificá-lo
    sob os termos da Licença Pública Geral GNU conforme publicada pela 
    Free Software Foundation, seja a versão 3 da Licença ou 
    (a seu critério) qualquer versão posterior.

    O Grbl é distribuído na esperança de ser útil, 
    mas SEM NENHUMA GARANTIA; nem mesmo a garantia implícita de 
    COMERCIABILIDADE ou ADEQUAÇÃO A UM PROPÓSITO ESPECÍFICO. Consulte a 
    Licença Pública Geral GNU para mais detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU 
    junto com o Grbl_ESP32. Caso contrário, veja <http://www.gnu.org/licenses/>.
*/

#define MACHINE_NAME "Test Drive - Demo Only No I/O!"


#define N_AXIS 3
// Isso não pode usar homing porque não há interruptores.
#ifdef DEFAULT_HOMING_CYCLE_0
    #undef DEFAULT_HOMING_CYCLE_0
#endif

#ifdef DEFAULT_HOMING_CYCLE_1
    #undef DEFAULT_HOMING_CYCLE_1
#endif

#define SPINDLE_TYPE    SpindleType::NONE

#ifdef USE_RMT_STEPS
#undef USE_RMT_STEPS  // Suprimir aviso de variável não utilizada
#endif
