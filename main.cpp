#include <iostream>
#include <vector>
using namespace std;
using std::vector;

void tablero(int tablero[8][8]);
char piezas(int p);
bool Val_Win(int tablero[8][8], int blancas, int negras);
vector<int> Val_Mov_Ini(int tablero[8][8], vector<int> &i);
vector<int> Val_Mov_fin(int tablero[8][8], vector<int> &i);
vector<int> Val_Dama(int tablero[8][8], vector<int> &Rxy);
void P_inicial(void);

int main()
{
vector<int> i={0,0,0,0,8,8,0,9,9,0,0};
vector<int> Rxy{9,9};
int blancas=0;
int negras=0;
int pasar=0;
bool Ganar=true;
int matrizA[8][8] =
{
    {0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0},
    {0, 2, 0, 2, 0, 2, 0, 2},
    {1, 0, 1, 0, 2, 0, 1, 0},
    {0, 1, 0, 1, 0, 3, 0, 1},
    {3, 0, 3, 0, 3, 0, 1, 0},
    {0, 3, 0, 3, 0, 3, 0, 3},
    {3, 0, 3, 0, 3, 0, 3, 0}
};
P_inicial();
tablero(matrizA); //llama al tablero

do{
    i=Val_Mov_Ini(matrizA, i);
    i=Val_Mov_fin(matrizA, i);
    blancas=i[4];
    negras=i[5];
    if(i[6]==0 && i[9]==1)
    {
     matrizA[i[0]-1][i[1]-1]=1;
     matrizA[i[7]][i[8]]=1;
     if(i[10]==1)
     {
          matrizA[i[2]][i[3]]=4;
     }else
     {
          matrizA[i[2]][i[3]]=2;
     }
    }
    if(i[6]==0 && i[9]==0)
    {
        matrizA[i[0]-1][i[1]-1]=1;
        if(i[10]==1)
     {
          matrizA[i[2]][i[3]]=4;
     }else
     {
          matrizA[i[2]][i[3]]=2;
     }
    }
    if(i[6]==1 && i[9]==1)
    {
     matrizA[i[0]-1][i[1]-1]=1;
     matrizA[i[7]][i[8]]=1;
     if(i[10]==1)
     {
          matrizA[i[2]][i[3]]=5;
     }else{
          matrizA[i[2]][i[3]]=3;
     }
    }
    if(i[6]==1 && i[9]==0)
    {
        matrizA[i[0]-1][i[1]-1]=1;
        if(i[10]==1)
     {
          matrizA[i[2]][i[3]]=5;
     }else{
          matrizA[i[2]][i[3]]=3;
     }
    }


    Rxy=Val_Dama(matrizA, i);
    if (Rxy[0]!=9)
    {
        if(Rxy[0]==0)
        {
            matrizA[0][Rxy[1]]=5;
            tablero(matrizA);
            Rxy[0]=9;
            Rxy[1]=9;
        }else
        {
            matrizA[7][Rxy[1]]=4;
            tablero(matrizA);
            Rxy[0]=9;
            Rxy[1]=9;
        }
    }
    tablero(matrizA); //llama al tablero
    cout<<"\t\t\t              Sino tienes mas Movimientos Validos debes pasar turno : ";
    cout<<"\t\t\t              1= si 2 = no ";
    cin>>pasar;
    if (pasar ==1)
    {
        if(i[6]==0)
            i[6]=1;
        else
            i[6]=0;
    }

    Ganar=Val_Win(matrizA, blancas, negras);

}while(Ganar);

return 0;
}
void P_inicial (void)
{
    cout<<"\t\t_____________________________________________________________________"<<endl;
    cout<<"\t\t                                                                    "<<endl;
    cout<<"\t\t Universidad de Guanajuato"<<endl;
    cout<<"\t\t Division de Ingenierias Campus Irapuato Salamanca"<<endl;
    cout<<"\t\t Programacion en ingenieria "<<endl;
    cout<<"\t\t Torres Villa Carlos"<<endl;
    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
}

vector<int> Val_Dama(int tablero[8][8], vector<int> &Rxy)
{
    //Para  Damas Blancas
    for(int i; i < 8; i++)
    {
        if(tablero[0][i]==3)
        {
            Rxy[0]=0;
            Rxy[1]=i;
        }
    }
    //Para  Damas Negras
    for(int i; i < 8; i++)
    {
        if(tablero[7][i]==2)
        {
            Rxy[0]=7;
            Rxy[1]=i;
        }
    }
    return Rxy;
}

