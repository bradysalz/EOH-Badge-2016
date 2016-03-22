/* EOH AND CHILL 2K16
 *  AN ENDEAVOR BY BRADY SALZ
 *  AND IEEE UIUC 
 *  
 *  2/29/19
 */

// Notes
const int Note_C  = 239;
const int Note_CS = 225;
const int Note_D  = 213;
const int Note_DS = 201;
const int Note_E  = 190;
const int Note_F  = 179;
const int Note_FS = 169;
const int Note_G  = 159;
const int Note_GS = 150;
const int Note_A  = 142;
const int Note_AS = 134;
const int Note_B  = 127;

// tempos is 96 beats per minute
// 96bpm = 625ms / beat
const int beatDuration = 626; 
const int noteCount = 38;

// are counts global? now they are!
int i;

float hailToTheOrange[3*noteCount] = {
//    50, 1, 1,   // garbage note to init? didn't up working, should debug later
    Note_E, 4, 1,
    Note_A, 4, 0.75,
    Note_FS, 4, 0.25,
    Note_GS, 4, 1,
    Note_FS, 4, 1,

    Note_E, 4, 1,
    Note_A, 4, 0.75,
    Note_FS, 4, 0.25,
    Note_GS, 4, 2,

    Note_CS, 5, 2,
    Note_D, 5, 2,
    Note_CS, 5, 1,
    Note_B, 4, 0.5,
    Note_FS, 4, 1.5,

    Note_FS, 4, 2,
    Note_GS, 4, 1,
    Note_A, 4, 0.5,
    Note_B, 4, 2,

    Note_E, 4, 1,
    Note_A, 4, 0.75,
    Note_FS, 4, 0.25,
    Note_GS, 4, 1,
    Note_FS, 4, 0.75,
    Note_E, 4, 0.25,

    Note_E, 4, 0.75,
    Note_E, 4, 0.25, 
    Note_A, 4, 0.75,
    Note_FS, 4, 0.25,
    Note_GS, 4, 2,

    Note_CS, 5, 2,
    Note_D, 5, 2,
    Note_CS, 5, 1,
    Note_B, 4, 1,
    Note_A, 4, 0.5,
    Note_FS, 4, 1.5,

    Note_CS, 5, 1.5,
    Note_GS, 4, 1.5,
    Note_A, 4, 2
};


int prev_sample = 1023;
int next_sample = 1023;

void setup()
{
    DDRB |= 0x03;  // Set pins DDB0, DDB1 high (physical pins 5,6)

    TCCR1 |= (1 << PWM1A); // use Timer1, CompA in PWM Mode
    TCCR1 |= (1 << COM1A0); // Toggle 0C1A Output on match
    TCCR1 &= ~(1 << COM1A1); // Toggle the 0C1A Output on match

    GTCCR |= (1 << FOC1A); // Force output compare match 1A 
                            // makes output comparator read these settings
    PORTB &= ~(0x06);
    pinMode(A1, INPUT); // too lazy to write ADC interrupts sorry
    prev_sample = analogRead(A1);
    next_sample = analogRead(A1);
    delay(500);
}

// holders for trigger checks
int threshold = 25;
int diff = 0;

void loop()
{
    next_sample = analogRead(A1);
    diff = next_sample - prev_sample;
    
    if( diff > threshold ) // check if SENSE pin went low
    { 
      PORTB |= 0x01; // XOR toggling
      for(i = 0; i < 3*noteCount; i+=3)
      {
          
          PORTB ^= 0x01;  // XOR toggling, switch every note
//          PORTB |= 0x01; // ALL toggling, pulse every note
          myTone(hailToTheOrange[i], hailToTheOrange[i+1]-1, (int)beatDuration*hailToTheOrange[i+2]);

//          PORTB &= ~(0x01); // ALL toggling, pulse every note
          myTone(0, 4, 40);
          
      }
      delay(1000); // ensure we wait at least a second before the song starts again
                   // one might call this a literal sanity check
    }
    delay(10); // delay between samples  
    prev_sample = next_sample;
}

void myTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
    TCCR1 |= (1 << CTC1);  // Start the counter
    TCCR1 |= (1 << PWM1A); // Use PWM Mode for Timer1, OCRA
    TCCR1 &= ~(1 << COM1A0); // Toggle 0C1A Output on match
    TCCR1 |= (1 << COM1A1); // Toggle the 0C1A Output on match
    TCCR1 |= (8 - octave); // Set clock prescaler
    
    OCR1C = divisor;   // sets frequency (timer reset value)
    OCR1A = divisor/2; // set the OCR to value/2, 50% duty cycle
    delay(duration);   // play note for said duration
    TCCR1 = 0x90;      // reset + stop the counter (end PWM)
}

