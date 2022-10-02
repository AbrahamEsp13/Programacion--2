#include <iostream>
#include <string>
#include <map>
#include <bits/stdc++.h>

using namespace std;

string sesion_email = "";

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
            cout << "Ingrese el nuevo nip: " << endl;
            cin >> nuevo_nip;
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

void registrar_usuario()
{
    Usuario nuevo_usuario;
    
    cout << "Ingrese su correo: " << endl;
    cin >> nuevo_usuario.email;
    cout << "Ingrese nombre: " << endl;
    cin >> nuevo_usuario.nombre;
    cout << "Ingrese su nip: " << endl;
    cin >> nuevo_usuario.nip;
    
    usuarios_map.insert({nuevo_usuario.email, nuevo_usuario});
}

bool validar_usuario(string email) 
{
    return usuarios_map.count(email) == 1;
}

bool ingresar() 
{
    string email;
    int nip;
    
    cout << "Ingrese email: " << endl;
    cin >> email;
    
    if (!validar_usuario(email)) {
        cout << "Usuario no existe, ingrese un usuario valido." << endl;
        return false;
    }
    
    cout << "Ingrese NIP: " << endl;
    cin >> nip;
    
    if (usuarios_map[email].nip != nip) {
        cout << "No coinciden el NIP del usuario." << endl;
        return false;
    }
    
    sesion_email = email;
    
    return true;
}

void menu_cajero() 
{
    system("clear");
    cout << "MENU DE OPERACIONES" << endl;
    cout << "1. Deposito" << endl;
    cout << "2. Retiro" << endl;
    cout << "3. Cambio de nip" << endl;
    cout << "4. Consulta de saldo" << endl;
    cout << "5. Transferencia" << endl;
    cout << "6. historial ultimos 5 movimientos" << endl;
    cout << "7. Salir" << endl;
}
int opc;
int main()
{
    int op = 0;
    string email;
    
    while (op != 3) 
    {   
        system("clear");
        cout << "Ingrese una opcion: " << endl;
        cout << "1 - Ingresar" << endl;
        cout << "2 - Registrar Nuevo Usuario" << endl;
        cout << "3 - Salir" << endl;
        cin >> op;
        
        if(op == 1) {
            bool credenciales_correctas = ingresar();
            if(credenciales_correctas) {
                
                email = sesion_email;
                while (opc != 7)
                {
                    system("clear");
                    menu_cajero();
                    cout << "Eliga una opcion: " << endl;
                    cin >> opc;
                
                    if(opc == 1){
                        usuarios_map[email].deposito(200);
                    }
                    if(opc == 2){
                        usuarios_map[email].retiro(200);
                    }
                    if(opc == 3){
                        usuarios_map[email].cambiar_nip(200);
                    }
                    if(opc == 4){
                        usuarios_map[email].consulta_saldo(200);
                    }
                    if(opc == 5){
                        usuarios_map[email].transferencia(200);
                    }
                    if(opc == 6){
                        usuarios_map[email].imprimir_movimientos(200);
                    }
                }
                
            }
            
        }
        if(op == 2){
            registrar_usuario();
        }
    }
    
    return 0;
}