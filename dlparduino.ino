/*
 */

const int ledPin = 13; // the pin that the LED is attached to
char in; //incomming byte

struct channel_s
{
    int pin;
    int analog;
};

const struct channel_s channel[9] =
{
    {
        //Channel 0 don't exists in the protocol
        .pin = 0,
        .analog = 0
    }
    , {
        .pin = 1,
        .analog = A0
    }
    , {
        .pin = 2,
        .analog = A1
    }
    , {
        .pin = 3,
        .analog = A2
    }
    , {
        .pin = 4,
        .analog = A3
    }
    , {
        .pin = 5,
        .analog = A4
    }
    , {
        .pin = 6,
        .analog = A5
    }
    , {
        .pin = 7,
        .analog = A6
    }
    , {
        .pin = 8,
        .analog = A7
    }
};

void digitalout( const struct channel_s chan, const char val )
{
    pinMode( chan.pin, OUTPUT );
    digitalWrite( chan.pin, val );
}

void digitalin( const struct channel_s chan )
{
    pinMode( chan.pin, INPUT );
    int val = digitalRead( chan.pin );
    Serial.print( val );
}

void analogin( const struct channel_s chan )
{
    int ana_in = analogRead( chan.analog );
    // map it to the range of the analog out:
    //outputValue = map( sensorValue, 0, 1023, 0, 255 );
    // change the analog out value:
    //analogWrite( analogOutPin, outputValue );
    // print the results to the serial monitor:
    Serial.print( "sensor = " );
    Serial.print( ana_in );
}



void setup()
{
    Serial.begin( 115200 );
    // initialize the LED pin as an output:
    pinMode( ledPin, OUTPUT );
    analogReference( DEFAULT );
}

void loop()
{
    if( Serial.available() > 0 )
    {
        // read the oldest byte in the serial buffer:
        in = Serial.read();
        switch( in )
        {
                // Channel 1
            case '1':
                digitalout( channel[1], HIGH );
                break;
            case 'Q':
                digitalout( channel[1], LOW );
                break;
            case 'A':
                digitalin( channel[1] );
                break;
            case 'Z':
                analogin( channel[1] );
                break;
                // Channel 2
            case '2':
                digitalout( channel[2], HIGH );
                break;
            case 'W':
                digitalout( channel[2], LOW );
                break;
            case 'S':
                digitalin( channel[2] );
                break;
            case 'X':
                analogin( channel[2] );
                break;
                // Channel 3
            case '3':
                digitalout( channel[3], HIGH );
                break;
            case 'E':
                digitalout( channel[3], LOW );
                break;
            case 'D':
                digitalin( channel[3] );
                break;
            case 'C':
                analogin( channel[3] );
                break;
                // Channel 4
            case '4':
                digitalout( channel[4], HIGH );
                break;
            case 'R':
                digitalout( channel[4], LOW );
                break;
            case 'F':
                digitalin( channel[4] );
                break;
            case 'V':
                analogin( channel[4] );
                break;
                // Channel 5
            case '5':
                digitalout( channel[5], HIGH );
                break;
            case 'T':
                digitalout( channel[5], LOW );
                break;
            case 'G':
                digitalin( channel[5] );
                break;
            case 'B':
                analogin( channel[5] );
                break;
                // Channel 6
            case '6':
                digitalout( channel[6], HIGH );
                break;
            case 'Y':
                digitalout( channel[6], LOW );
                break;
            case 'H':
                digitalin( channel[6] );
                break;
            case 'N':
                analogin( channel[6] );
                break;
                // Channel 7
            case '7':
                digitalout( channel[7], HIGH );
                break;
            case 'U':
                digitalout( channel[7], LOW );
                break;
            case 'J':
                digitalin( channel[7] );
                break;
            case 'M':
                analogin( channel[7] );
                break;
                // Channel 8
            case '8':
                digitalout( channel[8], HIGH );
                break;
            case 'I':
                digitalout( channel[8], LOW );
                break;
            case 'K':
                digitalin( channel[8] );
                break;
            case ',':
                analogin( channel[8] );
                break;
            default:
                break;
        }
    }
}


