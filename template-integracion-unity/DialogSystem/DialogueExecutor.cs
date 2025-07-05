using UnityEngine;

public static class DialogueExecutor {
    public static void EjecutarNPCs(NPCData datos, Jugador jugador) {
        foreach (var npc in datos.npcs) {
            Debug.Log("NPC: " + npc.nombre);
            foreach (var accion in npc.acciones) {
                ProcesarAccion(accion, jugador);
            }
        }
    }

    static void ProcesarAccion(Accion accion, Jugador jugador) {
        if (accion.tipo == "decir") {
            Debug.Log("NPC dice: " + accion.texto);
        } else if (accion.tipo == "si") {
            if (NPCGameLogic.VerificarCondicion(jugador, accion.condicion)) {
                foreach (var a in accion.accionesSi) {
                    ProcesarAccion(a, jugador);
                }
            } else {
                foreach (var a in accion.accionesSino) {
                    ProcesarAccion(a, jugador);
                }
            }
        }
    }
}
