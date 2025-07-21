using UnityEngine;

public class CameraController : MonoBehaviour
{
    [Header("First Person Settings")]
    public Transform target; // El jugador a seguir
    public float mouseSensitivity = 100f;
    public float eyeHeight = 1.6f; // Altura de los ojos del jugador
    
    [Header("Look Limits")]
    public float minVerticalAngle = -90f;
    public float maxVerticalAngle = 90f;
    
    private float rotationX = 0f;
    private float rotationY = 0f;
    
    void Start()
    {
        // Bloquear cursor inmediatamente
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        
        // Si no se asignó un target, buscar al jugador
        if (target == null)
        {
            GameObject player = GameObject.FindWithTag("Player");
            if (player != null)
                target = player.transform;
        }
    }
    
    void Update()
    {
        // Liberar/bloquear cursor con ESC
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (Cursor.lockState == CursorLockMode.Locked)
            {
                Cursor.lockState = CursorLockMode.None;
                Cursor.visible = true;
            }
            else
            {
                Cursor.lockState = CursorLockMode.Locked;
                Cursor.visible = false;
            }
        }
        
        // Bloquear cursor al hacer click
        if (Input.GetMouseButtonDown(0))
        {
            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
        }
        
        // Rotar cámara con mouse
        if (Cursor.lockState == CursorLockMode.Locked)
        {
            float mouseX = Input.GetAxis("Mouse X") * mouseSensitivity * Time.deltaTime;
            float mouseY = Input.GetAxis("Mouse Y") * mouseSensitivity * Time.deltaTime;
            
            rotationY += mouseX;
            rotationX -= mouseY;
            
            // Limitar rotación vertical (mirar arriba/abajo)
            rotationX = Mathf.Clamp(rotationX, minVerticalAngle, maxVerticalAngle);
            
            // Aplicar TODA la rotación a la cámara
            transform.rotation = Quaternion.Euler(rotationX, rotationY, 0f);
            
            // Rotar el jugador solo horizontalmente (para que el movimiento funcione)
            if (target != null)
            {
                target.rotation = Quaternion.Euler(0f, rotationY, 0f);
            }
        }
    }
    
    void LateUpdate()
    {
        // Posicionar cámara en los ojos del jugador
        if (target != null)
        {
            transform.position = target.position + Vector3.up * eyeHeight;
        }
    }
}