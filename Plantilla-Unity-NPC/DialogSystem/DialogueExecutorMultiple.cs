using UnityEngine;
using System.IO;
using System.Collections.Generic;
using DialogueSystem;

public class DialogueExecutor : MonoBehaviour
{
    public DetectorNPC detector;
    public Jugador jugador;
    private NPCList datos;

    void Start()
    {
        CargarTodosLosNPCs();
    }

    void CargarTodosLosNPCs()
    {
        datos = new NPCList();
        datos.npcs = new List<NPC>();

        // Buscar todos los archivos JSON en Resources
        string resourcesPath = Path.Combine(Application.dataPath, "Resources");
        string[] archivosJson = Directory.GetFiles(resourcesPath, "*.json");

        foreach (string archivo in archivosJson)
        {
            try
            {
                string json = File.ReadAllText(archivo);
                NPCList npcTemp = JsonUtility.FromJson<NPCList>(json);
                
                // Agregar todos los NPCs de este archivo
                if (npcTemp != null && npcTemp.npcs != null)
                {
                    datos.npcs.AddRange(npcTemp.npcs);
                }
                
                Debug.Log($"Cargado: {Path.GetFileName(archivo)}");
            }
            catch (System.Exception e)
            {
                Debug.LogWarning($"Error cargando {archivo}: {e.Message}");
            }
        }
        
        Debug.Log($"Total NPCs cargados: {datos.npcs.Count}");
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
