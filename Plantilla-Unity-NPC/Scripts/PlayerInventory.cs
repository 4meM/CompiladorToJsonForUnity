using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class InventoryItem
{
    public string itemName;
    public int quantity;
    
    public InventoryItem(string name, int qty)
    {
        itemName = name;
        quantity = qty;
    }
}

public class PlayerInventory : MonoBehaviour
{
    [Header("Player Inventory")]
    public List<InventoryItem> items = new List<InventoryItem>();
    
    void Start()
    {
        // Add some default items for testing
        AddItem("oro", 100);
        AddItem("espada", 1);
        AddItem("pocion", 3);
    }
    
    public bool HasItem(string itemName)
    {
        return GetItemQuantity(itemName) > 0;
    }
    
    public int GetItemQuantity(string itemName)
    {
        InventoryItem item = items.Find(i => i.itemName.ToLower() == itemName.ToLower());
        return item != null ? item.quantity : 0;
    }
    
    public void AddItem(string itemName, int quantity = 1)
    {
        InventoryItem existingItem = items.Find(i => i.itemName.ToLower() == itemName.ToLower());
        
        if (existingItem != null)
        {
            existingItem.quantity += quantity;
        }
        else
        {
            items.Add(new InventoryItem(itemName, quantity));
        }
    }
    
    public bool RemoveItem(string itemName, int quantity = 1)
    {
        InventoryItem item = items.Find(i => i.itemName.ToLower() == itemName.ToLower());
        
        if (item != null && item.quantity >= quantity)
        {
            item.quantity -= quantity;
            
            if (item.quantity <= 0)
            {
                items.Remove(item);
            }
            
            return true;
        }
        
        return false;
    }
    
    public List<InventoryItem> GetAllItems()
    {
        return new List<InventoryItem>(items);
    }
}
