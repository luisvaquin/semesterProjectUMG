#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// llamada de funciones
void menuAcciones();
void mostrarRecursos();
void explorarPlaneta();
void repararNave();
void enviarSenales();
void eventoNocturno();
bool verificarCondiciones();

int combustible = 30;
int oxigeno = 50;
int suministros = 40;
int integridad_nave = 100;
int days = 0;

int main(){
    srand(time(0)); // Inicializador par time numeros randoms para rand xd
    cout << "||BIENVENIDO CAPITAN|| \n";
    mostrarRecursos();

    while(true) { // Estructura de juego
        menuAcciones();

        if(!verificarCondiciones()) {
            break;
        }
        eventoNocturno();
        mostrarRecursos();
        if(!verificarCondiciones()) {
            break;
        }
    }
    return 0;
}

void mostrarRecursos(){
    cout << "\nRecursos del jugador:" << endl;
    cout << "Combustible: " << combustible << " unidades" << endl;
    cout << "Oxigeno: " << oxigeno << " unidades" << endl;
    cout << "Suministros: " << suministros << " unidades" << endl;
    cout << "Integridad de la nave: " << integridad_nave << "%" << endl;
    cout << "Dia: " << days << "/10" << endl;
}

void explorarPlaneta(){
    cout << "Explorando planeta..." << endl;

    // Verificar si hay suficiente combustible
    if(combustible < 15) {
        cout << "No tienes suficiente combustible para explorar (necesitas 15 unidades)" << endl;
        return;
    }

    combustible -= 15; // Validacion de extraccion de combustible

    int oxigenoEncontrado = 20 + (rand() % 21);
    oxigeno += oxigenoEncontrado;
    cout << "Encontraste " << oxigenoEncontrado << " unidades de oxigeno." << endl;

    int combustibleEncontrado = 10 + (rand() % 21);
    combustible += combustibleEncontrado;
    cout << "Encontraste " << combustibleEncontrado << " unidades de combustible." << endl;

    int suministrosEncontrados = 30 + (rand() % 71);
    suministros += suministrosEncontrados;
    cout << "Encontraste " << suministrosEncontrados << " unidades de suministros." << endl;
    days++;
}

void repararNave(){
    cout << "Reparando nave..." << endl;

    // Verificar si la nave ya está al 100% SIUUU
    if(integridad_nave >= 100) {
        cout << "La nave ya esta en perfecto estado (100% integridad), no es necesario remplazar" << endl;
        return;
    }

    // Calcular cuánto se puede reparar como máximo
    int maxReparable = 100 - integridad_nave;
    int maxPosiblePorSuministros = suministros / 10;

    cout << "Integridad actual: " << integridad_nave << "%" << endl;
    cout << "Suministros disponibles: " << suministros << " unidades" << endl;
    cout << "Suministros necesarios para reparacion: " << maxPosiblePorSuministros << "%" << endl;

    int porcentajeReparar;
    cout << "¿Cuanto porcentaje deseas reparar?: ";
    cin >> porcentajeReparar;

    if(porcentajeReparar < 0) {
        cout << "No puedes ingresar un porcentaje negativo." << endl;
        return;
    }

    int costoSuministros = porcentajeReparar * 10; //Calculo de costos de suministros

    if(costoSuministros > suministros) { // Verificar si hay suficientes suministros
        cout << "No tienes suficientes suministros para esta reparacion." << endl;
        cout << "Necesitas: " << costoSuministros << " unidades" << endl;
        return;
    }

    int integridadFinal = integridad_nave + porcentajeReparar; // Calcular la integridad final

    if(integridadFinal > 100) { // Verificar si excede el 100%
        cout << "ADVERTENCIA: La reparacion excederia el 100% de integridad." << endl;
        cout << "Se ajustara automaticamente para reparar solo hasta el 100%." << endl;

        // Ajustar valores
        porcentajeReparar = maxReparable;
        costoSuministros = porcentajeReparar * 10;
        integridadFinal = 100;
    }

    // Realizar la reparación
    suministros -= costoSuministros;
    integridad_nave = integridadFinal;

    cout << "Reparacion exitosa. Integridad: " << integridad_nave << "%" << endl;
    days++;
}

