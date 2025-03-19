#pragma once
// clang-format desativado

/*
    tmc2130_pen.h
    Parte do Grbl_ESP32

    Atribuições de pinos para o controlador de Caneta/Laser TMC2130
    https://github.com/bdring/Grbl_ESP32_TMC2130_Plotter_Controller

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

// Select a version to match your PCB
//#define MACHINE_V1 // version 1 PCB
#define MACHINE_V2  // version 2 PCB

#ifdef MACHINE_V1
#    define MACHINE_NAME "ESP32_TMC2130_PEN V1"
#    define X_LIMIT_PIN GPIO_NUM_2
#else
#    define MACHINE_NAME "ESP32_TMC2130_PEN V2"
#    define X_LIMIT_PIN GPIO_NUM_32
#endif

#define TRINAMIC_RUN_MODE TrinamicMode ::CoolStep
#define TRINAMIC_HOMING_MODE TrinamicMode ::CoolStep

#define X_STEP_PIN GPIO_NUM_12
#define X_DIRECTION_PIN GPIO_NUM_26
#define X_TRINAMIC_DRIVER 2130  // Which Driver Type?
#define X_CS_PIN GPIO_NUM_17    //chip select
#define X_RSENSE TMC2130_RSENSE_DEFAULT

#define Y_STEP_PIN GPIO_NUM_14
#define Y_DIRECTION_PIN GPIO_NUM_25
#define Y_TRINAMIC_DRIVER 2130  // Which Driver Type?
#define Y_CS_PIN GPIO_NUM_16    //chip select
#define Y_RSENSE TMC2130_RSENSE_DEFAULT

// OK to comment out to use pin for other features
#define STEPPERS_DISABLE_PIN GPIO_NUM_13

// Define one of these 2 options for spindle or servo
#define Z_SERVO_PIN GPIO_NUM_27    // comment this out if PWM spindle/laser control.
#define DEFAULT_Z_MAX_TRAVEL 5.0   // Range of travel is 5mm
#define DEFAULT_Z_HOMING_MPOS 5.0  // MPos will be set to 5mm after homing
#define Z_SERVO_CAL_MIN 1.0        // calibration factor for the minimum PWM duty
#define Z_SERVO_CAL_MAX 1.0        // calibration factor for the maximum PWM duty

// #define X_LIMIT_PIN          See version section at beginning of file
#define Y_LIMIT_PIN GPIO_NUM_4
