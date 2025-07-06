using UnityEngine;
using System.IO;
using DialogueSystem;

public class DialogueExecutor : MonoBehaviour
{
    public DetectorNPC detector;
    public Jugador jugador;
    private NPCList datos;

    void Start()
    {
        string ruta = Path.Combine(Application.dataPath, "Resources/npc.json");
        string json = File.ReadAllText(ruta);
        datos = JsonUtility.FromJson<NPCList>(json);
    }

    void Update()
    {
        if (detector.npcActual != "" && Input.GetKeyDown(KeyCode.E))
        {
            NPC npc = datos.npcs.Find(n => n.nombre == detector.npcActual);
            if (npc != null)
            {
                EjecutarDialogo(npc);
            }
        }
    }

    void EjecutarDialogo(NPC npc)
    {
        foreach (var accion in npc.acciones)
        {
            if (accion.tipo == "decir")
            {
                Debug.Log(accion.texto);
            }
            else if (accion.tipo == "si")
            {
                bool cumple = VerificarCondicion(accion.condicion);
                var lista = cumple ? accion.accionesSi : accion.accionesSino;
                foreach (var subAccion in lista)
                {
                    if (subAccion.tipo == "decir")
                    {
                        Debug.Log(subAccion.texto);
                    }
                }
            }
        }
    }

    bool VerificarCondicion(string condicion)
    {
        return condicion == "oro" ? jugador.tieneOro : false;
    }
}

