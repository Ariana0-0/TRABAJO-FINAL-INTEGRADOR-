#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define ANIO_ACTUAL 2025

float calcularFA(int anio, bool hibrido) {
	int antiguedad = ANIO_ACTUAL - anio;
	if (hibrido) return -0.20;
	
	if (antiguedad < 5) return 0.0;
	else if (antiguedad <= 10) return 0.05;
	else if (antiguedad <= 15) return 0.10;
	else if (antiguedad <= 20) return 0.15;
	else return 0.20;
}

float calcularT(int cilindraje) {
	if (cilindraje < 1500) return 0.00;
	else if (cilindraje <= 2000) return 0.08;
	else if (cilindraje <= 2500) return 0.09;
	else if (cilindraje <= 3000) return 0.11;
	else if (cilindraje <= 3500) return 0.12;
	else if (cilindraje <= 4000) return 0.24;
	else return 0.35;
}

float calcularIACV(int cilindraje, int anio, bool hibrido, float avaluo) {
	float t = calcularT(cilindraje);
	float fa = calcularFA(anio, hibrido);
	float iacv = (cilindraje - 1500) * t;
	
	if (iacv < 0) iacv = 0;
	
	iacv *= (1 + fa);
	float maximo = 0.4 * avaluo;
	if (iacv > maximo) iacv = maximo;
	
	return iacv;
}

void guardarEnArchivo(int revisiones, float multa, int anio, bool hibrido,
					  int cilindraje, float avaluo, float iacv, float total) {
	FILE *archivo = fopen("matricula.txt", "w");
	if (archivo == NULL) {
		printf("Error al crear el archivo.\n");
		return;
	}
	
	fprintf(archivo, "--- DETALLE DEL CALCULO DE MATRICULA ---\n");
	fprintf(archivo, "Revisiones: %d -> Multa: $%.2f\n", revisiones, multa);
	fprintf(archivo, "Antigüedad del vehículo: %d años\n", ANIO_ACTUAL - anio);
	fprintf(archivo, "¿Híbrido?: %s\n", hibrido ? "Sí" : "No");
	fprintf(archivo, "IACV calculado: $%.2f\n", iacv);
	fprintf(archivo, "1%% del avalúo: $%.2f\n", avaluo * 0.01);
	fprintf(archivo, "----------------------------------------\n");
	fprintf(archivo, "Total a pagar por matrícula: $%.2f\n", total);
	fclose(archivo);
	
	printf("Resultado guardado exitosamente en 'matricula.txt'\n");
}
				int main() {
					int revisiones, anio, cilindraje;
					float multa = 0.0, avaluo;
					char respuesta[10];
					bool hibrido = false;
						  
					// Revisión Técnica
					do {
						system("cls");
						printf("Ingrese la cantidad de revisiones tecnicas vehiculares (0 a 3): ");
						scanf("%d", &revisiones);
						if (revisiones < 0 || revisiones > 3) {
							printf("Ingrese un número válido entre 0 y 3.\n");
							system("pause");
							}
					} while (revisiones < 0 || revisiones > 3);
						  
					if (revisiones == 0) {
						printf("\n? El vehículo NO puede circular por falta total de revisiones.\n");
						return 0;
					} else if (revisiones == 1) {
							multa = 80;
					} else if (revisiones == 2) {
							multa = 40;
					}
						
					// Año del vehículo
					do {
						system("cls");
						printf("Ingrese el año del vehículo (1920 - %d): ", ANIO_ACTUAL);
						scanf("%d", &anio);
						if (anio < 1920 || anio > ANIO_ACTUAL) {
							printf("Año fuera de rango.\n");
							system("pause");
						}
					} while (anio < 1920 || anio > ANIO_ACTUAL);
						
					// ¿Híbrido?
					do {
						system("cls");
						printf("¿El vehículo es híbrido? (si/no): ");
						scanf("%s", respuesta);
						if (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0 &&
							strcmp(respuesta, "SI") != 0 && strcmp(respuesta, "NO") != 0) {
							printf("Responda solo con 'si' o 'no'.\n");
							system("pause");
						}
					} while (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0 &&
							strcmp(respuesta, "SI") != 0 && strcmp(respuesta, "NO") != 0);
						
					if (strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0) {
						hibrido = true;
					}
						
					// Cilindraje
					do {
						system("cls");
						printf("Ingrese el cilindraje en cc (mayor a 0): ");
						scanf("%d", &cilindraje);
						if (cilindraje <= 0) {
							printf("El cilindraje debe ser mayor a 0.\n");
							system("pause");
						}
					} while (cilindraje <= 0);
						
					// Avalúo
					do {
						system("cls");
						printf("Ingrese el avalúo del vehículo (mayor a 0): ");
						scanf("%f", &avaluo);
						if (avaluo <= 0) {
							printf("El avalúo debe ser mayor a 0.\n");
							system("pause");
						}
					} while (avaluo <= 0);
						
					// Calculo final
					system("cls");
					float iacv = calcularIACV(cilindraje, anio, hibrido, avaluo);
					float total = (avaluo * 0.01) + iacv + multa;
						
					printf("\n--- DETALLE DEL CALCULO DE MATRICULA ---\n");
					printf("Revisiones: %d ? Multa: $%.2f\n", revisiones, multa);
					printf("Antigüedad del vehículo: %d años\n", ANIO_ACTUAL - anio);
					printf("¿Híbrido?: %s\n", hibrido ? "Sí" : "No");
					printf("IACV calculado: $%.2f\n", iacv);
					printf("1%% del avalúo: $%.2f\n", avaluo * 0.01);
					printf("----------------------------------------\n");
					printf("?? Total a pagar por matrícula: $%.2f\n", total);
						
					// Preguntar si desea guardar
					printf("\n¿Desea guardar este cálculo en un archivo? (si/no): ");
					scanf("%s", respuesta);
					if (strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0) {
						guardarEnArchivo(revisiones, multa, anio, hibrido, cilindraje, avaluo, iacv, total);
					}
						
					return 0;
				}
					  
