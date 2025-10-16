#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// llamada de funcion
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
    srand(time(0)); // Inicializar semilla aleatoria
    cout << "||BIENVENIDO CAPITAN|| \n";
    cout << "Mision: Sobrevivir 10 dias en el espacio y llegar al destino\n" << endl;
    mostrarRecursos();

    // Loop principal del juego
    while(true) {
        menuAcciones();

        // Verificar si el juego debe continuar después de la acción
        if(!verificarCondiciones()) {
            break;
        }

        // Evento nocturno (después de cada acción)
        eventoNocturno();

        // Mostrar recursos después del evento nocturno
        mostrarRecursos();

        // Verificar condiciones nuevamente después de la noche
        if(!verificarCondiciones()) {
            break;
        }
    }

    return 0;
}

void mostrarRecursos(){
    cout << "\n==================================" << endl;
    cout << "        RECURSOS ACTUALES         " << endl;
    cout << "==================================" << endl;
    cout << "Combustible disponible..... " << combustible << " litros" << endl;
    cout << "Oxigeno disponible......... " << oxigeno << " %" << endl;
    cout << "Suministros disponible..... " << suministros << " unidades" << endl;
    cout << "Integridad de nuestra nave. " << integridad_nave << " %" << endl;
    cout << "Dias en mision............. " << days << " / 10 dias" << endl;
    cout << "==================================" << endl;
}

void explorarPlaneta(){
    cout << "\n>>> Explorando planeta cercano..." << endl;

    // Verificar si hay suficiente combustible
    if(combustible < 15) {
        cout << "\nNo tienes suficiente combustible para explorar (necesitas 15 litros)" << endl;
        return; // No consume el día
    }

    // Gastar combustible
    combustible -= 15;
    cout << "[-15 Combustible usado para viajar]" << endl;

    // Eventos aleatorios con sus probabilidades

    // 1. Oxígeno (60% probabilidad)
    if((rand() % 100) < 60) {
        int oxigenoEncontrado = 20 + (rand() % 21); // 20 a 40
        oxigeno += oxigenoEncontrado;
        cout << "\n¡DESCUBRIMIENTO! Encontraste una fuente de oxigeno" << endl;
        cout << "[+" << oxigenoEncontrado << " Oxigeno]" << endl;
    }

    // 2. Combustible (25% probabilidad)
    if((rand() % 100) < 25) {
        int combustibleEncontrado = 10 + (rand() % 21); // 10 a 30
        combustible += combustibleEncontrado;
        cout << "\n¡DESCUBRIMIENTO! Encontraste depositos de combustible" << endl;
        cout << "[+" << combustibleEncontrado << " Combustible]" << endl;
    }

    // 3. Suministros (50% probabilidad)
    if((rand() % 100) < 50) {
        int suministrosEncontrados = 30 + (rand() % 71); // 30 a 100
        suministros += suministrosEncontrados;
        cout << "\n¡DESCUBRIMIENTO! Encontraste suministros abandonados" << endl;
        cout << "[+" << suministrosEncontrados << " Suministros]" << endl;
    }

    // 4. Tormenta eléctrica (25% probabilidad)
    if((rand() % 100) < 25) {
        int danio = 10 + (rand() % 11); // 10 a 20
        integridad_nave -= danio;
        cout << "\n¡PELIGRO! Una tormenta electrica azota la nave" << endl;
        cout << "[-" << danio << "% Integridad de la nave]" << endl;
    }

    // 5. Aterrizaje forzado (25% probabilidad)
    if((rand() % 100) < 25) {
        int danio = 10 + (rand() % 11); // 10 a 20
        integridad_nave -= danio;
        cout << "\n¡ALERTA! Aterrizaje forzado debido a fallas tecnicas" << endl;
        cout << "[-" << danio << "% Integridad de la nave]" << endl;
    }

    // Incrementar días
    days++;
    cout << "\n[Dia " << days << " completado]" << endl;
}