vector<int> Val_Mov_fin(int tablero[8][8], vector<int> &i)
{
    int Df,Dc;
    bool correcto=true;
    do{
    cout<<"\t\t\t              Ingrese fila de destino  : ";
    cin>>Df;
    cout<<"\t\t\t              Ingrese columna de destino  : ";
    cin>>Dc;
//---------------Validacion 1 salto Blancas
    if ((i[1]-(Dc)==-1 || i[1]-(Dc)==1) && tablero[Df-1][Dc-1]==1 && i[6]==0)
        {
        if (Df-i[0]==1)
            {
            cout << "\t\t\t\t Movimiento permitido " << endl;
            correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[9]=0;
            i[10]=0;
            }
            else
            {
            cout << "\t\t\t\t Solo puedes ir hacia adelante " << endl;
            }
        }
    else{
        cout << "\t\t\t\t Solo puedes mover en diagonal o la casilla esta ocupada " << endl;
        }
//------------------------------- Validacion doble salto Blancas
    if ((i[1]-(Dc)==-2 || i[1]-(Dc)==2) && tablero[Df-1][Dc-1]==1 && (tablero[Df-2][Dc-2]==3 || tablero[Df-2][Dc-2]==5) && i[6]==0)
        {
        if (Df-i[0]==2)
            {
            correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[5]--;
            i[7]=Df-2;
            i[8]=Dc-2;
            i[9]=1;
            i[10]=0;
            cout << "\t\t\t\t Movimiento permitido comiste ficha " << endl;

            }
            else
            {
            cout << "\t\t\t\t Solo puedes ir hacia adelante " << endl;
            }
        }
    else{
        cout << "\t\t\t\t Solo puedes mover en diagonal o la casilla esta ocupada con una ficha tuya " << endl;
        }
//-----------------------Validacion Dama Blanca-----------------------------------
    if ((i[1]-(Dc)< 7 || i[1]-(Dc)< -7) && tablero[Df-1][Dc-1]==1 && i[6]==0 && tablero[i[0]-1][i[1]-1]==4)
    {
        cout << "\t\t\t\t Movimiento permitido " << endl;
            correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[9]=0;
            i[10]=1;
    }
//---------------------- Validacion Dama Blanca Comio ficha---------------------
    if ((i[1]-(Dc)<-7 || i[1]-(Dc)<7) && tablero[Df-1][Dc-1]==1 && (tablero[Df-2][Dc-2]==3 || tablero[Df-2][Dc-2]==5) && i[6]==0 && tablero[i[0]-1][i[1]-1]==4)
    {
        correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[5]--;
            i[7]=Df-2;
            i[8]=Dc-2;
            i[9]=1;
            i[10]=1;
            cout << "\t\t\t\t Movimiento permitido comiste ficha " << endl;
    }

//---------------------- Validacion Negras---------------------------------------
    if ((i[1]-(Dc)==-1 || i[1]-(Dc)==1) && tablero[Df-1][Dc-1]==1 && i[6]==1)
        {
        if (Df-i[0]==-1)
            {
            cout << "\t\t\t\t Movimiento permitido " << endl;
            correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[9]=0;
            i[10]=0;
            }
            else
            {
            cout << "\t\t\t\t Solo puedes ir hacia adelante " << endl;
            }
        }
    else{
        cout << "\t\t\t\t Solo puedes mover en diagonal o la casilla esta ocupada " << endl;
        }
//-------------------------------Validacion Ficha negra doble salto---------------------------------------
    if ((i[1]-(Dc)==-2 || i[1]-(Dc)==2) && tablero[Df-1][Dc-1]==1 && (tablero[Df][Dc]==2 || tablero[Df][Dc]==4) && i[6]==1)
        {
        if (Df-i[0]==-2)
            {
            correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[5]--;
            i[7]=Df;
            i[8]=Dc;
            i[9]=1;
            i[10]=0;
            cout << "\t\t\t\t Movimiento permitido comiste ficha " << endl;

            }
            else
            {
            cout << "\t\t\t\t Solo puedes ir hacia adelante " << endl;
            }
        }
    else{
        cout << "\t\t\t\t Solo puedes mover en diagonal o la casilla esta ocupada con una ficha tuya " << endl;
        }
//-------------------------------------Validacion Dama Negra -----------------
    if ((i[1]-(Dc)<-7 || i[1]-(Dc)<7) && tablero[Df-1][Dc-1]==1 && i[6]==1 && tablero[i[0]-1][i[1]-1]==5)
    {
        cout << "\t\t\t\t Movimiento permitido " << endl;
            correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[9]=0;
            i[10]=1;
    }
//------------------------------------Validacion Dama Negra Multisalto comiendo
    if ((i[1]-(Dc)<-7 || i[1]-(Dc)<7) && tablero[Df-1][Dc-1]==1 && (tablero[Df][Dc]==2 || tablero[Df][Dc]==4) && i[6]==1 && tablero[i[0]-1][i[1]-1]==5)
    {
        correcto=false;
            i[2]=Df-1;
            i[3]=Dc-1;
            i[5]--;
            i[7]=Df;
            i[8]=Dc;
            i[9]=1;
            i[10]=1;
            cout << "\t\t\t\t Movimiento permitido comiste ficha " << endl;
    }

    } while(correcto);
    return i;
}

