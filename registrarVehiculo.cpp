#include <stdio.h>

typedef struct {
	char placa[10];
	char cedula[11];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3];
} Vehiculo;



void registrarVehiculo() {
	
	Vehiculo v;
	
	printf("\n--- Registro de Veh�culo ---\n");
	
	printf("Ingrese la placa: ");
	scanf("%s", v.placa);
	
	printf("Ingrese la c�dula: ");
	scanf("%s", v.cedula);
	
	printf("Ingrese el a�o del veh�culo: ");
	scanf("%d", &v.anio);
	
	printf("Ingrese el tipo de veh�culo: ");
	scanf("%s", v.tipo);
	
	printf("Ingrese el aval�o del veh�culo: ");
	scanf("%f", &v.avaluo);
	// Inicializa revisiones en 0
	for (int i = 0; i < 3; i++) {
		v.revisiones[i] = 0;
	}
		printf("Veh�culo registrado correctamente.\n");
	// Muestra los datos ingresados
	printf("\n----- Datos del Veh�culo -----\n");
	printf("Placa: %s\n", v.placa);
	printf("C�dula: %s\n", v.cedula);
	printf("A�o: %d\n", v.anio);
	printf("Tipo: %s\n", v.tipo);
	printf("Aval�o: %.2f\n", v.avaluo);
}
int main() {
	
	return 0;
}

