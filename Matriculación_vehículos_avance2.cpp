#include <stdio.h>
//Funci�n para crear el men�
void menu_vehiculos(){
	printf("--------Men� Principal--------\n");
	printf("1. Registrar veh�culo\n");
	printf("2. Calcular matr�cula\n");
	printf("3. Registrar revisiones t�cnicas\n");
	printf("4. Buscar veh�culo por placa\n");
	printf("5. Listar veh�culos matriculados\n");
	printf("6. Generar comprobante\n");
	printf("7. Guardar y salir\n");
	printf("Seleccione una opci�n: ");
}

int main() {
	//Aqui se valida que funciona la funci�n men� (es temporal)
	menu_vehiculos();
	return 0;
}

