# Inbyggda-System-2 #

## Deluppgift 1: Blinka LED ##

#### 1. Koppla in LED och lämplig resistor till pinne 8 på Arduinons expansionsport med hjälp av kopplingsdäck och kablar. Minns från labb 1 att det motvarar PORTB0, och konfigurera upp den som utgång (alternativt valfri led på din egentillverkade, handgjorda, lokalproducerade sköld).
Svar: Jag har använt arduino skölden 
```C
void LED_init() {
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
}
```

#### 2. Konfigurera upp timer0 mha kap 19 i databladet: ###
Svar: 16000000/(1024 * 100) = 156,25 \
      156 - 1 = 155 (noll indexerat).
```C
void timer_init() {
	OCR0A = 155;
	TCCR0A |= (1 << WGM01); // enable ctc mode
  	TCCR0B |= (1 << CS02) | (1 << CS00);  //Set prescaler
}
```

#### 3. Skapa en oändlig loop i main(). I den, vänta på att räknaren når/matchar output comparevärdet (övervaka matchflaggan), och när så sker:
 * Rensa flaggan
 * Inkrementera en räknarvariabel, och när denna når 10; nollställ den och toggla LEDen. Detta för att förenkla, ögat ser inte blinkningarna i 100 Hz, så vi delar ner frekvensen till 10 Hz. Skriv och testa gärna den här delen innan du kopplar in timer-koden.

```C
//---------- led.c ----------

void toggle_LED(enum COLORS color){
	switch(color){
		case RED:
      			PORTB ^= (1 << PB3);
     			break;
    		case BLUE:
      			PORTB ^= (1 << PB2);
      			break;
    		case GREEN:
      			PORTB ^= (1 << PB1);
      			break;
    		case MAGENTA:
      			PORTB ^= (1 << PB3) | (1 << PB2);
      			break;
    		case CYAN:
      			PORTB ^= (1 << PB2) | (1 << PB1);
      			break;
    		case YELLOW:
      			PORTB ^= (1 << PB1)| (1 << PB3);
      			break;
	}
}

//---------- main.c ----------

static volatile int indexing = 0;

void main(void){
	timer_init();
	LED_init();
	
	while(1){
		if(TIFR0 & (1<<OCF0A)){
      			indexing++;
	      		TIFR0 |= ~(1 << OCF0A);
    		}
    		if(indexing == 10){
      			toggle_LED(MAGENTA);
      			indexing = 0;
    		}	
  	}
}
```

## Deluppgift 2: VERIERA LJUSSTYRKAN MED PWN

#### 1. Koppla upp en LED med resistor på den Arduino-expansionsport som motsvarar OC0A på ATMegan. Sätt upp den som utgång.
Svar: Kopplade in en LED till pinne 6 och till GND

#### 2. Konfigurera om timer0:
 * Fast PWM-mod, 0xFF som TOP, Non-inverting mode.
 * Prescaler = 64. Ange i git-commiten vilken PWM-frekvens det resulterar i samt beräkningen du använde.
 
 Svar: PWM_fequency = clock_speed / (Prescaller_value * (1 + TOP_Value))\
 PWM_fequency = 16000000 / (64 * (1 + 255)) = 976.5625
 ```C
void timer_init() {
	TIMSK0 |= (1 << OCIE0A); // sätter på interrupts för  TIMER0_COMPA
	TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
	TCCR0B |= (1 << CS00) | (1 << CS01);  //Set prescaler
}

 ```
 
 #### 3.Prova att variera ljusstyrka/duty cycle genom att skriva ett par olika värden till OCR0A, och visa att det fungerar genom att periodiskt växla mellan dem med en enkel loop och fördröjning mellan varje ändring. Välj värdena så att man tydligt ser skillnader.
```C
static volatile int pwm_value = 0;
static volatile bool ramp_up = true;
void main(void){
	timer_init();
	LED_init();
	//sei();
	while(1){
		if(ramp_up){
			pwm_value++;
			if(pwm_value == 255){
				ramp_up = false;
			}
		}		
		else{
			pwm_value--;
      if(pwm_value <= 0){
				ramp_up = true;
			}		
		}
		_delay_ms(10);
		OCR0A = pwm_value;
	}
}


ISR(TIMER0_COMPA_vect){			//Ramping LED uncomment sei(); for interrupts
	if(ramp_up){
		pwm_value++;
		if(pwm_value >= 255){
			ramp_up = false;
		}
	}
	else{
		pwm_value--;
		if(pwm_value <= 0){
			ramp_up = true;
		}
	}
	OCR0A = pwm_value;
}


```

## Deluppgift 3 (VG-krav): led-rampning
#### 1. Konfigurera timer0 som Fast PWM enligt ovan, och timer2 som enkel timer i CTC-mod, periodtid 16 ms.
````C
void timer_init() {
	TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);    // Fast PWM-mode
	TCCR0B |= (1 << CS00) | (1 << CS01);  //Set prescaler
	
	OCR2A = 249; 
	TCCR2A |= (1 << WGM21); // enable ctc mode
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  //Set prescaler
}
````
#### 3. Deklarera och implementera en funktion uint8_t simple_ramp() som vid varje anrop returnerar ett värde mellan 0–255. Värdet ska börja på 0, och för varje anrop inkrementeras, tills det når 255. Därefter ska det dekrementeras ner till 0, varpå cykeln börjar om.
````C
uint8_t simple_ramp(){
  static bool ramp_up = true;
  static int pwm_value = 0;
  
  if(ramp_up){
    pwm_value++;
    if(pwm_value >= 255){
      ramp_up = false;
    }
  }
  else{
    pwm_value--;
    if(pwm_value <= 0){
      ramp_up = true;
    }
  }
  return pwm_value;
}
````
#### 4. Anropa funktionen periodiskt med hjälp av timer2 och använd returvärdet som duty cycle för LEDens PWM-styrning. Förväntat beteende är att LEDen synligt pulserar av och på.
````C
void main(void){
	timer_init();
	LED_init();
	//sei();
	while(1){
		if(TIFR2 & (1<<OCF2A)){
			OCR0A = simple_ramp();
			TIFR2 |= ~(1<<OCF2A);
		}
	}
}
````

done!

