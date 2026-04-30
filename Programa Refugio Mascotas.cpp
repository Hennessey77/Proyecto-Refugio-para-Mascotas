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

template<class T>
class Repositorio
{
private:
    vector<T> datos;

public:

    void agregar(T obj)
    {
        datos.push_back(obj);
    }

    vector<T>& obtener()
    {
        return datos;
    }

    bool estaVacio()
    {
        return datos.empty();
    }
};

// ================= PERSONA =================

class Persona : public Mostrable, public Identificable
{
private:

    string id;
    string nombre;
    string cedula;
    string telefono;
    string direccion;

public:

    Persona(string id,string nombre,string cedula,string telefono,string direccion)
    {
        this->id=id;
        this->nombre=nombre;
        this->cedula=cedula;
        this->telefono=telefono;
        this->direccion=direccion;
    }

    string getID() override
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    void mostrar() override
    {
        cout<<"ID: "<<id
            <<" | Nombre: "<<nombre
            <<" | Cedula: "<<cedula
            <<" | Telefono: "<<telefono
            <<" | Direccion: "<<direccion
            <<endl;
    }
    
    // ===== GETTERS =====
string getCedula()
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

// ===== SETTERS =====
void setNombre(string nombre)
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

// ================= ANIMAL ABSTRACTO =================

class Animal : public Mostrable, public Identificable
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

    string getID() override
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    virtual void mostrar() = 0;

    virtual ~Animal(){}
    // ===== GETTERS =====
string getRaza()
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

// ===== SETTERS =====
void setNombre(string nombre)
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

// ================= PERRO =================

class Perro : public Animal
{
public:

    Perro(string id,string nombre,string raza,float peso,int anios,int meses)
    : Animal(id,nombre,raza,peso,anios,meses){}

    void mostrar() override
    {
        cout<<"[Perro] ID: "<<id
            <<" | Nombre: "<<nombre
            <<" | Raza: "<<raza
            <<" | Peso: "<<peso<<" kg"
            <<" | Edad: "<<edadAnios<<" anios "<<edadMeses<<" meses"
            <<endl;
    }
};

// ================= GATO =================

class Gato : public Animal
{
public:

    Gato(string id,string nombre,string raza,float peso,int anios,int meses)
    : Animal(id,nombre,raza,peso,anios,meses){}

    void mostrar() override
    {
        cout<<"[Gato] ID: "<<id
            <<" | Nombre: "<<nombre
            <<" | Raza: "<<raza
            <<" | Peso: "<<peso<<" kg"
            <<" | Edad: "<<edadAnios<<" anios "<<edadMeses<<" meses"
            <<endl;
    }
};

// ================= SISTEMA =================

class SistemaRefugio
{
private:

    Repositorio<Persona> personas;
    vector<shared_ptr<Animal>> animales;

public:

    SistemaRefugio()
    {
        cargarAnimalesIniciales();
    }

// ================= DATOS INICIALES =================

    void cargarAnimalesIniciales()
    {
        animales.push_back(make_shared<Perro>("1","Max","Labrador",20,2,3));
        animales.push_back(make_shared<Gato>("2","Luna","Siames",4,1,6));
        animales.push_back(make_shared<Perro>("3","Rocky","Bulldog",18,3,2));
        animales.push_back(make_shared<Gato>("4","Milo","Persa",5,2,1));
        animales.push_back(make_shared<Perro>("5","Toby","Beagle",10,1,4));
    }

// ================= PERSONAS CRUD =================

    void registrarPersona()
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

    void listarPersonas()
    {
        if(personas.estaVacio())
        {
            cout<<"No hay personas registradas\n";
            return;
        }

        for(auto &p:personas.obtener())
            p.mostrar();
    }

    void modificarPersona()
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

    void eliminarPersona()
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

// ================= ANIMALES CRUD =================

    void registrarAnimal()
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

    void listarAnimales()
    {
        if(animales.empty())
        {
            cout<<"No hay animales disponibles\n";
            return;
        }

        for(auto &a:animales)
            a->mostrar();
    }

    void modificarAnimal()
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

    void eliminarAnimal()
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

// ================= ADOPCION =================

    void adoptarAnimal()
    {
        try
        {
            if(personas.estaVacio())
                throw runtime_error("Debe registrar personas primero");

            listarPersonas();

            string idPersona;

            cout<<"ID persona: ";
            cin>>idPersona;

            Persona *adoptante=nullptr;

            for(auto &p:personas.obtener())
                if(p.getID()==idPersona)
                    adoptante=&p;

            if(!adoptante)
                throw runtime_error("Persona no encontrada");

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
                        <<endl;

                    animales.erase(animales.begin()+i);

                    cout<<"Animal eliminado correctamente\n";

                    return;
                }
            }

            throw runtime_error("Animal no encontrado");
        }
        catch(const exception &e)
        {
            cout<<e.what()<<endl;
        }
    }
};

// ================= MAIN =================

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