void enviarSenales(){
    cout << "Enviando senal..." << endl;
    int eventoAleatorio = rand() % 2; // 50% de probabilidad para cada evento 0 o 1 random xd

    if(eventoAleatorio == 0) {
        // Evento positivo: Ayuda con combustible
        combustible += 60;
        cout << "Recibiste 60 unidades de combustible." << endl;
    } else {
        // Evento negativo: Piratas espaciales xD
        integridad_nave -= 15;
        suministros -= 20;
        cout << "Piratas espaciales detectaron tu senal y atacaron." << endl;

        if(suministros < 0) {
            suministros = 0; // Evitar que los suministros sean negativos
        }
    }
    days++;
}

void eventoNocturno(){
    cout << "\nHa pasado la noche. Dia " << days << ". Consumo de recursos: Oxigeno -20, Suministros -30" << endl;

    oxigeno -= 20; // Consumo automático de recursos cada noche
    suministros -= 30;

    // Evitar valores negativos
    if(oxigeno < 0) oxigeno = 0;
    if(suministros < 0) suministros = 0;

    if((rand() % 100) < 15) { // 15% de probabilidad de que ocurra un evento nocturno
        cout << "\n--- EVENTO NOCTURNO ---" << endl;
        int tipoEvento = rand() % 3; //Tres posibles eventos (0, 1 o 2)

        if(tipoEvento == 0) {
            oxigeno -= 10;  // Tormenta cósmica
            cout << "Tormenta cosmica: Perdiste 10 unidades de oxigeno." << endl;

            if(oxigeno < 0) oxigeno = 0; //Validacion de oxigeno xd

        } else if(tipoEvento == 1) {
            cout << "Encuentro alienigena detectado..." << endl;
            int tipoAlien = rand() % 2;
            if(tipoAlien == 0) { // Amistoso
                combustible += 20;
                cout << "Los alienigenas fueron amistosos. Recibiste 20 unidades de combustible." << endl;
            } else {   // Hostil
                integridad_nave -= 10;
                cout << "Los alienigenas fueron hostiles. Perdiste 10% de integridad." << endl;
            }

        } else { // Meteoritos
            cout << "Campo de meteoritos detectado!" << endl;
            cout << "1. Maniobrar (gasta combustible)" << endl;
            cout << "2. Recibir el impacto (dana la nave)" << endl;
            cout << "Elige una opcion: ";

            int decision;
            cin >> decision;

            if(decision == 1) {
                // Maniobrar
                int combustibleGastado = 10 + (rand() % 21);
                combustible -= combustibleGastado;
                cout << "Maniobras evasivas. Gastaste " << combustibleGastado << " unidades de combustible." << endl;
                if(combustible < 0) combustible = 0;

            } else {
                // Recibir impacto
                int danio = 15 + (rand() % 11);
                integridad_nave -= danio;
                cout << "Impacto de meteoritos. Perdiste " << danio << "% de integridad." << endl;
            }
        }
    }
}

bool verificarCondiciones(){
    if(days >= 10) { // Verificar victoria - Llegar al día 10
        cout << "\n=== MISION COMPLETADA ===" << endl;
        cout << "Has sobrevivido 10 dias en el espacio!" << endl;
        mostrarRecursos();
        cout << "FELICIDADES CAPITAN!" << endl;
        return false;
    }

    if(integridad_nave <= 0) {     // Verificar derrota - Integridad de la nave
        cout << "\n=== GAME OVER ===" << endl;
        cout << "La nave ha sido destruida." << endl;
        mostrarRecursos();
        return false;
    }

    if(oxigeno <= 0) { // Verificar derrota - Sin oxígeno
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Te has quedado sin oxigeno." << endl;
        mostrarRecursos();
        return false;
    }

    if(combustible <= 0) { // Verificar derrota - Sin combustible
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Te has quedado sin combustible." << endl;
        mostrarRecursos();
        return false;
    }

    return true; // El juego continúa
}

void menuAcciones(){
    int op;
    bool opcionValida;

    do {
        cout << "1. Explorar planeta" << endl;
        cout << "2. Reparar nave" << endl;
        cout << "3. Enviar senal" << endl;
        cout << "4. Rendirse" << endl;
        cin >> op;

        opcionValida = true;
        switch (op){
        case 1:
            explorarPlaneta();
            break;
        case 2:
            repararNave();
            break;
        case 3:
            enviarSenales();
            break;
        case 4:
            cout << "\nTe has rendido. GAME OVER :(" << endl;
            exit(0);
            break;
        default:
            cout << "Opcion no valida. Por favor, selecciona una opcion valida :)" << endl;
            opcionValida = false;
            break;
        }
    } while (!opcionValida);
}
