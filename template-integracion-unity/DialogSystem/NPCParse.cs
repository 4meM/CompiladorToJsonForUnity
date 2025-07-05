using UnityEngine;

public static class NPCParser {
    public static NPCData CargarNPCs(string nombreArchivo) {
        TextAsset jsonFile = Resources.Load<TextAsset>(nombreArchivo);
        if (jsonFile != null) {
            return JsonUtility.FromJson<NPCData>(jsonFile.text);
        } else {
            Debug.LogError("No se encontró el archivo " + nombreArchivo);
            return null;
        }
    }
}
