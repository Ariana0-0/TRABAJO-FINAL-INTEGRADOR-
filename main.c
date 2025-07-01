#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"

int main (){
	int opcion;
	
	do {
		system("cls");
		menuVehiculos();
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			registrarVehiculo();
			break;
		case 2:
			calculoMatricula();			
			break;
		case 3:
			buscarVehiculoPlaca();
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			break;
		case 7:
			printf("Saliendo del sistema...\n");
			break;
		default:
			printf("Opción inválida.\n");
			break;
		}
		system("pause");
	} while (opcion != 7);
	
	return 0;	
}
	
