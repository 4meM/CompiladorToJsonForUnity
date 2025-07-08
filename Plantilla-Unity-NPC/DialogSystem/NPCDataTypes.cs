using System.Collections.Generic;

namespace DialogueSystem
{
    [System.Serializable]
    public class Variable
    {
        public string tipo;
        public string valor;
    }

    [System.Serializable]
    public class VariableEntry
    {
        public string nombre;
        public Variable variable;
    }

    [System.Serializable]
    public class Accion
    {
        public string tipo;
        public string texto;
        public string condicion;
        public List<Accion> accionesSi;
        public List<Accion> accionesSino;
    }

    [System.Serializable]
    public class NPC
    {
        public string nombre;
        public List<VariableEntry> variables;  // Cambio de Dictionary a List
        public List<Accion> acciones;
        
        // Método helper para buscar variables
        public string GetVariableValue(string nombreVariable)
        {
            if (variables != null)
            {
                foreach (var varEntry in variables)
                {
                    if (varEntry.nombre == nombreVariable)
                    {
                        return varEntry.variable.valor;
                    }
                }
            }
            return "";
        }
    }

    [System.Serializable]
    public class NPCList
    {
        public List<NPC> npcs;
    }
}
