
## Dynamisk Skedulering (Out-of-order execution)

Alle moderne højtydende processor-kerner har samme grundlæggende design som præsenteres
nedenfor. Præsentationen her har til formål at gøre performance overvejelser
meningsfuld, så vi vil se bort fra mange detaljer.

Out-of-order execution bygger på tre overordnede design principper

* Forudsigelse af programforløb. Maskinen opsamler statistik om programmets
  opførsel og forudsiger på basis heraf programforløbet.
* Spekulativ udførelse. Instruktioner udføres før det er afgjort om de skal.
* Udførelse i dataflow-rækkefølge. Instruktioner udføres tidligst muligt efter
  at deres operander er til rådighed og uden hensyn til deres rækkefølge i
  programforløbet.

Alle tre design principper er nødvendige for at få høj ydeevne.

### Overordnet struktur (mikroarkitektur)

Mikroarkitekturen i en højtydende processor er delt i tre overordnede sektioner:

* En "forende" som skaffer instruktioner og klargør dem til udførelse. Det gøres i programrækkefølge.
* En "bagende" som tjekker resultater for fejl (exceptions) og griber ind hvis noget er gået galt. Det gøres ligeledes i programrækkefølge
* En "dataflow-del" som udfører instruktionerne i en rækkefølge bestemt af deres dataafhængigheder.

Instruktionerne begynder deres vej i den forreste del af mikroarkitekturen, der 
indeholder allerede kendte elementer som forudsigelse, hentning og afkodning. 
Efter afkodning udføres *fusionering* og *registeromdøbning* som beskrives nærmere nedenfor.
Når instruktionerne har gennemført registeromdøbning kan de udføres i dataflow rækkefølge,
dvs i en rækkefølge bestemt af deres indbyrdes afhængigheder men uden at respektere
deres oprindelige rækkkefølge i programmet. Moderne processor-kerner har plads til
flere hundrede instruktioner i deres dataflow sektion. Slutteligt tjekkes instruktionerne
for fejlsituationer i den oprindelige programrækkefølge. Hvis en fejl er opstået
og der skal udføres en *exception* ("undtagelse?"), kan maskinen annullere alle instruktioner 
der kommer logisk *efter* den fejlende instruktion. Det giver illusionen af at alt er udført
i programrækkefølge.

Figuren nedenfor illustrerer en moderne out-of-order mikroarkitektur

![image ooo-mikroarkitektur](la-machine.svg)


