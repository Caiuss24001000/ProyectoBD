#include <cstdlib>
#include <iostream>
#include <fstream>
//#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;
///Definir variables necesarias
string nombre, auxnombre, apPaterno, apMaterno;
int idCliente, auxidCliente;
float credito=0, deuda=0;
char opca;
bool encontrado = false;


void altas()
{
    ///Variables de la biblioteca fstream para el manejo de archivos
    ofstream escritura;
    ifstream consulta;

    do{
    escritura.open("tienda.txt", ios::out | ios::app);//crea y escribe, si ya tiene texto une al final del archivo
    consulta.open("tienda.txt", ios::in);//solamente consulta o lee usando la variable sobre el archivo físico tienda.txt

    if (escritura.is_open() && consulta.is_open()){


            bool repetido=false;

            cout<<"\n";
            cout<<"\tIngresa el ID del cliente:    ";
            cin>>auxidCliente;
            
            ///A continuación se aplica el tipo de lectura de archivos secuencial
            consulta>>idCliente;
            while (!consulta.eof()){
                consulta>>nombre>>apPaterno>>apMaterno>>credito>>deuda;
                if (auxidCliente==idCliente){
                    cout<<"\t\tYa existe el ID del Cliente...\n";
                    repetido=true;
                    break;
                }
                consulta>>idCliente;
            }

            if (repetido==false){
                cout<<"\tIngresa el nombre del cliente:   ";
                cin>>nombre;
                cout<<"\tIngresa el apellido paterno del cliente: ";
                cin>>apPaterno;
                cout<<"\tIngresa el apellido materno del cliente:    ";
                cin>>apMaterno;
                ///cout<<"\tIngresa el credito del cliente:    ";
                //cin>>credito;
                
					do{
                cout<<"\tIngresa el credito del cliente:    ";
                cin>>credito;
        			if (credito < 0){
            			cout << "\tEl credito es menor a cero." << endl;
        			}
        			else if (credito > 1000000){
            		cout << "\tLa tienda no da credito mayor a 999,999." << endl;
        			} 
        		}while(credito < 0 || credito >= 999999); 
        		//cout<<"\tIngresa la deuda del cliente:    ";
                //cin>>deuda;
        		//while(deuda > 0  || deuda <= 999999)
				do{
                	cout<<"\tIngresa la deuda del cliente:    ";
                	cin>>deuda;
                	if (deuda < 0){
            			cout << "\tLa deuda es menor a cero." << endl;
        			}
        			else if (deuda > 1000000){
            		cout << "\tLa tienda acepta deduda mayor a 999,999." << endl;
        			}
				}while(deuda < 0  || deuda >= 999999);
				
                //ESCRIBIENDO LOS DATOS CAPTURADOS POR EL USUARIO EN EL ARCHIVO
                escritura<<auxidCliente<<" "<<nombre<<" "<<apPaterno<<" "<<apMaterno<<" "<<credito<<" "<<deuda<<endl;
                cout<<"\n\tRegistro agregado...\n";
            }

            cout<<"\n\tDeseas ingresar otro cliente? (S/N): ";
            cin>>opca;

    }else{
        cout<<"El archivo no se pudo abrir \n";
    }

    escritura.close();
    consulta.close();

    }while (opca=='S' or opca=='s');

}