vector<int> Val_Mov_Ini(int tablero[8][8], vector<int> &i)
{
    int Of,Oc;
    bool correcto=true;
    do{
    if (i[6]==0)
    cout<<"\t\t\t              Fichas Blancas  : ";

    if (i[6]==1)
    cout<<"\t\t\t              Fichas Negras  : ";

    cout<<"\n\t\t\t            Ingrese fila de origen  : ";
    cin>>Of;
    cout<<"\t\t\t              Ingrese columna de origen  : ";
    cin>>Oc;


        if (i[6]==0 && (tablero[Of-1][Oc-1]==2 || tablero[Of-1][Oc-1]==4))
            {
                cout << "\t\t\t\t si tienes ficha en la casilla " << endl;
                correcto= false;
                i[0]=Of;
                i[1]=Oc;
            }
            else{
                cout << "\t\t\t\t no tienes ficha en la casilla " << endl;
            }
        if (i[6]==1 && (tablero[Of-1][Oc-1]==3 || tablero[Of-1][Oc-1]==5))
            {
                cout << "\t\t\t\t si tienes ficha en la casilla " << endl;
                correcto= false;
                i[0]=Of;
                i[1]=Oc;
            }
            else{
                cout << "\t\t\t\t no tienes ficha en la casilla " << endl;
            }
    }while(correcto);
   return i;
}

bool Val_Win(int tablero[8][8], int blancas, int negras)
{
    int R=0;
    int S=0;

    if (negras == 0 )
    {
        cout << "\t\t\t\t Gana blancas " << endl;
        return false;
    }

    if (blancas == 0)
    {
        cout << "\t\t\t\t Gana negras " << endl;
        return false;
    }

     for(int i; i < 8; i++)
         for(int j; j < 8; j++)
     {
         if(tablero[i][j]==4){R++;}
         if(tablero[i][j]==5){S++;}
     }

     if(R>=3 && S==1){return false;}
      if(S>=3 && R==1){return false;}


     return true;
}

void tablero(int tablero[8][8])
{
int trazarFilas, trazarCol;

cout << "\t\t\t\t JUEGO DE DAMAS ESPAÑOLAS " << endl;
cout << "\n\t\t\t\t B = Piezas Blancas";
cout << "\n\t\t\t\t N = Piezas Negras";
cout << "\n\t\t\t\t R = Dama Blanca";
cout << "\n\t\t\t\t S = Dama Negra";
cout << "\n\t\t\t\t - = Espacios Disponibles";
cout << "\n\n\t\t\t\t +---+---+---+---+---+---+---+---+\n";
for (trazarFilas = 0; trazarFilas < 8; ++trazarFilas)
{
    cout << "\t\t\t\t" << trazarFilas + 1 << " | "; // Identifica las filas en el tablero
    for (trazarCol = 0; trazarCol < 8; ++trazarCol)
    {
        cout << piezas(tablero[trazarFilas][trazarCol]) << " | ";//Llena las piezas en el tablero
    }
    cout << "\n";
    cout << "\t\t\t\t +---+---+---+---+---+---+---+---+\n";
}
cout << "\n\t\t\t \t   1   2   3   4   5   6   7  8\n\n";//Identifica las colunmnas en el tablero
}
char piezas(int p)//Piezas para el tablero
{
switch (p)
{
    case 0:
    return ' ';
    case 1:
    return '-';
    case 2:
    return 'B';
    case 3:
    return 'N';
    case 4:
    return 'R';
    case 5:
    return 'S';
}
return ('?');
}
