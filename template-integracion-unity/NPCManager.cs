using UnityEngine;

public class NPCManager : MonoBehaviour {
    public Jugador jugador;

    void Start() {
        if (jugador == null) {
            jugador = FindObjectOfType<Jugador>();
        }

        NPCData datos = NPCParser.CargarNPCs("npc");
        if (datos != null) {
            DialogueExecutor.EjecutarNPCs(datos, jugador);
        }
    }
}
