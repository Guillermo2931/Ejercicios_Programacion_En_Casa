#include <iostream>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
    //Verificamos que el usuario haya enviado correctamente los parametros
    if (argc != 5) {
        cout << "Error en el paso de parametros" << endl;
        cout << "Forma adecuada:" << argv[0] << " <a> <b> <c> <d>" << endl;
        return 1;
    }
    //r1,r2 y r3 almacenaran los resultados de las operaciones en el metodo de Ruffini. inc es el incremento que daremos dependiendo de si es positivo o negativo el número a operar
    //i es el apuntador de los for y ra1 y ra2 almacenaran las distintas raices para evitar  repetirlas
    int r1,r2,r3,inc,i,ra1=0,ra2=0;
    //Asignamos los valores del polinomio que se recibio como argumento
    int a=atoi(argv[1]);
    int b=atoi(argv[2]);
    int c=atoi(argv[3]);
    int d=atoi(argv[4]);
    cout<<"{";
    //Verificamos si d es negativo o positivo para asignar el incremento
    if(d>0){
        inc=1;
    }
    else{
        inc=-1;
    }
    //Iniciamos el recorrido por todos los numeros que estan entre -d y d buscando los divisores
    for(i=(-1*d);i!=d+inc;i=i+inc){
        if (i!=0){
                //Verifica si i es divisor de d
            if (d%i==0){
                //Realiza el metodo de Ruffini
                r1=b+a*i;
                r2=c+i*r1;
                r3=d+i*r2;
                if (r3==0){
                    cout<<i;
                    ra1=i;
                    break;
                }
            }
        }
    }
    //Guarda los valores de los resultados anteriores en nuevas variables para poder trabajar
    int aux=r2;
    int b2=r1;
    int c2=r2;
    //Repetimos el proceso anterior
    if(aux>0){
        inc=1;
    }
    else{
        inc=-1;
    }
    for(i=(-1*aux);i!=aux+inc;i=i+inc){
        if (i!=0){
            if (d%i==0){
                    //Realizamos el metodo de Riffini pero con una operacion menos
                r1=b2+a*i;
                r2=c2+i*r1;
                //Verificamos que no se repita
                if (r2==0 && i!=ra1){
                    cout<<","<<i;
                    ra2=i;
                    break;
                }
            }
        }
    }
    //Repetimos lo anterior para terminar de buscar las raices
    aux=r1;
    int b3=r1;
    if(aux>0){
        inc=1;
    }
    else{
        inc=-1;
    }
    for(i=(-1*aux);i!=aux+inc;i=i+inc){
        if (i!=0){
            if (d%i==0){
                r1=b3+a*i;
                if (r1==0 && i!=ra1&& i!=ra2){
                    cout<<","<<i;
                    break;
                }
            }
        }
    }
    cout<<"}";
}
