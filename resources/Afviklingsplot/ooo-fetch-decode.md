
## Forudsigelse og instruktionshentning

I beskrivelsen af simplere pipelines foretager man først instruktionshentning. De
hentede instruktioner afkodes dernæst så hop/kald/retur identificeres. Derpå forudsiges
programforløbet. Som nævnt tidligere kan en branch target buffer levere forudsigelser
lidt tidligere.

Her ses en programstump og nogle tilsvarende elementer i BTB'en:

~~~
Branch Target Buffer                    Instruction Cache

entry   = 10074                          10074: addi    sp,sp,-16
next[0] = 100b0                          10078: sw      ra,12(sp)
next[1] = 10074                          1007c: sw      s0,8(sp)
after   = 1009c                          10080: sw      s1,4(sp)
predict, call                            10084: mv      s0,a0
                                         10088: li      a5,1
                                         1008c: bgeu    a5,a0,100b0 <fib+0x3c>
                                         10090: addi    a0,a0,-1
                                         10094: auipc   ra,0x0
                                         10098: jalr    -32(ra) # 10074 <fib>

entry   = 1009c                          1009c: mv      s1,a0
next[0] = xxx                            100a0: addi    a0,s0,-2
next[1] = 10074                          100a4: auipc   ra,0x0
after   = 100ac                          100a8: jalr    -48(ra) # 10074 <fib>
no predict, call
                                         100ac: add     a0,s1,a0
entry   = 100ac
next[0] = xxx        entry = 100b0       100b0: lw      ra,12(sp)
next[1] = xxx        next[0] = xxx       100b4: lw      s0,8(sp)
after = xxx          next[1] = xxx       100b8: lw      s1,4(sp)
no predict, ret      after = xxx         100bc: addi    sp,sp,16
                     no predict, ret     100c0: ret
~~~
(Selvom der her vises hele adresser i BTB elementerne, så vil der i virkeligheden blot skulle
indkodes bits nok til at identificere en position i den primære cache)

I en moderne mikroarkitektur kan man ligeså godt vende beskrivelsen på hovedet:
Forudsigelser gøres *uden* afkodning af instruktioner. Maskinen "lærer" control-flow-grafen
for programmet. Indlæring foretages når forudsigelser enten bekræftes eller afvises.
Forudsigelser baseres på det indlærte og driver instruktionshentning. Med andre ord
kommer forudsigelse før instruktionshentning.

I praksis har det ikke nogen betydning for vores afviklingsplot fordi hverken forudsigelse
eller indlæring forlænger pipelinen. "Indlæring"
sker samtidigt med andre aktiviteter og "ses" derfor ikke. Selvom forudsigelsen logisk
set sker tidligt, før instruktionshentning, så kan den heller ikke "ses" fordi en
fejlforudsigelse omdirigerer instruktionshentning uden forsinkelse - dvs omdirigeringen
skal ikke først pasere i gennem et eller flere trin der laver forudsigelser.

Her ses en mulig organisering af den primære cache:

![cache](svg/cache.svg)

BTB'en skal tilgås i første trin og være færdigt tids nok til at kunne omdirigere
instruktionshentning i løbet af dette trin. Det er ofte nødvendigt at lave to niveauer
af BTB: en mindre der kan tilgås på denne en cyklus og en større der tager længere
tid.

I det følgende vil vi antage at vi kan forudsige en hop/kald/retur pr maskin-cyklus,
og udelade selve forudsigelsen fra vores "flow" beskrivelse, der derfor stadig
vil starte med de tre trin Fa, Fb og Fc.


## Fusionering

I de fleste maskinsprog er der bestemte instruktionssekvenser som med fordel kan omskrives
til en enkelt instruktion på hardware niveau. For eksempel har IA64 ikke nogen compare-and-branch
instruktion som RISC-V, men må bruge to separate instruktioner for henholdsvis sammenligning
og betinget hop. Disse to instruktioner fusioneres på IA64 almindeligvis til en compare-and-branch.

Det er (ofte) en forudsætning for at fusionere to instruktioner:

 * At de har det samme destinationsregister
 * At den sidste afhænger af den første
 * At de tilsammen max har to kilderegistre og en immediate
 * At de tilsammen kan udføres i et hug længere nede i pipelinen

RISC-V har (mindst) to sekvenser som med fordel kan fusioneres:

 * lui efterfulgt af addi. (Tilsammen udgør de pseudo-instruktionen "li")
 * add efterfulgt af load/store. Det er billigt at bygge AGUen (address generate unit) 
så den kan addere *tre* tal, to registre og et konstant offset
for at forme en adresse, men RISC-V har ikke nogen instruktion der matcher.

Fusionering kræver typisk et eller to trin oven i afkodning. Vi antager et trin og
markerer det med Fu i vores "flow" beskrivelse.


