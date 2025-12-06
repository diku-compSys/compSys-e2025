
### Overførsel til dataflow sektionen

Efter renaming overføres instruktioner til et særlig lager i dataflow sektionen, som
beskrives nedenfor. Skrivning til dette lager kan involvere kompliceret allokering
af plads og tager et pipeline-trin. Vi markerer det med "Qu" (Queue) i vores flow beskrivelse.

### Fuldførelse (bagende)

Når en instruktion er udført uden fejl og blevet den ældste "fuldføres" den ved at
"Commit RAT" omdøbningstabellen opdateres og det fysiske registernummer associeret med den
nye instruktions logiske destinationsregister returneres til frilisten. Det tager to pipeline trin,
som markeres med "Ca" og "Cb" i vores flow beskrivelse.

### Opsamling af instruktions-"flow" for forende og bagende

Vi kan nu give en beskrivelse af in-order delene af en out-of-order mikroarkitektur i form
af et (ufuldendt) "flow" for instruktionerne.

~~~
alle: Fa Fb Fc De Fu Al Rn Qu ...out-of-order... Ca Cb
      |        |  |  |  |  |                     |
      Hent     |  |  |  |  Sæt i "kø"            Fuldfør
           Afkod  |  |  Omdøb registre
      og omskriv  |  Alloker (registre, resourcer)
                  Omskriv/Fusioner
~~~

Fusionering af to instruktioner markeres ved at den første af dem holder op med at
eksistere efter "Fu" i afviklingsplottet.


