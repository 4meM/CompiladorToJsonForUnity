using UnityEngine;

public class DetectorNPC : MonoBehaviour
{
    public string npcActual = "";

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("NPC"))
        {
            npcActual = other.gameObject.name;
            Debug.Log("Cerca de: " + npcActual);
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("NPC"))
        {
            npcActual = "";
            Debug.Log("Te alejaste del NPC");
        }
    }
}
