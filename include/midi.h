#include <Arduino.h>
// Solder closed jumper on bottom!

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 31
#define VS1053_BANK_DEFAULT 0x00
#define VS1053_BANK_DRUMS1 0x78
#define VS1053_BANK_DRUMS2 0x7F
#define VS1053_BANK_MELODY 0x79

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 32 for more!

#define VS1053_GM1_VIBRAPHONE 12

#define VS1053_GM1_TRUMPET 57
#define VS1053_GM1_TROMBONE 58
#define VS1053_GM1_TUBA 59
#define VS1053_GM1_MUTED_TRUMPET 60
#define VS1053_GM1_FRENCH_HORN 61
#define VS1053_GM1_BRASS_SECTION 62
#define VS1053_GM1_SYNTH_BRASS_1 63
#define VS1053_GM1_SYNTH_BRASS_2 64
#define VS1053_GM1_SOPRANO_SAX 65
#define VS1053_GM1_ALTO_SAX 66
#define VS1053_GM1_TENOR_SAX 67
#define VS1053_GM1_BARITONE_SAX 68
#define VS1053_GM1_OBOE 69
#define VS1053_GM1_ENGLISH_HORN 70
#define VS1053_GM1_BASSOON 71
#define VS1053_GM1_CLARINET 72
#define VS1053_GM1_PICCOLO 73
#define VS1053_GM1_FLUTE 74
#define VS1053_GM1_RECORDER 75
#define VS1053_GM1_PAN_FLUTE 76
#define VS1053_GM1_BLOWN_BOTTLE 77
#define VS1053_GM1_SHAKUHACHI 78
#define VS1053_GM1_WHISTLE 79
#define VS1053_GM1_OCARINA 80

#define VS1053_GM1_TINKLE_BELL 113
#define VS1053_GM1_AGOGO 114
#define VS1053_GM1_WOODBLOCK 116
#define VS1053_GM1_TAIKO_DRUM 117
#define VS1053_GM1_SYNTH_DRUM 118

#define MIDI_NOTE_ON  0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_CHAN_MSG 0xB0
#define MIDI_CHAN_BANK 0x00
#define MIDI_CHAN_VOLUME 0x07
#define MIDI_CHAN_PROGRAM 0xC0

// Which output to use for midi (depending on Arduino)
#define VS1053_MIDI Serial1

void midiSetInstrument(uint8_t chan, uint8_t inst);
void midiSetChannelVolume(uint8_t chan, uint8_t vol);
void midiSetChannelBank(uint8_t chan, uint8_t bank);
void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel);
void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel);
void midiAllOff(uint8_t chan);