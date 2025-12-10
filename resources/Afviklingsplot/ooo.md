# Out of order Execution

## Overordnet:

 * [Introduktion til Out-of-order](ooo-concept.md)

## In-order del af maskinen

Denne del af en out-of-order maskine håndterer instruktioner i den rækkefølge de
angives i programmet. Følgende elementer indgår:

 * [Hentning, afkodning, omskrivning](ooo-fetch-decode.md)
 * [Registeromdøbning](ooo-renaming.md)
 * [Fuldførelse](ooo-completion.md)

Mellem registeromdøbning og fuldførelse håndteres instruktionerne derimod i en
rækkefølge bestemt ud fra deres indbyrdes afhængigheder, se nedenfor

## Out-of-order / Dataflow del af maskinen


Vi kigger først på dataflow via registre, dernæst på dataflow via lageret.

 * [Dataflow via registre](ooo-dataflow-registers.md)
 * [Dataflow via lageret](ooo-dataflow-memory.md)

Det er en god ide at betragte denne figur over en (mindre) dataflow-maskine
samtidigt:

![dataflow-del](svg/dataflow-big.svg)

Afslutningsvis en note om "fejlagtig schedulering"

 * [Fejl-schedulering](ooo-misscheduling.md)

## Eksempel på afvikling på out-of-order maskine

 * [Et fuldt eksempel](ooo-example.md)


