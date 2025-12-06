
### Et samlet billede

Vi kan nu (omsider) give et samlet billede af hvordan en out-of-order maskine udfører
en programstump. Betragt følgende eksempel fra tidligere:

~~~
while (ptr < limit) { sum += *ptr++; }
~~~

To gennemløb:

~~~
                                0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8
0:  lw x11,0(x10)               Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
4:  add x10,x10,4               Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
8:  add x12,x12,x11             Fa Fb Fc De Fu Al Rn Qu -- -- -- -- pk rd ex wb Ca Cb
C:  bne x10,x13,0               Fa Fb Fc De Fu Al Rn Qu -- pk rd ex -- -- -- -- Ca Cb
0:  lw x11,0(x10)                  Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
4:  add x10,x10,4                  Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- Ca Cb
8:  add x12,x12,x11                Fa Fb Fc De Fu Al Rn Qu -- -- -- -- pk rd ex wb Ca Cb
C:  bne x10,x13,0                  Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- Ca Cb
~~~

På denne kodestump opnås en IPC på 4.

Bemærk forskellen fra den in-order superskalare præsenteret tidligere. For den maskine
var IPC for samme kodestump kun 1.
