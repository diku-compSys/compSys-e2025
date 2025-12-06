
### Dataflow baseret udførelse

Når instruktionerne er paseret gennem forenden af mikroarkitekturen når de dataflow-sektionen,
hvor de indsættes i en "scheduler". Scheduleren består af to halvdele som udgør en
feedback sløjfe der hver cyclus udvælger instruktioner til udførelse. De to halvdele
er:

 * Wakeup. Hver cycle signaleres hvilke fysiske registre der forventes at få skrevet en værdi
to cykler senere. Det sammenlignes for hver instruktion i scheduleren med instruktionens fysiske kilderegistre.
Når en instruktion har "set" alle sine kilderegister markeres den som "vågen".
 * Pick. Flere instruktioner kan være vågne samtidig, og så skal der vælges i mellem
dem. Oftest anvendes en tilnærmelse til "ældste først". Når instruktionerne er udvalgt
kan deres fysiske destinationsregistre tilføjes til mængden af "skrevne" værdier i
den følgende maskincyklus - eller senere, alt afhængig af de valgte instruktioners
latenstid. En single-cycle ALU operation har en latenstid på 1, mens en load instruktion
(jvf tidligere diskussion) har en latenstid på 4. 

I nogle maskiner er der mange små schedulere, som hver udvælger en instruktion, i andre
er der færre schedulere som hver især kan udvælge flere instruktioner.

Bemærk at da schedulering foretages flere pipeline trin før udførelse, så er den af
natur spekulativ og baseret på antagelser om latenstider og vil fejle hvis en instruktion 
har en anden latenstid end antaget, for eksempel ved et cache-miss. Vi vil senere 
kort beskrive hvordan systemet håndterer en sådan "fejlschedulering".

Når en instruktion er udvalgt skal den læse operander fra de fysiske kilde-registre
før den endelig kan udføres og slutteligt skrive sit resultat til et fysisk destinationsregister.
Der er mange fysiske registre, så læsning og skrivning af registre kræver en fuld maskin cyklus hver.

De nye pipeline trin i dataflow-sektionen er:

 * pk: "pick". Udvælgelse af en instruktion til udførelse. Kaldes nogle gange "instruction issue"
 * rd: "read". Læsning af operander fra registre (eller overførsel via forwarding)
 * ex: "execute". Selve operationen udføres i en ALU
 * wr: "write". Resultatet skrives til et register

For hop og aritmetiske instruktioner (excl mul) ender vi med følgende "flow" beskrivelse:

~~~
ALU-op: Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
branch: Fa Fb Fc De Fu Al Rn Qu pk rd ex Ca Cb

inorder: Fa,Fb,Fc,De,Fu,Al,Rn,Qu,Ca,Cb
outoforder: pk,rd,ex,wb
~~~

Vi udtrykker størrelsen af dataflow-sektionen i form af en resource begrænsning for
antallet af instruktioner mellem Qu og Ca. For eksempel kunne en fire-vejs out-of-order
maskine med 64 instruktioner i dataflow-sektionen være beskrevet således:

~~~
Resources: Fa:4, Fb:4, Fc:4, De:4, Fu:4, Al:4, Rn:4 Qu:4 [Qu-Ca]:64, Ca:4 Cb:4
~~~

Instruktioner som venter i dataflow-sektionen på at blive udvalgt til udførelse eller
på at blive fuldført (commit) kan vi markere med "--". Det giver afviklingsplot a la

~~~
Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- Ca Cb
Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- Ca Cb
Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ex wb Ca Cb
~~~

Vi har nu beskrevet tilstrækkeligt meget af mikroarkitekturen til at vi kan bestemme
hvad et fejlforudsagt hop koster (i vores maskine). "Fa" for instruktionen efter hoppet 
kan tidligst ligge i cyklen efter "ex" for det fejlforudsagte hop. Det giver en 
"branch mispredict penalty" på 10 maskincykler.

Typiske tal for moderne mikroarkitekturer er 10-15 maskincykler.


