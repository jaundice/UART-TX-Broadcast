
const byte interruptPin = 2; //INT0 on nano

const byte MaskB = B00011111;
const byte MaskC = B00111111;
const byte MaskD = B00111011;

void setup()
{
	DDRB = MaskB;
	DDRC = MaskC;
	DDRD = MaskD | (DDRD & !(0x1 << 2));
	PORTD = PORTD | (0x1 << interruptPin);

	attachInterrupt(digitalPinToInterrupt(interruptPin), doInterrupt, CHANGE);

}

void loop()
{
}

void doInterrupt()
{
	byte bit = (PIND >> interruptPin) & 0x1;

	byte b = bit;

	for (byte a = 0; a < 8; a++)
	{
		b = (b << 1) | bit;
	}
	PORTD = b | (PORTD & !MaskD);
	PORTB = b | (PORTB & !MaskB);
	PORTC = b | (PORTC & !MaskC);

}
