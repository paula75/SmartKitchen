package hello.facade;

import hello.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.MediaType;
import org.springframework.web.client.RestTemplate;

import java.util.List;
import java.util.Optional;

@RestController
class ApplicationFacadeController {


    @Autowired
    private NfcRepository nfcRepository;

    @Autowired
    private SensorRepository sensorRepository;

    @Autowired
    private BestandRepository bestandRepository;

@Autowired
private ProduktmatchRepository produktmatchRepository;

    @RequestMapping(value = "/nfc", method = RequestMethod.GET)
    public Nfc getAllNfc(){
        return nfcRepository.findFirst1ByOrderByIdDesc();
    }

    @RequestMapping(value = "/nfc", method = RequestMethod.PUT, consumes = {MediaType.ALL_VALUE})
    @ResponseBody
    public String updateNfc(@RequestBody String uBody){
	String[] uBodyList = uBody.split(":");
	Sensor sensor = sensorRepository.findFirst1ByOrderByIdDesc();
	Nfc nfc = new Nfc();
	nfc.setData(uBodyList[0]);
        nfcRepository.save(nfc);
        return nfc.getData() + " | " + sensor.getWert();
    }


    
    @CrossOrigin
    @RequestMapping(value = "/sensor", method = RequestMethod.GET)
	        public Sensor getAllWerte(){
			        return sensorRepository.findFirst1ByOrderByIdDesc();
				    }

        @RequestMapping(value = "/sensor", method = RequestMethod.PUT, consumes = {MediaType.ALL_VALUE})
		@ResponseBody
		        public Sensor updateSensor(@RequestBody String sBody){
			String[] sBodyList = sBody.split(":");
			Sensor sensor = new Sensor();
			sensor.setWert(sBodyList[0]);
			sensorRepository.save(sensor);
		        return sensor;
			}

@CrossOrigin
    @RequestMapping(value = "/bestand", method = RequestMethod.GET)
    public String getAllBestand(){
	List<Bestand> lb =  bestandRepository.findAll();
	String val = "";
	for (Bestand b : lb){
		val = val + " | " + b.getLfd() + " | " + b.getId() + " | " + b.getGewicht() + " | " + b.getTemp() + " | " + b.getKategorie() + " | " + b.getProdukt() + " |";
	}
		return val;							                                        }

        @RequestMapping(value = "/bestand", method = RequestMethod.PUT, consumes = {MediaType.ALL_VALUE})	                @ResponseBody
	           public Bestand updateBestand(@RequestBody String bBody){
                   String[] bBodyList = bBody.split(":");
                   Bestand bestand = new Bestand();
                   bestand.setId(Integer.valueOf(bBodyList[0]));
		   bestand.setGewicht(Integer.valueOf(bBodyList[1]));
		   bestand.setTemp(Integer.valueOf(bBodyList[2]));
	bestand.setKategorie(bBodyList[3]);
	bestand.setProdukt(bBodyList[4]);
		   bestandRepository.save(bestand);
    		   return bestand;
	                        }
	@CrossOrigin
	@RequestMapping(value = "/produktmatch", method = RequestMethod.GET)
        public Produktmatch getAllProduktmatch(){
	return produktmatchRepository.findFirst1ByOrderByIdDesc();
				                }

        @RequestMapping(value = "/produktmatch", method = RequestMethod.PUT, consumes = {MediaType.ALL_VALUE})                       @ResponseBody
	 public Produktmatch updateProduktmatch(@RequestBody String bBody){
	String[] bBodyList = bBody.split(":");	
	Produktmatch produktmatch = new Produktmatch();
	produktmatch.setId(Integer.valueOf(bBodyList[0]));
        produktmatch.setNfctag(bBodyList[1]);
	produktmatch.setProdukt(bBodyList[2]);
        produktmatch.setKategorie(bBodyList[3]);
        produktmatchRepository.save(produktmatch);
        return produktmatch;
}
}

