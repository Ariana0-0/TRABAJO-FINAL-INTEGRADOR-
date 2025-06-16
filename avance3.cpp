#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Vehiculo {
	char placa[10];
	char cedula[11];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3];
};

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
		printf("Ingrese la placa: ");
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
		if (v.anio <= 0 || v.anio > 2025){
			printf("A�o inv�lido \n");
		}
	} while(v.anio <= 0 || v.anio > 2025);
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
}
int main() {
registrarVehiculo();
	return 0;
}
