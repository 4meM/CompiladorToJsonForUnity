using System.Collections.Generic;

[System.Serializable]
public class Accion {
    public string tipo;
    public string texto;
    public string condicion;
    public List<Accion> accionesSi;
    public List<Accion> accionesSino;
}

[System.Serializable]
public class NPC {
    public string nombre;
    public List<Accion> acciones;
}

[System.Serializable]
public class NPCData {
    public List<NPC> npcs;
}
