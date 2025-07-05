using UnityEngine;

// Aquí el usuario define sus condiciones según su juego.
public static class NPCGameLogic {
    public static bool VerificarCondicion(Jugador jugador, string condicion) {
        if (condicion == "oro") return jugador.tieneOro;
        if (condicion == "espada") return jugador.tieneEspada;
        if (condicion == "mapa") return jugador.tieneMapa;
        // Aquí el usuario puede añadir más condiciones.
        return false;
    }
}
