# SmartKitchen
  
WS 2017/18 - RIOT im Internet of Things - Bachelor Project of Computer Science and Electrical Engineering 
   
# What is SmartKitchen?
  
  We monitor the contents of a fridge (Product and weight).
        
For this we used 4 NoSQL Tables:

**Bestand**
  
  - Lfd: Auto-incremented value
  - ID: ID of the product in the fridge
  - Gewicht: Weight
  - Temp: Did it previously exist?
  - Kategorie: Category of the food (e.g. meat product, dairy)
  - Produkt: Name of the product
  
  **Sensor**
  
  - ID: Auto-incremented value
  - Wert: Value
  - Timestamp: Timestamp of the transaction
  
  **NFC**
  
  - ID: Auto-incremented value
  - Data: Identifier for the nfc tag
  - Timestamp: Timestamp of the transaction
  
  **Produktmatch**
  
  - ID: ID of the product in the fridge
  - NFCTag: NFCtag identifier (Data in NFC)
  - Produkt: Name of the product
  - Kategorie: Name of the product-category (e.g. Meat product, dairy)

    
   