void repararNave(){
    cout << "\n>>> Iniciando reparaciones de la nave..." << endl;

    // Verificar si la nave ya está al 100%
    if(integridad_nave >= 100) {
        cout << "\nLa nave ya esta en perfecto estado (100% integridad)" << endl;
        cout << "No es necesario repararla." << endl;
        return; // No consume el día
    }

    // Calcular cuánto se puede reparar como máximo
    int maxReparable = 100 - integridad_nave;
    int maxPosiblePorSuministros = suministros / 10;

    cout << "\nIntegridad actual: " << integridad_nave << "%" << endl;
    cout << "Suministros disponibles: " << suministros << " unidades" << endl;
    cout << "Maximo reparable con tus suministros: " << maxPosiblePorSuministros << "%" << endl;
    cout << "Porcentaje necesario para llegar al 100%: " << maxReparable << "%" << endl;

    // Preguntar cuánto quiere reparar
    int porcentajeReparar;
    cout << "\n¿Cuanto porcentaje deseas reparar? (0 para cancelar): ";
    cin >> porcentajeReparar;

    // Validar cancelación
    if(porcentajeReparar == 0) {
        cout << "\nReparacion cancelada." << endl;
        return; // No consume el día
    }

    // Validar que el porcentaje sea positivo
    if(porcentajeReparar < 0) {
        cout << "\nNo puedes ingresar un porcentaje negativo." << endl;
        return; // No consume el día
    }

    // Calcular el costo en suministros
    int costoSuministros = porcentajeReparar * 10;

    // Verificar si hay suficientes suministros
    if(costoSuministros > suministros) {
        cout << "\nNo tienes suficientes suministros para esta reparacion." << endl;
        cout << "Necesitas: " << costoSuministros << " unidades" << endl;
        cout << "Tienes: " << suministros << " unidades" << endl;
        return; // No consume el día
    }

    // Calcular la integridad final
    int integridadFinal = integridad_nave + porcentajeReparar;

    // Verificar si excede el 100%
    if(integridadFinal > 100) {
        cout << "\nADVERTENCIA: La reparacion excederia el 100% de integridad." << endl;
        cout << "Se ajustara automaticamente para reparar solo hasta el 100%." << endl;

        // Ajustar valores
        porcentajeReparar = maxReparable;
        costoSuministros = porcentajeReparar * 10;
        integridadFinal = 100;

        cout << "Porcentaje a reparar ajustado: " << porcentajeReparar << "%" << endl;
        cout << "Costo en suministros: " << costoSuministros << " unidades" << endl;
    }

    // Realizar la reparación
    suministros -= costoSuministros;
    integridad_nave = integridadFinal;

    cout << "\n¡REPARACION EXITOSA!" << endl;
    cout << "[+" << porcentajeReparar << "% Integridad recuperada]" << endl;
    cout << "[-" << costoSuministros << " Suministros utilizados]" << endl;
    cout << "Nueva integridad: " << integridad_nave << "%" << endl;

    // Incrementar días
    days++;
    cout << "\n[Dia " << days << " completado]" << endl;
}

void enviarSenales(){
    cout << "\n>>> Enviando senales de emergencia al espacio..." << endl;
    cout << "Transmitiendo en todas las frecuencias..." << endl;
    cout << "Esperando respuesta...\n" << endl;

    // 50% de probabilidad para cada evento
    int eventoAleatorio = rand() % 2; // 0 o 1

    if(eventoAleatorio == 0) {
        // Evento positivo: Ayuda con combustible
        combustible += 60;
        cout << "¡BUENAS NOTICIAS! Una nave aliada ha respondido" << endl;
        cout << "Te han enviado suministros de combustible de emergencia" << endl;
        cout << "[+60 Combustible recibido]" << endl;
    } else {
        // Evento negativo: Piratas espaciales
        integridad_nave -= 15;
        suministros -= 20;
        cout << "¡ALERTA ROJA! Piratas espaciales detectaron tu senal" << endl;
        cout << "Han abordado la nave y robado recursos" << endl;
        cout << "[-15% Integridad de la nave]" << endl;
        cout << "[-20 Suministros robados]" << endl;

        // Evitar que los suministros sean negativos
        if(suministros < 0) {
            suministros = 0;
        }
    }

    // Incrementar días
    days++;
    cout << "\n[Dia " << days << " completado]" << endl;
}

