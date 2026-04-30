#include <iostream>
#include <vector>
#include <memory>
#include <cctype>
#include <limits>
#include <stdexcept>

using namespace std;

// INTERFACES 

class Mostrable //Cualquier clase que herede de aquí debe poder mostrarse
{
public:
    virtual void mostrar() = 0; //función virtual pura, permite polimorfismos
    virtual ~Mostrable(){} //destructor virtual
};

class Identificable //Obliga a que cualquier clase que herede de aquí tenga un ID y pueda devolverlo.
{
public:
    virtual string getID() = 0; //funcion virtual pura
    virtual ~Identificable(){} // destructor virtual
};

// VALIDACION 

bool esNumero(const string &str) //Verifica si un texto contiene solo números, evita copiar string
{
    if(str.empty()) return false; // si esta vacio no es numero

    for(char c : str) //Recorre cada carácter del string
        if(!isdigit(c)) return false; //Si alguno caracter no es numero es falso

    return true; // si todos son numeros es valido el programa
}

string pedirID()
{
    string id;

    while(true)
    {
        cout<<"Ingrese ID numerico: ";
        cin>>id;

        if(esNumero(id)) return id;

        throw invalid_argument("Error: solo numeros permitidos"); //excepcion si el ID es invalido
    }
}

// TEMPLATE // clase generica que guarda objetos en un vector

template<class T> // no repites codigo
class Repositorio
{
private:
    vector<T> datos; // crea vector

public:

    void agregar(T obj)
    {
        datos.push_back(obj); // agrega un elemento al vector
    }

    vector<T>& obtener() // pasa por referecia el vector
    {
        return datos;
    }

    bool estaVacio() // Verifica si no hay elementos
    {
        return datos.empty();
    }
};

// PERSONA 

class Persona : public Mostrable, public Identificable //herencia multiple, hereda de dos clases
{
private:

    string id;
    string nombre;
    string cedula;
    string telefono;
    string direccion;

public:

    Persona(string id,string nombre,string cedula,string telefono,string direccion) //inicializa objeto cuando se crea
    {
        this->id=id;
        this->nombre=nombre;
        this->cedula=cedula;
        this->telefono=telefono;
        this->direccion=direccion;
    }

    string getID() override //devuelve id
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    void mostrar() override //polimorfismo
    {
        cout<<"ID: "<<id
            <<" | Nombre: "<<nombre
            <<" | Cedula: "<<cedula
            <<" | Telefono: "<<telefono
            <<" | Direccion: "<<direccion
            <<endl;
    }
    
    // GETTERS 
string getCedula() //Devuelven datos privados, encapsulamiento
{
    return cedula;
}

string getTelefono()
{
    return telefono;
}

string getDireccion()
{
    return direccion;
}

// SETTERS
void setNombre(string nombre) //metodos para modificar datos
{
    this->nombre = nombre;
}

void setCedula(string cedula)
{
    this->cedula = cedula;
}

void setTelefono(string telefono)
{
    this->telefono = telefono;
}

void setDireccion(string direccion)
{
    this->direccion = direccion;
}
};

// ANIMAL ABSTRACTO 

class Animal : public Mostrable, public Identificable //herencia multiple
{
protected:

    string id;
    string nombre;
    string raza;
    float peso;
    int edadAnios;
    int edadMeses;

public:

    Animal(string id,string nombre,string raza,float peso,int edadAnios,int edadMeses)
    {
        this->id=id;
        this->nombre=nombre;
        this->raza=raza;
        this->peso=peso;
        this->edadAnios=edadAnios;
        this->edadMeses=edadMeses;
    }

    string getID() override //polimorfismo
    {
        return id;
    }

    string getNombre() //encapsulamiento
    {
        return nombre;
    }

    virtual void mostrar() = 0; // Animal no tiene implementacion de mostrar

    virtual ~Animal(){} // destructor virtual
    // GETTERS 
string getRaza() //Devuelve raza
{
    return raza;
}

float getPeso()
{
    return peso;
}

int getEdadAnios()
{
    return edadAnios;
}

int getEdadMeses()
{
    return edadMeses;
}

//  SETTERS 
void setNombre(string nombre) // Modifican atributos
{
    this->nombre = nombre;
}

void setRaza(string raza)
{
    this->raza = raza;
}

void setPeso(float peso)
{
    this->peso = peso;
}

void setEdadAnios(int anios)
{
    this->edadAnios = anios;
}

void setEdadMeses(int meses)
{
    this->edadMeses = meses;
}
};

// PERRO 

class Perro : public Animal //herencia simple, hereda de animal
{
public:

    Perro(string id,string nombre,string raza,float peso,int anios,int meses)
    : Animal(id,nombre,raza,peso,anios,meses){} //llama al constructor de animal

