/*
  Grbl.cpp - Inicialização e loop principal para o Grbl
  Parte do Grbl
  Copyright (c) 2014-2016 Sungeun K. Jeon para Gnea Research LLC

  2018 - Bart Dring Este arquivo foi modificado para uso no ESP32
         CPU. Não use isto com o Grbl para atMega328P

  O Grbl é um software livre: você pode redistribuí-lo e/ou modificá-lo
  sob os termos da Licença Pública Geral GNU conforme publicada pela
  Free Software Foundation, seja a versão 3 da Licença, ou
  (a seu critério) qualquer versão posterior.
  O Grbl é distribuído na esperança de que seja útil,
  mas SEM NENHUMA GARANTIA; sem mesmo a garantia implícita de
  COMERCIABILIDADE ou ADEQUAÇÃO A UM PROPÓSITO PARTICULAR. Veja a
  Licença Pública Geral GNU para mais detalhes.
  Você deve ter recebido uma cópia da Licença Pública Geral GNU
  junto com o Grbl. Se não, veja <http://www.gnu.org/licenses/>.
*/

#include "Grbl.h"
#include <WiFi.h>

void grbl_init() {
#ifdef USE_I2S_OUT
    i2s_out_init();  // O I2S out deve ser inicializado antes de poder acessar a porta GPIO expandida
#endif
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.enableSTA(false);
    WiFi.enableAP(false);
    WiFi.mode(WIFI_OFF);
    client_init();  // Configura a taxa de baud e interrupções da serial
    display_init();
    grbl_msg_sendf(
        CLIENT_SERIAL, MsgLevel::Info, "Grbl_ESP32 Ver %s Date %s", GRBL_VERSION, GRBL_VERSION_BUILD);  // Imprime a versão do grbl_esp32
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Compilado com ESP32 SDK:%s", ESP.getSdkVersion());   // Imprime a versão do SDK
// Exibe o nome do mapa na inicialização
#ifdef MACHINE_NAME
    report_machine_type(CLIENT_SERIAL);
#endif
    settings_init();  // Carrega as configurações do Grbl a partir de armazenamento não volátil
    stepper_init();   // Configura os pinos do motor e os temporizadores de interrupção
    system_ini();     // Configura os pinos de saída e interrupções de mudança de pino (Renomeado devido a conflito com arquivos do esp32)
    init_motors();
    memset(sys_position, 0, sizeof(sys_position));  // Limpa a posição da máquina.
    machine_init();                                 // Definição fraca em Grbl.cpp não faz nada
    // Inicializa o estado do sistema.
#ifdef FORCE_INITIALIZATION_ALARM
    // Força o Grbl a entrar em estado de ALARME após um ciclo de energia ou reset completo.
    sys.state = State::Alarm;
#else
    sys.state = State::Idle;
#endif
    // Verifica a inicialização e define o alarme do sistema se a homing estiver ativada para forçar o ciclo de homing
    // definindo o estado de alarme do Grbl. O alarme bloqueia todos os comandos G-code, incluindo os
    // scripts de inicialização, mas permite o acesso às configurações e comandos internos. Somente um ciclo de homing
    // '$H' ou o desbloqueio do alarme '$X' desabilitarão o alarme.
    // NOTA: O script de inicialização será executado após a conclusão bem-sucedida do ciclo de homing, mas
    // não após desabilitar os bloqueios de alarme. Evita que os blocos de inicialização de movimento batam
    // de forma descontrolada em objetos. Muito ruim.
#ifdef HOMING_INIT_LOCK
    if (homing_enable->get()) {
        sys.state = State::Alarm;
    }
#endif
    Spindles::Spindle::select();
#ifdef ENABLE_WIFI
    WebUI::wifi_config.begin();
#endif
#ifdef ENABLE_BLUETOOTH
    WebUI::bt_config.begin();
#endif
    WebUI::inputBuffer.begin();
}

static void reset_variables() {
    // Reseta as variáveis do sistema.
    State prior_state = sys.state;
    memset(&sys, 0, sizeof(system_t));  // Limpa a variável struct do sistema.
    sys.state             = prior_state;
    sys.f_override        = FeedOverride::Default;              // Define para 100%
    sys.r_override        = RapidOverride::Default;             // Define para 100%
    sys.spindle_speed_ovr = SpindleSpeedOverride::Default;      // Define para 100%
    memset(sys_probe_position, 0, sizeof(sys_probe_position));  // Limpa a posição da sonda.

    sys_probe_state                      = Probe::Off;
    sys_rt_exec_state.value              = 0;
    sys_rt_exec_accessory_override.value = 0;
    sys_rt_exec_alarm                    = ExecAlarm::None;
    cycle_stop                           = false;
    sys_rt_f_override                    = FeedOverride::Default;
    sys_rt_r_override                    = RapidOverride::Default;
    sys_rt_s_override                    = SpindleSpeedOverride::Default;

    // Reseta os sistemas principais do Grbl.
    client_reset_read_buffer(CLIENT_ALL);
    gc_init();  // Define o parser G-code para o estado padrão
    spindle->stop();
    coolant_init();
    limits_init();
    probe_init();
    plan_reset();  // Limpa o buffer de blocos e as variáveis do planejador
    st_reset();    // Limpa as variáveis do subsistema de steppers
    // Sincroniza as posições do G-code e do planejador com a posição atual do sistema.
    plan_sync_position();
    gc_sync_position();
    report_init_message(CLIENT_ALL);

    // Usado para rastrear um comando de jog enviado para mc_line() para que possamos cancelá-lo.
    // Isso é necessário se um jogCancel ocorrer depois que já tivermos analisado um jog e ele estiver em voo.
    sys_pl_data_inflight = NULL;
}

void run_once() {
    reset_variables();
    // Inicia o loop principal do Grbl. Processa as entradas do programa e as executa.
    // Isso pode sair em uma condição de abortamento do sistema, caso em que run_once()
    // é reexecutado por um loop externo.
    protocol_main_loop();
}

void __attribute__((weak)) machine_init() {}

void __attribute__((weak)) display_init() {}

void __attribute__((weak)) user_m30() {}

void __attribute__((weak)) user_tool_change(uint8_t new_tool) {}
/*
  setup() e loop() no Arduino .ino implementam este fluxo de controle:

  void main() {
     init();          // setup()
     while (1) {      // loop()
         run_once();
     }
  }
*/