void bajas()
{
    ofstream aux;
    ifstream lectura;

    encontrado=false;

    aux.open("auxiliar.txt", ios::out);
    lectura.open("tienda.txt", ios::in);

    if (aux.is_open() && lectura.is_open()){

        cout<<"\n";
        cout<<"\tIngresa el ID del cliente que deseas eliminar: ";
        cin>>auxidCliente;
            
            ///De nuevo se aplica el tipo de lectura de archivos secuencial, esto quiere decir que lee campo por campo hasta
            ///hasta llegar al final del archivo gracias a la función .eof()
            lectura>>idCliente;
            while (!lectura.eof()){
                lectura>>nombre>>apPaterno>>apMaterno>>credito>>deuda;
                if (auxidCliente==idCliente){
                        encontrado=true;
                        cout<<"\n";
                        cout<<"\tID Cliente:    "<<idCliente<<endl;
                        cout<<"\tNombre:   "<<nombre<<endl;
                        cout<<"\tApellido Paterno: "<<apPaterno<<endl;
                        cout<<"\tApellido Materno:    "<<apMaterno<<endl;
                        cout<<"\tCredito:    "<<credito<<endl;
                        cout<<"\tDeuda:    "<<deuda<<endl;
                        cout<<"\t________________________________\n\n";
                        cout<<"\tRealmente deseas eliminar el registro actual (S/N)? ---> ";
                        cin>>opca;

                        if (opca=='S' or opca=='s'){
                            cout<<"\n\n\t\t\tRegistro eliminado...\n\n\t\t\a";
                        }else{
                            aux<<idCliente<<" "<<nombre<<" "<<apPaterno<<" "<<apMaterno<<" "<<credito<<0.0<<deuda<<0.0<<endl;
                        }

                    }else{
                        aux<<idCliente<<" "<<nombre<<" "<<apPaterno<<" "<<apMaterno<<" "<<credito<<0.0<<deuda<<0.0<<endl;
                    }
                lectura>>idCliente;
            }
    }else{
        cout<<"\n\tEl archivo no se pudo abrir \n";
    }

    if (encontrado==false){
                cout<<"\n\tNo se encontro ningun registro con la clave: "<<auxidCliente<<"\n\n\t\t\t";
            }

    aux.close();
    lectura.close();
    remove ("tienda.txt");
    rename("auxiliar.txt", "tienda.txt");
}


void consultas()
{
    //Lectura de archivos

    ifstream lectura;
    lectura.open("tienda.txt", ios::out | ios::in);//CREA, ESCRIBE O LEE
    if (lectura.is_open()){
       //LEYENDO Y MOSTRANDO CADA CAMPO DEL ARCHIVO DE FORMA SECUENCIAL
       lectura>>idCliente;
       while (!lectura.eof()){
            lectura>>nombre>>apPaterno>>apMaterno>>credito>>deuda;
            cout<<"\n";
            cout<<"\tID Cliente:    "<<idCliente<<endl;
            cout<<"\tNombre:   "<<nombre<<endl;
            cout<<"\tApellido Paterno: "<<apPaterno<<endl;
            cout<<"\tApellido Materno:    "<<apMaterno<<endl;
            cout<<"\tCredito:    "<<credito<<endl;
            cout<<"\tDeuda:    "<<deuda<<endl;
            lectura>>idCliente;
            cout<<"\t________________________________\n";
       }

    }else{
        cout<<"El archivo no se pudo abrir \n";
    }
    lectura.close();
}


void buscar()
{
    ifstream lectura;
    lectura.open("tienda.txt", ios::out | ios::in);

    encontrado=false;

    if (lectura.is_open()){
        cout<<"\n\tIngresa la ID del cliente que deseas buscar: ";
        cin>>auxidCliente;

        lectura>>idCliente;
        while(!lectura.eof()){
            lectura>>nombre>>apPaterno>>apMaterno>>credito>>deuda;
        //comparar cada registro para ver si es encontrado

        if(auxidCliente==idCliente){
            cout<<"\n";
            cout<<"\tID Cliente:    "<<idCliente<<endl;
            cout<<"\tNombre:   "<<nombre<<endl;
            cout<<"\tApellido Paterno: "<<apPaterno<<endl;
            cout<<"\tApellido Materno:    "<<apMaterno<<endl;
            cout<<"\tCredito:    "<<credito<<endl;
            cout<<"\tDeuda:    "<<deuda<<endl;
            cout<<"\t________________________________\n";
            encontrado=true;
            break;
        }//fin del if mostrar encontrado

        //lectura adelantada
        lectura>>idCliente;
        }//fin del while
        if (encontrado==false){
            cout<<"\n\n\tNo hay registros con el ID: "<<auxidCliente<<"\n\n\t\t\t";
        }
    }else{
        cout<<"\n\tAun no se pudo abrir el archivo...";
    }

    lectura.close();
}

