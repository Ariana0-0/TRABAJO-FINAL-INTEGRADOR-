#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libreria.h"

#define anioActual 2025

void menuVehiculos(){
	printf("--------Men� Principal--------\n");
	printf("1. Registrar veh�culo\n");
	printf("2. Calcular matr�cula\n");
	printf("3. Buscar veh�culo por placa\n");
	printf("4. Listar veh�culos matriculados\n");
	printf("5. Registrar revisiones t�cnicas\n");
	printf("6. Generar comprobante\n");
	printf("7. Guardar y salir\n");
	printf("Seleccione una opci�n: ");
}

	
void guardarVehiculo(struct Vehiculo v){
	FILE *archivo = fopen("vehiculos.txt", "a"); //"a" append para agregar sin borrar
	if(archivo == NULL){
		printf("Error al abrir el archivo para guardar.\n");
		return;
	}
	fprintf(archivo, "Placa: %s\n", v.placa); //fprintf se usa para escribir los datos del veh�culo en el archivo
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
//si el usuario pone  letras mayusculas lo pne en may�sculas para formato correcto
	if(strlen(placa) != 8){ 
		return 0;
	}
	//1. validaci�n "strlen" cuenta cuantos caracteres hay en la cadena "8" <ctype>
	for(int i=0; i < 3; i++ ){
		if (!isalpha(placa[i])){
			return 0;
		}
	}
	// 2. validaci�n "isalpha" devuelve verdadero si es que hay letras, "!" es negaci�n
	//si no hay letras retorna 0 "ctype"
	if (placa[3] != '-'){
		return 0;
	}
	// 3. validaci�n en la posicion tres debe estar "-"
	for (int i=4; i<8; i++){
		if (!isdigit(placa[i])){
			return 0; //el 0 retorna falso
		}
	}
	//4. validaci�n en la posici�n 4 donde comienza los n�meros verifica "isdigit"
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
	} //empieza desde el digito 1 hasta llegar al diez verificando si son n�meros y si no retorna "0"
	return 1;
}
	
void registrarVehiculo() {
			
	struct Vehiculo v;
				
	printf("\n--- Registro de Veh�culo ---\n");
	do {
		printf("Ingrese la placa (formato ABC-1234): ");
		scanf("%s", v.placa);
		if (!validarPlaca(v.placa)){
			printf("Placa inv�lida \n");
		}
	} while(!validarPlaca(v.placa));//se ejecta si la placa no es valida "!"
	system("cls");
	
	do {
		printf("Ingrese la c�dula: ");
		scanf("%s", v.cedula); //lee la c�dula como cadena
		if (!validarCedula(v.cedula)){
			printf("C�dula de identidad mal ingresado \n");
		}
	} while(!validarCedula(v.cedula));
	system("cls");

	do{
		printf("Ingrese el a�o del veh�culo: ");
		scanf("%d", &v.anio);
		if (v.anio > anioActual || v.anio <1920){
			printf("A�o inv�lido \n");
		}
	} while(v.anio > anioActual || v.anio < 1920);
	system("cls");
	
	printf("Ingrese el modelo del veh�culo: ");//solo carros
	fflush(stdin); //limipa el compilador
	fgets(v.tipo, sizeof(v.tipo), stdin);
	
	size_t len = strlen(v.tipo);
	if (len > 0 && v.tipo[len - 1] == '\n') {
		v.tipo[len - 1] = '\0';
	} //elimina el salto de linea al mostrar en la consola
	system("cls");
	
	do {
		printf("Ingrese el aval�o del veh�culo: ");
	    scanf("%f", &v.avaluo);
	    if (v.avaluo <= 0){
			printf("Aval�o inv�lido \n");
			printf("Int�ntelo de nuevo ");
			
		}
	} while(v.avaluo <= 0);
	system("cls");
					
	// Inicializa revisiones en 0
	for (int i = 0; i < 3; i++) {
		v.revisiones[i] = 0;
	}
	system("cls");
	printf("Veh�culo registrado correctamente.\n");
    // Muestra los datos ingresados
	printf("\n----- Datos del Veh�culo -----\n");
	printf("Placa: %s\n", v.placa);
	printf("C�dula: %s\n", v.cedula);
	printf("A�o: %d\n", v.anio);
	printf("Tipo: %s\n", v.tipo);
	printf("Aval�o: %.2f\n", v.avaluo);
	
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
	fprintf(archivo, "Antig�edad del veh�culo: %d a�os\n", anioActual - anio);
	fprintf(archivo, "�H�brido?: %s\n", hibrido ? "S�" : "No");
	fprintf(archivo, "IACV calculado: $%.2f\n", iacv);
	fprintf(archivo, "1%% del aval�o: $%.2f\n", avaluo * 0.01);
	fprintf(archivo, "----------------------------------------\n");
	fprintf(archivo, "Total a pagar por matr�cula: $%.2f\n", total);
	fclose(archivo);
	
	printf("Resultado guardado exitosamente en 'matricula.txt'\n");
}


