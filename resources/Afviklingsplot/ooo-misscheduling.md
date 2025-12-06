
### Fejlagtig planlægning (mis-scheduling)

Schedulering sker under antagelse af en bestemt latenstid for de involverede
instruktioner. Det fungerer perfekt for instruktioner som altid har den samme
latenstid, men ikke for instruktioner med variabel latenstid. For eksempel load
instruktioner. En load der får et hit i L1 har en latenstid på 4 cykler. Men en load
der har et miss i L1 eller skal forwarde fra en store som ikke har data eller addresse
har en længere latenstid.

På det tidspunkt hvor behovet for forsinket wb opdages kan instruktioner som skal
have forwardet resultat fra en load allerede være udvalgt og være på vej ned
igennem andre pipelines. Disse instruktioner vil blive udført med forkerte input
og beregne forkerte resultater. Vi kan ikke stalle de afhængige instruktioner, fordi
vi gerne skal kunne køre andre uafhængige instruktioner gennem de samme pipelines.

En mulig måde at håndtere problemet på er at gøre følgende i den cycle, hvor der
ellers skulle have været udført wb:

 * Annuller alle instruktioner i pk,rd,ex,ag - uanset om de er afhængige eller ej
 * Retabler schedulerens tilstand fra tre clockcykler tidligere (du har taget backup, ikke?)
 * Men uden at den forsinkede værdi (fra f.eks. cache miss) er regnet som tilgængelig

I de efterfølgende cyckler vil scheduleren planlægge således at afhængige instruktioner
ikke udvælges. På et senere tidspunkt, når den forsinkede værdi bliver tilgængelig,
signaleres dette til scheduleren og de afhængige instruktioner kan igen blive udvalgt.

Fejlagtig planlægning er dyrt, og det kan søges minimeret ved forudsigere, der
på basis af programmets tidligere opførsel vil levere et bedre gæt på latenstiden
for load instruktioner.

Vi ignorerer fejlagtig planlægning helt i udarbejdelsen af afviklingsplot.

