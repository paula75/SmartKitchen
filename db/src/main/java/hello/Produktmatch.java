package hello;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity // This tells Hibernate to make a table out of this class
public class Produktmatch{
    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Integer id;

    private String nfctag;

    private String produkt;

    private String kategorie;

    public Integer getId() {
        return id;
    }

    public String getNfctag(){
	    return nfctag;
    }
    public void setNfctag(String nfctag){
	    this.nfctag = nfctag;}

    public void setId(Integer id) {
        this.id = id;
    }

    public String getProdukt() {
        return produkt;
    }

    public void setProdukt(String produkt) {
        this.produkt = produkt;
    }

    public String getKategorie(){
	    return kategorie;
    }

    public void setKategorie(String kategorie){
	    this.kategorie = kategorie;
    }

}

