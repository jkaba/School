using UnityEngine;

/* 
 * BlockScript class
 * This class is used to handle the the blocks which act as barriers
 */ 
public class BlockScript : MonoBehaviour
{
    //variables
    public Material[] Materials;
    private bool damaged;
    private Renderer renderer;

    void Start()
    {
        // Set and render the material
        renderer = GetComponent<Renderer>();
        renderer.sharedMaterial = Materials[0];
    }

    public void Collision()
    {
        // If the block is damaged when hit then destroy it
        if (damaged)
        {
            Destroy(gameObject);
        }
        // Else change material, and set damage to true
        else
        {
            renderer.sharedMaterial = this.Materials[1];
            damaged = true;
        }
    }
}