void eventoNocturno(){
    cout << "\n===========================================" << endl;
    cout << "           LLEGANDO LA NOCHE...           " << endl;
    cout << "===========================================" << endl;

    // Consumo automático de recursos cada noche
    oxigeno -= 20;
    suministros -= 30;

    cout << "Consumo nocturno de recursos:" << endl;
    cout << "[-20 Oxigeno consumido]" << endl;
    cout << "[-30 Suministros consumidos]" << endl;

    // Evitar valores negativos
    if(oxigeno < 0) oxigeno = 0;
    if(suministros < 0) suministros = 0;

    // 15% de probabilidad de que ocurra un evento nocturno
    if((rand() % 100) < 15) {
        cout << "\n¡EVENTO NOCTURNO!" << endl;

        // Elegir uno de los 3 eventos posibles
        int tipoEvento = rand() % 3; // 0, 1 o 2

        if(tipoEvento == 0) {
            // Tormenta cósmica
            oxigeno -= 10;
            cout << "Una tormenta cosmica ha impactado la nave" << endl;
            cout << "Los sistemas de soporte vital fueron afectados" << endl;
            cout << "[-10 Oxigeno]" << endl;

            if(oxigeno < 0) oxigeno = 0;

        } else if(tipoEvento == 1) {
            // Encuentro alienígena
            cout << "¡Contacto! Formas de vida alienigenas detectadas" << endl;

            // 50% amistoso, 50% hostil
            int tipoAlien = rand() % 2;

            if(tipoAlien == 0) {
                // Amistoso
                combustible += 20;
                cout << "Los alienigenas son amistosos y te ofrecen ayuda" << endl;
                cout << "[+20 Combustible recibido como regalo]" << endl;
            } else {
                // Hostil
                integridad_nave -= 10;
                cout << "Los alienigenas son hostiles y atacan la nave" << endl;
                cout << "[-10% Integridad de la nave]" << endl;
            }

        } else {
            // Meteoritos
            cout << "¡ALERTA! Campo de meteoritos detectado en tu trayectoria" << endl;
            cout << "\n¿Que deseas hacer?" << endl;
            cout << "1. Maniobrar para esquivarlos (gasta combustible)" << endl;
            cout << "2. Recibir el impacto (dana la nave)" << endl;
            cout << "Selecciona tu opcion: ";

            int decision;
            cin >> decision;

            if(decision == 1) {
                // Maniobrar
                int combustibleGastado = 10 + (rand() % 21); // 10 a 30
                combustible -= combustibleGastado;
                cout << "\nManiobras evasivas ejecutadas exitosamente" << endl;
                cout << "[-" << combustibleGastado << " Combustible gastado]" << endl;

                if(combustible < 0) combustible = 0;

            } else {
                // Recibir impacto
                int danio = 15 + (rand() % 11); // 15 a 25
                integridad_nave -= danio;
                cout << "\nLos meteoritos han impactado la nave" << endl;
                cout << "[-" << danio << "% Integridad de la nave]" << endl;
            }
        }
    } else {
        cout << "\nNoche tranquila. Sin eventos especiales." << endl;
    }

    cout << "===========================================" << endl;
}

bool verificarCondiciones(){
    // Verificar victoria - Llegar al día 10
    if(days >= 10) {
        cout << "\n*******************************************" << endl;
        cout << "      ¡¡¡MISION COMPLETADA!!!" << endl;
        cout << "*******************************************" << endl;
        cout << "Has sobrevivido 10 dias en el espacio" << endl;
        cout << "¡Has llegado al destino exitosamente!" << endl;
        cout << "\n=== ESTADISTICAS FINALES ===" << endl;
        mostrarRecursos();
        cout << "\n¡FELICIDADES CAPITAN!" << endl;
        return false; // Termina el juego
    }

    // Verificar derrota - Integridad de la nave
    if(integridad_nave <= 0) {
        cout << "\n*******************************************" << endl;
        cout << "           GAME OVER" << endl;
        cout << "*******************************************" << endl;
        cout << "La nave ha sido destruida completamente" << endl;
        cout << "Integridad: 0%" << endl;
        cout << "\nLa tripulacion no sobrevivio..." << endl;
        return false; // Termina el juego
    }

    // Verificar derrota - Sin oxígeno
    if(oxigeno <= 0) {
        cout << "\n*******************************************" << endl;
        cout << "           GAME OVER" << endl;
        cout << "*******************************************" << endl;
        cout << "Te has quedado sin oxigeno" << endl;
        cout << "La tripulacion ha perecido por asfixia..." << endl;
        return false; // Termina el juego
    }

    // Verificar derrota - Sin combustible
    if(combustible <= 0) {
        cout << "\n*******************************************" << endl;
        cout << "           GAME OVER" << endl;
        cout << "*******************************************" << endl;
        cout << "Te has quedado sin combustible" << endl;
        cout << "La nave esta a la deriva en el espacio..." << endl;
        return false; // Termina el juego
    }

    return true; // El juego continúa
}

void menuAcciones(){
    int op;
    bool opcionValida;

    do {
        cout << "\n -------------------------" << endl;
        cout << "| 1. Explorar planeta     |" << endl;
        cout << "| 2. Reparar nave         |" << endl;
        cout << "| 3. Enviar senales       |" << endl;
        cout << "| 4. Rendirse (Game Over) |" << endl;
        cout << "|_________________________|" << endl;
        cout << "  " << endl;
        cout << "Selecciona una opcion valida: ";
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
            cout << "\n*******************************************" << endl;
            cout << "      TE HAS RENDIDO" << endl;
            cout << "*******************************************" << endl;
            cout << "Has decidido abandonar la mision..." << endl;
            cout << "GAME OVER" << endl;
            exit(0);
            break;
        default:
            cout << "\nOpcion no valida. Por favor, selecciona 1, 2, 3 o 4." << endl;
            opcionValida = false;
            break;
        }
    } while (!opcionValida);
}
