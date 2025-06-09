#include <stdio.h>
//Función para crear el menú
void menu_vehiculos(){
	printf("--------Menú Principal--------\n");
	printf("1. Registrar vehículo\n");
	printf("2. Calcular matrícula\n");
	printf("3. Registrar revisiones técnicas\n");
	printf("4. Buscar vehículo por placa\n");
	printf("5. Listar vehículos matriculados\n");
	printf("6. Generar comprobante\n");
	printf("7. Guardar y salir\n");
	printf("Seleccione una opción: ");
}

int main() {
	//Aqui se valida que funciona la función menú (es temporal)
	menu_vehiculos();
	return 0;
}

