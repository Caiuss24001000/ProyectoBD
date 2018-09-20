#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
///Definir variables necesarias
string nombre, auxnombre, apPaterno, apMaterno;
int idCliente, auxidCliente, day, month, year;
float credito=0, deuda=0;
char opca;
bool encontrado = false;
bool bisiesto = false;

void validacionFechaCorrecta();
void validacionFecha();

void validacionFechaCorrecta(){
	
	validacionFecha();
	
	if(month == 2){
		
		if(day == 30 || day == 31){
			
			cout<<"\n\nError mes o d\241a incorrecto";
			validacionFecha();
		}else{
			
			if(!((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) && day == 29){
				
				cout<<"\n\nError d\241a incorrecto";
				validacionFecha();
			}
		}
	}else{
		
		if(month == 4 || month == 6 || month == 9 || month == 11){
			
			if(day == 31){
				
				cout<<"\n\nError mes o d\241a incorrecto";
				validacionFecha();
			}
		}
	}
	
	cout<<"\n\nFecha ingresada: "<<day<<"/"<<month<<"/"<<year; 
}

void validacionFecha(){
	
	do{
		
		//cout << "\tLa tienda no da credito mayor a 999,999." << endl;
		cout<<"Ingrese el d\241a de registro: ";
		cin>>day; //Día
	}while(day>31 || day<1);
	
	do{
		
		cout<<"\nIngrese el mes de registro: ";
		cin>>month; //Mes
	}while(month<1 || month>12);
	
	//Falta saber el rango de la Fecha
	do{
		
		cout<<"\nIngrese el a\244o de registro: ";
		cin>>year; //Año 
	}while(year < 2018 || year > 5000);
}

int main(){
	
	validacionFechaCorrecta();
}