void calculoMatricula (){
	int revisiones, anio, cilindraje;
	float multa = 0.0, avaluo;
	char respuesta[10];
	bool hibrido = false;
	char linea[100];  // Para capturar la l�nea de entrada
	int valido;
	
	// Revisi�n T�cnica
	do {
		system("cls");
		printf("Ingrese la cantidad de revisiones tecnicas vehiculares (0 a 3): ");
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);  // Lee una l�nea como texto
		valido = sscanf(linea, "%d", &revisiones);  // Intenta convertir a entero
		
		if (valido != 1 || revisiones < 0 || revisiones > 3) {
			printf("Ingrese un n�mero v�lido entre 0 y 3.\n");
			system("pause");
		}
		
	} while (valido != 1 || revisiones < 0 || revisiones > 3);
	
	if (revisiones == 0) {
		printf("\n? El veh�culo NO puede circular por falta total de revisiones.\n");
		return 0; //revisar
	} else if (revisiones == 1) {
		multa = 80;
	} else if (revisiones == 2) {
		multa = 40;
	}
	
    // A�o del veh�culo
	do {
		system("cls");
		printf("Ingrese el a�o del veh�culo (1920 - %d): ", anioActual);
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);
		valido = sscanf(linea, "%d", &anio);
		
		if (valido != 1 || anio < 1920 || anio > anioActual) {
			printf("A�o fuera de rango o inv�lido.\n");
			system("pause");
		}
	} while (valido != 1 || anio < 1920 || anio > anioActual);
	// �H�brido?
	do {
		system("cls");
		printf("�El veh�culo es h�brido? (si/no): ");
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
		fgets(linea, sizeof(linea), stdin);  // Lee una l�nea como texto
		valido = sscanf(linea, "%d", &cilindraje);  // Intenta convertir a entero
		
		if (valido != 1 ||cilindraje <= 0) {
			printf("El cilindraje debe ser un n�mero mayor a 0.\n");
			system("pause");
		}
		
	} while (valido != 1 || cilindraje <= 0);
	
// Aval�o
	do {
		system("cls");
		printf("Ingrese el aval�o del veh�culo (mayor a 0): ");
		fflush(stdin); //limipa el compilador
		fgets(linea, sizeof(linea), stdin);  // Lee una l�nea como texto
		valido = sscanf(linea, "%d", &avaluo);  // Intenta convertir a entero
		if (valido != 1 ||avaluo <= 0) {
			printf("El aval�o debe ser un n�mero mayor a 0.\n");
			system("pause");
		}
	} while (valido != 1 || avaluo <= 0);

	// Calculo final
	system("cls");
	float iacv = calcularIACV(cilindraje, anio, hibrido, avaluo);
	float total = (avaluo * 0.01) + iacv + multa;
	
	printf("\n--- DETALLE DEL CALCULO DE MATRICULA ---\n");
	printf("Revisiones: %d ? Multa: $%.2f\n", revisiones, multa);
	printf("Antig�edad del veh�culo: %d a�os\n", anioActual - anio);
	printf("�H�brido?: %s\n", hibrido ? "S�" : "No");
	printf("IACV calculado: $%.2f\n", iacv);
	printf("1%% del aval�o: $%.2f\n", avaluo * 0.01);
	printf("----------------------------------------\n");
	printf(" Total a pagar por matr�cula: $%.2f\n", total);
						  
	// Preguntar si desea guardar
	printf("\n�Desea guardar este c�lculo en un archivo? (si/no): ");
    scanf("%s", respuesta);
	if (strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0) {
		guardarEnArchivo(revisiones, multa, anio, hibrido, cilindraje, avaluo, iacv, total);
	}
	
	return 0; //revisar
}

void buscarVehiculoPlaca() {
	char placaBuscada[10];
	char linea[100]; //tama�o limite de cada linea del archivo
	bool encontrado = false;
	printf("\n--- Buscar Veh�culo por Placa ---\n");
	do {
		printf("Ingrese la placa a buscar (formato ABC-1234): ");
		scanf("%s", placaBuscada);
		system("cls");
		if (!validarPlaca(placaBuscada)){
			printf("Placa inv�lida \n");
		}
	} while(!validarPlaca(placaBuscada));//se ejecta mientras la placa no es valida "!"
	system("cls");
	
	FILE *archivo= fopen("vehiculos.txt", "r");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo de veh�culos.\n");
		return;
	}
	
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		// Busca l�nea que comience con "Placa: "
		if (strncmp(linea, "Placa: ", 7) == 0) {
			// Extrae la placa actual del archivo
			char placaArchivo[10];
			sscanf(linea + 7, "%s", placaArchivo);
			
			if (strcmp(placaBuscada, placaArchivo) == 0) {
				// Se encontr� la placa
				encontrado = true;
				printf("\nVeh�culo encontrado:\n");
				printf("%s", linea); // imprime l�nea de la placa
				
				// imprime las siguientes 4 l�neas del veh�culo
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
		printf("\nVeh�culo con placa %s no encontrado.\n", placaBuscada);
	}
	
	fclose(archivo);
}
