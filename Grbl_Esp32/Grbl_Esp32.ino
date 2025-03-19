/*
 Grbl_ESP32.ino - Cabeçalho para comandos de nível de sistema e processos em tempo real  
Parte do Grbl  
Copyright (c) 2014-2016 Sungeun K. Jeon para Gnea Research LLC  

2018 - Bart Dring Este arquivo foi modificado para uso no  
          processador ESP32. Não use este arquivo com o Grbl para atMega328P  


  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "src/Grbl.h"

void setup() {
    grbl_init();
}

void loop() {
    run_once();
}
