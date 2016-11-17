/*
    dlparduino : DPL-IO8 Compatible firmware/sketch for Arduino-like boards.

    Copyright 2016 Romain Rossi <kubiack@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

const int ledPin = 13; // the pin that the LED is attached to
char in; //incomming byte

struct channel_s
{
    int pin;
    int analog;
};

// Array to have association between channel number and pin number
// current pinout is for arduino nano : uses A0-A7 pins + 2 and 3
// A6 and A7 pins are input-only (on arduino nano board) so should be externally connected to 3 and 2 repectively to provides digital in/out function
const struct channel_s channels[8] =
{
    {
        .pin = A0,
        .analog = A0
    }
    , {
        .pin = A1,
        .analog = A1
    }
    , {
        .pin = A2,
        .analog = A2
    }
    , {
        .pin = A3,
        .analog = A3
    }
    , {
        .pin = A4,
        .analog = A4
    }
    , {
        .pin = A5,
        .analog = A5
    }
    , {
        .pin = 3,
        .analog = A6
    }
    , {
        .pin = 2,
        .analog = A7
    }
};

// Configure the pin as a digital output and set the ping level
void digitalout( const struct channel_s chan, const char val )
{
    pinMode( chan.pin, OUTPUT );
    digitalWrite( chan.pin, val );
}

// Configure the pin as digital input, read the level and send it to the uart
void digitalin( const struct channel_s chan )
{
    pinMode( chan.pin, INPUT );
    int val = digitalRead( chan.pin );
    Serial.print( val );
}

// Configure the pin as analog input, read the value and sent it to the uart
void analogin( const struct channel_s chan )
{
    pinMode( chan.pin, INPUT );
    int ana_in = analogRead( chan.analog );
    // map it to centivolts:
    int ana_in_v = map( ana_in, 0, 1023, 0, 500 );
    Serial.print( ana_in_v );
}

void setup()
{
    Serial.begin( 115200 );
    // initialize the LED pin as an output:
    //pinMode( ledPin, OUTPUT );
    analogReference( DEFAULT );
}

void loop()
{
    if( Serial.available() > 0 )
    {
        int channel = -1;
        // read the oldest byte in the serial buffer:
        in = Serial.read();
        // which channel [1 to 8]?
        switch( in )
        {
            case '1':
            case 'Q':
            case 'A':
            case 'Z':
                channel = 1;
                break;
            case '2':
            case 'W':
            case 'S':
            case 'X':
                channel = 2;
                break;
            case '3':
            case 'E':
            case 'D':
            case 'C':
                channel = 3;
                break;
            case '4':
            case 'R':
            case 'F':
            case 'V':
                channel = 4;
                break;
            case '5':
            case 'T':
            case 'G':
            case 'B':
                channel = 5;
                break;
            case '6':
            case 'Y':
            case 'H':
            case 'N':
                channel = 6;
                break;
            case '7':
            case 'U':
            case 'J':
            case 'M':
                channel = 7;
                break;
            case '8':
            case 'I':
            case 'K':
            case ',':
                channel = 8;
                break;
            default:
                channel = -1;
                break;
        }
        // which operation ?
        if( channel > 0 )
        {
            switch( in )
            {
                    // DigitalOut HIGH
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                    digitalout( channels[channel - 1], HIGH );
                    break;
                    // DigitalOut LOW
                case 'Q':
                case 'W':
                case 'E':
                case 'R':
                case 'T':
                case 'Y':
                case 'U':
                case 'I':
                    digitalout( channels[channel - 1], LOW );
                    break;
                    // Digital IN
                case 'A':
                case 'S':
                case 'D':
                case 'F':
                case 'G':
                case 'H':
                case 'J':
                case 'K':
                    digitalin( channels[channel - 1] );
                    break;
                    // Analog IN
                case 'Z':
                case 'X':
                case 'C':
                case 'V':
                case 'B':
                case 'N':
                case 'M':
                case ',':
                    analogin( channels[channel - 1] );
                    break;
                default:
                    break;
            }
        }
    }
}


