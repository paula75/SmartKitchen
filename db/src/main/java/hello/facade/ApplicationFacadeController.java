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



    @RequestMapping(value = "/nfc", method = RequestMethod.GET)
    public Nfc getAllNfc(){
        return nfcRepository.findFirst1ByOrderByIdDesc();
    }

    @RequestMapping(value = "/nfc", method = RequestMethod.PUT, consumes = {MediaType.ALL_VALUE})
    @ResponseBody
    public Nfc updateNfc(@RequestBody String uBody){
	String[] uBodyList = uBody.split(":");
	Nfc nfc = new Nfc();
	nfc.setData(uBodyList[0]);
        nfcRepository.save(nfc);
        return nfc;
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
			sensor.setWert(Integer.valueOf(sBodyList[0]));
			sensorRepository.save(sensor);
		        return sensor;
			}

@CrossOrigin
    @RequestMapping(value = "/bestand", method = RequestMethod.GET)
    public Bestand getAllBestand(){
	return bestandRepository.findFirst1ByOrderByIdDesc();
							                                        }

        @RequestMapping(value = "/bestand", method = RequestMethod.PUT, consumes = {MediaType.ALL_VALUE})	                @ResponseBody
	           public Bestand updateBestand(@RequestBody String bBody){
                   String[] bBodyList = bBody.split(":");
                   Bestand bestand = new Bestand();
		   bestand.setName(bBodyList[0]);
                   bestand.setWert(Integer.valueOf(bBodyList[1]));
		   bestandRepository.save(bestand);
    		   return bestand;
	                        }
}


