#include <stdio.h>
#include <string.h>

// ",".join([f"{110*2**(halftone_dist/12):.1f}" for halftone_dist in range(12)])
// " ".join(n + p for p in "'' ' ".split() for n in "C C# D D# E F F# G G# A A# H".split())
// NOTE_LADDER = "C'' C#'' D'' D#'' E'' F'' F#'' G'' G#'' A'' A#'' H'' C' C#' D' D#' E' F' F#' G' G#' A' A#' H' C C# D D# E F F# G G# A A# H c c# d d# e f f# g g# a a# h"
// PIECE = "C E G c e C D A d f H' D G d f C E G c e C E A e a C D F# A d H' D G d g H' C E G c A' C E G c D' A' D F# c G' H' D G H G' A#' E G c# F' A' D A d F' G#' D F H E' G' C G c E' F' A' C F D' F' A' C F G'' D' G' H' F C' E' G' C E C' G' A#' C E F'' F' A' C E F#'' C' A' C D# G#'' F' H' C D G'' F' A' H' D G'' E' G' C E G'' D' G' C F G'' D' G' H' F G'' D#' A' C F# G'' E' G' C G G'' D' G' C F G'' D' G' H' F C'' C' G' A#' E"
// "".join(chr(NOTE_LADDER.split().index(n) + 40) for n in PIECE.split())
// Notes must be ~222bpm
// That's 10844.3 samples at 44.1kHz.

/*

C E G c e
C D A d f
H' D G d f
C E G c e
C E A e a (5)
C D F# A d
H' D G d g
H' C E G c
A' C E G c
D' A' D F# c (10)
G' H' D G H
G' A#' E G c#
F' A' D A d
F' G#' D F H
E' G' C G c (15)
E' F' A' C F
D' F' A' C F
G'' D' G' H' F
C' E' G' C E
C' G' A#' C E (20)
F'' F' A' C E
F#'' C' A' C D#
G#'' F' H' C D
G'' F' A' H' D
G'' E' G' C E (25)
G'' D' G' C F
G'' D' G' H' F
G'' D#' A' C F#
G'' E' G' C G
G'' D' G' C F (30)
G'' D' G' H' F
C'' C' G' A#' E

C'' C' F' A' C F C A'   C A' F' A' F' D' F' D'
C'' H'' G H d f d H     d H G H D F E D
C'' C' E G c G E C'     C' C' C' C' C' C' C' C'

Note that C# is not used, and could be elided.

*/

// gcc praeludium.c -o praeludium && ./praeludium | aplay -f cd
// ./praeludium | ffmpeg -f s16le -ar 44100 -ac 2 -i - -acodec copy praeludium.wav
static double ff[] = { 110.0, 116.5, 123.5, 130.8, 138.6, 146.8, 155.6, 164.8,
    174.6, 185.0, 196.0, 207.7 };
static char const* n1 = "8<?DH8:AFI7:?FI8<?DH8<AHM8:>AF7:?FK78<?D58<?D.A:>D3C:?C36<?E15:AF"
                        "14:=C038?D0158=.158='.37=,038<,368<%158<&,58;(178:'157:'038<'.38="
                        "'.37='/58>'038?'.38='.37= ,36<";
static char const* n2 = " ,158=8585151.1. +?CFIFCFC?C:=<: ,<?D?<,0,0,,,,,";
static void p(int n)
{
    double f = ff[n % 12];
    while (n >= 12) {
        n -= 12;
        f *= 2;
    }
    for (int k = 0; k < 9000; ++k) {
        double ph = k * f / 44100;
        int v = (int)((ph - (int)ph) * 16384);
        // Modify v sometimes:
        if (v > 8192)
            v = 16384 - v;
        if (k < 4000)
            v = (int)(v * (1 + (4000. - k) / 4000.));
        if (k < 100)
            v = (int)(v * k / 100);
        if (k > 8000)
            v = (int)(v * (9000 - k) / 1000);
        putchar(v & 255);
        putchar((v >> 8) & 255);
        putchar(v & 255);
        putchar((v >> 8) & 255);
    }
}
// Main entry point:
int main()
{
    for (int i = 0; i < strlen(n1) / 5; ++i)
        for (int j = 0; j < 16; ++j)
            p(n1[i * 5 + (j % 8) % 5] - 29);
    for (int i = 0; i < strlen(n2); ++i)
        p(n2[i] - 29);
}
