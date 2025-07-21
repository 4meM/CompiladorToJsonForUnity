using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [Header("Movement Settings")]
    public float moveSpeed = 5f;
    public float rotationSpeed = 720f;
    
    [Header("Interaction Settings")]
    public KeyCode interactionKey = KeyCode.E;
    public float interactionRange = 3f;
    public LayerMask npcLayerMask = 1 << 6; // Layer 6 for NPCs
    
    [Header("Player Attributes")]
    public PlayerInventory inventory;
    
    [Header("Camera Reference")]
    public Transform playerCamera; // Referencia a la cámara
    
    private CharacterController characterController;
    private Vector3 velocity;
    private bool isGrounded;
    private float gravity = -9.81f;
    private Transform currentNPC;
    
    void Start()
    {
        characterController = GetComponent<CharacterController>();
        
        // Initialize inventory if not assigned
        if (inventory == null)
            inventory = GetComponent<PlayerInventory>();
            
        // Find camera if not assigned
        if (playerCamera == null)
            playerCamera = Camera.main.transform;
    }
    
    void Update()
    {
        HandleMovement();
        HandleInteraction();
        CheckForNearbyNPCs();
    }
    
    void HandleMovement()
    {
        isGrounded = characterController.isGrounded;
        
        if (isGrounded && velocity.y < 0)
        {
            velocity.y = -2f;
        }
        
        // Get input
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        
        // Get camera's forward and right vectors, but flatten them (no Y component)
        Vector3 forward = playerCamera.forward;
        Vector3 right = playerCamera.right;
        
        // Remove Y component to keep movement on ground level
        forward.y = 0f;
        right.y = 0f;
        
        // Normalize to ensure consistent speed
        forward.Normalize();
        right.Normalize();
        
        // Calculate movement direction based on camera orientation
        Vector3 direction = (forward * vertical + right * horizontal).normalized;
        
        if (direction.magnitude >= 0.1f)
        {
            // Move player in the direction relative to camera view
            characterController.Move(direction * moveSpeed * Time.deltaTime);
        }
        
        // Apply gravity
        velocity.y += gravity * Time.deltaTime;
        characterController.Move(velocity * Time.deltaTime);
    }
    
    void HandleInteraction()
    {
        if (Input.GetKeyDown(interactionKey) && currentNPC != null)
        {
            NPCController npcController = currentNPC.GetComponent<NPCController>();
            if (npcController != null)
            {
                npcController.StartDialogue(this);
            }
        }
    }
    
    void CheckForNearbyNPCs()
    {
        Collider[] nearbyNPCs = Physics.OverlapSphere(transform.position, interactionRange, npcLayerMask);
        
        if (nearbyNPCs.Length > 0)
        {
            // Find the closest NPC
            Transform closestNPC = null;
            float closestDistance = Mathf.Infinity;
            
            foreach (Collider npcCollider in nearbyNPCs)
            {
                float distance = Vector3.Distance(transform.position, npcCollider.transform.position);
                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestNPC = npcCollider.transform;
                }
            }
            
            if (closestNPC != currentNPC)
            {
                currentNPC = closestNPC;
                if (currentNPC != null)
                {
                    Debug.Log($"Near {currentNPC.name} - Press E to talk");
                }
            }
        }
        else
        {
            if (currentNPC != null)
            {
                currentNPC = null;
                Debug.Log("Moving away from NPC");
            }
        }
    }
    
    void OnDrawGizmosSelected()
    {
        // Draw interaction range
        Gizmos.color = Color.yellow;
        Gizmos.DrawWireSphere(transform.position, interactionRange);
    }
}
