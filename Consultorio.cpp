/*

									Módulo Consultorio:
	
Esta parte del proyecto estará dirigida a los diferentes profesionales que atienden y registran la
evolución de las mascotas en una base de datos de historias clínicas

Los datos de interés para el veterinario en este proceso son: Apellido y Nombres de la mascota (el
apellido corresponde al dueño o familia), DNI del dueño, Localidad, Edad, Peso.


Nombre y Apellido

-Ruiz Linda Selena 

Comision ; 1k1

Correo Electronico

Linda.Ruiz@alu.frt.utn.edu.ar
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

struct veterinario
{
	char nom[60];
	int mat;
	int dni;
	char tel[25];
	
};
struct fecha
{
    int dia,mes,anio;
};
struct mascota
{
    char nom[60];
    char dom[60];
    int dni;
    char loc[60];
    fecha nac;
    int pes;
    char tel[25];
};
struct turno
{
    int mat;
    fecha fec;
    int dni;
    char det[380];
};

int buscarUsuario(char usu[10],char cla[10]);
void visualizarLista();
void evolucionMascota();

main()
{
	int h,res;
	char usu[10], cla[10];
	
	system("COLOR 3A");
	
	printf("\n---------------------------------------------------------------");
	printf("\n------------------------MODULO RECEPCION-----------------------");
	printf("\n---------------------------------------------------------------");
	printf("\nIngrese el usario: ");
	_flushall( );
	gets(usu);
	printf("Ingrese la clave: ");
	_flushall( );
	gets(cla);
	
	h=buscarUsuario(usu,cla);

	
	if (h==0)
	{
		printf("\nUsuario no reconocido");
	}
	else
	{
		printf("Bienvenido al sistema");
		do
		{
            printf("\n1)Visualizar lista de espera de turnos");
            printf("\n2)Registrar evolución de la mascota");
            printf("\n3)Cerrar la aplicación");
            printf("\nElija una opcion: ");
            scanf("%d", &res);
            switch(res)
            {
                case 1:visualizarLista(); //funcion void 1era
                break;
                case 2:evolucionMascota(); //funcion void 2da
                break;
            }
        } while(res!=3); //CIERRE DE PROGRAMA 
	}
	getch();	
	
}

void visualizarLista()
{
    FILE*arch;
    turno reg;
    fecha fec;
    int mat;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    
    printf("\nIngrese el dia del turno: ");
    scanf("%d", &fec.dia);
    
    printf("\nIngrese el mes del turno: ");
    scanf("%d", &fec.mes);
    
    printf("\nIngrese el anio del turno: ");
    scanf("%d", &fec.anio);
    
    printf("\nIngrese la matricula del veterinario: ");
    scanf("%d", &mat);
    arch=fopen("turnos.dat","rb");
    fread(&reg, sizeof (reg),1,arch);
    while(!feof(arch))
    {
        if(fec.dia==reg.fec.dia && fec.mes==reg.fec.mes && fec.anio==reg.fec.anio && mat==reg.mat)
        {
            printf("\nDni: %d",reg.dni);
            printf("\nFecha %d/%d/%d: ",reg.fec.dia, reg.fec.mes, reg.fec.anio);
            printf("\nDetalle de la mascota: %s", reg.det);
        }
        fread(&reg, sizeof (reg),1,arch);
    }
    fclose(arch);
}
void evolucionMascota()
{
    FILE*arch, *arch1;
    int dni;
    mascota reg;
    turno reg1;
    long posi;
    bool h=false,h1=false;
    printf("\nIngrese el dni de la mascota: ");
    scanf("%d", &dni);
    arch1=fopen("turnos.dat","rb+");
    fread(&reg1,sizeof (reg1),1,arch1);
    while(!feof(arch1) && h==false)
    {
        
        if(dni==reg1.dni)
        {
            posi=ftell(arch1)-sizeof(reg1);
            h=true;
            
        }
        else
        fread(&reg1,sizeof (reg1),1,arch1);
    
    }
    if(h==false)
    {
        printf("\nNo se hallo el turno solicitado: ");
    } 
    else{
        
          arch=fopen("mascotas.dat","rb+");
          fread(&reg,sizeof(reg),1,arch);
    while(!feof(arch) && h1==false)
    {
        printf("\nDni: %d detalle: %s",reg1.dni,reg1.det);
        if(dni==reg.dni)
        {
            h1=true;
        }
        else
        fread(&reg,sizeof(reg),1,arch);
    
    }
    printf("\nDatos de la mascota: ");
    printf("\nNombre: %s",reg.nom);
    printf("\nDomicilio: %s",reg.dom);
    printf("\nPeso: %d  kilos",reg.pes);
    printf("\nNacimiento: %d/%d/%d",reg.nac.dia,reg.nac.mes,reg.nac.anio);
    printf("\nDetalle de la mascota: %s",reg1.det);
    char datos[100];
    printf("\nIngrese otro detalle: ");
    _flushall();
    gets(datos);
    strcat(reg1.det,"\n");
    strcat(reg1.det,datos);
    fseek(arch1,posi,SEEK_SET);
    fwrite(&reg1,sizeof(reg1),1,arch1);
    fclose(arch1);
    fclose(arch);
    printf("\nTurno actualizado: ");
        }
        
    
}
int Buscar(char linea[80],char usu[10],char cla[10])
{
	if(strstr(linea,usu)!=NULL && strstr (linea,cla)!=NULL)
	return 1;
	
	return 0;
	
}
int buscarUsuario(char usu[10],char cla[10])
{
	FILE*arch;
	char linea[80];
	arch=fopen("usuario.txt","rt");
	fgets(linea,80,arch);
	while(!feof(arch))
	{
		if(Buscar(linea, usu, cla))
		{
			fclose(arch);
			return 1; //1=Hallado
		}
	fgets(linea,80,arch);	
	}
	fclose(arch);
	return 0;//0=No hallado
	
}







