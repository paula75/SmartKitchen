package hello;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity // This tells Hibernate to make a table out of this class
public class Bestand{
    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Integer lfd;

    private Integer id;

    private Integer gewicht;

    private Integer temp;

    private String kategorie;

    private String produkt;

    public String getKategorie(){
	    return kategorie;
    }

public void setKategorie(String kategorie){
	this.kategorie = kategorie;
}

public String getProdukt(){
	return produkt;}

	public void setProdukt(String produkt){
		this.produkt = produkt;}


    public Integer getId() {
        return id;
    }

    public Integer getLfd(){
	    return lfd;
    }
    public void setLfd(Integer lfd){
	    this.lfd = lfd;}

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getGewicht() {
        return gewicht;
    }

    public void setGewicht(Integer gewicht) {
        this.gewicht = gewicht;
    }

    public Integer getTemp(){
	    return temp;
    }

    public void setTemp(Integer temp){
	    this.temp = temp;
    }

}

