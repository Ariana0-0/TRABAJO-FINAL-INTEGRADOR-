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
		printf("Ingrese la placa: ");
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
		if (v.anio <= 0 || v.anio > 2025){
			printf("Año inválido \n");
		}
	} while(v.anio <= 0 || v.anio > 2025);
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
}
int main() {
registrarVehiculo();
	return 0;
}
