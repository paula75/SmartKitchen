import MySQLdb

# Datenbankverbindung
connection = MySQLdb.connect("localhost", "root", "hamburg", "smartkitchen")
cursor = connection.cursor()

# Aktuellen NFC-Tag und die vier letzten Gewichtswerte auswaehlen
cursor.execute("SELECT data FROM nfc ORDER BY timestamp DESC LIMIT 1")
nfc_raw = cursor.fetchone()
cursor.execute("SELECT data FROM sensor ORDER BY timestamp DESC LIMIT 4")
fsr_raw = cursor.fetchmany(size=4)
weight = (fsr_raw[0] + fsr_raw[1] + fsr_raw[2] + fsr_raw[3]) / 4

# Debug
print(nfc_raw)
print(fsr_raw)
print(weight)

# ID mit NFC-Tag matchen
cursor.execute("SELECT ID FROM xxx WHERE nfc_tag=" + nfc_raw)
actual_id = cursor.fetchone()

# ID mit LaufenderID matchen
cursor.execute("SELECT LID FROM xxx WHERE ID=" + actual_id)
actual_Lid = cursor.fetchone()
# Bestand aktuallisieren
if(actual_Lid == -1):
    cursor.execute("INSERT INTO xxx (ID, actual_force, temp) VALUES (" + actual_id + ", " + weight + " ,1)")
else:
    cursor.execute("DELETE FROM xxx WHERE ID=" + actual_id)
