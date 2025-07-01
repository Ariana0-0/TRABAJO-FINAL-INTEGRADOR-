#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libreria.h"

#define anioActual 2025

void menuVehiculos(){
	printf("--------Menú Principal--------\n");
	printf("1. Registrar vehículo\n");
	printf("2. Calcular matrícula\n");
	printf("3. Buscar vehículo por placa\n");
	printf("4. Listar vehículos matriculados\n");
	printf("5. Registrar revisiones técnicas\n");
	printf("6. Generar comprobante\n");
	printf("7. Guardar y salir\n");
	printf("Seleccione una opción: ");
}

	
void guardarVehiculo(struct Vehiculo v){
	FILE *archivo = fopen("vehiculos.txt", "a"); //"a" append para agregar sin borrar
	if(archivo == NULL){
		printf("Error al abrir el archivo para guardar.\n");
		return;
	}
	fprintf(archivo, "Placa: %s\n", v.placa); //fprintf se usa para escribir los datos del vehículo en el archivo
	fprintf(archivo, "Cedula: %s\n", v.cedula);
	fprintf(archivo, "Ano: %d\n", v.anio);
	fprintf(archivo, "Tipo: %s\n", v.tipo);
	fprintf(archivo, "Avaluo: %.2f\n", v.avaluo);
	fprintf(archivo, "--------------------------\n");
	fclose(archivo); //con fclose se cierra el archivo 
}
		
int validarPlaca(char placa[]){
	for (int i = 0; i < 3; i++){
		placa[i] = toupper(placa[i]);
	}
//si el usuario pone  letras mayusculas lo pne en mayúsculas para formato correcto
	if(strlen(placa) != 8){ 
		return 0;
	}
	//1. validación "strlen" cuenta cuantos caracteres hay en la cadena "8" <ctype>
	for(int i=0; i < 3; i++ ){
		if (!isalpha(placa[i])){
			return 0;
		}
	}
	// 2. validación "isalpha" devuelve verdadero si es que hay letras, "!" es negación
	//si no hay letras retorna 0 "ctype"
	if (placa[3] != '-'){
		return 0;
	}
	// 3. validación en la posicion tres debe estar "-"
	for (int i=4; i<8; i++){
		if (!isdigit(placa[i])){
			return 0; //el 0 retorna falso
		}
	}
	//4. validación en la posición 4 donde comienza los números verifica "isdigit"
	//"!" si no es numero retorna 0 
	return 1; //el uno retorna verdadero
}
int validarCedula(char cedula[]){
	if (strlen(cedula) != 10){
		return 0; //retorna 0 "falso" si es que es distinto de 10
	}
	for (int i = 0; i < 10; i++){
		if (!isdigit(cedula[i])){
			return 0;
		}
	} //empieza desde el digito 1 hasta llegar al diez verificando si son números y si no retorna "0"
	return 1;
}
	
void registrarVehiculo() {
			
	struct Vehiculo v;
				
	printf("\n--- Registro de Vehículo ---\n");
	do {
		printf("Ingrese la placa (formato ABC-1234): ");
		scanf("%s", v.placa);
		if (!validarPlaca(v.placa)){
			printf("Placa inválida \n");
		}
	} while(!validarPlaca(v.placa));//se ejecta si la placa no es valida "!"
	system("cls");
	
	do {
		printf("Ingrese la cédula: ");
		scanf("%s", v.cedula); //lee la cédula como cadena
		if (!validarCedula(v.cedula)){
			printf("Cédula de identidad mal ingresado \n");
		}
	} while(!validarCedula(v.cedula));
	system("cls");

	do{
		printf("Ingrese el año del vehículo: ");
		scanf("%d", &v.anio);
		if (v.anio > anioActual || v.anio <1920){
			printf("Año inválido \n");
		}
	} while(v.anio > anioActual || v.anio < 1920);
	system("cls");
	
	printf("Ingrese el modelo del vehículo: ");//solo carros
	fflush(stdin); //limipa el compilador
	fgets(v.tipo, sizeof(v.tipo), stdin);
	
	size_t len = strlen(v.tipo);
	if (len > 0 && v.tipo[len - 1] == '\n') {
		v.tipo[len - 1] = '\0';
	} //elimina el salto de linea al mostrar en la consola
	system("cls");
	
	do {
		printf("Ingrese el avalúo del vehículo: ");
	    scanf("%f", &v.avaluo);
	    if (v.avaluo <= 0){
			printf("Avalúo inválido \n");
			printf("Inténtelo de nuevo ");
			
		}
	} while(v.avaluo <= 0);
	system("cls");
					
	// Inicializa revisiones en 0
	for (int i = 0; i < 3; i++) {
		v.revisiones[i] = 0;
	}
	system("cls");
	printf("Vehículo registrado correctamente.\n");
    // Muestra los datos ingresados
	printf("\n----- Datos del Vehículo -----\n");
	printf("Placa: %s\n", v.placa);
	printf("Cédula: %s\n", v.cedula);
	printf("Año: %d\n", v.anio);
	printf("Tipo: %s\n", v.tipo);
	printf("Avalúo: %.2f\n", v.avaluo);
	
	guardarVehiculo(v);
}

