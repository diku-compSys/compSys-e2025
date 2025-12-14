# Øvelser til 15. december

## Optakt til dagens forelæsning

Læn dig tilbage og nyd at du har afleveret A4.

Langsomt drik en kaffe eller te mens du mediterer over noget smukt assembler kode.


# Opgaver til tidligere forelæsninger

Nedenstående opgaver tager udgangspunkt i dataflow maskinen præsenteret mandag 8/12 og onsdag 10/12.

Opgave 1 og 2 fra onsdag sidste uge, hvis de ikke allerede er løst. Derpå:


## Opgave 1

Spg 1:

Oversæt dette C-fragment til RISC-V assembler

~~~
while (a < limit) { *a++ = *b++; }
~~~ 

hvor de tre variable a,b og limit alle er af typen pointer to int.


Spg 2:

Konstruer et afviklingsplot der viser afvikling af
to iterationer af løkken i dit program på en simpel 
5-trins pipeline med fuld forwarding.

Spg 3:

Konstruer et afviklingsplot der viser afvikling af to iterationer af
løkken i dit program på en 9-trins in-order pipeline med
realistisk cache tilgang (dvs "Fa Fb Fc De Ex Ma Mb Mc Wb").
Pipelinen har fuld forwarding.

Gør eventuelt antagelser om branch prediction

Spg 4:

Konstruer er afviklingsplot der viser afvikling af to iterationer
af løkken i dit program på en out-of-order maskine som
beskrevet i slides for mandag  8/12 og onsdag 10/12 samt noten om
afviklingsplot.

Husk at angive antagelser du må gøre for at præcisere opgaven.



