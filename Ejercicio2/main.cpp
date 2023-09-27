#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
//Declaramos todo lo que se va a usar
using std::cout; 
using std::cin;
using std::endl; 
using std::ifstream;
using std::ofstream;
using std::fstream; 
using std::string;

int main(int argc, char * argv[]) {
    //Tomamos la direccion que proporciona el usuario al llamar el .exe
    string a_carpeta=argv[1];
    //Agregamos un "/" al final para un buen funcionamiento
    a_carpeta.append("/");
    //Creamos el nombre del archivo json
    string nombreArchivo = "dir.json";
    //Creamos nuestra variable para el archivo
    ofstream archivo;
    //Para este caso vamos a apoyarnos de las herramientas nativas de windows para buscar archivos, por lo que creamos nuestro FIND_DATA
    WIN32_FIND_DATA ffd{};
    //COntador que nos va a indicar si es el primer archivo que escribiremos en el json
    int conta=0;
    //Empezamos a escribir el json
    string cadena="{ \"files\": [";
    //Abrimos nuestro archivo para escritura
    archivo.open(nombreArchivo.c_str(), fstream::out);
    //Escribimos el inicio del json en el archivo
    archivo << cadena;
    //Empezamos la busqueda de archivos en el directorio verificando que exista la carpeta y obtenemos todos sus archivos
    if (auto handle = FindFirstFile((a_carpeta + "/*.*").c_str(), &ffd))
    {
        //Vamos a recorrer la lista de archivos hasta el final
        do
        {
            //Se comprueba que no sea una carpeta para poder obtener el tamaño y escribirlo en el json
            if(!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
                //Verificamos que no sea el primer archivo que se va a agregar al json para poder poner una ",", en caso de que lo sea cambiamos el contador
                if (conta!=0){
                archivo<<",";
                }
                else{
                    conta=1;
                }
                //damos un salto de linea en el json y posteriormente escribirmos la estructura deseado
                archivo << endl;
                archivo << "{\"name\":\"";
                //Escribimos el nombre del archivo en el json
                archivo << ffd.cFileName;
                archivo << "\",\"size\":";
                //Con esto obtenemos el tamano del archivo en la ruta que se proporciono y se escribe en el json
                archivo << std::filesystem::file_size(a_carpeta+ffd.cFileName);
                archivo <<"}";
            }
            
        }
        //Busca si aun hay un archivo siguiente
        while (FindNextFile(handle, &ffd) != 0);
    }//Finalizamos la escritura y cerramos
    archivo << "]}";
    archivo.close();
}