float calcularFA(int anio, bool hibrido) {
	int antiguedad = anioActual - anio;
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
	fprintf(archivo, "Antigüedad del vehículo: %d años\n", anioActual - anio);
	fprintf(archivo, "¿Híbrido?: %s\n", hibrido ? "Sí" : "No");
	fprintf(archivo, "IACV calculado: $%.2f\n", iacv);
	fprintf(archivo, "1%% del avalúo: $%.2f\n", avaluo * 0.01);
	fprintf(archivo, "----------------------------------------\n");
	fprintf(archivo, "Total a pagar por matrícula: $%.2f\n", total);
	fclose(archivo);
	
	printf("Resultado guardado exitosamente en 'matricula.txt'\n");
}


void calculoMatricula (){
	int revisiones, anio, cilindraje;
	float multa = 0.0, avaluo;
	char respuesta[10];
	bool hibrido = false;
	char linea[100];  // Para capturar la línea de entrada
	int valido;
	
	// Revisión Técnica
	do {
		system("cls");
		printf("Ingrese la cantidad de revisiones tecnicas vehiculares (0 a 3): ");
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);  // Lee una línea como texto
		valido = sscanf(linea, "%d", &revisiones);  // Intenta convertir a entero
		
		if (valido != 1 || revisiones < 0 || revisiones > 3) {
			printf("Ingrese un número válido entre 0 y 3.\n");
			system("pause");
		}
		
	} while (valido != 1 || revisiones < 0 || revisiones > 3);
	
	if (revisiones == 0) {
		printf("\n? El vehículo NO puede circular por falta total de revisiones.\n");
		return 0; //revisar
	} else if (revisiones == 1) {
		multa = 80;
	} else if (revisiones == 2) {
		multa = 40;
	}
	
    // Año del vehículo
	do {
		system("cls");
		printf("Ingrese el año del vehículo (1920 - %d): ", anioActual);
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);
		valido = sscanf(linea, "%d", &anio);
		
		if (valido != 1 || anio < 1920 || anio > anioActual) {
			printf("Año fuera de rango o inválido.\n");
			system("pause");
		}
	} while (valido != 1 || anio < 1920 || anio > anioActual);
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
	
// cilindraje
	do {
		system("cls");
		printf("Ingrese el cilindraje en cc (mayor a 0): "); //agregar un rango maximo
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);  // Lee una línea como texto
		valido = sscanf(linea, "%d", &cilindraje);  // Intenta convertir a entero
		
		if (valido != 1 ||cilindraje <= 0) {
			printf("El cilindraje debe ser un número mayor a 0.\n");
			system("pause");
		}
		
	} while (valido != 1 || cilindraje <= 0);
	
// Avalúo
	do {
		system("cls");
		printf("Ingrese el avalúo del vehículo (mayor a 0): ");
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);  // Lee una línea como texto
		valido = sscanf(linea, "%d", &avaluo);  // Intenta convertir a entero
		if (valido != 1 ||avaluo <= 0) {
			printf("El avalúo debe ser un número mayor a 0.\n");
			system("pause");
		}
	} while (valido != 1 || avaluo <= 0);

	// Calculo final
	system("cls");
	float iacv = calcularIACV(cilindraje, anio, hibrido, avaluo);
	float total = (avaluo * 0.01) + iacv + multa;
	
	printf("\n--- DETALLE DEL CALCULO DE MATRICULA ---\n");
	printf("Revisiones: %d ? Multa: $%.2f\n", revisiones, multa);
	printf("Antigüedad del vehículo: %d años\n", anioActual - anio);
	printf("¿Híbrido?: %s\n", hibrido ? "Sí" : "No");
	printf("IACV calculado: $%.2f\n", iacv);
	printf("1%% del avalúo: $%.2f\n", avaluo * 0.01);
	printf("----------------------------------------\n");
	printf(" Total a pagar por matrícula: $%.2f\n", total);
						  
	// Preguntar si desea guardar
	printf("\n¿Desea guardar este cálculo en un archivo? (si/no): ");
    scanf("%s", respuesta);
	if (strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0) {
		guardarEnArchivo(revisiones, multa, anio, hibrido, cilindraje, avaluo, iacv, total);
	}
	
	return 0; //revisar
}

void buscarVehiculoPlaca() {
	char placaBuscada[10];
	char linea[100]; //tamaño limite de cada linea del archivo
	bool encontrado = false;
	printf("\n--- Buscar Vehículo por Placa ---\n");
	do {
		printf("Ingrese la placa a buscar (formato ABC-1234): ");
		scanf("%s", placaBuscada);
		system("cls");
		if (!validarPlaca(placaBuscada)){
			printf("Placa inválida \n");
		}
	} while(!validarPlaca(placaBuscada));//se ejecta mientras la placa no es valida "!"
	system("cls");
	
	FILE *archivo= fopen("vehiculos.txt", "r");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo de vehículos.\n");
		return;
	}
	
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		// Busca línea que comience con "Placa: "
		if (strncmp(linea, "Placa: ", 7) == 0) {
			// Extrae la placa actual del archivo
			char placaArchivo[10];
			sscanf(linea + 7, "%s", placaArchivo);
			
			if (strcmp(placaBuscada, placaArchivo) == 0) {
				// Se encontró la placa
				encontrado = true;
				printf("\nVehículo encontrado:\n");
				printf("%s", linea); // imprime línea de la placa
				
				// imprime las siguientes 4 líneas del vehículo
				for (int i = 0; i < 4; i++) {
					if (fgets(linea, sizeof(linea), archivo) != NULL) {
						printf("%s", linea);
					}
				}
				break;
			}
		}
	}
	
	if (!encontrado) { //si no se encuentra la placa
		printf("\nVehículo con placa %s no encontrado.\n", placaBuscada);
	}
	
	fclose(archivo);
}