    void mostrar() override //implementa al método que animal dejo pendiente
    {
        cout<<"[Perro] ID: "<<id
            <<" | Nombre: "<<nombre
            <<" | Raza: "<<raza
            <<" | Peso: "<<peso<<" kg"
            <<" | Edad: "<<edadAnios<<" anios "<<edadMeses<<" meses"
            <<endl;
    }
};

// GATO 

class Gato : public Animal // hereda de animal
{
public:

    Gato(string id,string nombre,string raza,float peso,int anios,int meses)
    : Animal(id,nombre,raza,peso,anios,meses){} // llama al constructor de animal

    void mostrar() override // define como se muestra gato
    {
        cout<<"[Gato] ID: "<<id
            <<" | Nombre: "<<nombre
            <<" | Raza: "<<raza
            <<" | Peso: "<<peso<<" kg"
            <<" | Edad: "<<edadAnios<<" anios "<<edadMeses<<" meses"
            <<endl;
    }
};

// SISTEMA REFUGIO 

class SistemaRefugio //clase que controla todo el sistema
{
private:

    Repositorio<Persona> personas; // guarda todas las personas
    vector<shared_ptr<Animal>> animales; // guarda todos los animales

public:

    SistemaRefugio()
    {
        cargarAnimalesIniciales();
    }

// DATOS INICIALES para simular un sistema de refugio, decidimos poner algunos animales que ya son parte del refugio para poder utilizar esos datos para adopciones, modificacion o eliminaciones

    void cargarAnimalesIniciales()
    {
        animales.push_back(make_shared<Perro>("1","Max","Labrador",20,2,3));
        animales.push_back(make_shared<Gato>("2","Luna","Siames",4,1,6));
        animales.push_back(make_shared<Perro>("3","Rocky","Bulldog",18,3,2));
        animales.push_back(make_shared<Gato>("4","Milo","Persa",5,2,1));
        animales.push_back(make_shared<Perro>("5","Toby","Beagle",10,1,4));
    }

//  PERSONAS CRUD 

    void registrarPersona() // C = Create
    {
        try
        {
            string id=pedirID();

            string nombre,cedula,telefono,direccion;

            cout<<"Nombre: ";
            cin>>nombre;

            cout<<"Cedula: ";
            cin>>cedula;

            cout<<"Telefono: ";
            cin>>telefono;

            cout<<"Direccion: ";
            cin>>direccion;

            personas.agregar(Persona(id,nombre,cedula,telefono,direccion));

            cout<<"Persona registrada correctamente\n";
        }
        catch(const exception &e)
        {
            cout<<e.what()<<endl;
        }
    }

    void listarPersonas() // R = Read
    {
        if(personas.estaVacio())
        {
            cout<<"No hay personas registradas\n";
            return;
        }

        for(auto &p:personas.obtener())
            p.mostrar();
    }

    void modificarPersona() // U = Update
    {
        string id;

        cout<<"ID persona a modificar: ";
        cin>>id;

        for(auto &p:personas.obtener())
        {
            if(p.getID()==id)
            {
                string nombre,cedula,telefono,direccion;

                cout<<"Nuevo nombre: ";
                cin>>nombre;

                cout<<"Nueva cedula: ";
                cin>>cedula;

                cout<<"Nuevo telefono: ";
                cin>>telefono;

                cout<<"Nueva direccion: ";
                cin>>direccion;

                p=Persona(id,nombre,cedula,telefono,direccion);

                cout<<"Persona modificada correctamente\n";
                return;
            }
        }

        throw runtime_error("Persona no encontrada");
    }

    void eliminarPersona() // D = Delete
    {
        string id;

        cout<<"ID persona a eliminar: ";
        cin>>id;

        auto &lista=personas.obtener();

        for(int i=0;i<lista.size();i++)
        {
            if(lista[i].getID()==id)
            {
                lista.erase(lista.begin()+i);

                cout<<"Persona eliminada correctamente\n";
                return;
            }
        }

        throw runtime_error("Persona no encontrada");
    }

// ANIMALES CRUD 

    void registrarAnimal() // C = Create
    {
        try
        {
            string tipo;

            cout<<"Tipo (perro/gato): ";
            cin>>tipo;

            string id=pedirID();

            string nombre,raza;
            float peso;
            int anios,meses;

            cout<<"Nombre: ";
            cin>>nombre;

            cout<<"Raza: ";
            cin>>raza;

            cout<<"Peso kg: ";
            cin>>peso;

            cout<<"Edad anios: ";
            cin>>anios;

            cout<<"Edad meses: ";
            cin>>meses;

            if(tipo=="perro")
            {
                animales.push_back(make_shared<Perro>(id,nombre,raza,peso,anios,meses));
                cout<<"Perro agregado correctamente\n";
            }

            else if(tipo=="gato")
            {
                animales.push_back(make_shared<Gato>(id,nombre,raza,peso,anios,meses));
                cout<<"Gato agregado correctamente\n";
            }

            else
                throw invalid_argument("Tipo invalido");
        }
        catch(const exception &e)
        {
            cout<<e.what()<<endl;
        }
    }

