
// ZEITPUNKTE FÜR DIE NÄCHSTEN AKTIONEN
// t... VERWENDE ICH ALS PRÄFIX FÜR VARIABLEN DIE EINE ZEIT DARSTELLEN (VON TIME)
// unsigned long LAUFEN VON 0 BIS 4294967295 (2 ^ 32 - 1) 
 
unsigned long	mtJedeSekunde;
unsigned long	mtJedeMinute;
unsigned long	mtJedeStunde;
unsigned long	mtJedenTag;
 

void setup() {
	unsigned long	tJetzt;
	unsigned long	tAktion;
	
	pinMode (LED_BUILTIN, OUTPUT);
	
	Serial.begin (115200); 
	
	tJetzt = 4294967290;
	Serial.print ("Jetzt: ");
	Serial.println (tJetzt);
	
	// OVERFLOW PROVOZIEREN
	
	tAktion = tJetzt + 10;	
	Serial.print ("Aktion: ");
	Serial.println (tAktion);
	
	// SO GEHT DER TEST NICHT
	
	if (tJetzt > tAktion) {
		Serial.println ("Test A: Es ist was zu tun");
	} else {
		Serial.println ("Test A: Es ist noch nix zu tun");
	}
	
	// SO AUCH NICHT 
	
	if ((tJetzt - tAktion) > 0) {
		Serial.println ("Test B: Es ist was zu tun");
	} else {
		Serial.println ("Test B: Es ist noch nix zu tun");
	}

	// NUR SO 
	
	if ((int) (tJetzt - tAktion) > 0) {
		Serial.println ("Test C: Es ist was zu tun");
	} else {
		Serial.println ("Test C: Es ist noch nix zu tun");
	}
	
	// DIE ZEIT SCHREITET FORT
	
	tJetzt += 20;
	Serial.print ("Jetzt: ");
	Serial.println (tJetzt);
	
	// C GEHT IMMER NOCH
	
	if ((int) (tJetzt - tAktion) > 0) {
		Serial.println ("Test C: Es ist was zu tun");
	} else {
		Serial.println ("Test C: Es ist noch nix zu tun");
	}
	
	// AKTION WEITER IN DIE ZUKUNFT SCHIEBEN
	
	tAktion += 20;
	Serial.print ("Aktion: ");
	Serial.println (tAktion);
	
	// C GEHT IMMER NOCH
	
	if ((int) (tJetzt - tAktion) > 0) {
		Serial.println ("Test C: Es ist was zu tun");
	} else {
		Serial.println ("Test C: Es ist noch nix zu tun");
	}

	// DIE AKTIONEN INITIALISIEREN
	
	tJetzt = millis ();
	
	mtJedeSekunde = tJetzt + 1000;	
	mtJedeMinute  = tJetzt + 60UL * 1000;	
	mtJedeStunde  = tJetzt + 60UL * 60 * 1000;
	mtJedenTag    = tJetzt + 24UL * 60 * 60 * 1000;
}

// the loop function runs over and over again forever

void loop() {
	unsigned long	tJetzt;
	                     
	tJetzt = millis ();
		                     
	// TASTER ?
	
	if (TasterGedrueckt ()) PumpeLaufenLassen ();
	
	// FEUCHTIGKEIT ?
	
	if (ZuTrocken ()) PumpeLaufenLassen ();

	// SEKÜNDLICHE AKTION ? 
	
	if ((int) (tJetzt - mtJedeSekunde) > 0) {
		SekundenAktion ();
		mtJedeSekunde += 1000;
	}	
	
	// MINÜTLICHE AKTION ? 
	
	if ((int) (tJetzt - mtJedeMinute) > 0) {
		MinutenAktion ();
		mtJedeMinute += 60UL * 1000;
	}	
	
	// STÜNDLICHE AKTION ? 
	
	if ((int) (tJetzt - mtJedeStunde) > 0) {
		StundenAktion ();
		mtJedeStunde += 60UL * 60 * 1000;
	}	
	
	// TÄGLICHE AKTION ? 
	
	if ((int) (tJetzt - mtJedenTag) > 0) {
		TagesAktion ();
		mtJedenTag += 24UL * 60 * 60 * 1000;
	}	
}

bool TasterGedrueckt (void)
{
	// 
}

bool ZuTrocken (void)
{
	// 
}

void PumpeLaufenLassen (void)
{
	// 
} 

void SekundenAktion (void)
{
	//
}

void MinutenAktion (void)
{
	//
}

void StundenAktion (void)
{
	//
}

void TagesAktion (void)
{
	//
}
