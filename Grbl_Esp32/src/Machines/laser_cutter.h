#pragma once
// clang-format off

/*
    laser_cutter.h
*/

#define MACHINE_NAME            "LASER_CUTTER" // Nome da máquina

#define X_STEP_PIN                  GPIO_NUM_12
#define X_DIRECTION_PIN             GPIO_NUM_17
#define Y_STEP_PIN                  GPIO_NUM_26
#define Y_DIRECTION_PIN             GPIO_NUM_4

#define X_LIMIT_PIN                 GPIO_NUM_14
#define Y_LIMIT_PIN                 GPIO_NUM_15

#define STEPPERS_DISABLE_PIN        GPIO_NUM_13 //En+

//Configuração do tipo de spindle (eixo giratório)
#define SPINDLE_TYPE            SpindleType::LASER
#define SPINDLE_OUTPUT_PIN          GPIO_NUM_2 // Rotulado como SpinPWM
//#define SPINDLE_ENABLE_PIN          GPIO_NUM_22  // Rotulado como SpinEnbl

// Configuração para resfriamento
//#define COOLANT_MIST_PIN        GPIO_NUM_21  // Rotulado como Mist
//#define COOLANT_FLOOD_PIN       GPIO_NUM_25  // Rotulado como Flood
//#define PROBE_PIN               GPIO_NUM_32  // Rotulado como Probe


// Pinos de controle adicionais (requerem pull-up externo)
//define CONTROL_SAFETY_DOOR_PIN GPIO_NUM_35  // Rotulado como Door
#define CONTROL_FEED_HOLD_PIN       GPIO_NUM_27 //Pause
#define CONTROL_CYCLE_START_PIN     GPIO_NUM_33 //resume
#define CONTROL_RESET_PIN           GPIO_NUM_16 //cancel