    void listarAnimales() // R = Read
    {
        if(animales.empty())
        {
            cout<<"No hay animales disponibles\n";
            return;
        }

        for(auto &a:animales)
            a->mostrar();
    }

    void modificarAnimal() // U = Update
    {
        string id;

        cout<<"ID animal a modificar: ";
        cin>>id;

        for(int i=0;i<animales.size();i++)
        {
            if(animales[i]->getID()==id)
            {
                string nombre,raza;
                float peso;
                int anios,meses;

                cout<<"Nuevo nombre: ";
                cin>>nombre;

                cout<<"Nueva raza: ";
                cin>>raza;

                cout<<"Nuevo peso: ";
                cin>>peso;

                cout<<"Edad anios: ";
                cin>>anios;

                cout<<"Edad meses: ";
                cin>>meses;

                if(dynamic_pointer_cast<Perro>(animales[i]))
                    animales[i]=make_shared<Perro>(id,nombre,raza,peso,anios,meses);

                else
                    animales[i]=make_shared<Gato>(id,nombre,raza,peso,anios,meses);

                cout<<"Animal modificado correctamente\n";
                return;
            }
        }

        throw runtime_error("Animal no encontrado");
    }

    void eliminarAnimal() // D = Delete
    {
        string id;

        cout<<"ID animal a eliminar: ";
        cin>>id;

        for(int i=0;i<animales.size();i++)
        {
            if(animales[i]->getID()==id)
            {
                animales.erase(animales.begin()+i);

                cout<<"Animal eliminado correctamente\n";
                return;
            }
        }

        throw runtime_error("Animal no encontrado");
    }

//  ADOPCION 

    void adoptarAnimal() //Permite que una persona adopte un animal y lo elimina del sistema
    {
        try
        {
            if(personas.estaVacio()) // No hay como adoptar si no hay personas registradas
                throw runtime_error("Debe registrar personas primero");

            listarPersonas();

            string idPersona;

            cout<<"ID persona: ";
            cin>>idPersona;

            Persona *adoptante=nullptr; //Puntero

            for(auto &p:personas.obtener()) // Busca persona por ID
                if(p.getID()==idPersona)
                    adoptante=&p;

            if(!adoptante)
                throw runtime_error("Persona no encontrada"); // Si no hay persona, lanza error

            listarAnimales();

            string idAnimal;

            cout<<"ID animal: ";
            cin>>idAnimal;

            for(int i=0;i<animales.size();i++)
            {
                if(animales[i]->getID()==idAnimal) 
                {
                    cout<<adoptante->getNombre()
                        <<" adopto con exito a "
                        <<animales[i]->getNombre()
                        <<endl; // muestra la adopcion

                    animales.erase(animales.begin()+i); // borra animal del vector

                    cout<<"Animal eliminado correctamente\n";

                    return;
                }
            }

            throw runtime_error("Animal no encontrado"); // si encuentra el animal que pediste
        }
        catch(const exception &e)
        {
            cout<<e.what()<<endl;
        }
    }
}; // Maneja errores sin que el programa se rompa, se utiliza manejo de excepciones para controlar errores de forma segura

// MAIN 

int main()
{
    SistemaRefugio sistema;

    int opcion;

    do
    {
        try
        {
            cout<<"\n===== SISTEMA REFUGIO =====\n";
            cout<<"1 Registrar persona\n";
            cout<<"2 Listar personas\n";
            cout<<"3 Registrar animal\n";
            cout<<"4 Listar animales\n";
            cout<<"5 Adoptar animal\n";
            cout<<"6 Modificar persona\n";
            cout<<"7 Eliminar persona\n";
            cout<<"8 Modificar animal\n";
            cout<<"9 Eliminar animal\n";
            cout<<"10 Salir\n";

            cin>>opcion;

            switch(opcion)
            {
                case 1: sistema.registrarPersona(); break;
                case 2: sistema.listarPersonas(); break;
                case 3: sistema.registrarAnimal(); break;
                case 4: sistema.listarAnimales(); break;
                case 5: sistema.adoptarAnimal(); break;
                case 6: sistema.modificarPersona(); break;
                case 7: sistema.eliminarPersona(); break;
                case 8: sistema.modificarAnimal(); break;
                case 9: sistema.eliminarAnimal(); break;
                case 10: cout<<"Saliendo...\n"; break;
                default: cout<<"Opcion invalida\n";
            }
        }
        catch(const exception &e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }

    }
    while(opcion!=10);

    return 0;
}
