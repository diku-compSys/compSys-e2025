
### Registeromdøbning 

Vi skelner mellem *logiske* og *fysiske* registre. På maskinsprogsniveau er (mellem)resultater 
placeret i logiske registre. Det er de registernumre en compiler bruger, når den oversætter
til assembler. I en simpel mikroarkitektur svarer hvert logisk register til *et*
*fysisk* register. I en out-of-order maskine er det mere kompliceret. 

En out-of-order maskine skal kunne håndtere mange instruktioner
som potentielt skriver til samme logiske register og mange instruktioner som læser
fra samme logiske register men på forskellige tidspunkter. For at kunne holde styr
på de mange resultater/registre der er i brug samtidigt udføres "registeromdøbning"
(eng: register renaming). Registeromdøbning er en teknik der sikrer at forskellige 
instruktioner der skriver til samme logiske register i stedet vil skrive til hver
deres *fysiske register.* Registeromdøbning sikrer også at læsere af et givet logisk
register vil læse det korrekte fysiske register.

Nedenstående figur viser hvordan registeromdøbning indgår i mikroarkitekturen. 
Instruktionerne følger de tykke sorte pile. Registerreferencerne følger de tynde
pile.

![renaming](svg/renamer.svg)

Registeromdøbning udføres ved hjælp af en omdøbningstabel, aka. "Register Alias Table" eller "RAT". 
Denne tabel associerer hvert logisk registernummer med et fysisk registernummer. 
Instruktionens logiske kilde-registre slås op i tabellen og de tilsvarende fysiske registernumre følger
med instruktionen videre frem i maskinen. Ved omdøbning allokeres et fysisk destinationsregister
fra en friliste og omdøbningstabellen opdateres så den afspejler den nye binding fra
logisk til fysisk registernummer.

En typisk implementation bruger en cirkulær buffer til at holde såvel frilisten som
listen over allokerede destinationsregistre. En "tæller" indikerer allokeringspunkt
og allokering af fysiske registre sker ved at justere tælleren.

Instruktionerne slutter deres liv i "bagenden" af mikroarkitekturen. Her findes endnu
en omdøbningstabel, "Commit RAT", som holder afbildningen fra logisk til fysisk register
for den senest fuldførte instruktion. Endnu en tæller holder rede på hvor den ældste instruktion
befinder sig i bufferen. Den ældste instruktion *fuldføres* (eng: commits, retires)
ved at dens tidligere fysiske destinations registernummer læses fra "Commit RAT"
og indsættes i frilisten. Derpå opdateres "Commit RAT" til at udpege det nye fysiske
destinationsregister for instruktionen.

Omdøbning tager typisk et eller to trin, afhængigt af hvor mange instruktioner der
skal behandles samtidigt. Vi antager to trin som vi markerer med "Al" (allocate) og
"Rn" (rename) i vores "flow" beskrivelse.

### Registeromdøbning og exceptions

Hvis en instruktion fejler (f.eks. tilgår reserveret lager, dividerer med nul) skal
maskinen reagere ved at kalde en "exception handler." Moderne
maskiner understøtter *præcise* exceptions: Herved forstås at en exception ses som
associeret med *en* bestemt fejlende instruktion. Alle tidligere instruktioner skal 
fremstå som værende udført og alle efterfølgende som ikke udført. 

I en simpel pipeline modsvares instruktionernes rækkefølge i programudførelsen
af deres placering i pipelinen. Derfor kan præcise exceptions sikres ved at
have Wb trinnet *efter* det trin hvor fejl detekteres. I en out-of-order maskine
med hundredevis af instruktioner i forskellige stadier af udførelse skal der andre
boller på suppen.

Registeromdøbning er designet til at understøtte præcise "exceptions" som følger:
Hvis en instruktion fejler, så markeres den blot som fejlet men iøvrigt fortsætter
udførelsen. Instruktionshentning stopper dog omgående og afventer. Når den fejlende
instruktion er blevet den ældste instruktion og når til commit-trinnet så aborteres alle andre
instruktioner og  omdøbningstabellen i forenden af pipelinen (RAT) geninitialiseres fra omdøbningstabellen i commit (Commit RAT). 
Endeligt returneres de fysiske destinationsregistre
for de aborterede instruktioner til frilisten. Som nævnt tidligere implementeres
friliste og listen over allokerede fysiske registre med en cirkulær buffer og frigivelse
kan gøres ved at sætte tælleren for allokering så den svarer til tælleren for
frigivelse. 

Figuren nedenfor viser systemet med flere detaljer.

![renaming-2](svg/overview2.svg)

### Registeromdøbning og fejl-Forudsigelser

Håndtering af fejl-forudsigelser minder om håndtering af exceptions, men der er andre
krav til ydeevnen. Fejl-forudsigelser forekommer langt hyppigere og skal derfor håndteres
hurtigere. Det er ikke godt nok at vente til et fejl-forudsagt hop bliver den ældste
instruktion og når commit-trinnet.

Derfor udbygges maskinen med en "snapshot" mekanisme. Man gemmer simpelthen hele omdøbnings-tabellen
med korte mellemrum, så man hurtigt kan retablere tilstanden efter enhver fejlforudsigelse.

Her ses systemet udbygget med en kø af snapshots:

![renaming-3](svg/overview3.svg)

Når dataflow-delen af maskinen signalerer at en forudsigelse bliver afgjort, så reagerer
systemt omgående ved samtidigt at:

 * Opdatere hopforudsigere m.v.
 * Stoppe og derpå fjerne spekulativt udførte instruktioner efter det fejlforudsagte hop
 * Fjerne elementer i STORE-køen for instruktioner efter det fejlforudsagte hop
 * Omdirigere instruktionshentning og fylde pipelinen med de korrekte instruktioner
 * Retablere RAT'en i omdøbnings-trinnet svarende til tilstanded ved det fejlforudsagte hop.



