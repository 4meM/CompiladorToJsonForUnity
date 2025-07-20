using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class NPCVariable
{
    public string nombre;
    public Variable variable;
}

[System.Serializable]
public class Variable
{
    public string tipo;
    public string valor;
}

[System.Serializable]
public class NPCAction
{
    public string tipo;
    public string texto;
    public string condicion;
    public List<NPCAction> accionesSi;
    public List<NPCAction> accionesSino;
}

[System.Serializable]
public class NPCData
{
    public string nombre;
    public List<NPCVariable> variables;
    public List<NPCAction> acciones;
}

[System.Serializable]
public class NPCJsonRoot
{
    public List<NPCData> npcs;
}

public class NPCController : MonoBehaviour
{
    [Header("NPC Configuration")]
    [Tooltip("Name of the JSON file in Resources folder (without .json extension)")]
    public string npcJsonFile = "comerciante";
    
    [Header("Visual Settings")]
    public Color npcColor = Color.blue;
    
    private NPCData npcData;
    private Dictionary<string, string> variables = new Dictionary<string, string>();
    
    void Start()
    {
        LoadNPCData();
        SetupVisuals();
    }
    
    void LoadNPCData()
    {
        TextAsset jsonFile = Resources.Load<TextAsset>(npcJsonFile);
        
        if (jsonFile == null)
        {
            Debug.LogError($"Could not load NPC JSON file: {npcJsonFile}");
            return;
        }
        
        try
        {
            NPCJsonRoot root = JsonUtility.FromJson<NPCJsonRoot>(jsonFile.text);
            
            if (root?.npcs != null && root.npcs.Count > 0)
            {
                npcData = root.npcs[0]; // Take the first NPC
                
                // Load variables into dictionary
                if (npcData.variables != null)
                {
                    foreach (var variable in npcData.variables)
                    {
                        variables[variable.nombre] = variable.variable.valor;
                    }
                }
                
                Debug.Log($"Loaded NPC: {npcData.nombre} with {npcData.acciones?.Count ?? 0} actions");
            }
            else
            {
                Debug.LogError("No NPCs found in JSON or invalid JSON structure");
            }
        }
        catch (System.Exception e)
        {
            Debug.LogError($"Error parsing NPC JSON: {e.Message}");
        }
    }
    
    void SetupVisuals()
    {
        // Set NPC color
        Renderer renderer = GetComponent<Renderer>();
        if (renderer != null)
        {
            renderer.sharedMaterial.color = npcColor;
        }
        
        // Ensure NPC is on the correct layer
        gameObject.layer = 6; // NPC layer
    }
    
    public void StartDialogue(PlayerController player)
    {
        if (npcData == null)
        {
            Debug.LogError($"No NPC data loaded for {gameObject.name}!");
            return;
        }
        
        if (npcData.acciones == null || npcData.acciones.Count == 0)
        {
            Debug.LogError($"No actions defined for {npcData.nombre}!");
            return;
        }

        Debug.Log($"=== {npcData.nombre} ===");
        
        List<string> dialogue = ProcessActions(npcData.acciones, player);
        
        // Display all dialogue lines
        foreach (string line in dialogue)
        {
            Debug.Log($"{npcData.nombre}: {line}");
        }
        
        Debug.Log($"=== End of conversation ===");
    }
    
    List<string> ProcessActions(List<NPCAction> actions, PlayerController player)
    {
        List<string> dialogue = new List<string>();
        
        if (actions == null) return dialogue;
        
        foreach (var action in actions)
        {
            ProcessSingleAction(action, player, dialogue);
        }
        
        return dialogue;
    }
    
    void ProcessSingleAction(NPCAction action, PlayerController player, List<string> dialogue)
    {
        switch (action.tipo.ToLower())
        {
            case "decir":
                string message = ReplaceVariables(action.texto);
                dialogue.Add(message);
                break;
                
            case "si":
                bool conditionMet = EvaluateCondition(action.condicion, player);
                
                if (conditionMet && action.accionesSi != null)
                {
                    foreach (var subAction in action.accionesSi)
                    {
                        ProcessSingleAction(subAction, player, dialogue);
                    }
                }
                else if (!conditionMet && action.accionesSino != null)
                {
                    foreach (var subAction in action.accionesSino)
                    {
                        ProcessSingleAction(subAction, player, dialogue);
                    }
                }
                break;
        }
    }
    
    string ReplaceVariables(string text)
    {
        string result = text;
        
        foreach (var kvp in variables)
        {
            string placeholder = "{" + kvp.Key + "}";
            result = result.Replace(placeholder, kvp.Value);
        }
        
        return result;
    }
    
    bool EvaluateCondition(string condition, PlayerController player)
    {
        if (string.IsNullOrEmpty(condition))
            return false;
            
        // Simple condition evaluation
        // Format: "jugador.tiene(\"item\")" becomes "item"
        if (condition.Contains("jugador.tiene"))
        {
            // Extract item name from condition
            int startIndex = condition.IndexOf("\"") + 1;
            int endIndex = condition.LastIndexOf("\"");
            
            if (startIndex > 0 && endIndex > startIndex)
            {
                string itemName = condition.Substring(startIndex, endIndex - startIndex);
                return player.inventory.HasItem(itemName);
            }
        }
        
        // Direct item check
        return player.inventory.HasItem(condition);
    }
}
