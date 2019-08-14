/*
Este programa fue hecho por: Wilbert Alexander Arana Diaz
Carnet: AD18005
Carrera: Ingenieria de Sistemas Informaticos.
Materia: Programacion III 
*/
#include <iostream>
#include <stdlib.h>  //Cabezera del programa

using namespace std; 

typedef struct nodo{
     int nro;     		
     struct nodo *izq, *der;
}*ABB;

struct nodoCola{
    ABB ptr;		//estructuras 
    struct nodoCola *sgte;
};
struct cola{	//estructyra para encolar
    struct nodoCola *delante;
    struct nodoCola *atras;
};

void inicializaCola(struct cola &q) //inicia
{
    q.delante = NULL;
    q.atras = NULL;
}

void encola(struct cola &q, ABB n) //funcion encola
{
     struct nodoCola *p;
     p = new(struct nodoCola);
     p->ptr = n;
     p->sgte = NULL;
     if(q.delante==NULL)
         q.delante = p;
     else
         (q.atras)->sgte = p;
     q.atras = p;
}

ABB desencola(struct cola &q) //abb desencola de la estructura
{
    struct nodoCola *p;
    p = q.delante;
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}

ABB crearNodo(int x) //crea un nuevo nodo
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void insertar(ABB &arbol, int x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
           cout<<"\n\t  Insertado..!"<<endl<<endl;
     }
     else if(x < arbol->nro)
          insertar(arbol->izq, x);
     else if(x > arbol->nro)
          insertar(arbol->der, x);
}

void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->nro <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}

void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          cout << arbol->nro << " ";
          enOrden(arbol->der);
     }
}

void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          enOrden(arbol->der);
          cout << arbol->nro << " ";
     }
}

void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"   ";

     cout<< arbol->nro <<endl;

     verArbol(arbol->izq, n+1);
}

bool busquedaRec(ABB arbol, int dato)
{
     int r=0;   

     if(arbol==NULL)
        return r;

     if(dato<arbol->nro)
         r = busquedaRec(arbol->izq, dato);

     else if(dato> arbol->nro)
         r = busquedaRec(arbol->der, dato);

     else
        r = 1;   

     return r;
}

ABB unirABB(ABB izq, ABB der)
{
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}

void elimina(ABB &arbol, int x)
{
     if(arbol==NULL) return;

     if(x<arbol->nro)
         elimina(arbol->izq, x);
     else if(x>arbol->nro)
         elimina(arbol->der, x);

     else
     {
         ABB p = arbol;
         arbol = unirABB(arbol->izq, arbol->der);
         delete p;
     }
}

int alturaAB(ABB arbol)
{
    int AltIzq, AltDer;

    if(arbol==NULL)
        return -1;
    else
    {
        AltIzq = alturaAB(arbol->izq);
        AltDer = alturaAB(arbol->der);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}

void recorrerxNivel(ABB arbol)
{
     struct cola q;
     inicializaCola(q);
     cout << "\t";

     if(arbol!=NULL)
     {
         encola(q, arbol);

         while(q.delante!=NULL)
         {
             arbol = desencola(q);
             cout << arbol->nro << ' ';

             if(arbol->izq!=NULL)
                 encola(q, arbol->izq);
             if(arbol->der!=NULL)
                 encola(q, arbol->der);
         }
     }
}

void menu()
{
    // system("cls");
     cout << "\n\t\t  ..[ ARBOL BINARIO ]..              \n\n";
     cout << "\t [1]  Insertar elemento                  \n";
     cout << "\t [2]  Mostrar arbol                      \n";
     cout << "\t [3]  Recorridos                         \n";
     cout << "\t [4]  Buscar elemento                    \n";
     cout << "\t [5]  Eliminar elemento                  \n";
     cout << "\t [6]  Recorrido por Grado			     \n";
     cout << "\t [7]  Altura del arbol                   \n";
     cout << "\t [8]  Salir                              \n";

     cout << "\n\t Ingrese opcion : ";
}

void menu2()
{
  //   system("cls");   
     cout << endl;
     cout << "\t [1] En Orden     \n";
     cout << "\t [2] Pre Orden    \n";
     cout << "\t [3] Post Orden   \n";
     cout << "\n\t     Opcion :  ";
     
}

int main()
{
    ABB arbol = NULL;
    int x;
    int op, op2;


    system("color 09");   
    do
    {
          menu();  cin>> op;
          cout << endl;

          switch(op)
          {
               case 1:
                    cout << " Ingrese valor : ";  cin>> x;
                    insertar( arbol, x);
                    break;

               case 2:
             
                    verArbol(arbol, 0);
                    break;

               case 3:
              
                    menu2();  cin>> op2;

                    if(arbol!=NULL)
                    {
                         switch(op2)
                         {
                             case 1:
                                 enOrden(arbol); break;
                             case 2:
                                 preOrden(arbol); break;
                             case 3:
                                 postOrden(arbol); break;
                         }
                    }
                    else
                        cout << "\n\t Arbol vacio..!";
                    break;

               case 4:
               
                    bool band;

                    cout<<" Valor a buscar: "; cin>> x;

                    band = busquedaRec(arbol,x);

                    if(band==1)
                       cout << "\n\tEncontrado...";
                    else
                       cout << "\n\tNo encontrado...";
                    break;

               case 5:
               
                    cout<<" Valor a eliminar: "; cin>> x;
                    elimina(arbol, x);
                    cout << "\n\tEliminado..!";
                    break;

               case 6:
               
                    cout<<"\n\n Mostrando recorrido por grado\n\n";
                    recorrerxNivel(arbol);
                    break;

               case 7:
               	
                    int h;
                    h = alturaAB(arbol);
                    cout << " La altura es : "<< h << endl;
                    break;
               case 8:
                    exit(0);
          }

          cout<<"\n\n\n";
          
    }while(op!=7);

}
