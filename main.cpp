#include <iostream>
#include <string>
#include <map>

using namespace std;

class Usuario
{
    private:
        int saldo = 0;
        int indice_movimiento = 0;
        string movimientos[5] = {"", "", "", "", ""};
        
        void actualizar_historial(string nuevo_movimiento)
        {
            movimientos[indice_movimiento] = nuevo_movimiento;
            indice_movimiento += 1;
            
            if (indice_movimiento == 5)
            {
                indice_movimiento = 0;
            }
        }
        
    public: 
        string email;
        string nombre;
        int nip;
        
        void cambiar_nip(int nuevo_nip) 
        {
            nip = nuevo_nip;
            actualizar_historial("Cambio de NIP.");
        }
        
        int deposito(int cantidad)
        {
            saldo += cantidad;
            
            string movimiento = "Deposito por la cantidad de: " + to_string(cantidad);
            actualizar_historial(movimiento);
            
            return saldo;
        }
        
        int retiro(int cantidad)
        {
            saldo -= cantidad;
            
            string movimiento = "Retiro por la cantidad de: " + to_string(cantidad);
            actualizar_historial(movimiento);
            
            return saldo;
        }
        
        bool validar_saldo(int cantidad)
        {
            return saldo >= cantidad;
        }
        
        void consulta_saldo()
        {
            cout << "Su saldo es: " << saldo << endl;
            
            actualizar_historial("Consulta de saldo");
        }
        
        void imprimir_movimientos()
        {
            for(int i = indice_movimiento; i < 5; i++)
            {
                cout << movimientos[i] << endl;
            }
            
            for (int i = 0; i < indice_movimiento; i++)
            {
                cout << movimientos[i] << endl;
            }
        }
        
        int transferencia(int cantidad, string email)
        {
            saldo -= cantidad;
            
            string movimiento = "Transferencia para: " + email + " por la cantidad de: " + to_string(cantidad);
            actualizar_historial(movimiento);
            
            return saldo;
        }
};

map<string, Usuario> usuarios_map;

Usuario registrar_usuario()
{
    Usuario nuevo_usuario;
    
    cout << "Ingrese su correo: " << endl;
    cin >> nuevo_usuario.email;
    cout << "Ingrese nombre: " << endl;
    cin >> nuevo_usuario.nombre;
    cout << "Ingrese su nip: " << endl;
    cin >> nuevo_usuario.nip;
    
    usuarios_map.insert({nuevo_usuario.email, nuevo_usuario});
    
    return nuevo_usuario;
}

int main()
{
    
    
    
    return 0;
}