#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <stdbool.h>

struct Vehiculo {
	char placa[10];
	char cedula[11];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3];
};

void menuVehiculos();
void guardarVehiculo(struct Vehiculo v);
int validarPlaca(char placa[]);
int validarCedula(char cedula[]);
void registrarVehiculo();
float calcularFA(int anio, bool hibrido);
float calcularT(int cilindraje);
float calcularIACV(int cilindraje, int anio, bool hibrido, float avaluo);
void guardarEnArchivo(int revisiones, float multa, int anio, bool hibrido, int cilindraje, float avaluo, float iacv, float total);
void calculoMatricula();
void buscarVehiculoPorPlaca();


#endif
