using UnityEngine;

public class JugadorMovimiento : MonoBehaviour
{
    public float velocidad = 5f;

    void Update()
    {
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");
        Vector3 movimiento = new Vector3(h, 0, v);
        transform.Translate(movimiento * velocidad * Time.deltaTime, Space.World);
    }
}
