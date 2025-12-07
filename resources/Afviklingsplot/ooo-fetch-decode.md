
### Forudsigelse og instruktionshentning

I beskrivelsen af simplere pipelines foretager man først instruktionshentning. De
hentede instruktioner afkodes dernæst så hop/kald/retur identificeres. Derpå forudsiges
programforløbet. Som nævnt tidligere kan en branch target buffer levere forudsigelser
lidt tidligere.

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

I det følgende vil vi antage at vi kan forudsige en hop/kald/retur pr maskin-cyklus,
og udelade selve forudsigelsen fra vores "flow" beskrivelse, der derfor stadig
vil starte med de tre trin Fa, Fb og Fc.


### Fusionering

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


