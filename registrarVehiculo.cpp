#include <stdio.h>

struct Vehiculo {
	char placa[10];
	char cedula[11];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3];
} ;



void registrarVehiculo() {
	
	struct Vehiculo v;
	
	printf("\n--- Registro de Vehículo ---\n");
	
	printf("Ingrese la placa: ");
	scanf("%s", v.placa);
	
	printf("Ingrese la cédula: ");
	scanf("%s", v.cedula);
	
	printf("Ingrese el año del vehículo: ");
	scanf("%d", &v.anio);
	
	printf("Ingrese el tipo de vehículo: ");
	scanf("%s", v.tipo);
	
	printf("Ingrese el avalúo del vehículo: ");
	scanf("%f", &v.avaluo);
	// Inicializa revisiones en 0
	for (int i = 0; i < 3; i++) {
		v.revisiones[i] = 0;
	}
		printf("Vehículo registrado correctamente.\n");
	// Muestra los datos ingresados
	printf("\n----- Datos del Vehículo -----\n");
	printf("Placa: %s\n", v.placa);
	printf("Cédula: %s\n", v.cedula);
	printf("Año: %d\n", v.anio);
	printf("Tipo: %s\n", v.tipo);
	printf("Avalúo: %.2f\n", v.avaluo);
}
int main() {
	
	return 0;
}

