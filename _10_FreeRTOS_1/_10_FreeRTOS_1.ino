
void tarea(void * pvParameters) {
  while (true) {
 
  }
}

void setup() {
  xTaskCreate(tarea,     // Puntero a la función
              "ejemplo", // Nombre de la tarea
              10000,     // Tamaño del stack
              NULL,      // Parámetros
              0,         // Prioridad
              NULL);     // Manejador
}

void loop() {
  while (true) {
    delay(10);
  }
}

