
# In-program-order del af out-of-order execution

Denne del af en out-of-order maskine håndterer instruktioner i den rækkefølge de
angives i programmet. Følgende elementer indgår:

 * [Hentning, afkodning, omskrivning](ooo-fetch-decode.md)
 * [Registeromdøbning](ooo-renaming.md)
 * [Fuldførelse](ooo-completion.md)

Mellem registeromdøbning og fuldførelse håndteres instruktionerne derimod i en
rækkefølge bestemt ud fra deres indbyrdes afhængigheder, som beskrevet her [dataflow](ooo-dataflow.md)


