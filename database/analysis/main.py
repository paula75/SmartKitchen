import MySQLdb
from time import sleep

# Datenbankverbindung
connection = MySQLdb.connect("localhost", "root", "hamburg", "smartkitchen")
cursor = connection.cursor()

old_id = 0
while (1):
    sleep(1)
    print("looking for changes")
    cursor.execute("SELECT id FROM nfc ORDER BY timestamp DESC LIMIT 1;")
    id = cursor.fetchone()
    if (id != old_id):
        print("Something changed")
        old_id = id
        # Aktuellen NFC-Tag und die vier letzten Gewichtswerte auswaehlen
        cursor.execute("SELECT data FROM nfc ORDER BY timestamp DESC LIMIT 1;")
        nfc_tag = cursor.fetchone()[0]
        cursor.execute("SELECT wert FROM sensor ORDER BY timestamp DESC LIMIT 1;")
        fsr_data = cursor.fetchone()[0]
        a, b, c, d = fsr_data.split(",")

        weight = (int(a) + int(b) + int(c) + int(d)) / 4

        print(nfc_tag)
        print(weight)

        cursor.execute("SELECT id FROM produktmatch WHERE nfctag=" + "\"" + nfc_tag + "\"" + ";")
        actual_id = cursor.fetchone()[0]
        print(actual_id)

        cursor.execute("SELECT produkt FROM produktmatch WHERE id=" + str(actual_id) + ";")
        actual_produkt = cursor.fetchone()[0]
        cursor.execute("SELECT kategorie FROM produktmatch WHERE id=" + str(actual_id) + ";")
        actual_kategorie = cursor.fetchone()[0]

        cursor.execute("SELECT id FROM bestand WHERE id=" + str(actual_id) + ";")
        actual_Lid_raw = cursor.fetchone()
        print(actual_Lid_raw)
        if (actual_Lid_raw == None):
            str1 = "INSERT INTO bestand (id, gewicht, temp, kategorie, produkt) VALUES (" + str(actual_id) + "," + str(
                int(weight)) + ",1," + "\"" + str(actual_kategorie) + "\",\"" + str(actual_produkt) + "\");"
            cursor.execute(str1)
            connection.commit()
            print("Data written")
        else:
            print("DELETE Data")
            actual_Lid = list(actual_Lid_raw)
            print(actual_Lid[0])
            cursor.execute("DELETE FROM bestand WHERE id=" + str(actual_id) + ";")
            connection.commit()
