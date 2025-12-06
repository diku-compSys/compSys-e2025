
### Load instruktioner

Håndtering af lagerreferencer er den mest komplicerede del af en moderne mikroarkitektur.
Formodentlig cirka ligeså omfattende som alle de øvrige elementer til sammen. Så "brace for impact!"

Først betragter vi load instruktioner der finder deres data i datacachen. De har
følgende "flow" beskrivelse:

~~~
load: Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb

outoforder: pk,rd,ex,ag,ma,mb,mc,wr
~~~

Ved cache-miss er data først tilgængeligt meget senere. Vi markerer forsinkelse
af load data, uanset årsag, ved at forsinke "wb". Et cache miss i L1 cache og hit 
i L2 cache kunne give følgende afviklingsplot:

~~~
load: Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- -- -- -- -- -- -- -- -- wb Ca Cb
~~~

### Store instruktioner

Skrivning til lageret må ikke foregå spekulativt. En store instruktion
kan ikke opdatere lageret før den har nået "commit" og vi ved med sikkerhed at den
virkeligt skal fuldføres. Ergo må skrivninger holdes tilbage i en kø, analogt til
køen af allokerede destinationsregistre. Denne kø kaldes en store-kø.

Omvendt: selvom store instruktioner ikke må opdatere lageret, så skal alle
efterfølgende load instruktioner fra samme instruktionsstrøm *se* opdateringerne.
Når disse opdateringer ikke er at finde i lageret (der jo ikke må opdateres), så må
de findes i store-køen.

Store-køen indeholder store instruktioner i programrækkefølge og for hver instruktion
følgende data:

 * Adresse.
 * Er adressen gyldig?
 * Data (altid som et word på adresse delelig med 4)
 * Er data gyldig - dette angives pr byte

Vi allokerer pladser i store-køen samtidig med registeromdøbning.

En store instruktion udføres som to særskilte operationer

 1. Beregning af adressen, som derpå skrives i det relevante felt i store-køen.
    Også tilgang til cache med henblik på at udløse page faults eller cache-miss
 2. Overførsel af store data til store-køen. 

De to operationer vil ofte blive skeduleret separat. Det kan vi illustrere sådan her:

~~~text
store: Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb   // addresse
       -                    Q* -- -- -- -- pk rd st C*      // data
~~~
De særlige trin "Q*" og "C*" bruges kun for data-delen af store instruktionerne.
I typiske implementationer vil "Q*" altid ske samtidigt med "Qu" for den operation
der beregner af adressen, ligesom "C*" vil ske samtidigt med "Ca"

For både load og store instruktioner startes cache opslag så snart deres adresse er
beregnet. Men store instruktioner skriver ikke deres data til cachen i første omgang.
Opslaget foretages for at trigge eventuelle TLB miss og cache miss. Opdatering af
cachen sker først senere når store instruktionen bliver den ældste i store-køen og når
til commmit-trinnet. Vi viser ikke denne sene skrivning til cachen i afviklingsplottet.

### Store til Load forwarding

Betragt denne instruktionssekvens

~~~
sb  x7,(x4)
sb  x8,1(x4)
sb  x9,3(x4)
lw  x10,(x4)
~~~

Load instruktionen til sidst skal gerne ende med at "loade" en værdi der er sammensat af de
tre bytes fra store instruktionerne ovenfor og en enkelt byte fra lageret.

Det kræver et omfattende maskineri: Når en load instruktion har
beregnet den adresse den skal tilgå, sammenlignes adressen med alle ældre store instruktioner
i store-køen (vi ignorerer her hvordan der holdes rede på instruktioners "alder").
Der kan være flere matchende store instruktioner.

Dernæst bestemmes, separat for hver byte der refereres, hvilken matchende store instruktion der
er nyest. Fra den store instruktion overføres den relevante byte til load instruktionen.
Bemærk at for hver byte kan der være en sådan nyeste store instruktion eller ej - i 
sidste tilfælde hentes den relevante byte i stedet fra datacachen.

Hele denne process udføres parallelt med opslaget i datacachen og er derfor almindeligvis
"skjult" - latenstiden matcher opslaget i cachen. Vi anfører ikke i vores afviklingsplot
om en load får sin værdi fra cache, tidligere store eller en kombination deraf.

Der kan opstå to "udfordringer"

 * En tidligere store med matchende adresse har endnu ikke skrevet data til store-køen
 * En tidligere store har endnu ikke beregnet adresse

I det første tilfælde må load instruktionen udskyde sin "wb" til efter den (de) matchende
store instruktion(er) har overført data til skrive-køen.

Den anden situation kan håndteres på flere måder:

 * konservativt: load instruktionen må vente. Det viser sig at give meget dårlig ydeevne.
 * aggressivt: ignorer problemet, udfør load på basis af tilgængelige data. tjek efter senere
 * typisk: brug en forudsiger (alias-predictor), tjek senere.

Under alle omstændigheder er det nødvendigt at placere load instruktionerne i en load-kø.
Når en store instruktion har beregnet sin adresse og modtaget den værdi der skal stores, 
foretager den en sammenligning med instruktionerne i load-køen. Matchende yngre 
load-instruktioner "vækkes" og derpå genkøres søgeprocessen for de vækkede load-instruktioner, 
så de får en chance for at få et korrekt resultat.

Når vi konstruerer vores afviklingsplot vil vi nøjes med at forsinke "wb" uanset,
hvad der er den bagvedliggende årsag.