void modificar()
{
    ofstream aux;
    ifstream lectura;

    encontrado=false;

    aux.open("auxiliar.txt", ios::out);
    lectura.open("tienda.txt", ios::in);

    if (aux.is_open() && lectura.is_open()){

        cout<<"\n";
        cout<<"\tIngresa la ID del cliente que deseas modificar: ";
        cin>>auxidCliente;

            lectura>>idCliente;
            while (!lectura.eof()){
                lectura>>nombre>>apPaterno>>apMaterno>>credito>>deuda;
                if (auxidCliente==idCliente){
                    encontrado=true;
                    cout<<"\n";
                    cout<<"\tID Cliente:    "<<idCliente<<endl;
                    cout<<"\tNombre:   "<<nombre<<endl;
                    cout<<"\tApellido Paterno: "<<apPaterno<<endl;
                    cout<<"\tApellido Materno:    "<<apMaterno<<endl;
                    cout<<"\tCredito:    "<<credito<<endl;
            		cout<<"\tDeuda:    "<<deuda<<endl;
                    cout<<"\t________________________________\n\n";
                    cout<<"\tIngresa el nuevo nombre del cliente con el ID Cliente: "<<auxidCliente<<"\n\n\t---> ";
                    cin>>auxnombre;

                    aux<<idCliente<<" "<<nombre<<" "<<apPaterno<<" "<<apMaterno<<" "<<credito<<0.0<<deuda<<0.0<<endl;
                    cout<<"\n\n\t\t\tRegistro modificado...\n\t\t\a";
                    }else{
                    aux<<idCliente<<" "<<nombre<<" "<<apPaterno<<" "<<apMaterno<<" "<<credito<<0.0<<deuda<<0.0<<endl;
                    }
                lectura>>idCliente;
            }
    }else{
        cout<<"\n\tEl archivo no se pudo abrir \n";
    }

    if (encontrado==false){
                cout<<"\n\tNo se encontro ningun cliente con el ID: "<<auxidCliente<<"\n\n\t\t\t";
            }

    aux.close();
    lectura.close();
    remove ("tienda.txt");
    rename("auxiliar.txt", "tienda.txt");
}

int main()
{
    int opc;

    do{
    system("cls");

    cout<<"\n\tTienda Azul\n\n";
    cout<<"\n\t1.-Altas";
    cout<<"\n\t2.-Bajas";
    cout<<"\n\t3.-Consultas";
    cout<<"\n\t4.-Buscar un registro";
    cout<<"\n\t5.-Modificaciones";
    cout<<"\n\t6.-Salir";
    cout<<"\n\n\tElige una opcion:  ";
    cin>>opc;
    switch (opc)
    {
case 1:{
    system("cls");
    altas();
    cout<<"\n\t\t";
    system ("pause");
    break;
}
case 2:{
    system("cls");
    bajas();
    cout<<"\n\t\t";
    system ("pause");
    break;
}

case 3:{
    system("cls");
    consultas();
    cout<<"\n\t\t";
    system ("pause");
    break;
}
case 4:{
    system("cls");
    buscar();
    cout<<"\n\t\t";
    system ("pause");
    break;
}
case 5:{
    system("cls");
    modificar();
    cout<<"\n\t\t";
    system ("pause");

    break;
}
case 6:{
    cout<<"\n\n\tHa elegido salir...\n\n\t\t"; system ("pause");
    break;
}
default:{
    cout<<"\n\n\tHa elegido una opcion inexistente...\n\n\t\t"; system ("pause");
    break;
}
    }//fin switch

    }while (opc!=6);

    system("cls");

    return 0;
}

