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
            cout << nip;
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
            validar_saldo(cantidad);
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
        
        int recibir_transferencia(int cantidad, string email)
        {
            saldo += cantidad;
            
            string movimiento = "Recibida transferencia de: " + email + ", por la cantidad de: " + to_string(cantidad);
            actualizar_historial(movimiento);
            
            return saldo;
        }
};

map<string, Usuario> usuarios_map;
string sesion_email = "";

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

void transferir_saldo() {
    int cantidad;
    string email;
    
    cout << "Ingrese email a quien quiere transfeir: " << endl;
    cin >> email;
    
    bool existe_usuario = validar_usuario(email);
    if(!existe_usuario || email == sesion_email) {
        cout << "Ingrese un email de usuario existente y que no sea el usuario activo." << endl;
        return;
    }
    
    cout << "Ingrese la cantidad a transferir: " << endl;
    cin >> cantidad;
    
    bool saldo_suficiente = usuarios_map[sesion_email].validar_saldo(cantidad);
    if(!saldo_suficiente) {
        cout << "Saldo insuficiente." << endl;
        return;
    }
    
    usuarios_map[email].recibir_transferencia(cantidad, email);
    usuarios_map[sesion_email].transferencia(cantidad, email);
    
    cout << "Se ha transferido la cantidad: " << to_string(cantidad) << ", para " << email << endl;
}

void menu_cajero() 
{
    int opc = 0;
    
    while (opc != 7)
    {
        cout << endl;
        cout << "MENU DE OPERACIONES" << endl;
        cout << "1. Deposito" << endl;
        cout << "2. Retiro" << endl;
        cout << "3. Cambio de nip" << endl;
        cout << "4. Consulta de saldo" << endl;
        cout << "5. Transferencia" << endl;
        cout << "6. historial ultimos 5 movimientos" << endl;
        cout << "7. Salir" << endl;
        cout << endl;
        cout << "Eliga una opcion: " << endl;
        cin >> opc;
        cout << " " << endl;
        
        if(opc == 1) {
            int cantidad;
            cout << "Ingrese la cantidad a depositar: ";
            cin >> cantidad;
            if (cantidad > 0)
            {
                usuarios_map[sesion_email].deposito(cantidad);
            }
            else 
            {
                cout << endl;
                cout << "Valor no valido" << endl;
            }
            
        }
        else if(opc == 2) {
            int cantidad;
            cout << "Ingrese la cantidad a retirar: ";
            cin >> cantidad;
            if (usuarios_map[sesion_email].validar_saldo(cantidad))
            {
                
                usuarios_map[sesion_email].retiro(cantidad);
            }
            else 
            {
                cout << endl;
                cout << "Saldo insuficiente" << endl;
            }
            
        }
        else if(opc == 3) {
            int nuevo_nip;
            cout << "Ingrese el nuevo NIP: ";
            cin >> nuevo_nip;
            usuarios_map[sesion_email].cambiar_nip(nuevo_nip);
        }
        else if(opc == 4) {
            usuarios_map[sesion_email].consulta_saldo();
        }
        else if(opc == 5) {
            transferir_saldo();
        }
        else if(opc == 6) {
            usuarios_map[sesion_email].imprimir_movimientos();
        }
    }
}

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
                menu_cajero();
            }
        }
        if(op == 2){
            registrar_usuario();
        }
    }
    
    cout << "Cajero Cerrado" << endl;
    return 0;
}



